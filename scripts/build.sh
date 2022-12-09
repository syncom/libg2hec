#!/usr/bin/env bash

set -euxo pipefail

SCRIPT_DIR=$(dirname "$0")
FLAGS_TMPDIR=$(mktemp -d)
readonly FLAGS_TMPDIR

INSTALL_DIR_PREFIX=${INSTALL_DIR_PREFIX:-${FLAGS_TMPDIR}}

# Where we run ./configure and NTL installation script
cd "${SCRIPT_DIR}/.."

# Install NTL
scripts/install-ntl-5.5.sh "${INSTALL_DIR_PREFIX}"

env LDFLAGS="-L${INSTALL_DIR_PREFIX}/lib" \
    CXXFLAGS="-I${INSTALL_DIR_PREFIX}/include" \
    ./configure \
    --prefix="${INSTALL_DIR_PREFIX}"
make clean
# For debugging
bear --version
BEAR_VERSION_MAJOR="$(bear --version | cut -f2 -d' ' | cut -f1 -d'.')"
if (( BEAR_VERSION_MAJOR > 2 )); then
  bear -- make
else
  bear make
fi

if [ "$#" -ge 1 ] && [ "$1" = "distcheck" ]; then
  echo "Creating tarball for distribution"
  make install
  DISTCHECK_CONFIGURE_FLAGS="LDFLAGS=-L${INSTALL_DIR_PREFIX}/lib CXXFLAGS=-I${INSTALL_DIR_PREFIX}/include" make distcheck
fi