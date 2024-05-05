import subprocess


def run_c_program(input_value):
    command = ["./test1"]  # Replace with the actual name of your compiled C program
    process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    # Input the value to the C program
    process.stdin.write(f"{input_value}\n")
    process.stdin.flush()

    # Get the output and return code
    output, _ = process.communicate()

    # Extract the total cycles from the output
    lines = output.split('\n')
    cycles_line = next(line for line in lines if line.startswith("Total cycles taken by CPU:"))
    cycles = int(cycles_line.split(":")[1])

    return cycles

# Run the C program 10 times for inputs 10, 15, and 20
inputs = [500,1000,2000,3000,4000,5000,6000,7000,8000,9000]
num_runs = 1000

mean_cycles = {}

for input_value in inputs:    
    total_cycles = 0
    for _ in range(num_runs):
        cycles = run_c_program(input_value)
        total_cycles += cycles

    mean_cycles[input_value] = total_cycles / num_runs

print("Mean Cycles:")
for input_value, mean in mean_cycles.items():
    print(f"Input {input_value}: {mean} cycles")
