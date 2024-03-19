#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 128
#define FIFO_FILE "fifo"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.txt output.txt" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    mkfifo(FIFO_FILE, 0666);

    int fd = open(FIFO_FILE, O_WRONLY);
    char buffer[BUFFER_SIZE];
    inputFile.read(buffer, BUFFER_SIZE);
    write(fd, buffer, inputFile.gcount());
    close(fd);

    int fd2 = open(FIFO_FILE, O_RDONLY);
    std::ofstream outputFile(outputFileName);
    read(fd2, buffer, BUFFER_SIZE);
    outputFile.write(buffer, strlen(buffer));
    close(fd2);

    remove(FIFO_FILE);

    std::cout << "Process 1 finished" << std::endl;

    return 0;
}
