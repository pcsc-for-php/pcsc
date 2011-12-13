#!/bin/bash

#echo "Cleaning up ...\n"

make clean
phpize --clean

#echo "Compile package...\n"

phpize
aclocal
libtoolize --force
autoheader
autoconf

#echo "Configure package...\n"

./configure --enable-pcsc --prefix=/usr

make

#echo "Now type su and the make install...\n"


