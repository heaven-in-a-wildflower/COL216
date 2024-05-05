# Cache Simulator 

## Overview
- An elementary cache simulator in C++.

## Features
- Support for both LRU and FIFO policies.
- Configurable cache size, set size, and block size.
- Options for different write policies including write-back and write-through also write policies as write-allocate and write-through.
- Statistics such as load hits, load misses, store hits, store misses, and total cycles are displayed.

## Usage
1. Build the executable using the provided Makefile, Run
```bash
make
```

2. Execute the executable with command-line arguments specifying the cache configuration and workload file.

```css
$ ./cacheSim [CacheSize] [SetSize] [BlockSize] [WritePolicy1] [WritePolicy2] [ReplacementPolicy] < [WorkloadFile]
```
Example:
```python
./cacheSim 256 4 16 write-allocate write-back lru < gcc.trace
```
Sample output:
    
    Total loads: 318197
    Total stores: 197486
    Load hits: 314798
    Load misses: 3399
    Store hits: 188250
    Store misses: 9236
    Total cycles: 9344483
    Miss Ratio: 0.0245015

3. To clean the executable and object files in the directory, Run

```
make clean
```
## Specifications
- `n_sets_in_cache`: No of sets present in the cache.
- `n_blocks_in_set`: associativity of the cache.
- `n_bytes_in_block`: Size of each cache block in bytes.
- `write_allocation`: Write policy for cache writes (write-back or write-through).
- `write_method`: Write policy for cache reads (write-allocate or no-write-allocate).
- `eviction_policy`: Replacement policy for cache eviction (lru or fifo).
- `trace_file`: File containing memory access commands (loads and stores).

## Workload File Format
The workload file should contain memory access commands in the following format:

```css
[l/s] [addr] [garbage]
```

- `l`: Load command.
- `s`: Store command.
- `addr`: Memory address in hexadecimal format.
- `garbage`: Ignored field, can be any integer.

## About the Code

### Code structure 

The code is organized into several classes:

-  `Block`: Represents cache blocks and maintains information about dirty bits and tags.

```cpp
class Block
{
    bool valid;
    unsigned int n_bytes_in_block;
    unsigned int age;
    unsigned int recency;
    bool dirty;
    uint32_t *byte_array;
    friend class Set;
    friend class Cache;
};
```
- `Set`: Implements
```cpp
class Set
{
    unsigned int n_blocks_in_set;
    Block *block_array;
    friend class Cache;
};
```
- `Cache`: Represents the entire cache memory system and manages sets based on the specified replacement policy. 
```cpp
unsigned int n_sets_in_cache;
    unsigned int n_blocks_in_set;
    unsigned int n_bytes_in_block;

    unsigned int words = n_bytes_in_block / 4;

    unsigned int b_sets_in_cache = log2(n_sets_in_cache);
    unsigned int b_blocks_in_set = log2(n_blocks_in_set);
    unsigned int b_bytes_in_block = log2(n_bytes_in_block);

    Set *set_array;

    Write_Method write_method;
    Write_Allocation write_allocation;
    Eviction_Policy eviction_policy;

    // Whenever a block is accessed, this value is assigned to the block's
    // recency and then incremented.
    unsigned int recentness;

    unsigned int loads, stores, load_hits, load_misses, store_hits,
        store_misses, cycles;
```

### Logic for cycle computation 
This denotes the method for cycle calculation for various schemes :-

- Memory access delay (Time to load or store 4 bytes from/to main memory) = 100 cycles

- Cache access delay (Time to load or store 4 bytes from/to cache) = 1 cycle

```txt
		                            Load				    STORE
		                    Miss		    Hit		Miss		    Hit
write_back 
	    write_allocate	    100*b + 1	    1		100*b + 1	    1
		                    + (100*b)** 	    	+ (100*b)**

	    no_write_allocate 	  invalid                 invalid

write_through
	    write_allocate	    100*b + 1	    1		100*b + 100	    100 + 1
			                + 1				 

	    no_write_allocate	100*b + 1	    1		100		        100 + 1

** In case of dirty bit

b = No. of 4-byte words in the block

- It is ambiguous whether after parsing the trace file, the contents of blocks having a dirt bit have to be written back to memory. These cycles have thus not been included but may be included simply using a for loop.

```
