#!/usr/bin/env bash
set -euo pipefail

wget -c https://libntl.org/ntl-5.5.2.tar.gz -O /tmp/ntl.tar.gz
tar xvfz /tmp/ntl.tar.gz -C /tmp/
cd /tmp/ntl-5.5.2/src
./configure PREFIX=/tmp/nssw
make
make install
