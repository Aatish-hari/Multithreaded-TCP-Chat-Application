# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Linker flags (Winsock2)
LDFLAGS = -lws2_32

# Output program name
TARGET = client.exe

# Source files
SRCS = client.c utils.c

# Object files
OBJS = client.o utils.o

# Default rule: compile and run
all: $(TARGET)
	@echo Running $(TARGET)...
	@$(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile step
client.o: client.c utils.h
	$(CC) $(CFLAGS) -c client.c -o client.o

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o

# Clean build files
clean:
	@echo Cleaning files...
	del /Q $(OBJS) $(TARGET) 2>nul || echo "Nothing to delete"