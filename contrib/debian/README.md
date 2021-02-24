
Debian
====================
This directory contains files used to package __decenomy__d/__decenomy__-qt
for Debian-based Linux systems. If you compile __decenomy__d/__decenomy__-qt yourself, there are some useful files here.

## pivx: URI support ##


__decenomy__-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install __decenomy__-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your __decenomy__-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

__decenomy__-qt.protocol (KDE)

