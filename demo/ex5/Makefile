CC=clang
AR=ar
ARFLAGS=rcs

FUZZ_CFLAGS=-fsanitize=address,fuzzer -g -O1
COV_CFLAGS=-fsanitize=fuzzer -fprofile-instr-generate -fcoverage-mapping -g -O1

all: libvuln.a fuzz_vuln fuzz_vuln_cov

# Compile vuln_lib.o
vuln_lib.o: vuln_lib.c vuln_lib.h
	$(CC) -c vuln_lib.c -o vuln_lib.o

# Create static library
libvuln.a: vuln_lib.o
	$(AR) $(ARFLAGS) libvuln.a vuln_lib.o

# Build fuzzing binary (for finding crashes)
fuzz_vuln: fuzz_vuln.c libvuln.a
	$(CC) $(FUZZ_CFLAGS) fuzz_vuln.c libvuln.a -o fuzz_vuln

# Build coverage binary (for code coverage analysis)
fuzz_vuln_cov: fuzz_vuln.c vuln_lib.c
	$(CC) $(COV_CFLAGS) fuzz_vuln.c vuln_lib.c -o fuzz_vuln_cov

clean:
	rm -f fuzz_vuln fuzz_vuln_cov vuln_lib.o libvuln.a *.profraw *.profdata coverage_report coverage.html

# Run fuzzer normally
run-fuzz:
	./fuzz_vuln

# Run coverage version
run-cov: fuzz_vuln_cov
	rm -f coverage.profraw
	LLVM_PROFILE_FILE="coverage.profraw" ./fuzz_vuln_cov -runs=100000

run-cov-corpus: fuzz_vuln_cov
	rm -rf coverage.profraw corpus/
	mkdir corpus/
	printf "\xef\xbe\xad\xde\xbe\xba\xfe\xca\xfe\xca\xba\xabHello" > corpus/test1
	printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00Data" > corpus/test2
	printf "\xef\xbe\xad\xde\xbe\xba\xfe\xca\xfe\xca\xba\xabHelloFuzzing!" > corpus/valid_input
	LLVM_PROFILE_FILE="coverage.profraw" ./fuzz_vuln_cov corpus -runs=1000

# Generate coverage report
coverage: run-cov-corpus
	llvm-profdata merge -sparse coverage.profraw -o coverage.profdata
	llvm-cov show ./fuzz_vuln_cov -instr-profile=coverage.profdata > coverage_report.txt
	llvm-cov report ./fuzz_vuln_cov -instr-profile=coverage.profdata

# Generate an HTML coverage report
coverage-html: coverage
	llvm-cov show ./fuzz_vuln_cov -format=html -instr-profile=coverage.profdata > coverage.html

