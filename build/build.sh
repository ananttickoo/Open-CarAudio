#!/bin/bash

#create run if does not exit
mkdir -p ../run/

LIB="-lwiringpi -lpthreads"

cd ../src

gcc spi.c bike_play.c -o ../run/bike_play $LIB