.. -*- coding: utf-8; mode: rst -*-

.. _VIDIOC_G_STD:

<<<<<<< HEAD
**************************************************************************
ioctl VIDIOC_G_STD, VIDIOC_S_STD, VIDIOC_SUBDEV_G_STD, VIDIOC_SUBDEV_S_STD
**************************************************************************
=======
********************************
ioctl VIDIOC_G_STD, VIDIOC_S_STD
********************************
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

Name
====

<<<<<<< HEAD
VIDIOC_G_STD - VIDIOC_S_STD - VIDIOC_SUBDEV_G_STD - VIDIOC_SUBDEV_S_STD - Query or select the video standard of the current input
=======
VIDIOC_G_STD - VIDIOC_S_STD - Query or select the video standard of the current input
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')


Synopsis
========

.. c:function:: int ioctl( int fd, VIDIOC_G_STD, v4l2_std_id *argp )
    :name: VIDIOC_G_STD

.. c:function:: int ioctl( int fd, VIDIOC_S_STD, const v4l2_std_id *argp )
    :name: VIDIOC_S_STD

<<<<<<< HEAD
.. c:function:: int ioctl( int fd, VIDIOC_SUBDEV_G_STD, v4l2_std_id *argp )
    :name: VIDIOC_SUBDEV_G_STD

.. c:function:: int ioctl( int fd, VIDIOC_SUBDEV_S_STD, const v4l2_std_id *argp )
    :name: VIDIOC_SUBDEV_S_STD

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

Arguments
=========

``fd``
    File descriptor returned by :ref:`open() <func-open>`.

``argp``
    Pointer to :c:type:`v4l2_std_id`.


Description
===========

To query and select the current video standard applications use the
:ref:`VIDIOC_G_STD <VIDIOC_G_STD>` and :ref:`VIDIOC_S_STD <VIDIOC_G_STD>` ioctls which take a pointer to a
:ref:`v4l2_std_id <v4l2-std-id>` type as argument. :ref:`VIDIOC_G_STD <VIDIOC_G_STD>`
can return a single flag or a set of flags as in struct
:c:type:`v4l2_standard` field ``id``. The flags must be
unambiguous such that they appear in only one enumerated
struct :c:type:`v4l2_standard` structure.

:ref:`VIDIOC_S_STD <VIDIOC_G_STD>` accepts one or more flags, being a write-only ioctl it
does not return the actual new standard as :ref:`VIDIOC_G_STD <VIDIOC_G_STD>` does. When
no flags are given or the current input does not support the requested
standard the driver returns an ``EINVAL`` error code. When the standard set
is ambiguous drivers may return ``EINVAL`` or choose any of the requested
standards. If the current input or output does not support standard
video timings (e.g. if :ref:`VIDIOC_ENUMINPUT`
does not set the ``V4L2_IN_CAP_STD`` flag), then ``ENODATA`` error code is
returned.


Return Value
============

On success 0 is returned, on error -1 and the ``errno`` variable is set
appropriately. The generic error codes are described at the
:ref:`Generic Error Codes <gen-errors>` chapter.

EINVAL
    The :ref:`VIDIOC_S_STD <VIDIOC_G_STD>` parameter was unsuitable.

ENODATA
    Standard video timings are not supported for this input or output.
