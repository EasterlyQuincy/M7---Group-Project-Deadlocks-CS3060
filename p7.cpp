#include <array>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

// Boilerplate and initial example deadlock handled by Brayden Carlson.
// README documentation handled by Brayden Carlson.

void MainMenu();
void MutualExclusion();
void HoldAndWait();
void NoPreemption();
void CircularWait();
void GenericDeadlockDemo();

// Shared helpers
void PrintLine(const std::string& message)
{
    static std::mutex outputMutex;

    std::lock_guard<std::mutex> outputLock(outputMutex);
    std::cout << message << std::endl;
}

// Mutual Exclusion
// Assigned group member: Tyler Francom
void MutualExclusion()
{
    std::cout << "Selected: Mutual Exclusion\n\n";
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

// Hold and Wait
// Assigned group member: Quincy Easterly
void HoldAndWait()
{
    std::cout << "Selected: Hold and Wait\n\n";
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

// No Preemption
// Assigned group member: Dylan Edwards
void NoPreemption()
{
    std::cout << "Selected: No Preemption\n\n";
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

// Circular Wait
// Assigned group member: Jaden Ewell
void CircularWait()
{
    std::cout << "Selected: Circular Wait\n\n";
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

// Generic Deadlock Demonstration
void GenericDeadlockDemo()
{
    std::cout << "Generic Deadlock Demonstration\n\n"
              << "Philosopher 1 holds Fork 1 and waits for Fork 2\n"
              << "Philosopher 2 holds Fork 2 and waits for Fork 3\n"
              << "Philosopher 3 holds Fork 3 and waits for Fork 1\n\n";

    for (int cycle = 1; cycle <= 10; ++cycle) {
        std::cout << "Cycle " << cycle << ": No philosopher can proceed.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    std::cout << "\nNo progress occurred during the demonstration.\n"
              << "Returning to the main menu.\n\n";
}

// Main Menu
void MainMenu()
{
    while (true) {
        std::cout << "Deadlock Demonstration\n\n"
                  << "1. Mutual Exclusion\n"
                  << "2. Hold and Wait\n"
                  << "3. No Preemption\n"
                  << "4. Circular Wait\n"
                  << "5. Generic Deadlock Demonstration\n"
                  << "6. Quit\n\n"
                  << "Enter your selection: ";

        std::string selection;
        if (!std::getline(std::cin, selection)) {
            return;
        }

        if (selection.size() != 1 || selection[0] < '1' || selection[0] > '6') {
            std::cout << "\nInvalid selection. Please enter a number from 1 to 6.\n\n";
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
            GenericDeadlockDemo();
            break;
        case '6':
            return;
        }
    }
}

int main()
{
    MainMenu();
    return 0;
}
