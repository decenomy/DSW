#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
    CPU_CORES=1
fi

# Clone code from official Github repository
    rm -rf SAGA
    git clone https://github.com/cryptosagacoin/SAGA.git

# Entering directory
    cd SAGA

# Compile dependencies
    cd depends
    mkdir SDKs
    cd SDKs
    wget -c https://cloudflare-ipfs.com/ipfs/QmYv9wHqKa5gZE1kL4ZpcVqKp1coS5tS9cYKGe4mUxxrqL/SDKs/MacOSX10.11.sdk.tar.xz
    tar -xf MacOSX10.11.sdk.tar.xz
    cd ..
    make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin14
    cd ..

# Compile
    ./autogen.sh
    ./configure --prefix=$(pwd)/depends/x86_64-apple-darwin14 --enable-cxx --enable-static --disable-shared --disable-debug --disable-tests --disable-bench --disable-online-rust --enable-upnp-default
    make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin14
    make deploy
    cd ..

# Create zip file of binaries
    cp SAGA/src/cryptosagad SAGA/src/cryptosaga-cli SAGA/src/cryptosaga-tx SAGA/src/qt/cryptosaga-qt SAGA/CryptoSaga-Core.dmg .
    zip SAGA-MacOS.zip cryptosagad cryptosaga-cli cryptosaga-tx cryptosaga-qt CryptoSaga-Core.dmg
    rm -f cryptosagad cryptosaga-cli cryptosaga-tx cryptosaga-qt CryptoSaga-Core.dmg
