#!/usr/bin/bash

rm -f log.log strace_out

pvs-studio-analyzer trace -- make
pvs-studio-analyzer analyze -o log.log
#plog-converter -a GA:1,2 -t tasklist -o report.tasks log.log || exit 1
plog-converter -a GA:1,2 -t tasklist -o report.tasks log.log
