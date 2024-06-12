#!/bin/bash

# Function to check if a number is prime
is_prime() {
    num=$1
    for ((i=2; i*i<=num; i++)); do
        if ((num % i == 0)); then
            return 1
        fi
    done
    return 0
}

# Main function to generate the first 100 prime numbers
generate_primes() {
    count=0
    num=2
    while ((count < 100)); do
        if is_prime "$num"; then
            echo -n "$num "
            ((count++))
        fi
        ((num++))
    done
}

# Generate the first 100 primes
primes=$(generate_primes)

# Run the program with each prime as num2
precision=1000
base=10
numerator="1"

# Print header to CSV
echo "Prime,Result"

for prime in $primes; do
    result=$(./iterative_division "$numerator" "$prime" "$precision" "$base")
    echo "$prime,$result"
done

