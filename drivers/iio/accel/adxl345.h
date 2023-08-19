/*
 * ADXL345 3-Axis Digital Accelerometer
 *
 * Copyright (c) 2017 Eva Rachel Retuya <eraretuya@gmail.com>
 *
 * This file is subject to the terms and conditions of version 2 of
 * the GNU General Public License. See the file COPYING in the main
 * directory of this archive for more details.
 */

#ifndef _ADXL345_H_
#define _ADXL345_H_

<<<<<<< HEAD
enum adxl345_device_type {
	ADXL345,
	ADXL375,
};

int adxl345_core_probe(struct device *dev, struct regmap *regmap,
		       enum adxl345_device_type type, const char *name);
=======
int adxl345_core_probe(struct device *dev, struct regmap *regmap,
		       const char *name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int adxl345_core_remove(struct device *dev);

#endif /* _ADXL345_H_ */
