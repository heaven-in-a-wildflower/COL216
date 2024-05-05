#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

// void indent(int i)
// {
//     string spaces(i, '\t');
//     cout << spaces;
// }

enum Write_Method
{
    write_back,
    write_through
};

enum Write_Allocation
{
    write_allocate,
    no_write_allocate
};

enum Eviction_Policy
{
    fifo,
    lru
};

class Block
{
    // For this assignment, storing the address is suffciient as we are not
    // concerned with values
    bool valid;
    unsigned int n_bytes_in_block;
    unsigned int age;
    unsigned int recency;
    bool dirty;

    // Change this to a pointer to a pair or vector of uint_32 to store values
    // alongside addresses pair<uint32_t,uint32_t>* byte_array
    uint32_t *byte_array;

    // Data structure to store bytes which must be written with new values
    // vector<pair<uint32_t, uint32_t>> *store_values;
    // may have to modify the destructor

    friend class Set;
    friend class Cache;

  public:
    Block()
        : n_bytes_in_block(0), byte_array(nullptr), age(0), recency(0),
          valid(false), dirty(false){};

    Block(int _n_byes_in_block, unsigned int *_byte_array)
        : n_bytes_in_block(_n_byes_in_block), byte_array(_byte_array), age(0),
          recency(0), valid(false), dirty(false){};

    ~Block() { delete[] byte_array; }
};

class Set
{
    unsigned int n_blocks_in_set;
    Block *block_array;
    friend class Cache;

  public:
    Set() : n_blocks_in_set(0), block_array(nullptr){};

    Set(int _n_blocks_in_set, Block *_block_array)
        : n_blocks_in_set(_n_blocks_in_set), block_array(_block_array){};

    ~Set() { delete[] block_array; }
};

class Cache
{
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

  public:
    Cache(unsigned int _n_sets_in_cache, unsigned int _n_blocks_in_set,
          unsigned int _n_bytes_in_block, Write_Method _write_method,
          Write_Allocation _write_allocation, Eviction_Policy _eviction_policy)
        : n_sets_in_cache(_n_sets_in_cache), n_blocks_in_set(_n_blocks_in_set),
          n_bytes_in_block(_n_bytes_in_block), set_array(nullptr), loads(0),
          stores(0), load_hits(0), load_misses(0), store_hits(0),
          store_misses(0), cycles(0), recentness(0),
          write_method(_write_method), write_allocation(_write_allocation),
          eviction_policy(_eviction_policy)
    {
        set_array = new Set[n_sets_in_cache];
        for (unsigned int i = 0; i < n_sets_in_cache; i++)
        {
            set_array[i].block_array = new Block[n_blocks_in_set];
            for (unsigned int j = 0; j < n_blocks_in_set; j++)
            {
                set_array[i].block_array[j].byte_array =
                    new uint32_t[n_bytes_in_block]();
                // This initialises all adrresses to 0
            }
        }
    };

    ~Cache() { delete[] set_array; }

    void updateAges()
    {
        for (unsigned int i = 0; i < n_sets_in_cache; i++)
        {
            for (unsigned int j = 0; j < n_blocks_in_set; j++)
            {
                set_array[i].block_array[j].age++;
            }
        }
    }

    // In case where memory is modelled, we need to copy the contents of the
    // block to memory before deallocating the byte_array.
    void evictBlock(Block &block)
    {
        if (write_method == write_back)
        {
            if (block.dirty == true)
            {
                cycles += (100 * words);
            }
        }
        delete[] block.byte_array;
    }

