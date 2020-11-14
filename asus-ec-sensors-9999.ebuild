# Copyright 2020 Anthony DeRossi
# Distributed under the terms of the GNU General Public License v2

EAPI=7

inherit linux-mod

DESCRIPTION="Asus EC sensor driver"
HOMEPAGE="https://github.com/anthonyde/asus-ec-sensors"

if [[ ${PV} = 9999 ]]; then
	inherit git-r3
	EGIT_REPO_URI="https://github.com/anthonyde/${PN}.git"
else
	SRC_URI="https://github.com/anthonyde/${PN}/archive/v${PV}.tar.gz -> ${P}.tar.gz"
	KEYWORDS="~amd64"
fi

LICENSE="GPL-2+"
SLOT="0"
IUSE=""

DEPEND=""
RDEPEND="${DEPEND}"
BDEPEND=""

BUILD_TARGETS="clean modules"
MODULE_NAMES="asus-ec-sensors(extra)"
CONFIG_CHECK="ACPI HWMON"
