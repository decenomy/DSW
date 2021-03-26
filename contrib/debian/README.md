
Debian
====================
This directory contains files used to package dashdiamondd/dashdiamond-qt
for Debian-based Linux systems. If you compile dashdiamondd/dashdiamond-qt yourself, there are some useful files here.

## pivx: URI support ##


dashdiamond-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dashdiamond-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dashdiamond-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

dashdiamond-qt.protocol (KDE)

