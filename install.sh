#!/bin/bash

set -e

rm -rf build
mkdir -p build
cd build

cmake -DKDE_INSTALL_PLUGINDIR=`kf5-config --qt-plugins` -DCMAKE_BUILD_TYPE=Release  ..
make -j$(nproc)

sudo make install

kquitapp5 krunner