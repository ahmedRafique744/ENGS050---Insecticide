#!/usr/bin/env bash

exe="${1:-./queueTest}"
out="valgrind_output.txt"

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=all --quiet --log-file="$out" "$exe"

grep -E "ERROR SUMMARY|definitely lost|indirectly lost|possibly lost|still reachable" "$out"

ok=0
grep -q "ERROR SUMMARY: 0 errors" "$out" || ok=1
grep -q "definitely lost: 0 bytes" "$out" || ok=1
grep -q "indirectly lost: 0 bytes" "$out" || ok=1

[ $ok -eq 0 ] && echo "PASS" || echo "FAIL (see $out)"
exit $ok
