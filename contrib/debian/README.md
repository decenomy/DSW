
Debian
====================
This directory contains files used to package monkd/monk-qt
for Debian-based Linux systems. If you compile monkd/monk-qt yourself, there are some useful files here.

## pivx: URI support ##


monk-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install monk-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your monk-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

monk-qt.protocol (KDE)

