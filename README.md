# THE G2HEC LIBRARY

Ning Shang <geek@cerias.net>

---

The G2HEC (Genus 2 HyperElliptic Curve) library is a free portable C++
library providing divisor group operations in the Jacobian of genus 2
(imaginary) hyperelliptic curve.  Such curves can be used for
discrete-logarithm-based cryptosystems with advantages over elliptic
curves (genus 1 curves).  Divisor group operations are essential to
using genus 2 curves for cryptography.

It is built on top of [V. Shoup's NTL
library](http://www.shoup.net/ntl/), "a high performance, portable C++
library providing data structures and algorithms for arbitrary length
integers; for vectors, matrices, and polynomials over the integers and
over finite fields; and for arbitrary precision floating point
arithmetic." G2HEC has been tested with NTL 5.5 on an `x86_64` Ubuntu.
You may refer to build scripts
[scripts/install-ntl-5.5.sh](./scripts/install-ntl-5.5.sh) and
[scripts/build.sh](./scripts/build.sh) for sample commands building the
library.

It is recommended to build NTL using GMP (the GNU Multi-Precision
package) for best performance.  However, the G2HEC library can be built
and used with and without the existence of GMP.  The GMP library
homepage: http://www.swox.com/gmp/.

This library does not assume users' familiarity with any non-trivial
math background except basic concepts of finite fields and polynomials.
No prior knowledge of genus 2 curve is needed to used the library.

The G2HEC library is released under the GNU Lesser General Public
License Version 2.1.  See the file COPYING for details.

## How to build
On Ubuntu,

```bash
$ cd libg2hec/
# Install dependencies
$ sudo apt-get install autotools-dev autoconf texinfo build-essential
# Bootstrap
$ autoreconf -vi
# Build NTL
$ ./scripts/install-ntl-5.5.sh
# Build libg2hec
$ ./scripts/build.sh
# Install libg2hec
$ make install 
```

This installs NTL and libg2hec (including documentation) in `/tmp/nssw/`
by default. You may configure different paths in build scripts in
`scripts/` for the installation.

## Documentation

[https://syncom.github.io/libg2hec/](https://syncom.github.io/libg2hec/)
