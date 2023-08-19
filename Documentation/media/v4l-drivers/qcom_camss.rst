.. include:: <isonum.txt>

Qualcomm Camera Subsystem driver
================================

Introduction
------------

This file documents the Qualcomm Camera Subsystem driver located under
<<<<<<< HEAD
drivers/media/platform/qcom/camss.

The current version of the driver supports the Camera Subsystem found on
Qualcomm MSM8916/APQ8016 and MSM8996/APQ8096 processors.
=======
drivers/media/platform/qcom/camss-8x16.

The current version of the driver supports the Camera Subsystem found on
Qualcomm MSM8916 and APQ8016 processors.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

The driver implements V4L2, Media controller and V4L2 subdev interfaces.
Camera sensor using V4L2 subdev interface in the kernel is supported.

The driver is implemented using as a reference the Qualcomm Camera Subsystem
<<<<<<< HEAD
driver for Android as found in Code Aurora [#f1]_ [#f2]_.
=======
driver for Android as found in Code Aurora [#f1]_.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')


Qualcomm Camera Subsystem hardware
----------------------------------

<<<<<<< HEAD
The Camera Subsystem hardware found on 8x16 / 8x96 processors and supported by
the driver consists of:

- 2 / 3 CSIPHY modules. They handle the Physical layer of the CSI2 receivers.
  A separate camera sensor can be connected to each of the CSIPHY module;
- 2 / 4 CSID (CSI Decoder) modules. They handle the Protocol and Application
  layer of the CSI2 receivers. A CSID can decode data stream from any of the
  CSIPHY. Each CSID also contains a TG (Test Generator) block which can generate
  artificial input data for test purposes;
- ISPIF (ISP Interface) module. Handles the routing of the data streams from
  the CSIDs to the inputs of the VFE;
- 1 / 2 VFE (Video Front End) module(s). Contain a pipeline of image processing
  hardware blocks. The VFE has different input interfaces. The PIX (Pixel) input
=======
The Camera Subsystem hardware found on 8x16 processors and supported by the
driver consists of:

- 2 CSIPHY modules. They handle the Physical layer of the CSI2 receivers.
  A separate camera sensor can be connected to each of the CSIPHY module;
- 2 CSID (CSI Decoder) modules. They handle the Protocol and Application layer
  of the CSI2 receivers. A CSID can decode data stream from any of the CSIPHY.
  Each CSID also contains a TG (Test Generator) block which can generate
  artificial input data for test purposes;
- ISPIF (ISP Interface) module. Handles the routing of the data streams from
  the CSIDs to the inputs of the VFE;
- VFE (Video Front End) module. Contains a pipeline of image processing hardware
  blocks. The VFE has different input interfaces. The PIX (Pixel) input
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
  interface feeds the input data to the image processing pipeline. The image
  processing pipeline contains also a scale and crop module at the end. Three
  RDI (Raw Dump Interface) input interfaces bypass the image processing
  pipeline. The VFE also contains the AXI bus interface which writes the output
  data to memory.


Supported functionality
-----------------------

The current version of the driver supports:

- Input from camera sensor via CSIPHY;
- Generation of test input data by the TG in CSID;
<<<<<<< HEAD
- RDI interface of VFE

  - Raw dump of the input data to memory.

    Supported formats:

    - YUYV/UYVY/YVYU/VYUY (packed YUV 4:2:2 - V4L2_PIX_FMT_YUYV /
      V4L2_PIX_FMT_UYVY / V4L2_PIX_FMT_YVYU / V4L2_PIX_FMT_VYUY);
    - MIPI RAW8 (8bit Bayer RAW - V4L2_PIX_FMT_SRGGB8 /
      V4L2_PIX_FMT_SGRBG8 / V4L2_PIX_FMT_SGBRG8 / V4L2_PIX_FMT_SBGGR8);
    - MIPI RAW10 (10bit packed Bayer RAW - V4L2_PIX_FMT_SBGGR10P /
      V4L2_PIX_FMT_SGBRG10P / V4L2_PIX_FMT_SGRBG10P / V4L2_PIX_FMT_SRGGB10P /
      V4L2_PIX_FMT_Y10P);
    - MIPI RAW12 (12bit packed Bayer RAW - V4L2_PIX_FMT_SRGGB12P /
      V4L2_PIX_FMT_SGBRG12P / V4L2_PIX_FMT_SGRBG12P / V4L2_PIX_FMT_SRGGB12P).
    - (8x96 only) MIPI RAW14 (14bit packed Bayer RAW - V4L2_PIX_FMT_SRGGB14P /
      V4L2_PIX_FMT_SGBRG14P / V4L2_PIX_FMT_SGRBG14P / V4L2_PIX_FMT_SRGGB14P).

  - (8x96 only) Format conversion of the input data.

    Supported input formats:

    - MIPI RAW10 (10bit packed Bayer RAW - V4L2_PIX_FMT_SBGGR10P / V4L2_PIX_FMT_Y10P).

    Supported output formats:

    - Plain16 RAW10 (10bit unpacked Bayer RAW - V4L2_PIX_FMT_SBGGR10 / V4L2_PIX_FMT_Y10).
=======
- RDI interface of VFE - raw dump of the input data to memory.

  Supported formats:

  - YUYV/UYVY/YVYU/VYUY (packed YUV 4:2:2 - V4L2_PIX_FMT_YUYV /
    V4L2_PIX_FMT_UYVY / V4L2_PIX_FMT_YVYU / V4L2_PIX_FMT_VYUY);
  - MIPI RAW8 (8bit Bayer RAW - V4L2_PIX_FMT_SRGGB8 /
    V4L2_PIX_FMT_SGRBG8 / V4L2_PIX_FMT_SGBRG8 / V4L2_PIX_FMT_SBGGR8);
  - MIPI RAW10 (10bit packed Bayer RAW - V4L2_PIX_FMT_SBGGR10P /
    V4L2_PIX_FMT_SGBRG10P / V4L2_PIX_FMT_SGRBG10P / V4L2_PIX_FMT_SRGGB10P);
  - MIPI RAW12 (12bit packed Bayer RAW - V4L2_PIX_FMT_SRGGB12P /
    V4L2_PIX_FMT_SGBRG12P / V4L2_PIX_FMT_SGRBG12P / V4L2_PIX_FMT_SRGGB12P).
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

- PIX interface of VFE

  - Format conversion of the input data.

    Supported input formats:

    - YUYV/UYVY/YVYU/VYUY (packed YUV 4:2:2 - V4L2_PIX_FMT_YUYV /
      V4L2_PIX_FMT_UYVY / V4L2_PIX_FMT_YVYU / V4L2_PIX_FMT_VYUY).

    Supported output formats:

    - NV12/NV21 (two plane YUV 4:2:0 - V4L2_PIX_FMT_NV12 / V4L2_PIX_FMT_NV21);
    - NV16/NV61 (two plane YUV 4:2:2 - V4L2_PIX_FMT_NV16 / V4L2_PIX_FMT_NV61).
<<<<<<< HEAD
    - (8x96 only) YUYV/UYVY/YVYU/VYUY (packed YUV 4:2:2 - V4L2_PIX_FMT_YUYV /
      V4L2_PIX_FMT_UYVY / V4L2_PIX_FMT_YVYU / V4L2_PIX_FMT_VYUY).
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

  - Scaling support. Configuration of the VFE Encoder Scale module
    for downscalling with ratio up to 16x.

  - Cropping support. Configuration of the VFE Encoder Crop module.

<<<<<<< HEAD
- Concurrent and independent usage of two (8x96: three) data inputs -
  could be camera sensors and/or TG.
=======
- Concurrent and independent usage of two data inputs - could be camera sensors
  and/or TG.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')


Driver Architecture and Design
------------------------------

The driver implements the V4L2 subdev interface. With the goal to model the
hardware links between the modules and to expose a clean, logical and usable
<<<<<<< HEAD
interface, the driver is split into V4L2 sub-devices as follows (8x16 / 8x96):

- 2 / 3 CSIPHY sub-devices - each CSIPHY is represented by a single sub-device;
- 2 / 4 CSID sub-devices - each CSID is represented by a single sub-device;
- 2 / 4 ISPIF sub-devices - ISPIF is represented by a number of sub-devices
  equal to the number of CSID sub-devices;
- 4 / 8 VFE sub-devices - VFE is represented by a number of sub-devices equal to
  the number of the input interfaces (3 RDI and 1 PIX for each VFE).
=======
interface, the driver is split into V4L2 sub-devices as follows:

- 2 CSIPHY sub-devices - each CSIPHY is represented by a single sub-device;
- 2 CSID sub-devices - each CSID is represented by a single sub-device;
- 2 ISPIF sub-devices - ISPIF is represented by a number of sub-devices equal
  to the number of CSID sub-devices;
- 4 VFE sub-devices - VFE is represented by a number of sub-devices equal to
  the number of the input interfaces (3 RDI and 1 PIX).
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

The considerations to split the driver in this particular way are as follows:

- representing CSIPHY and CSID modules by a separate sub-device for each module
  allows to model the hardware links between these modules;
- representing VFE by a separate sub-devices for each input interface allows
  to use the input interfaces concurently and independently as this is
  supported by the hardware;
- representing ISPIF by a number of sub-devices equal to the number of CSID
  sub-devices allows to create linear media controller pipelines when using two
  cameras simultaneously. This avoids branches in the pipelines which otherwise
  will require a) userspace and b) media framework (e.g. power on/off
  operations) to  make assumptions about the data flow from a sink pad to a
  source pad on a single media entity.

