# Files to build deb package

## Before a new release
  !! Edit changelog file

## Dependencies
>> sudo apt-get install debhelper

## Build deb package
  Go to parent directory
  Cp binary file __decenomy__-qt binary to this folder

>> dpkg-buildpackage -us -uc -b
