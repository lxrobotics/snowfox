#!/bin/bash
cd $(dirname $(readlink -f $0))
cd ..

rm -rf ../../build
