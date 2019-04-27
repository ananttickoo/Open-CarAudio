#!/bin/bash

#create run if does not exit
mkdir -p ../run/

LIB="-lwiringpi -lpthreads"
LIBPATH=" -I/usr/local/include -L/usr/local/lib"
cd ../src

gcc spi.c bike_play.c -o ../run/bike_play $LIBPATH $LIB

