# Define the source files
SRCS = uimain.c tokenizer.c history.c

# Define the object files derived from source files
OBJS = $(SRCS:.c=.o)

# !Define the program name
PROGRAM_NAME = target

# Compilation flags
CFLAGS = -g -O3

# Default target: build the executable $(PROGRAM_NAME)
all: $(PROGRAM_NAME)

# $(PROGRAM_NAME) target depends on all object files ($(OBJS))
$(PROGRAM_NAME): $(OBJS)
	cc -o $(PROGRAM_NAME) $(CFLAGS) $(OBJS)

# Pattern rule to compile any .c file into corresponding .o file
%.o: %.c
	cc -c $(CFLAGS) $< 

# Individual dependencies for object files with header files
tokenizer.o: tokenizer.h
history.o: history.h

# Clean target: remove all generated object files and executable
clean:
	rm -f *.o $(PROGRAM_NAME)

# Run the program
run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)
