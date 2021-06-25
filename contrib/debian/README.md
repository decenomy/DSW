
Debian
====================
This directory contains files used to package eskacoind/eskacoin-qt
for Debian-based Linux systems. If you compile eskacoind/eskacoin-qt yourself, there are some useful files here.

## pivx: URI support ##


eskacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install eskacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your eskacoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

eskacoin-qt.protocol (KDE)

