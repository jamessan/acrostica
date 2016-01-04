#!/bin/sh
set -e

mkdir build
(
  cd build
  if [ "$TRAVIS_OS_NAME" = osx ]; then
    DIR=$(ls -1 /usr/local/Cellar/qt5)
    cmake -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt5/$DIR ..
  else
    cmake ..
  fi
)
make -C build
make -C build package
