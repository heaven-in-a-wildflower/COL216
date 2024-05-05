import subprocess
import math

# Different versions of this program were considered to fetch the data

def find_factorizations(x, y):
    """
    Finds the possible factorizations of x/y where both factors are powers of 2.
    
    Args:
        x (int): The first power of 2 number.
        y (int): The second power of 2 number.
    
    Returns:
        list: A list of tuples representing the possible factorizations.
    """
    # Calculate the ratio x/y
    ratio = x / y
    
    # Find the exponent of the ratio
    exponent = int(math.log2(ratio))
    
    # Generate the possible factorizations
    factorizations = []
    for i in range(exponent + 1):
        factor1 = 2 ** i
        factor2 = 2 ** (exponent - i)
        factorizations.append((factor1, factor2))
    
    return factorizations

# Path to the compiled C++ program
cpp_program = "./cache"

# Total cache size (bytes) and number of sets (both powers of 2)

# Find the possible factorizations of cache_size / num_sets
# factorizations = find_factorizations(cache_size, num_sets)

# Varying the last three arguments

arguments = [cpp_program, str(8), str(4), str(8), str(1), str(0), str(0)]
subprocess.run(arguments)