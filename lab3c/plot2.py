import matplotlib.pyplot as plt

# Read data from file
data = []
with open('data2.txt', 'r') as file:
    lines = file.readlines()
    for line in lines[1:]:
        values = line.split()
        n = float(values[0])
        times = [float(value) for value in values[1:]]
        data.append((n, times))

# Separate data for each function
functions = [
    "transpose_i_j",
    "transpose_j_i"
]

function_data = [[] for _ in range(2)]
for n, times in data:
    for i in range(2):
        function_data[i].append((n, times[i]))

# Plotting
plt.figure(figsize=(12, 6))
for i in range(2):
    plt.plot([n for n, _ in function_data[i]], [time for _, time in function_data[i]], label=functions[i])

plt.xlabel('n')
plt.ylabel('Time in microsecs')
plt.title('Transpose Timings for Different Algorithms')
plt.legend()
plt.grid(True)
plt.savefig('fig2')
plt.show()

