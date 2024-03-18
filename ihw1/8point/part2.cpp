#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 5000
#define FIFO_FILE "fifo"

void findDifferences(std::string str1, std::string str2, std::string& output1, std::string& output2) {
    // Implementation of findDifferences function
    // This function should find differences between str1 and str2
    // and store the results in output1 and output2
}

int main() {
    // Create FIFO
    mkfifo(FIFO_FILE, 0666);

    int fd = open(FIFO_FILE, O_RDONLY);
    char buffer[BUFFER_SIZE];
    read(fd, buffer, BUFFER_SIZE);
    close(fd);

    // Process the data
    std::string data(buffer);

    std::string output1, output2;
    findDifferences(data, "", output1, output2);

    int fd2 = open(FIFO_FILE, O_WRONLY);
    write(fd2, output1.c_str(), output1.length() + 1);
    close(fd2);

    remove(FIFO_FILE);

    std::cout << "Process 2 finished" << std::endl;

    return 0;
}
