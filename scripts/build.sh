#!/usr/bin/env bash

set -euxo pipefail

SCRIPT_DIR=$(dirname "$0")
FLAGS_TMPDIR=$(mktemp -d)
readonly FLAGS_TMPDIR

# Where we run ./configure and NTL installation script
cd "${SCRIPT_DIR}/.."

# Install NTL
scripts/install-ntl-5.5.sh "${FLAGS_TMPDIR}"

env LDFLAGS="-L${FLAGS_TMPDIR}/lib" \
    CXXFLAGS="-I${FLAGS_TMPDIR}/include" \
    ./configure \
    --prefix="${FLAGS_TMPDIR}"
make
make install
DISTCHECK_CONFIGURE_FLAGS="LDFLAGS=-L${FLAGS_TMPDIR}/lib CXXFLAGS=-I${FLAGS_TMPDIR}/include" make distcheck
