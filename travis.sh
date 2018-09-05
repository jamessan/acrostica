#!/bin/sh
set -e

if [ "$TRAVIS_OS_NAME" = osx ]; then
  export PATH="/usr/local/opt/qt/bin:$PATH"
fi
mkdir build
(
  cd build
  if [ "$TRAVIS_OS_NAME" = osx ]; then
    cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
  else
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
  fi
)
make -C build
