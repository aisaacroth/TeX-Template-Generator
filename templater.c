#include <stdio.h>
#include <stdlib.h>

static void printUsage();

int main(int argc, char **argv) {
    if (argc != 4) {
        printUsage();
    }
    return 0;
}

static void printUsage() {
    fprintf(stderr, "usage: templater <class> <series> <number>\n");
    exit(1);
}
