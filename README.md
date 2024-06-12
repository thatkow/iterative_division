# Iterative Division Program

This repository contains a C++ program that performs iterative division and prints each decimal value. Additionally, it includes a Bash script to automate running the program with different inputs.

## Compilation

To compile the C++ program, use the following command:

```bash
g++ -o iterative_division main.cpp
```

## Running the Program

Once compiled, you can run the program using the generated executable file (`iterative_division`). The program takes four arguments:

1. Numerator (`num1`)
2. Denominator (`num2`)
3. Precision (number of decimal places)
4. Base

For example, to perform iterative division with `num1` as 1, `num2` as 37, precision as 1000, and base as 10, you would run:

```bash
./iterative_division 1 37 1000 10
```

## Automating Execution

To automate running the program with different inputs, you can use the provided Bash script (`run_program_primes.sh`). This script generates the first 100 prime numbers and runs the program for each prime with `num1` as 1, `precision` as 1000, and `base` as 10.

### Setting Execute Permissions

Before running the script, ensure it has executable permissions. You can set this by running:

```bash
chmod +x run_program_primes.sh
```

### Running the Script

To use the script, simply run:

```bash
./run_program_primes.sh
```

This will execute the program for each prime number and print the results in CSV format to stdout.

## Conversational Context

For more information or assistance, refer to the conversation with the AI assistant on OpenAI's platform: [Link to Conversation](https://chatgpt.com/share/d6c23cad-3542-4db9-83d9-04e3e110d218)
