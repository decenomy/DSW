
Debian
====================
This directory contains files used to package cryptoflowd/cryptoflow-qt
for Debian-based Linux systems. If you compile cryptoflowd/cryptoflow-qt yourself, there are some useful files here.

## pivx: URI support ##


cryptoflow-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install cryptoflow-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your cryptoflow-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

cryptoflow-qt.protocol (KDE)

