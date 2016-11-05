/* < DTS2014052206888 yangxiaomei 20140523 begin */
/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __LINUX_SENSORS_H_INCLUDED
#define __LINUX_SENSORS_H_INCLUDED

#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/rwsem.h>

#define SENSORS_ACCELERATION_HANDLE		0
#define SENSORS_MAGNETIC_FIELD_HANDLE		1
#define SENSORS_ORIENTATION_HANDLE		2
#define SENSORS_LIGHT_HANDLE			3
#define SENSORS_PROXIMITY_HANDLE		4
#define SENSORS_GYROSCOPE_HANDLE		5
#define SENSORS_PRESSURE_HANDLE			6
#define SENSORS_HALL_HANDLE			7

#define SENSOR_TYPE_ACCELEROMETER		1
#define SENSOR_TYPE_GEOMAGNETIC_FIELD		2
#define SENSOR_TYPE_MAGNETIC_FIELD  SENSOR_TYPE_GEOMAGNETIC_FIELD
#define SENSOR_TYPE_ORIENTATION			3
#define SENSOR_TYPE_GYROSCOPE			4
#define SENSOR_TYPE_LIGHT			5
#define SENSOR_TYPE_PRESSURE			6
#define SENSOR_TYPE_TEMPERATURE			7
#define SENSOR_TYPE_PROXIMITY			8
#define SENSOR_TYPE_GRAVITY			9
#define SENSOR_TYPE_LINEAR_ACCELERATION		10
#define SENSOR_TYPE_ROTATION_VECTOR		11
#define SENSOR_TYPE_RELATIVE_HUMIDITY		12
#define SENSOR_TYPE_AMBIENT_TEMPERATURE		13
#define SENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED	14
#define SENSOR_TYPE_GAME_ROTATION_VECTOR	15
#define SENSOR_TYPE_GYROSCOPE_UNCALIBRATED	16
#define SENSOR_TYPE_SIGNIFICANT_MOTION		17
#define SENSOR_TYPE_STEP_DETECTOR		18
#define SENSOR_TYPE_STEP_COUNTER		19
#define SENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR	20
#define SENSOR_TYPE_HALL	10002
/**
 * struct sensors_classdev - hold the sensor general parameters and APIs
 * @dev:		The device to register.
 * @node:		The list for the all the sensor drivers.
 * @name:		Name of this sensor.
 * @vendor:		The vendor of the hardware part.
 * @handle:		The handle that identifies this sensors.
 * @type:		The sensor type.
 * @max_range:		The maximum range of this sensor's value in SI units.
 * @resolution:		The smallest difference between two values reported by
 *			this sensor.
 * @sensor_power:	The rough estimate of this sensor's power consumption
 *			in mA.
 * @min_delay:		This value depends on the trigger mode:
 *			continuous: minimum period allowed in microseconds
 *			on-change : 0
 *			one-shot :-1
 *			special : 0, unless otherwise noted
 * @fifo_reserved_event_count:	The number of events reserved for this sensor
 *				in the batch mode FIFO.
 * @fifo_max_event_count:	The maximum number of events of this sensor
 *				that could be batched.
 * @enabled:		Store the sensor driver enable status.
 * @delay_msec:		Store the sensor driver delay value. The data unit is
 *			millisecond.
 * @sensors_enable:	The handle for enable and disable sensor.
 * @sensors_poll_delay:	The handle for set the sensor polling delay time.
 */
struct sensors_classdev {
	struct device		*dev;
	struct list_head	node;
	const char		*name;
	const char		*vendor;
	int			version;
	int			handle;
	int			type;
	const char		*max_range;
	const char		*resolution;
	const char		*sensor_power;
	int			min_delay;
	int			fifo_reserved_event_count;
	int			fifo_max_event_count;
	unsigned int		enabled;
	unsigned int		delay_msec;
	/* enable and disable the sensor handle*/
	int	(*sensors_enable)(struct sensors_classdev *sensors_cdev,
					unsigned int enabled);
	int	(*sensors_poll_delay)(struct sensors_classdev *sensors_cdev,
					unsigned int delay_msec);
	int	(*sensors_self_test)(struct sensors_classdev *sensors_cdev);
};

extern int sensors_classdev_register(struct device *parent,
				 struct sensors_classdev *sensors_cdev);
extern void sensors_classdev_unregister(struct sensors_classdev *sensors_cdev);

/* < DTS2014041705903 zhangmin 20140418 begin */
/*----------------------------------------------------------------*/
/*This is for speed up boot time*/
enum input_name {
	ACC,
	AKM,
	GYRO,
	ALS,
	PS,
	HALL,
	SENSOR_MAX
};
/*layout of each devices*/
typedef enum
{
	COMPASS_TOP_GS_TOP			= 0,
	COMPASS_TOP_GS_BOTTOM		= 1,
	COMPASS_BOTTOM_GS_TOP		= 2,
	COMPASS_BOTTOM_GS_BOTTOM	= 3,
	COMPASS_NONE_GS_BOTTOM		= 4,
	COMPASS_NONE_GS_TOP			= 5,
	COMPASS_GS_POSITION_MAX,
}compass_gs_position_type;
/*DEVICE STATUS*/
#define DEVICE_SUSPEND  0
#define DEVICE_RESUME   1
#define IC_PM_ON   1
#define IC_PM_OFF  0

typedef enum
{
	NONE_SENSOR	= 0,
	G_SENSOR 	= 0x01,
	L_SENSOR	= 0x02,
	P_SENSOR 	= 0X04,
	M_SENSOR	= 0x08,
	GY_SENSOR   = 0x10,
}sensors_list_type;

int set_sensor_input(enum input_name name, const char *input_num);
void set_sensors_list(int sensor);
/*----------------------------------------------------------------*/
/* DTS2014052206888 yangxiaomei 20140523 end > */
/* DTS2014041705903 zhangmin 20140418 end > */
#endif		/* __LINUX_SENSORS_H_INCLUDED */
