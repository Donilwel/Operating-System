#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 128
#define FIFO_FILE "fifo"

void findDifferences(char *str1, char *str2, char *output1, char *output2) {
    int ascii[256] = {0};

    // Заполняем массив ascii с учетом символов из второй строки
    for (int i = 0; i < strlen(str2); i++) {
        ascii[(int)str2[i]] = 1;
    }

    int index1 = 0;
    int index2 = 0;

    // Находим символы, которых нет во второй строке
    for (int i = 0; i < strlen(str1); i++) {
        if (ascii[(int)str1[i]] == 0) {
            output1[index1++] = str1[i];
        }
    }

    // Находим символы, отсутствующие в первой строке
    for (int i = 0; i < strlen(str2); i++) {
        if (ascii[(int)str2[i]] == 0) {
            output2[index2++] = str2[i];
        }
    }

    output1[index1] = '\0';
    output2[index2] = '\0';
}

int main() {
    mkfifo(FIFO_FILE, 0666);

    int fd = open(FIFO_FILE, O_RDONLY);
    char buffer[BUFFER_SIZE];
    read(fd, buffer, BUFFER_SIZE);
    close(fd);

    char output1[BUFFER_SIZE];
    char output2[BUFFER_SIZE];
    findDifferences(buffer, "", output1, output2);

    int fd2 = open(FIFO_FILE, O_WRONLY);
    write(fd2, output1, strlen(output1));
    close(fd2);

    remove(FIFO_FILE);

    printf("Process 2 finished\n");

    return 0;
}
