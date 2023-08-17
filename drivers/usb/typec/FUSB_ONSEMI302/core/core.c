/*******************************************************************************
 * @file     core.c
 * @author   USB PD Firmware Team
 *
 * Copyright 2018 ON Semiconductor. All rights reserved.
 *
 * This software and/or documentation is licensed by ON Semiconductor under
 * limited terms and conditions. The terms and conditions pertaining to the
 * software and/or documentation are available at
 * http://www.onsemi.com/site/pdf/ONSEMI_T&C.pdf
 * ("ON Semiconductor Standard Terms and Conditions of Sale, Section 8 Software").
 *
 * DO NOT USE THIS SOFTWARE AND/OR DOCUMENTATION UNLESS YOU HAVE CAREFULLY
 * READ AND YOU AGREE TO THE LIMITED TERMS AND CONDITIONS. BY USING THIS
 * SOFTWARE AND/OR DOCUMENTATION, YOU AGREE TO THE LIMITED TERMS AND CONDITIONS.
 ******************************************************************************/
#include "core.h"
#include "TypeC.h"
#include "PDProtocol.h"
#include "PDPolicy.h"
#include "TypeC_Types.h"
#include "PD_Types.h"
#include "version.h"
#include "vendor_info.h"

#ifdef CONFIG_PRODUCT_MOBA
#define SUPPORT_ONSEMI_PDCONTROL
#endif

/*
 * Call this function to initialize the core.
 */
void core_initialize(Port_t *port, FSC_U8 i2cAddr)
{
    PortInit(port, i2cAddr);
    core_enable_typec(port, TRUE);
    core_set_state_unattached(port);
}

/*
 * Call this function to enable or disable the core Type-C state machine.
 */
void core_enable_typec(Port_t *port, FSC_BOOL enable)
{
    port->SMEnabled = enable;
}

/*
 * Call this function to enable or disable the core PD state machines.
 */
void core_enable_pd(Port_t *port, FSC_BOOL enable)
{
    port->USBPDEnabled = enable;
}

/*
 * Call this function to run the state machines.
 */
void core_state_machine(Port_t *port)
{
    FSC_U8 data = port->Registers.Control.byte[3] | 0x40;  /* Hard Reset bit */
#ifdef SUPPORT_ONSEMI_PDCONTROL
	mutex_lock(&port->thread_lock);
#endif
    /* Check on HardReset timeout (shortcut for SenderResponse timeout) */
    if ((port->WaitingOnHR == TRUE) &&
        TimerExpired(&port->PolicyStateTimer))
    {
        DeviceWrite(port->I2cAddr, regControl3, 1, &data);
    }

    /* Update the current port being used and process the port */
    /* The Protocol and Policy functions are called from within this call */
    StateMachineTypeC(port);
#ifdef SUPPORT_ONSEMI_PDCONTROL
	mutex_unlock(&port->thread_lock);
#endif
}

/*
 * Check for the next required timeout to support timer interrupt functionality
 */
FSC_U32 core_get_next_timeout(Port_t *port)
{
  FSC_U32 time = 0;
  FSC_U32 nexttime = 0xFFFFFFFF;
  FSC_U8 i;

  for (i = 0; i < FSC_NUM_TIMERS; ++i)
  {
    time = TimerRemaining(port->Timers[i]);
    if (time > 0 && time < nexttime) nexttime = time;
  }

  if (nexttime == 0xFFFFFFFF) nexttime = 0;

  return nexttime;
}

FSC_U8 core_get_rev_lower(void)
{
    return FSC_TYPEC_CORE_FW_REV_LOWER;
}

FSC_U8 core_get_rev_middle(void)
{
    return FSC_TYPEC_CORE_FW_REV_MIDDLE;
}

FSC_U8 core_get_rev_upper(void)
{
    return FSC_TYPEC_CORE_FW_REV_UPPER;
}

FSC_U8 core_get_cc_orientation(Port_t *port)
{
    return port->CCPin;
}

void core_send_hard_reset(Port_t *port)
{
    SendUSBPDHardReset(port);
}

void core_set_state_unattached(Port_t *port)
{
    SetStateUnattached(port);
}

void core_reset_pd(Port_t *port)
{
    port->USBPDEnabled = TRUE;
    USBPDEnable(port, TRUE, port->sourceOrSink);
}

