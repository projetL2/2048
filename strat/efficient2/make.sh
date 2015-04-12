#!/bin/bash

gcc -std=c99 -fPIC -c grid.c -o grid.o
gcc -std=c99 -fPIC -c strategy.c -o strategy.o
gcc -std=c99 -fPIC -c efficient.c -o efficient.o
gcc -shared -Wl,-soname,libA1_almyre_chambres_mahazoasy_petureau_efficient.so.1 -o libA1_almyre_chambres_mahazoasy_petureau_efficient.so *.o
