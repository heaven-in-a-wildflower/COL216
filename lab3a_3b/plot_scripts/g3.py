import matplotlib.pyplot as plt
import numpy as np

# For a given block size and given cache size, caches with different associativities were considered(form non associative upto fully associative) and their mean taken.
# Eviction policy was assumed to be lru

# Data for each dataset
data_sets = {
    '512 byte': {
        4: 0.147452,
        8: 0.139546,
        16: 0.129619,
        32: 0.137498,
        64: 0.172451
    },
    '1024 byte': {
        4: 0.106080,
        8: 0.092329,
        16: 0.080844,
        32: 0.083659,
        64: 0.101016
    },
    '2048 byte': {
        4: 0.084407,
        8: 0.065848,
        16: 0.049716,
        32: 0.048946,
        64: 0.057937
    },
    '4096 byte': {
        4: 0.073587,
        8: 0.053521,
        16: 0.033904,
        32: 0.025278,
        64: 0.025671
    },
    '8192 byte': {
        4: 0.067746,
        8: 0.047152,
        16: 0.027792,
        32: 0.018334,
        64: 0.014643
    }
}

plt.figure(figsize=(6, 4))  # Adjust the figsize for smaller size

# Define colors for each dataset
colors = ['b', 'g', 'r', 'c', 'm']

for idx, (dataset, data) in enumerate(data_sets.items()):
    x = list(data.keys())
    y = list(data.values())
    plt.plot(x, y, label=dataset, marker='o', color=colors[idx])

plt.xlabel('log2(Block Size in bytes)')
plt.ylabel('Miss Ratio')
plt.title('Miss Ratio vs Block Size for different cache sizes')
plt.grid(True)
plt.legend()

# Set the x-axis to logarithmic scale
plt.xscale('log')

# Manually set the tick labels to powers of 2
plt.xticks(list(data_sets['1024 byte'].keys()), [str(int(x)) for x in np.log2(list(data_sets['1024 byte'].keys()))])

plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.savefig('plot3.png')
plt.show()
