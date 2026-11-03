#!/usr/bin/env bash
# Compile every lab into ./build and run it.
set -e
mkdir -p build
for dir in lab-*/; do
  name="${dir%/}"
  g++ -std=c++17 -Wall -Wextra -O2 "$name/main.cpp" -o "build/$name"
  echo "===== $name ====="
  "./build/$name"
  echo
done
