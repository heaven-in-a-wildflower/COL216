import matplotlib.pyplot as plt
import numpy as np

# Write allocate and eviction policy parameters were varied for 4 way associative with block size of 8 bytes for different cache sizes.

miss_ratio_data = {
    'Write Allocate with fifo': {
        256: 0.292234,
        512: 0.14626,
        1024: 0.0941625,
        2048: 0.0688601,
        4096: 0.0567112
    },
    'Write Allocate with lru': {
        256: 0.256879,
        512: 0.127658,
        1024: 0.0803653,
        2048: 0.0590188,
        4096: 0.0506183
    },
    'No Write Allocate with fifo': {
        256: 0.341064,
        512: 0.193951,
        1024: 0.138548,
        2048: 0.115203,
        4096: 0.0998365
    },
    'No write Allocate with lru': {
        256: 0.30389,
        512: 0.172174,
        1024: 0.123582,
        2048: 0.101442,
        4096: 0.0940675
    }
}

write_miss_ratio_data = {

    'Write Allocate with fifo': {
        256: 0.280172,
        512: 0.16468,
        1024: 0.125979,
        2048: 0.108717,
        4096: 0.100275
    },
    'Write Allocate with lru': {
        256: 0.23509,
        512: 0.148147,
        1024: 0.115411,
        2048: 0.101177,
        4096: 0.0952017
    },
    'No Write Allocate with fifo': {
        256: 0.358213,
        512: 0.269325,
        1024: 0.232497,
        2048: 0.216506,
        4096: 0.196222
    },
    'No write Allocate with lru': {
        256: 0.328631,
        512: 0.249182,
        1024: 0.216653,
        2048: 0.19487,
        4096: 0.18974
    }
}

plt.figure(figsize=(12, 6))

# Plot for miss ratio data
for idx, (dataset, data) in enumerate(miss_ratio_data.items()):
    x = list(data.keys())
    y = list(data.values())
    plt.plot(x, y, label=f'{dataset}', marker='o', linestyle='-', color=f'C{idx}')

plt.xlabel('log2(Cache Size in bytes)')
plt.ylabel('Write Miss Ratio')
plt.title('Miss Ratio vs Cache Size for Different Allocation and Eviction Policies')
plt.grid(True)
plt.legend()

# Set the x-axis to logarithmic scale
plt.xscale('log')

# Manually set the tick labels to powers of 2
plt.xticks(list(miss_ratio_data['No write Allocate with lru'].keys()), [str(int(x)) for x in np.log2(list(miss_ratio_data['No write Allocate with lru'].keys()))])

# Save and show the plot
plt.tight_layout()
plt.savefig('plot4.png')
plt.show()

plt.figure(figsize=(12, 6))

# Plot for write miss ratio data
for idx, (dataset, data) in enumerate(write_miss_ratio_data.items()):
    x = list(data.keys())
    y = list(data.values())
    plt.plot(x, y, label=f'{dataset}', marker='s', linestyle='--', color=f'C{idx}')

plt.xlabel('log2(Cache Size in bytes)')
plt.ylabel('Write Miss Ratio')
plt.title('Write Miss Ratio vs Cache Size for Different Allocation and Eviction Policies')
plt.grid(True)
plt.legend()

# Set the x-axis to logarithmic scale
plt.xscale('log')

# Manually set the tick labels to powers of 2
plt.xticks(list(write_miss_ratio_data['No write Allocate with lru'].keys()), [str(int(x)) for x in np.log2(list(write_miss_ratio_data['No write Allocate with lru'].keys()))])

# Save and show the plot
plt.tight_layout()
plt.savefig('plot5.png')
plt.show()
