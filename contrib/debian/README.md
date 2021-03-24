
Debian
====================
This directory contains files used to package jackpotd/jackpot-qt
for Debian-based Linux systems. If you compile jackpotd/jackpot-qt yourself, there are some useful files here.

## pivx: URI support ##


jackpot-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install jackpot-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your jackpot-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

jackpot-qt.protocol (KDE)

