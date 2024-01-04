#!/bin/bash

# Default value for TICKER
TICKER="__DSW__"
PACKAGE="wallet"
VERSION="3.0.0.0"
NOTES="New release."

name="zimbora"
email="lucas.ua.eet@gmail.com"
input_date="2024-01-04 01:07:23"

# Function to check if a version is in the format x.y.z.u
is_valid_version() {
  local version="$1"
  if [[ "$version" =~ ^[0-99]+\.[0-99]+\.[0-99]+\.[0-99]+$ ]]; then
    return 0  # Valid version format
  else
    return 1  # Invalid version format
  fi
}

# Parse command line options
while [[ "$#" -gt 0 ]]; do
  case $1 in
    --help)
      echo "
        --ticker: set ticker
        --package: package name
        --version: set version
        --notes: set changelog notes
      "
      exit 1
      ;;
    --ticker)
      TICKER="$2"
      shift 2
      ;;
    --timestamp)
      input_date="$2"
      if echo "$input_date" | grep -E '^[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}$' >/dev/null; then
        echo "The date is in the correct format."
      else
        echo "Invalid date format."
      fi
      shift 2
      ;;
    --package)
      PACKAGE="$2"
      # Check if the PACKAGE string contains only lowercase letters
      if ! [[ "$PACKAGE" =~ ^[a-z]+$ ]]; then
          echo "The package args does not contain only lowercase letters."
          exit 1
      fi
      shift 2
      ;;
    --version)
      VERSION="$2"
      # Check if the provided version is in the format x.y.z.u
      if ! is_valid_version "$VERSION"; then
        echo "Invalid version format. Please use x.y.z.u format."
        exit 1
      fi
      shift 2
      ;;
    --notes)
      NOTES="$2"
      shift 2
      ;;
    *)
      echo "Unknown option: $1"
      exit 1
      ;;
  esac
done

formatted_date=$(echo "$input_date" | env LC_TIME=en_US.UTF-8 date "+%a, %d %b %Y %H:%M:%S +0000" --date="$(cat)")
#formatted_date=$(date -u "+%a, %d %b %Y %H:%M:%S +0000")
echo "ticker: $TICKER"
echo "package: $PACKAGE"
echo "version: $VERSION"
echo "date: $formatted_date"

#make dirs
rm -r debian
mkdir debian

#create changelog file
echo "${PACKAGE} (${VERSION}) stable; urgency=medium

 * ${NOTES}

 -- ${name} <${email}>  ${formatted_date}" >> debian/changelog

#create compat
echo "14" >> debian/compat

#create control
echo "Source: ${PACKAGE}
Section: misc
Priority: optional
Maintainer: ${name} <${email}>
Build-Depends: debhelper (>= 9)

Package: ${PACKAGE}
Architecture: any
Depends:
Description: ${TICKER} wallet
Homepage: https://explorer.decenomy.net/
" >> debian/control

#create install
echo "debian/app.desktop usr/share/applications/" >> debian/install

#create rules
echo "#!/usr/bin/make -f

export TICKER=${TICKER}

clean:
	@# Do nothing

build:
	@# Do nothing

binary:
	echo "${TICKER}"
	mkdir -p debian/wallet/usr/bin
	cp __decenomy__-qt debian/wallet/usr/bin/"${TICKER}"
	mkdir -p debian/wallet/usr/share/applications
	cp bitcoin.png debian/wallet/usr/share/applications
	echo \"[Desktop Entry]\nName=${TICKER}\nExec=/usr/bin/${TICKER}\nIcon=/usr/share/applications/bitcoin.png\nType=Application\nCategories=Finance;\" > debian/wallet/usr/share/applications/app.desktop

	dh_gencontrol
	dh_builddeb
" >> debian/rules

#build package
dpkg-buildpackage -us -uc -b
