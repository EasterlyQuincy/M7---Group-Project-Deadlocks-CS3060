# Deadlock Demonstration

This project demonstrates the four Coffman conditions that must be present for a deadlock:

1. Mutual Exclusion
2. Hold and Wait
3. No Preemption
4. Circular Wait

The current program is only the starting version. It creates a real deadlock on purpose. The solution sections below are intentionally blank so each group member can later add their assigned fix.

## What Was Added

- A command-line menu with options for the four Coffman conditions, a generic demonstration, and quit.
- Four independent student-owned functions:
  - `MutualExclusion()`
  - `HoldAndWait()`
  - `NoPreemption()`
  - `CircularWait()`
- A controlled `GenericDeadlockDemo()` option that returns to the menu.
- A three-thread Dining Philosophers setup in each Coffman-condition function that deadlocks permanently.
- Boilerplate, the initial example deadlock, and README documentation handled by Brayden Carlson.

## How The Deadlock Works

The program uses three philosophers and three forks. Each fork is represented by a mutex.

- Philosopher 1 locks Fork 1, then waits for Fork 2.
- Philosopher 2 locks Fork 2, then waits for Fork 3.
- Philosopher 3 locks Fork 3, then waits for Fork 1.

A synchronization gate makes sure all three philosophers grab their first fork before any of them tries to grab their second fork. After that:

- Philosopher 1 cannot get Fork 2 because Philosopher 2 is holding it.
- Philosopher 2 cannot get Fork 3 because Philosopher 3 is holding it.
- Philosopher 3 cannot get Fork 1 because Philosopher 1 is holding it.

No philosopher releases their first fork, so all three threads remain blocked. The main thread waits on `join()`, so the menu does not return after selecting options 1 through 4.

## Future Solution: Mutual Exclusion

Assigned group member: Tyler Francom

Notes:

## Future Solution: Hold and Wait

Assigned group member: Quincy Easterly

Notes:

## Future Solution: No Preemption

Assigned group member: Dylan Edwards

Notes:

## Future Solution: Circular Wait

Assigned group member: Jaden Ewell

Notes:
