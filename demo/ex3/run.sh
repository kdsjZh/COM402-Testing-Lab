#!/bin/sh
export AFL_SKIP_CPUFREQ=1
$AFL_PATH/afl-fuzz -i in/ -o out/ -c ./ex3.cmplog -l 3 -- ./ex3.afl @@
