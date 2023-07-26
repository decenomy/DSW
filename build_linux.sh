#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
	CPU_CORES=1
fi

echo -e "\033[0;32mDo you want to disable the tests? (yes/no)\033[0m"
read -e TEST_ANSWER
case "$TEST_ANSWER" in
        [nN] | [n|N][O|o] ) TEST_STATUS='--enable-tests' 	# qt tests still have some problems
           ;;											# so use --without-gui
        [yY] | [yY][Ee][Ss] ) TEST_STATUS='--disable-tests'
           ;;
        *) TEST_STATUS='--disable-tests'
            ;;
esac

echo -e "\033[0;32mDo you want to disable the debug? (yes/no)\033[0m"
read -e DEBUG_ANSWER
case "$DEBUG_ANSWER" in
        [nN] | [n|N][O|o] ) DEBUG_STATUS='--enable-debug' 	# qt tests still have some problems
           ;;											# so use --without-gui
        [yY] | [yY][Ee][Ss] ) DEBUG_STATUS='--disable-debug'
           ;;
        *) DEBUG_STATUS='--disable-debug'
            ;;
esac

# Upgrade the system and install required dependencies
	sudo apt update
	sudo apt install git zip unzip build-essential libtool bsdmainutils autotools-dev autoconf pkg-config automake python3 libqt5svg5-dev -y

# Clone code from official Github repository
	#rm -rf DSW
	#git clone https://github.com/decenomy/DSW.git

# Entering directory
	cd DSW

# Compile dependencies
	cd depends
	make -j$(echo $CPU_CORES) HOST=x86_64-pc-linux-gnu
	cd ..

# Compile
	./autogen.sh
	./configure --enable-glibc-back-compat --prefix=$(pwd)/depends/x86_64-pc-linux-gnu LDFLAGS="-static-libstdc++" --enable-cxx --enable-static --disable-shared $(echo $DEBUG_STATUS) $(echo $TEST_STATUS) --disable-bench --with-pic --enable-upnp-default CPPFLAGS="-fPIC -O3 --param ggc-min-expand=1 --param ggc-min-heapsize=32768" CXXFLAGS="-fPIC -O3 --param ggc-min-expand=1 --param ggc-min-heapsize=32768"
	make -j$(echo $CPU_CORES) HOST=x86_64-pc-linux-gnu
	cd ..

# Create zip file of binaries
	cp DSW/src/__decenomy__d DSW/src/__decenomy__-cli DSW/src/__decenomy__-tx DSW/src/qt/__decenomy__-qt .
	zip __DSW__-$(git describe --abbrev=0 --tags | sed s/v//)-Linux.zip __decenomy__d __decenomy__-cli __decenomy__-tx __decenomy__-qt
	rm -f __decenomy__d __decenomy__-cli __decenomy__-tx __decenomy__-qt
