#!/bin/bash

#create run if does not exit
mkdir -p ../run/

LIB="-lwiringPi -lpthread"
LIBPATH="-I/usr/include  -L/usr/local/lib"
cd ../src

gcc -g -lm -w -std=99 conver_spi.c spi.c bike_play.c -o ../run/bike_play $LIBPATH $LIB

 