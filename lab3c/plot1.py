import matplotlib.pyplot as plt

# Read data from file
data = []
with open('data1.txt', 'r') as file:
    lines = file.readlines()
    for line in lines[1:]:
        values = line.split()
        n = float(values[0])
        times = [float(value) for value in values[1:]]
        data.append((n, times))

# Separate data for each function
functions = [
    "mult_i_j_k",
    "mult_i_k_j",
    "mult_j_i_k",
    "mult_j_k_i",
    "mult_k_i_j",
    "mult_k_j_i"
]

function_data = [[] for _ in range(6)]
for n, times in data:
    for i in range(6):
        function_data[i].append((n, 2*times[i]))

# Plotting
plt.figure(figsize=(12, 6))
for i in range(6):
    plt.plot([n for n, _ in function_data[i]], [time for _, time in function_data[i]], label=functions[i])

plt.xlabel('n')
plt.ylabel('Time in ms')
plt.title('Matrix Multiplication Timings for Different Algorithms')
plt.legend()
plt.grid(True)
plt.savefig('fig1')
plt.show()

