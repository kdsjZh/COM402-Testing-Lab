#!/bin/sh
export AFL_SKIP_CPUFREQ=1
$AFL_PATH/afl-fuzz -i in/ -o out/ -m none -- ./ex4 @@
