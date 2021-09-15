
Debian
====================
This directory contains files used to package pepsd/peps-qt
for Debian-based Linux systems. If you compile pepsd/peps-qt yourself, there are some useful files here.

## pivx: URI support ##


peps-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install peps-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your peps-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

peps-qt.protocol (KDE)

