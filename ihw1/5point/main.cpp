#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 5000
#define FIFO_FILE1 "fifo1"
#define FIFO_FILE2 "fifo2"

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

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s input1.txt input2.txt output1.txt output2.txt\n", argv[0]);
        return 1;
    }

    mkfifo(FIFO_FILE1, 0666);
    mkfifo(FIFO_FILE2, 0666);

    pid_t pid1 = fork();

    if (pid1 == 0) {
        execlp("./process2", "./process2", NULL);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        execlp("./process3", "./process3", NULL);
    }

    char input1[BUFFER_SIZE];
    char input2[BUFFER_SIZE];
    char output1[BUFFER_SIZE];
    char output2[BUFFER_SIZE];

    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");

    fread(input1, sizeof(char), BUFFER_SIZE, file1);
    fread(input2, sizeof(char), BUFFER_SIZE, file2);

    int fd1 = open(FIFO_FILE1, O_WRONLY);
    write(fd1, input1, strlen(input1) + 1);
    write(fd1, input2, strlen(input2) + 1);
    close(fd1);

    int fd2 = open(FIFO_FILE2, O_RDONLY);
    read(fd2, output1, BUFFER_SIZE);
    read(fd2, output2, BUFFER_SIZE);
    close(fd2);

    FILE *file3 = fopen(argv[3], "w");
    FILE *file4 = fopen(argv[4], "w");

    fwrite(output1, sizeof(char), strlen(output1), file3);
    fwrite(output2, sizeof(char), strlen(output2), file4);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);

    unlink(FIFO_FILE1);
    unlink(FIFO_FILE2);

    printf("All processes finished\n");

    return 0;
}
