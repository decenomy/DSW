
Debian
====================
This directory contains files used to package beacond/beacon-qt
for Debian-based Linux systems. If you compile beacond/beacon-qt yourself, there are some useful files here.

## pivx: URI support ##


beacon-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install beacon-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your beacon-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

beacon-qt.protocol (KDE)

