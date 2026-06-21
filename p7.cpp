#include <array>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

void Deadlock();
void MutualExclusion();
void HoldAndWait();
void NoPreemption();
void CircularWait();

void PrintLine(const std::string& message)
{
    static std::mutex outputMutex;

    std::lock_guard<std::mutex> outputLock(outputMutex);
    std::cout << message << std::endl;
}

void Deadlock()
{
    std::cout << "Simulation starting...\n\n";

    std::array<std::mutex, 3> forks;
    std::mutex gateMutex;
    std::condition_variable gateCondition;
    int firstForksHeld = 0;

    auto philosopher = [&](int philosopherNumber, int firstFork, int secondFork) {
        std::unique_lock<std::mutex> firstForkLock(forks[firstFork]);
        PrintLine("Philosopher " + std::to_string(philosopherNumber) +
                  " acquired Fork " + std::to_string(firstFork + 1));

        {
            std::unique_lock<std::mutex> gateLock(gateMutex);
            ++firstForksHeld;

            if (firstForksHeld == 3) {
                gateCondition.notify_all();
            } else {
                gateCondition.wait(gateLock, [&]() {
                    return firstForksHeld == 3;
                });
            }
        }

        PrintLine("Philosopher " + std::to_string(philosopherNumber) +
                  " is waiting for Fork " + std::to_string(secondFork + 1));

        std::unique_lock<std::mutex> secondForkLock(forks[secondFork]);
    };

    std::thread philosopherOne(philosopher, 1, 0, 1);
    std::thread philosopherTwo(philosopher, 2, 1, 2);
    std::thread philosopherThree(philosopher, 3, 2, 0);

    philosopherOne.join();
    philosopherTwo.join();
    philosopherThree.join();
}

void MutualExclusion()
{
    std::cout << "Selected: Mutual Exclusion\n\n";
    Deadlock();
}

void HoldAndWait()
{
    std::cout << "Selected: Hold and Wait\n\n";
    Deadlock();
}

void NoPreemption()
{
    std::cout << "Selected: No Preemption\n\n";
    Deadlock();
}

void CircularWait()
{
    std::cout << "Selected: Circular Wait\n\n";
    Deadlock();
}

int main()
{
    while (true) {
        std::cout << "Deadlock Demonstration\n\n"
                  << "1. Mutual Exclusion\n"
                  << "2. Hold and Wait\n"
                  << "3. No Preemption\n"
                  << "4. Circular Wait\n"
                  << "5. Quit\n\n"
                  << "Enter your selection: ";

        std::string selection;
        if (!std::getline(std::cin, selection)) {
            return 0;
        }

        if (selection.size() != 1 || selection[0] < '1' || selection[0] > '5') {
            std::cout << "\nInvalid selection. Please enter a number from 1 to 5.\n\n";
            continue;
        }

        std::cout << '\n';

        switch (selection[0]) {
        case '1':
            MutualExclusion();
            break;
        case '2':
            HoldAndWait();
            break;
        case '3':
            NoPreemption();
            break;
        case '4':
            CircularWait();
            break;
        case '5':
            return 0;
        }
    }
}
