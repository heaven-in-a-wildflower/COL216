import matplotlib.pyplot as plt
import numpy as np

# Data collected for non-associative to fully associative caches for different cache sizes.
# Block size was fixed at 8 bytes
# write_back, write_allocate, lru cache

# Data for each dataset
data_sets = {
    '64 byte': {
        8: 0.719818,
        4: 0.71682,
        2: 0.697634,
        1: 0.69558
    },
    '128 byte': {
        16: 0.519893,
        8: 0.519459,
        4: 0.491073,
        2: 0.471516,
        1: 0.488977
    },
    '256 byte': {
        32: 0.215539,
        16: 0.224355,
        8: 0.246477,
        4: 0.256879,
        2: 0.263757,
        1: 0.294522
    },
    '512 byte': {
        64: 0.120504,
        32: 0.122073,
        16: 0.12256,
        8: 0.123661,
        4: 0.127658,
        2: 0.14307,
        1: 0.217298
    },
    '1024 byte': {
        128: 0.0742782,
        64: 0.0745012,
        32: 0.0755774,
        16: 0.0761708,
        8: 0.0779801,
        4: 0.0803653,
        2: 0.101367,
        1: 0.178394
    }
}

plt.figure(figsize=(6, 4))  # Adjust the figsize for smaller size

# Define colors for each dataset
colors = ['b', 'g', 'r', 'c', 'm']

for idx, (dataset, data) in enumerate(data_sets.items()):
    x = list(data.keys())
    y = list(data.values())
    plt.plot(x, y, label=dataset, marker='o', color=colors[idx])

plt.xlabel('Associativity')
plt.ylabel('Miss Ratio')
plt.title('Miss Ratio vs Associativity for different cache sizes')
plt.grid(True)
plt.legend()

# Set the x-axis to logarithmic scale
plt.xscale('log')

# Manually set the tick labels to powers of 2
plt.xticks(list(data_sets['1024 byte'].keys()), [str(int(x)) for x in np.log2(list(data_sets['1024 byte'].keys()))])

plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.savefig('plot1.png')
plt.show()