FSC_U16 core_get_advertised_current(Port_t *port)
{
    FSC_U16 power_current = 0;

    if (port->sourceOrSink == SINK)
    {
        if (port->PolicyHasContract)
        {
            /* If there is a PD contract - return contract current. */
            /* TODO - add PPS handling, etc. */
            power_current = port->USBPDContract.FVRDO.OpCurrent * 10;
        }
        else
        {
            /* Otherwise, return the TypeC advertised value... or... */
            /* Note for Default: This can be
             * 500mA for USB 2.0
             * 900mA for USB 3.1
             * Up to 1.5A for USB BC 1.2
             */
            switch (port->SinkCurrent)
            {
            case utccDefault:
                power_current = 500;
                break;
            case utcc1p5A:
                power_current = 1500;
                break;
            case utcc3p0A:
                power_current = 3000;
                break;
            case utccNone:
            default:
                power_current = 0;
                break;
            }
        }
    }
    return power_current;
}

void core_set_advertised_current(Port_t *port, FSC_U8 value)
{
    UpdateCurrentAdvert(port, value);
}

void core_set_drp(Port_t *port)
{
    port->PortConfig.PortType = USBTypeC_DRP;
    port->PortConfig.SnkPreferred = FALSE;
    port->PortConfig.SrcPreferred = FALSE;
    SetStateUnattached(port);
}

void core_set_try_snk(Port_t *port)
{
    port->PortConfig.PortType = USBTypeC_DRP;
    port->PortConfig.SnkPreferred = TRUE;
    port->PortConfig.SrcPreferred = FALSE;
    SetStateUnattached(port);
}

void core_set_try_src(Port_t *port)
{
    port->PortConfig.PortType = USBTypeC_DRP;
    port->PortConfig.SnkPreferred = FALSE;
    port->PortConfig.SrcPreferred = TRUE;
    SetStateUnattached(port);
}

void core_set_source(Port_t *port)
{
    port->PortConfig.PortType = USBTypeC_Source;
    SetStateUnattached(port);
}

void core_set_sink(Port_t *port)
{
    port->PortConfig.PortType = USBTypeC_Sink;
    SetStateUnattached(port);
}

/*
 * Transmit a PPSRequest for voltage, current, obj_pos.
 * Called by system after initial explicit contract. Can be called after pd is enabled
 * to queue a message to be transmitted in the SinkReady state.
 * Returns 0 if successful
 * Returns 1 if a message is already queued to send - message will not be sent
 * Returns 2 if PD is disabled
 */
FSC_U8 DPM_SendPPSRequest(struct Port *port, FSC_U16 voltage, FSC_U8 power_current, FSC_U8 obj_pos)
{
	if(port->USBPDTxFlag == TRUE) return 1;
	if(port->USBPDActive == FALSE) return 2;

    port->PDTransmitHeader.MessageType = DMTRequest;
    port->PDTransmitHeader.NumDataObjects = 1;
    port->PDTransmitHeader.Extended = 0;

    port->PDTransmitObjects[0].object = 0;
    port->PDTransmitObjects[0].PPSRDO.CapabilityMismatch = 0;
    port->PDTransmitObjects[0].PPSRDO.NoUSBSuspend = No_USB_Suspend_May_Be_Set;
    port->PDTransmitObjects[0].PPSRDO.USBCommCapable = USB_Comms_Capable;
    port->PDTransmitObjects[0].PPSRDO.UnChnkExtMsgSupport = 0;

    port->PDTransmitObjects[0].PPSRDO.ObjectPosition = obj_pos;
    port->PDTransmitObjects[0].PPSRDO.OpCurrent = power_current;
    port->PDTransmitObjects[0].PPSRDO.Voltage = voltage;

    port->USBPDTxFlag = TRUE;
    /* Wake up the port if idle */
    port->PEIdle = FALSE;

    return 0;
}

FSC_U8 DPM_SendControlMessage(struct Port *port, FSC_U8 message_type)
{
	if(port->USBPDTxFlag == TRUE) return 1;
	if(port->USBPDActive == FALSE) return 2;

    port->PDTransmitHeader.MessageType = message_type;
    port->PDTransmitHeader.NumDataObjects = 0;
    port->PDTransmitHeader.Extended = 0;

    port->USBPDTxFlag = TRUE;
    /* Wake up the port if idle */
    port->PEIdle = FALSE;

    return 0;
}

