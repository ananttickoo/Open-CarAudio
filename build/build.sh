#!/bin/bash

$LIB ="-lwiringpi -lpthreads"

cd ../src

gcc bike_play.c -o ../run/bike_play $LIB