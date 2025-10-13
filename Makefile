# CFLAGS for compiling
CFLAGS = -Wall -pedantic -std=c11 -I. -g

# Object files for the modules
MOD_OBJS = queue.o hash.o

# The main test executable
TARGET = hashTest

# The default 'make' command will build the hashTest executable
all: $(TARGET)

# Rule for linking the final executable
$(TARGET): $(TARGET).o $(MOD_OBJS)
	gcc $(CFLAGS) $^ -o $@

# Pattern rule to compile any .c file into a .o file
# This rule you already had works perfectly.
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

# Rule for running the test
test: $(TARGET)
	./$(TARGET)

# Rule to clean up compiled files
clean:
	rm -f *.o $(TARGET)