    void loadBlock(unsigned int &set_in_cache, Block *block, bool set_dirty)
    {
        // Check if any invalid block is present in the cache, if so replace.
        // Otherwise execute eviction strategy
        for (unsigned int i = 0; i < n_blocks_in_set; i++)
        {
            if (set_array[set_in_cache].block_array[i].valid == false)
            {
                evictBlock(set_array[set_in_cache].block_array[i]);
                set_array[set_in_cache].block_array[i] = *block;
                if (set_dirty)
                    set_array[set_in_cache].block_array[i].dirty = true;
                return;
            }
        }

        // Eviction strategies
        if (eviction_policy == fifo)
        {
            // cout << "pikachu" << endl;
            // Replace the oldest block
            unsigned int oldest = 0;
            for (unsigned int i = 1; i < n_blocks_in_set; i++)
            {
                if (set_array[set_in_cache].block_array[i].age >
                    set_array[set_in_cache].block_array[oldest].age)
                {
                    oldest = i;
                }
            }
            evictBlock(set_array[set_in_cache].block_array[oldest]);
            set_array[set_in_cache].block_array[oldest] = *block;
            if (set_dirty)
                set_array[set_in_cache].block_array[oldest].dirty = true;
        }

        else if (eviction_policy == lru)
        {
            // Replace least recently accessed block
            unsigned int least_recent = 0;
            for (unsigned int i = 1; i < n_blocks_in_set; i++)
            {
                // cout << "base addr: " << block->byte_array[0] << " "
                //      << "recency: " << block->recency << endl;
                if (set_array[set_in_cache].block_array[i].recency <
                    set_array[set_in_cache].block_array[least_recent].recency)
                {
                    least_recent = i;
                }
            }
            evictBlock(set_array[set_in_cache].block_array[least_recent]);
            set_array[set_in_cache].block_array[least_recent] = *block;
            if (set_dirty)
                set_array[set_in_cache].block_array[least_recent].dirty = true;
        }
    }

    // Need to pass the byte-value pair to this function for writing in case of
    // write_through and updating the vector for write_back
    void writeBlock(Block *block)
    {
        if (write_method == write_back)
        {
            block->dirty = true;
        }
        else if (write_method == write_through)
        {
            // Logic to actually write the value
        }
    }

    void processAddress(char op, uint32_t addr)
    {
        updateAges();

        unsigned int byte_in_block = addr & ((1 << b_bytes_in_block) - 1);

        unsigned int set_in_cache =
            (addr & ((1 << (b_bytes_in_block + b_sets_in_cache)) - 1)) >>
            b_bytes_in_block;

        uint32_t base_addr = addr & ((~0) << b_bytes_in_block);

        int block_in_set = -1;
        for (int i = 0; i < n_blocks_in_set; i++)
        {
            if (set_array[set_in_cache].block_array[i].valid == true &&
                set_array[set_in_cache].block_array[i].byte_array[0] ==
                    base_addr)
            {
                block_in_set = i;
                break;
            }
        }

        // Miss
        if (block_in_set == -1)
        {
            // Develop block
            uint32_t *byte_array = new uint32_t[n_bytes_in_block];
            for (unsigned int i = 0; i < n_bytes_in_block; i++)
            {
                byte_array[i] = base_addr + static_cast<uint32_t>(i);
            }
            Block *block = new Block(n_bytes_in_block, byte_array);
            block->valid = true;
            block->recency = ++recentness;

            if (op == 'l')
            {
                loads++;
                load_misses++;
                loadBlock(set_in_cache, block, false);

                cycles += (100 * words + 1);
            }
            else
            {
                stores++;
                store_misses++;

                if (write_method == write_back &&
                    write_allocation == write_allocate)
                {
                    cycles += (100 * words + 1);
                    loadBlock(set_in_cache, block, true);
                }

                else if (write_method == write_through &&
                         write_allocation == write_allocate)
                {
                    cycles += (100 * words + 100 + 1);
                    loadBlock(set_in_cache, block, false);
                }

                else if (write_method == write_through &&
                         write_allocation == no_write_allocate)
                {
                    cycles += 100;
                }
                // writeBlock(block);
            }
        }

        // Hit
        else
        {
            Block *block = &set_array[set_in_cache].block_array[block_in_set];
            block->recency = ++recentness;

            if (op == 'l')
            {
                loads++;
                load_hits++;
                cycles += 1;
            }
            else
            {
                stores++;
                store_hits++;
                if (write_method == write_back &&
                    write_allocation == write_allocate)
                {
                    cycles += 1;
                    block->dirty = true;
                }
                if (write_method == write_through)
                {
                    cycles += (100 + 1);
                }
                // writeBlock(block);
            }
        }
    }

