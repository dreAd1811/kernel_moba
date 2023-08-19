.. -*- coding: utf-8; mode: rst -*-

.. _lirc_get_send_mode:
.. _lirc_set_send_mode:

************************************************
ioctls LIRC_GET_SEND_MODE and LIRC_SET_SEND_MODE
************************************************

Name
====

<<<<<<< HEAD
LIRC_GET_SEND_MODE/LIRC_SET_SEND_MODE - Get/set current transmit mode.
=======
LIRC_GET_SEND_MODE/LIRC_SET_SEND_MODE - Get/set supported transmit mode.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

Synopsis
========

<<<<<<< HEAD
.. c:function:: int ioctl( int fd, LIRC_GET_SEND_MODE, __u32 *mode )
    :name: LIRC_GET_SEND_MODE

.. c:function:: int ioctl( int fd, LIRC_SET_SEND_MODE, __u32 *mode )
=======
.. c:function:: int ioctl( int fd, LIRC_GET_SEND_MODE, __u32 *tx_modes )
    :name: LIRC_GET_SEND_MODE

.. c:function:: int ioctl( int fd, LIRC_SET_SEND_MODE, __u32 *tx_modes )
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
    :name: LIRC_SET_SEND_MODE

Arguments
=========

``fd``
    File descriptor returned by open().

<<<<<<< HEAD
``mode``
    The mode used for transmitting.
=======
``tx_modes``
    Bitmask with the supported transmit modes.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')


Description
===========

Get/set current transmit mode.

Only :ref:`LIRC_MODE_PULSE <lirc-mode-pulse>` and
<<<<<<< HEAD
:ref:`LIRC_MODE_SCANCODE <lirc-mode-scancode>` are supported by for IR send,
=======
:ref:`LIRC_MODE_LIRCCODE <lirc-mode-lirccode>` is supported by for IR send,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
depending on the driver. Use :ref:`lirc_get_features` to find out which
modes the driver supports.

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

       -  Device does not support transmitting.

    -  .. row 3

       -  ``EINVAL``

       -  Invalid mode or invalid mode for this device.
=======
On success 0 is returned, on error -1 and the ``errno`` variable is set
appropriately. The generic error codes are described at the
:ref:`Generic Error Codes <gen-errors>` chapter.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
