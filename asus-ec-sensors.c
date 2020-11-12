// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Asus EC sensor driver
 *
 * Copyright (C) 2020 Anthony DeRossi <ajderossi@gmail.com>
 */

#include <linux/dmi.h>
#include <linux/hwmon.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

MODULE_AUTHOR("Anthony DeRossi <ajderossi@gmail.com>");
MODULE_DESCRIPTION("Asus EC sensor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static const struct dmi_system_id asus_ec_sensors_dmi_match[] = {
	{
		/* Asus Prime X570-Pro */
		.matches = {
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_BOARD_NAME, "PRIME X570-PRO"),
		},
	},
	{}
};
MODULE_DEVICE_TABLE(dmi, asus_ec_sensors_dmi_match);

static umode_t asus_hwmon_is_visible(const void *data,
				     enum hwmon_sensor_types type, u32 attr,
				     int channel)
{
	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			return 0444;
		default:
			break;
		}
	default:
		break;
	}
	return 0;
}

static int asus_hwmon_read(struct device *dev, enum hwmon_sensor_types type,
			   u32 attr, int channel, long *val)
{
	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			*val = 0;
			return 0;
		default:
			break;
		}
	default:
		break;
	}
	return -EOPNOTSUPP;
}

static const struct hwmon_ops asus_hwmon_ops = {
	.is_visible = asus_hwmon_is_visible,
	.read = asus_hwmon_read,
};

static const struct hwmon_channel_info *asus_hwmon_info[] = {
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT),
	NULL
};

static const struct hwmon_chip_info asus_hwmon_chip_info = {
	.ops = &asus_hwmon_ops,
	.info = asus_hwmon_info,
};

static struct platform_driver asus_platform_driver = {
	.driver = {
		.name = "asus-ec-sensors",
	},
};

static int __init asus_platform_probe(struct platform_device *pdev)
{
	struct device *hwmon_dev =
		devm_hwmon_device_register_with_info(&pdev->dev, "asusec",
						     NULL,
						     &asus_hwmon_chip_info,
						     NULL);

	return PTR_ERR_OR_ZERO(hwmon_dev);
}

static struct platform_device *asus_platform_device;

static int __init asus_ec_sensors_init(void)
{
	if (!dmi_first_match(asus_ec_sensors_dmi_match))
		return -ENODEV;

	asus_platform_device = platform_create_bundle(&asus_platform_driver,
						      asus_platform_probe,
						      NULL, 0, NULL, 0);

	return PTR_ERR_OR_ZERO(asus_platform_device);
}

static void __exit asus_ec_sensors_exit(void)
{
	platform_device_unregister(asus_platform_device);
	platform_driver_unregister(&asus_platform_driver);
}

module_init(asus_ec_sensors_init);
module_exit(asus_ec_sensors_exit);
