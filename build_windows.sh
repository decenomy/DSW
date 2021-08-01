#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
	CPU_CORES=1
fi

# Upgrade the system and install required dependencies
	sudo apt update
	sudo apt install git zip unzip build-essential libtool bsdmainutils autotools-dev autoconf pkg-config automake python3 curl g++-mingw-w64-x86-64 libqt5svg5-dev -y
	echo "1" | sudo update-alternatives --config x86_64-w64-mingw32-g++

# Clone code from official Github repository
	rm -rf KYAN
	git clone https://github.com/kyancoin/KYAN.git

# Entering directory
	cd KYAN

# Compile dependencies
	cd depends
	make -j$(echo $CPU_CORES) HOST=x86_64-w64-mingw32 
	cd ..

# Compile
	./autogen.sh
	./configure --prefix=$(pwd)/depends/x86_64-w64-mingw32 --disable-debug --disable-tests --disable-bench --disable-online-rust CFLAGS="-O3" CXXFLAGS="-O3"
	make -j$(echo $CPU_CORES) HOST=x86_64-w64-mingw32
	cd ..

# Create zip file of binaries
	cp KYAN/src/kyanited.exe KYAN/src/kyanite-cli.exe KYAN/src/kyanite-tx.exe KYAN/src/qt/kyanite-qt.exe .
	zip KYAN-Windows.zip kyanited.exe kyanite-cli.exe kyanite-tx.exe kyanite-qt.exe
	rm -f kyanited.exe kyanite-cli.exe kyanite-tx.exe kyanite-qt.exe
