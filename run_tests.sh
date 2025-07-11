#!/usr/bin/env bash
set -uo pipefail   # note: NO -e

NUM_TESTS=3

for i in $(seq 1 $NUM_TESTS); do
  echo "=== Running test $i ==="

  if ./MatamStory tests/test${i}.events tests/test${i}.players > test${i}.out; then
    # program exited cleanly
    if diff --strip-trailing-cr -B -Z test${i}.out tests/test${i}.expected; then
      echo "Test $i: PASS"
    else
      echo "Test $i: FAIL"
    fi
  else
    echo "Test $i: ERROR (MatamStory exited non-zero)"
  fi

  echo
done
