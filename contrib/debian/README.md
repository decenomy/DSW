
Debian
====================
This directory contains files used to package oneworldd/oneworld-qt
for Debian-based Linux systems. If you compile oneworldd/oneworld-qt yourself, there are some useful files here.

## pivx: URI support ##


oneworld-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install oneworld-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your oneworld-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

oneworld-qt.protocol (KDE)

