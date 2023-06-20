#!/bin/bash
set -euxo pipefail

#rm -rf ./build/*
cd build
cmake ..
make

./src/demo/testpilot_demo

