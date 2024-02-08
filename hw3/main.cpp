#include <iostream>
#include <unistd.h>


//constexpr size_t UINT64_MAX = 18446744073709551615ULL;

size_t computeFactorial(size_t number) {
    size_t result = 1;

    for (size_t i = 1; i <= number; ++i) {
        if (UINT64_MAX / i < result) {
            return 0;
        }
        result *= i;
    }

    return result;
}

size_t computeFibonacci(size_t number) {
    if (number <= 1) {
        return number;
    }

    size_t a = 0;
    size_t b = 1;

    for (size_t i = 2; i <= number; ++i) {
        if (UINT64_MAX - b < a) {
            return 0;
        }
        size_t c = a + b;
        a = b;
        b = c;
    }

    return b;
}

int main() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    size_t number;
    std::cout << "Enter a non-negative number: ";
    std::cin >> number;

    pid_t chpid = fork();

    if (!chpid) { // Child process
        size_t factorial = computeFactorial(number);
        if (factorial == 0) {
            std::cout << "Я - ребенок, мой_id=" << pid << ", родитель_id=" << ppid << ", ребенок_id=" << chpid << ", результат факториала = " <<  '\n';
        } else {
            std::cout << "Я - ребенок, мой_id="  << pid << ", родитель_id=" << ppid << ", ребенок_id=" << chpid << ", результат факториала = " << factorial << '\n';
        }
    } else { // Parent process
        size_t fibResult = computeFibonacci(number);
        if (fibResult == 0) {
            std::cout << "I am PARENT, my_id=" << pid << ", parent_id=" << ppid << ", ребенок_id=" << chpid << ", результат (n-го числа Фибоначчи) = " << '\n';
        } else {
            std::cout << "I am PARENT, my_id=" << pid << ", parent_id=" << ppid << ", ребенок_id=" << chpid << ", результат (n-го числа Фибоначчи) =" << fibResult << '\n';
        }
    }

    sleep(1); // To format output

    if (chpid) { // Parent process displays content of the current working directory
        std::cout << "Content of the current working directory: " << '\n';
        system("ls");
    }

    return 0;
}
