
Debian
====================
This directory contains files used to package ultracleard/ultraclear-qt
for Debian-based Linux systems. If you compile ultracleard/ultraclear-qt yourself, there are some useful files here.

## pivx: URI support ##


ultraclear-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ultraclear-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ultraclear-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

ultraclear-qt.protocol (KDE)

