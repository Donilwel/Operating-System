#include <iostream>
#include <signal.h>
#include <sys/types.h>

std::string received_bits;
std::string bit = "";
pid_t pid_transmitter;

void handler(int signum) {
    if (signum == SIGUSR1) {
        std::cout << 0;
        bit = "0";
    } else if (signum == SIGUSR2) {
        std::cout << 1;
        bit = "1";
    }
    received_bits += bit;
    kill(pid_transmitter, SIGUSR1);
}

void sigintHandler(int signum) {
    std::cout << std::endl;
    int received_number = std::stoul(received_bits, 0, 2);
    std::cout << "Принятое число: " << (int)received_number << std::endl;
    exit(0);
}

int main() {
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    signal(SIGINT, sigintHandler);
    std::cout << getpid() << std::endl;

    std::cout << "Введите PID передатчика: ";
    std::cin >> pid_transmitter;


    while (true) {
        pause();
    }

    return 0;
}
