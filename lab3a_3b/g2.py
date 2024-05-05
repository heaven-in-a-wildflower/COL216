import matplotlib.pyplot as plt
import numpy as np

# Data collected for 4 way associative cache with block size of 8 bytes for different cache sizes.

# Data for each dataset
fifo = {
    64: 0.723322,
    128: 0.515156,
    256: 0.292234,
    512: 0.14626,
    1024: 0.0941625
}

lru = {
    64: 0.71682,
    128: 0.491073,
    256: 0.256879,
    512: 0.127658,
    1024: 0.0803653
}

data_sets = {'LRU': lru, 'FIFO': fifo}

plt.figure(figsize=(6, 4))  # Adjust the figsize for smaller size

# Define colors for each dataset
colors = ['b', 'g', 'r', 'c', 'm']

for idx, (dataset, data) in enumerate(data_sets.items()):
    x = list(data.keys())
    y = list(data.values())
    plt.plot(x, y, label=dataset, marker='o', color=colors[idx])

plt.xlabel('log2(Cache size)')
plt.ylabel('Miss Ratio')
plt.title('Miss Ratio vs Cache Size for different eviction policies')
plt.grid(True)
plt.legend()

# Set the x-axis to logarithmic scale
plt.xscale('log')

# Manually set the tick labels to powers of 2
plt.xticks(list(fifo.keys()), [str(int(x)) for x in np.log2(list(fifo.keys()))])

plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.savefig('plot2.png')
plt.show()
