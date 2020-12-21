#!/usr/bin/env bash

set -euo pipefail

env LDFLAGS=-L/tmp/nssw/lib CXXFLAGS=-I/tmp/nssw/include ./configure \
    --prefix=/tmp/nssw
make
make check
