#!/usr/bin/env bash
if [ $# -eq 0 ]
then
    echo "Input version"
    exit
fi
sed -i -e '/- LIBRARY_VERSION=/d' .travis.yml
sed -i -e "/TRAVIS_DEBIAN_TARGET_DIR/a\        - LIBRARY_VERSION=\"v$1\"" .travis.yml
dch -v $1
