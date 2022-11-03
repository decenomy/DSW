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
        [nN] | [n|N][O|o] ) TEST_STATUS='--enable-tests --without-gui' 	# qt tests still have some problems
		;;																# so use --without-gui
        [yY] | [yY][Ee][Ss] ) TEST_STATUS='--disable-tests'				# or alternatively simply disable the tests
           ;;
        *) TEST_STATUS='--disable-tests'
            ;;
esac

echo -e "\033[0;32mDo you want to disable the debug? (yes/no)\033[0m"
read -e DEBUG_ANSWER
case "$DEBUG_ANSWER" in
        [nN] | [n|N][O|o] ) DEBUG_STATUS='--enable-debug --without-gui' 	# qt tests still have some problems
           ;;																# so use --without-gui
        [yY] | [yY][Ee][Ss] ) DEBUG_STATUS='--disable-debug'				# or alternatively simply disable the tests
           ;;
        *) DEBUG_STATUS='--disable-debug'
            ;;
esac


# Upgrade the system and install required dependencies
	sudo apt update
	sudo apt install git zip unzip build-essential libtool bsdmainutils autotools-dev autoconf pkg-config automake python3 libqt5svg5-dev -y

# Clone code from official Github repository
	rm -rf KYAN
	git clone https://github.com/kyancoin/KYAN.git

# Entering directory
	cd KYAN

# Compile dependencies
	cd depends
	make -j$(echo $CPU_CORES) HOST=x86_64-pc-linux-gnu 
	cd ..

# Compile
	./autogen.sh
	./configure --enable-glibc-back-compat --prefix=$(pwd)/depends/x86_64-pc-linux-gnu LDFLAGS="-static-libstdc++" --enable-cxx --enable-static --disable-shared $(echo $DEBUG_STATUS) $(echo $TEST_STATUS) --disable-bench --with-pic CPPFLAGS="-fPIC -O3 --param ggc-min-expand=1 --param ggc-min-heapsize=32768" CXXFLAGS="-fPIC -O3 --param ggc-min-expand=1 --param ggc-min-heapsize=32768"
	make -j$(echo $CPU_CORES) HOST=x86_64-pc-linux-gnu
	cd ..

# Create zip file of binaries
	cp KYAN/src/kyanited KYAN/src/kyanite-cli KYAN/src/kyanite-tx KYAN/src/qt/kyanite-qt .
	zip KYAN-Linux.zip kyanited kyanite-cli kyanite-tx kyanite-qt
	rm -f kyanited kyanite-cli kyanite-tx kyanite-qt
