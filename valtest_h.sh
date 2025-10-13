#!/usr/bin/env bash

exe="${1:-./hashTest}"
out="val_h.txt"

# Run Valgrind without --quiet to guarantee a summary is always created
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
         --errors-for-leak-kinds=all --log-file="$out" "$exe"

# Check the output file for the concrete "0 errors" success message
if grep -q "ERROR SUMMARY: 0 errors" "$out"; then
    echo "PASS"
    exit 0
else
    echo "FAIL (see $out)"
    # On failure, print the actual summary line for a quick diagnosis
    grep "ERROR SUMMARY" "$out"
    exit 1
fi
