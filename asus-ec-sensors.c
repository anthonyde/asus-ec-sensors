// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Asus EC sensor driver
 *
 * Copyright (C) 2020 Anthony DeRossi <ajderossi@gmail.com>
 */

#include <linux/dmi.h>
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

static struct platform_driver asus_platform_driver = {
	.driver = {
		.name = "asus-ec-sensors",
	},
};

static int __init asus_platform_probe(struct platform_device *pdev)
{
	return 0;
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
