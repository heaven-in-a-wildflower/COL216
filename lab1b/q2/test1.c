#include <stdio.h>

// Inline assembly to read the timestamp counter (TSC)
unsigned long rdtsc()
{
    unsigned int low, high;
    asm volatile("rdtsc" : "=a"(low), "=d"(high));
    return ((unsigned long)high << 32) | low;
}

int sum(int n, int acc)
{
    if (n > 0)
        return sum(n - 1, acc + n);
    else
        return acc;
}

int main()
{
    unsigned long start_cycles, end_cycles;
    int n;

    // Input a number from the user
    printf("Enter a number (n): ");
    scanf("%d", &n);

    // Measure start cycles
    start_cycles = rdtsc();

    // Execute the code you want to measure
    int result = sum(n, 0);

    // Measure end cycles
    end_cycles = rdtsc();

    printf("Result: %d\n", result);
    printf("Total cycles taken by CPU: %lu\n", end_cycles - start_cycles);

    return 0;
}
