#!/bin/sh

# setup fake ads server and install cleanup trap
ncat -l 48898 --keep-open &
ncat_pid=$!
trap "{ kill ${ncat_pid}; exit; }" EXIT

set -e

# wait for fake ads server to accept connections
while ! ncat --send-only localhost 48898; do sleep 1; done
./AdsLibTest.bin
./AdsLibOOITest.bin
./example/example.bin
