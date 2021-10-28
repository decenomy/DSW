
Debian
====================
This directory contains files used to package mobicd/mobic-qt
for Debian-based Linux systems. If you compile mobicd/mobic-qt yourself, there are some useful files here.

## pivx: URI support ##


mobic-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install mobic-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your mobic-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

mobic-qt.protocol (KDE)

