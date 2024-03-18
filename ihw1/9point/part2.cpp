#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define FIFO_FILE "fifo"

int main() {
    int fd = open(FIFO_FILE, O_RDONLY);

    std::ofstream outputFile("output.txt");
    if (!outputFile) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int bytesRead;
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        outputFile.write(buffer, bytesRead);
    }

    close(fd);

    std::cout << "Process 2 finished" << std::endl;

    return 0;
}
