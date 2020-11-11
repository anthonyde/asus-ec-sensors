// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Asus EC sensor driver
 *
 * Copyright (C) 2020 Anthony DeRossi <ajderossi@gmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

MODULE_AUTHOR("Anthony DeRossi <ajderossi@gmail.com>");
MODULE_DESCRIPTION("Asus EC sensor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

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
