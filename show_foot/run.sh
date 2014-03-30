#!/bin/sh

./kill.sh showfoot
make -f Makefile_pc clean
make -f Makefile_pc && ./showfoot
