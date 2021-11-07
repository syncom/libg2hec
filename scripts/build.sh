#!/usr/bin/env bash

set -euxo pipefail

SCRIPT_DIR=$(dirname $0)

# Where we run ./configure
cd "${SCRIPT_DIR}/.."

env LDFLAGS=-L/tmp/nssw/lib CXXFLAGS=-I/tmp/nssw/include ./configure \
    --prefix=/tmp/nssw
make
make check
