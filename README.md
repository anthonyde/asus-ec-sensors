# Linux EC sensor driver for Asus X570 motherboards

This is a Linux kernel module that provides a hardware monitoring interface
for additional sensors on Asus X570 motherboards, such as an external
temperature probe connected to the "T_Sensor" header.

Asus X570 motherboards expose most of their sensors via the NCT6798D hardware
monitoring interface.  Some sensors on these boards, however, are not
connected to this interface.  X470 boards support reading these sensors via
WMI, but the WMI interface is not available on X570 boards.  Instead, the
sensor values can be read directly from the board's embedded controller.

For the most recent version of this document see the [project page][1] on
GitHub.

For other sensors on X570 boards, see the `nct6775` kernel module.
For X470 boards, see [asus-wmi-sensors][2].

[1]: https://github.com/anthonyde/asus-ec-sensors
[2]: https://github.com/electrified/asus-wmi-sensors

## Supported motherboards and sensors

| Board               | Sensors    |
|---------------------|------------|
| Asus Prime X570-Pro | "T_Sensor" |

## Requirements

This module requires a 5.9 kernel with the following options configured:

    CONFIG_ACPI=y
    CONFIG_HWMON=y

Earlier kernels have not been tested.

## Installation

Build and install the kernel module:

    make
    make modules_install
    modprobe asus_ec_sensors

## Usage

Sensor values can be read with `lm_sensors`:

    > sensors asusec-*
    asusec-isa-0000
    Adapter: ISA adapter
    T_Sensor:     +82.0°C

When the module is loaded a new platform device is created called
`asus-ec-sensors`.  Sensor values can be read directly via its `hwmon`
interface:

    > cat /sys/bus/platform/devices/asus-ec-sensors/hwmon/hwmon*/temp1_input
    82000

## Development

For additional motherboard support please open a GitHub issue and include the
board's manufacturer and product name from the system's DMI table:

    dmidecode --type 2

Sensor offsets can be verified by monitoring the EC with the `ec_sys` module.
For example, to dump all EC data:

    xxd -l 256 /sys/kernel/debug/ec/ec0/io

## License

The files in this project are released under version 2 of the GNU General
Public License.  See the `LICENSE` file for the full license text.
