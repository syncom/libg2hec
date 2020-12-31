AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src doc

noinst_PROGRAMS = examples/dh examples/elgamal_enc examples/elgamal_sig

examples_dh_CXXFLAGS = -Iinclude/
examples_dh_LDADD = src/libg2hec.a -lntl
examples_dh_SOURCES = examples/dh.C

examples_elgamal_enc_CXXFLAGS = -Iinclude/
examples_elgamal_enc_LDADD = src/libg2hec.a -lntl
examples_elgamal_enc_SOURCES = examples/elgamal_enc.C

examples_elgamal_sig_CXXFLAGS = -Iinclude/
examples_elgamal_sig_LDADD = src/libg2hec.a -lntl
examples_elgamal_sig_SOURCES = examples/elgamal_sig.C

