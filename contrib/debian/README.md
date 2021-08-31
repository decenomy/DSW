
Debian
====================
This directory contains files used to package biraked/birake-qt
for Debian-based Linux systems. If you compile biraked/birake-qt yourself, there are some useful files here.

## pivx: URI support ##


birake-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install birake-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your birake-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

birake-qt.protocol (KDE)

