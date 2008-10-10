# Makefile.am

INCLUDES = -I$(top_srcdir)/include

include_HEADERS	= ../include/g2hec_Genus2_ops.h  ../include/g2hec_NAF.h  \
		../include/g2hec_nsfieldtype.h  ../include/g2hec_nstools.h \
		../include/g2hec_polytype.h ../include/g2hec_nsdebug.h \
                ../include/g2hec_rand.h

lib_LIBRARIES	= libg2hec.a
libg2hec_a_SOURCES	= g2hcurve.C cantor.C divisor.C add_explicit.C \
			divisor_negate.C sub.C scalar_mul.C rand.C

# Add data directory to distro
EXTRA_DIST	= testdata

# Test unit
check_PROGRAMS	= testcurve testrand
testcurve_SOURCES	= testcurve.C
testrand_SOURCES	= testrand.C 

LDADD	= libg2hec.a -lntl

check_SCRIPTS	= g2hectest_small.sh g2hectest_big.sh randtest.sh
TESTS		= $(check_SCRIPTS)

g2hectest_small.sh:
	echo -e "for i in \`ls $(srcdir)/testdata/testdata_small*.dat\`\n\
	do \n\
	./testcurve < \$${i} \n\
	done" > g2hectest_small.sh

	chmod +x g2hectest_small.sh

g2hectest_big.sh:
	echo -e "for i in \`ls $(srcdir)/testdata/testdata_big*.dat\`\n\
	do \n\
	./testcurve < \$${i} \n\
	done" > g2hectest_big.sh

	chmod +x g2hectest_big.sh

randtest.sh:
	echo -e "for i in 1 2 3 4 5 6 7 8 9 \n\
	do \n\
	./testrand \n\
	done" > randtest.sh

	chmod +x randtest.sh

CLEANFILES	= g2hectest_small.sh g2hectest_big.sh randtest.sh


