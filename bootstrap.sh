#!/bin/bash

# Find the highest numbered directory and increment
next=$(ls -d [0-9]* 2>/dev/null | sort -n | tail -1)
next=$((next + 1))

# Create new directory
mkdir "$next"

# Create main.c
cat > "$next/main.c" << 'EOF'
#include <stdio.h>

int main()
{
    printf("Hello, World!\n");

    return 0;
}
EOF

# Create Makefile
cat > "$next/Makefile" << 'EOF'
all: main
  ./main

main: main.c
	gcc -Wall -Wextra -pedantic -o main main.c
EOF

ln -s $(pwd)/AGENTS.md "$next/AGENTS.md"

echo "Created project in ./$next"
