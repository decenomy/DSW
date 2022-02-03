#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
    CPU_CORES=1
fi

# Clone code from official Github repository
    rm -rf DSW
    git clone https://github.com/decenomy/DSW.git

# Entering directory
    cd DSW
    
# Selecting wallet
	git checkout MONK-develop

# Compile dependencies
    cd depends
    mkdir SDKs
    cd SDKs
    wget https://github.com/phracker/MacOSX-SDKs/releases/download/10.15/MacOSX10.11.sdk.tar.xz
    tar -xf MacOSX10.11.sdk.tar.xz
    cd ..
    make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin14
    cd ..

# Compile
    ./autogen.sh
    ./configure --prefix=$(pwd)/depends/x86_64-apple-darwin14 --enable-cxx --enable-static --disable-shared --disable-debug --disable-tests --disable-bench --disable-online-rust
    make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin14
    make deploy
    cd ..

# Create zip file of binaries
    cp DSW/src/monkd DSW/src/monk-cli DSW/src/monk-tx DSW/src/qt/monk-qt DSW/Monk-Core.dmg .
    zip MONK-MacOS.zip monkd monk-cli monk-tx monk-qt monk-Core.dmg
    rm -f monkd monk-cli monk-tx monk-qt Monk-Core.dmg
