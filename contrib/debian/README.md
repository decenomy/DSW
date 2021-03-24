
Debian
====================
This directory contains files used to package aezorad/aezora-qt
for Debian-based Linux systems. If you compile aezorad/aezora-qt yourself, there are some useful files here.

## pivx: URI support ##


aezora-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install aezora-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your aezora-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

aezora-qt.protocol (KDE)

