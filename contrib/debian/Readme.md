# Script to build deb package

## Dependencies
>> sudo apt-get install debhelper

## Setup
  Go to parent directory
  Cp binary file __decenomy__-qt binary to this folder
  Cp bitcoin.png image for this folder

## Build

### Build (no args)
>> ./deb_build.sh
### Build (request help)
>> ./deb_build.sh --help
### Build (example)
>> ./deb_build.sh --timestamp "2024-01-04 01:07:23" --ticker 777 --package wallet --version 3.0.0.1 --notes "amazing app"
