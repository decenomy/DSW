
Debian
====================
This directory contains files used to package sapphired/sapphire-qt
for Debian-based Linux systems. If you compile sapphired/sapphire-qt yourself, there are some useful files here.

## sapphire: URI support ##


sapphire-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install sapphire-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your sapphire-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

sapphire-qt.protocol (KDE)

