# 42Philosophers

## Description

The **42Philosophers** project is an implementation of the classic "Dining Philosophers" problem, which is a well-known synchronization problem in computer science. The problem involves a group of philosophers who sit at a circular table with a fork placed between each pair of adjacent philosophers. Each philosopher must alternately think and eat, but to eat, a philosopher needs to acquire both the left and right forks. The challenge is to design a solution that ensures no deadlock or starvation while maintaining proper synchronization between philosophers.

This project is developed as part of the 42 curriculum to demonstrate the principles of concurrency, synchronization, and resource sharing in a multithreaded environment.

## Features

- **Concurrency**: Implements concurrent philosophers using threads.
- **Synchronization**: Uses mutexes to prevent deadlock and ensure proper resource sharing.
- **Deadlock Prevention**: Ensures that no philosopher is indefinitely waiting for resources.
- **Starvation Prevention**: Guarantees that every philosopher gets a chance to eat.

## Getting Started

### Prerequisites

- C/C++ compiler (e.g., GCC)
- Make utility
- Basic understanding of multithreading and synchronization

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/kuba2901/42_philosophers.git
   ```

2. Navigate to the project directory:

   ```bash
   cd 42_philosophers
   ```

3. Compile the project:

   ```bash
   make
   ```

## Running the Program

### Input Format

The program expects 4 or 5 arguments when running. The arguments should be provided in the following order:

1. **Number of philosophers**: An integer representing the total number of philosophers at the table.
2. **Time to die**: An integer representing the time a philosopher will die if he doesn’t eat within this time.
3. **Time to eat**: An integer representing the time it takes for a philosopher to eat.
4. **Time to sleep**: An integer representing the time it takes for a philosopher to sleep.
5. **Number of meals** *(optional)*: An integer representing the number of times each philosopher needs to eat before the program terminates. If omitted, the program will use a default value.

### Example Input

```bash
./philosophers 5 800 200 200 7
```

### Instructions

1. **Check Input Arguments**

   The program validates the number of arguments provided. It expects exactly 4 or 5 arguments. If the number of arguments is incorrect, the program will display an error message and terminate.

2. **Valid Argument Values**

   - **Number of philosophers**: Must be a positive integer greater than 0.
   - **Time to die**: Must be a positive integer representing the maximum time a philosopher can wait before eating.
   - **Time to eat**: Must be a positive integer representing how long it takes to eat.
   - **Time to sleep**: Must be a positive integer representing how long it takes to sleep.
   - **Number of meals** (optional): Must be a positive integer. If not provided, the default number of meals is used.

3. **Running the Program**

   To run the program with valid input arguments, use the following command:

   ```bash
   ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
   ```

   For example:

   ```bash
   ./philosophers 5 800 200 200 7
   ```

   This command starts the simulation with 5 philosophers, where each philosopher will die if not fed within 800 milliseconds, will take 200 milliseconds to eat, 200 milliseconds to sleep, and all philosophers will need to eat 7 times before the program ends.

### Error Handling

- **Invalid Number of Arguments**: If the number of arguments is not 4 or 5, the program will display an error message:

  ```
  Error: Invalid number of arguments. Expected 4 or 5 arguments.
  ```

- **Invalid Argument Values**: If any argument is not a positive integer, the program will display an error message:

  ```
  Error: All arguments must be positive integers.
  ```

## Project Structure

- `main.c`: Entry point of the program.
- `philosopher.c`: Contains the implementation of philosopher behavior.
- `fork.c`: Contains the implementation of fork management and synchronization.
- `Makefile`: Build script for compiling the project.
