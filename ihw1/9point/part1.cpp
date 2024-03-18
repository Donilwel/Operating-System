#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define FIFO_FILE "fifo"

int main() {
    mkfifo(FIFO_FILE, 0666);
    int fd = open(FIFO_FILE, O_WRONLY);

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    char buffer[BUFFER_SIZE];
    while (!inputFile.eof()) {
        inputFile.read(buffer, BUFFER_SIZE);
        write(fd, buffer, inputFile.gcount());
    }

    close(fd);
    remove(FIFO_FILE);

    std::cout << "Process 1 finished" << std::endl;

    return 0;
}
