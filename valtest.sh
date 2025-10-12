echo "Running Valgrind memory check on ListTest..."
echo

# Run valgrind, save all output to file
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         ./ListTest &> valgrind_output.txt

# Now print only the key summary lines
grep -E "ERROR SUMMARY|definitely lost|indirectly lost|possibly lost|still reachable" valgrind_output.txt

echo
echo "Valgrind check complete. Full report saved to valgrind_output.txt"
