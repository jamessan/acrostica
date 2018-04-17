#!/bin/sh
set -e

mkdir build
(
  cd build
  if [ "$TRAVIS_OS_NAME" = osx ]; then
    ROOT=/usr/local/Cellar/qt
    DIR=$(ls -1 "$ROOT")
    cmake -DCMAKE_PREFIX_PATH="$ROOT"/"$DIR" ..
  else
    cmake ..
  fi
)
make -C build
