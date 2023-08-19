.. -*- coding: utf-8; mode: rst -*-

.. _lirc_get_rec_mode:
.. _lirc_set_rec_mode:

**********************************************
ioctls LIRC_GET_REC_MODE and LIRC_SET_REC_MODE
**********************************************

Name
====

<<<<<<< HEAD
LIRC_GET_REC_MODE/LIRC_SET_REC_MODE - Get/set current receive mode.
=======
LIRC_GET_REC_MODE/LIRC_SET_REC_MODE - Get/set supported receive modes.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

Synopsis
========

<<<<<<< HEAD
.. c:function:: int ioctl( int fd, LIRC_GET_REC_MODE, __u32 *mode)
	:name: LIRC_GET_REC_MODE

.. c:function:: int ioctl( int fd, LIRC_SET_REC_MODE, __u32 *mode)
=======
.. c:function:: int ioctl( int fd, LIRC_GET_REC_MODE, __u32 rx_modes)
	:name: LIRC_GET_REC_MODE

.. c:function:: int ioctl( int fd, LIRC_SET_REC_MODE, __u32 rx_modes)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	:name: LIRC_SET_REC_MODE

Arguments
=========

``fd``
    File descriptor returned by open().

<<<<<<< HEAD
``mode``
    Mode used for receive.
=======
``rx_modes``
    Bitmask with the supported transmit modes.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

Description
===========

<<<<<<< HEAD
Get and set the current receive mode. Only
:ref:`LIRC_MODE_MODE2 <lirc-mode-mode2>` and
:ref:`LIRC_MODE_SCANCODE <lirc-mode-scancode>` are supported.
Use :ref:`lirc_get_features` to find out which modes the driver supports.
=======
Get/set supported receive modes. Only :ref:`LIRC_MODE_MODE2 <lirc-mode-mode2>`
and :ref:`LIRC_MODE_LIRCCODE <lirc-mode-lirccode>` are supported for IR
receive. Use :ref:`lirc_get_features` to find out which modes the driver
supports.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

Return Value
============

<<<<<<< HEAD
.. tabularcolumns:: |p{2.5cm}|p{15.0cm}|

.. flat-table::
    :header-rows:  0
    :stub-columns: 0


    -  .. row 1

       -  ``ENODEV``

       -  Device not available.

    -  .. row 2

       -  ``ENOTTY``

       -  Device does not support receiving.

    -  .. row 3

       -  ``EINVAL``

       -  Invalid mode or invalid mode for this device.
=======
On success 0 is returned, on error -1 and the ``errno`` variable is set
appropriately. The generic error codes are described at the
:ref:`Generic Error Codes <gen-errors>` chapter.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
