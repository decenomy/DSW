#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
    CPU_CORES=1
fi

# Clone code from official Github repository
    rm -rf 777
    git clone https://github.com/777-project/777.git

# Entering directory
    cd 777

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
    ./configure --prefix=$(pwd)/depends/x86_64-apple-darwin14 --enable-cxx --enable-static --disable-shared --disable-debug --disable-tests --disable-bench --disable-online-rust
    make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin14
    make deploy
    cd ..

# Create zip file of binaries
    cp 777/src/jackpotd 777/src/jackpot-cli 777/src/jackpot-tx 777/src/qt/jackpot-qt 777/Jackpot-Core.dmg .
    zip 777-MacOS.zip jackpotd jackpot-cli jackpot-tx jackpot-qt Jackpot-Core.dmg
    rm -f jackpotd jackpot-cli jackpot-tx jackpot-qt Jackpot-Core.dmg
