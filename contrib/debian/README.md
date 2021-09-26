
Debian
====================
This directory contains files used to package azzured/azzure-qt
for Debian-based Linux systems. If you compile azzured/azzure-qt yourself, there are some useful files here.

## pivx: URI support ##


azzure-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install azzure-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your azzure-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

azzure-qt.protocol (KDE)

