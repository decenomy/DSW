
Debian
====================
This directory contains files used to package peonyd/peony-qt
for Debian-based Linux systems. If you compile peonyd/peony-qt yourself, there are some useful files here.

## pivx: URI support ##


peony-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install peony-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your peony-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

peony-qt.protocol (KDE)