    // void readFromFile(const string &filename)
    // {
    //     ifstream file(filename);
    //     string line;
    //     std::ofstream outputFile("output.txt");
    //     if (file.is_open())
    //     {
    //         while (getline(file, line))
    //         {
    //             istringstream iss(line);
    //             char op;
    //             uint32_t addr;
    //             if (iss >> op >> hex >> addr)
    //             {
    //                 if (op == 'l' or op == 's')
    //                 {
    //                     processAddress(op, addr);
    //                     // outputFile << op << " "
    //                     //            << "0x" << hex << addr << endl;
    //                     // if (op == 'l')
    //                     // {
    //                     //     outputFile << "load ";
    //                     // }
    //                     // else if (op == 's')
    //                     // {
    //                     //     outputFile << "store ";
    //                     // }
    //                     // if (p.first == 0)
    //                     // {
    //                     //     outputFile << "miss : ";
    //                     // }
    //                     // else
    //                     // {
    //                     //     outputFile << "hit : ";
    //                     // }
    //                     // outputFile << "cycles =" << dec << cycles << endl;
    //                 }
    //                 else
    //                 {
    //                     cerr << "Invalid operation" << op << endl;
    //                 }
    //             }
    //             else
    //             {
    //                 cerr << "Invalid line format" << endl;
    //             }
    //         }
    //         outputFile.close();
    //     }
    //     else
    //         cerr << "Unable to open file" << endl;
    // }

    void summary()
    {
        cout << "Total loads: " << loads << endl;
        cout << "Total stores: " << stores << endl;
        cout << "Load hits: " << load_hits << endl;
        cout << "Loads misses: " << load_misses << endl;
        cout << "Store hits: " << store_hits << endl;
        cout << "Store misses: " << store_misses << endl;
        cout << "Total Cycles: " << cycles << endl;
        cout << "Miss Ratio: "
             << double(load_misses + store_misses) / double(loads + stores)
             << endl;
        // cout << "Write Miss Ratio: "
        //      << double(store_misses) / double(stores)
        //      << endl;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 7)
    {
        std::cerr << "Usage: " << argv[0]
                  << " <n_sets_in_cache> <n_blocks_in_set> <n_bytes_in_block> "
                     "<write_method> <write_allocation> <eviction_policy>"
                  << std::endl;
        return 1;
    }

    unsigned int n_sets_in_cache = std::stoi(argv[1]);
    unsigned int n_blocks_in_set = std::stoi(argv[2]);
    unsigned int n_bytes_in_block = std::stoi(argv[3]);

    string _write_allocation = argv[4];
    string _write_method = argv[5];
    string _evicttion_policy = argv[6];
    int x1 = (_write_allocation == "write-allocate") ? 0 : 1;
    int x2 = (_write_method == "write-back") ? 0 : 1;
    int x3 = (_evicttion_policy == "fifo") ? 0 : 1;

    Write_Method write_method =
               static_cast<Write_Method>(x2);
    Write_Allocation write_allocation =
        static_cast<Write_Allocation>(x1);
    Eviction_Policy eviction_policy =
        static_cast<Eviction_Policy>(x3);

    Cache *cache = new Cache(n_sets_in_cache, n_blocks_in_set, n_bytes_in_block,
                             write_method, write_allocation, eviction_policy);
    
    char op;
    uint32_t addr;
    int garbage;
    while(cin >> op >> hex >> addr >> garbage)
    {
        cache->processAddress(op,addr);
    }
    cache->summary();
    delete cache;
    cache = nullptr;
    return 0;
}