Each VFE sub-device is linked to a separate video device node.

<<<<<<< HEAD
The media controller pipeline graph is as follows (with connected two / three
OV5645 camera sensors):
=======
The media controller pipeline graph is as follows (with connected two OV5645
camera sensors):
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

.. _qcom_camss_graph:

.. kernel-figure:: qcom_camss_graph.dot
    :alt:   qcom_camss_graph.dot
    :align: center

<<<<<<< HEAD
    Media pipeline graph 8x16

.. kernel-figure:: qcom_camss_8x96_graph.dot
    :alt:   qcom_camss_8x96_graph.dot
    :align: center

    Media pipeline graph 8x96
=======
    Media pipeline graph
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')


Implementation
--------------

Runtime configuration of the hardware (updating settings while streaming) is
not required to implement the currently supported functionality. The complete
configuration on each hardware module is applied on STREAMON ioctl based on
the current active media links, formats and controls set.

The output size of the scaler module in the VFE is configured with the actual
compose selection rectangle on the sink pad of the 'msm_vfe0_pix' entity.

The crop output area of the crop module in the VFE is configured with the actual
crop selection rectangle on the source pad of the 'msm_vfe0_pix' entity.


Documentation
-------------

APQ8016 Specification:
https://developer.qualcomm.com/download/sd410/snapdragon-410-processor-device-specification.pdf
Referenced 2016-11-24.

<<<<<<< HEAD
APQ8096 Specification:
https://developer.qualcomm.com/download/sd820e/qualcomm-snapdragon-820e-processor-apq8096sge-device-specification.pdf
Referenced 2018-06-22.
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

References
----------

.. [#f1] https://source.codeaurora.org/quic/la/kernel/msm-3.10/
<<<<<<< HEAD
.. [#f2] https://source.codeaurora.org/quic/la/kernel/msm-3.18/
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
