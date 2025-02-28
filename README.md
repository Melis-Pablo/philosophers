# Philosophers

## 🍝 Project Overview

Philosophers is a project focused on the fundamentals of threading processes, demonstrating the classic dining philosophers problem. This implementation showcases solutions to concurrency challenges including deadlocks, resource sharing, and process synchronization using threads and mutexes.

## 🧠 The Dining Philosophers Problem

The dining philosophers problem is a classic example in computer science used to illustrate synchronization issues and techniques for resolving them:

- N philosophers sit at a round table with N forks
- Each philosopher needs two forks to eat (left and right)
- Philosophers alternate between eating, thinking, and sleeping
- The challenge is to design a concurrent solution that avoids:
  - **Deadlock**: Where all philosophers hold one fork and wait indefinitely for another
  - **Starvation**: Where philosophers are unable to eat and eventually die

## ✨ Features

### Core Implementation
- Multi-threaded simulation with one thread per philosopher
- Precise timing mechanisms for eating, sleeping, and monitoring death
- Resource management using mutexes for fork access control
- Death detection system with configurable time limits
- Clean termination when simulation goals are met or a philosopher dies

### Visualization and Monitoring
- Real-time status reporting with timestamps
- Color-coded console output for different philosopher states
- Death detection within 10ms of occurrence
- Detailed statistics tracking for each philosopher

## 💻 Usage

### Compilation

```bash
# Clone the repository
git clone https://github.com/Melis-Pablo/philosophers.git
cd philosophers

# Compile the threaded version
cd philo
make

```

### Running the Simulation

```bash
# Format:
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

# Examples:

# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# 4 philosophers, 410ms to die, 200ms to eat, 200ms to sleep, each must eat 5 times
./philo 4 410 200 200 5
```

### Parameter Details

- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds philosophers spend sleeping
- `number_of_times_each_philosopher_must_eat`: Optional - simulation stops after all philosophers eat this many times

## 🔧 Technical Implementation

### Concurrency Approach

The main implementation uses threads and mutexes:
- Each philosopher runs as an independent thread
- Forks are protected by mutexes to prevent simultaneous access
- A monitoring thread checks for deaths and simulation completion

### Deadlock Prevention

Several strategies are implemented to prevent deadlocks:
- **Even-Odd Approach**: Even-numbered philosophers reach for right fork first, odd-numbered for left
- **Resource Allocation**: Careful management of fork acquisition and release
- **Timeout Mechanism**: Philosophers release resources if they can't acquire both forks within a specified time

### Time Management

Precise time management is critical to this implementation:
- High-resolution timestamps using `gettimeofday()`
- Efficient sleep mechanisms that don't block thread execution
- Time difference calculations that maintain microsecond precision

## 📊 Performance Analysis

Various configurations were tested to measure the robustness of the implementation:

| Philosophers | Time to Die | Time to Eat | Time to Sleep | Outcome |
|--------------|-------------|-------------|--------------|---------|
| 5            | 800ms       | 200ms       | 200ms        | No deaths |
| 5            | 600ms       | 200ms       | 200ms        | No deaths |
| 4            | 410ms       | 200ms       | 200ms        | No deaths |
| 4            | 310ms       | 200ms       | 100ms        | Deaths occur |
| 200          | 800ms       | 200ms       | 200ms        | No deaths |
| 1            | 800ms       | 200ms       | 200ms        | Death at 800ms |

## 📝 Learning Outcomes

This project provided in-depth experience with:

- **Concurrent Programming**: Creating and managing threads
- **Synchronization Mechanisms**: Using mutexes effectively
- **Race Condition Prevention**: Designing code to avoid data races
- **Resource Management**: Handling shared resources to prevent deadlocks
- **Real-time Monitoring**: Implementing monitoring without affecting performance
- **Process vs. Thread Models**: Understanding the differences and trade-offs between them

## 🐛 Common Issues and Solutions

- **Deadlocks**: Resolved through careful ordering of mutex acquisitions
- **Performance Bottlenecks**: Optimized time measurement and status checking
- **Race Conditions**: Protected shared data with mutexes
- **Death Detection Accuracy**: Implemented high-precision timing mechanisms
- **Resource Cleanup**: Proper destruction of threads, and mutexes

## 📚 Resources

For detailed project requirements, see the [philosophers.md](philosophers.md) file.

---

*This project is part of the 42 School Common Core curriculum.*