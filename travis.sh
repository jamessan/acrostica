#!/bin/sh
set -e

mkdir build
(
  cd build
  if [ "$TRAVIS_OS_NAME" = osx ]; then
    ls /usr/local/Cellar/qt5
    cmake -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt5/* ..
  else
    cmake ..
  fi
)
make -C build
