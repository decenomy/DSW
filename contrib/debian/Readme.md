# Script to build deb package

## Dependencies
>> sudo apt-get install debhelper

## Setup
  Go to parent directory
  Cp binary file __decenomy__-qt binary to this folder
  Cp bitcoin.png image for this folder

## Build

### Build (no args)
>> ./build.sh
### Build (request help)
>> ./build.sh --help
### Build (example)
>> ./build.sh --ticker 777 --package wallet --version 3.0.0.1 --notes "amazing app"
