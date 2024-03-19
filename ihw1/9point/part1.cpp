#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 128
#define FIFO_FILE "fifo"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.txt output.txt\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];

    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        fprintf(stderr, "Error: Unable to open input file.\n");
        return 1;
    }

    mkfifo(FIFO_FILE, 0666);

    int fd = open(FIFO_FILE, O_WRONLY);
    char buffer[BUFFER_SIZE];
    fread(buffer, 1, BUFFER_SIZE, inputFile);
    write(fd, buffer, BUFFER_SIZE);
    close(fd);

    int fd2 = open(FIFO_FILE, O_RDONLY);
    FILE *outputFile = fopen(outputFileName, "w");
    read(fd2, buffer, BUFFER_SIZE);
    fwrite(buffer, 1, strlen(buffer), outputFile);
    fclose(outputFile);
    close(fd2);

    remove(FIFO_FILE);

    printf("Process 1 finished\n");

    return 0;
}
