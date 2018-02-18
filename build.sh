#! /bin/sh
autoreconf -i
automake
./configure
make
