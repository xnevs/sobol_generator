# sobol_generator
A parallel implementation of the Sobol' quasirandom number generator

A Sobol' quasirandom number generator is type [low-discrepancy](https://en.wikipedia.org/wiki/Low-discrepancy_sequence) number sequence generator.
A definition of a Sobol' number sequence can be found in [1].

The generated numbers are in no way random nor pseudorandom. 
They are, however, useful for Monte Carlo integration, where the low-discrepancy properties ensure faster convergence compared to pseudorandom numbers.

The parallel Sobol' generator implemented here allows the programer to generate a subsequence of the whole Sobol' sequence
on every compute node in such a way that the combined (interleaved) subsequences form the full Sobol' sequence.

For Monte Carlo integration this means that every process gets a subset of the samples from the Sobol' sequence,
but the end result is the same as in the serial case with the full Sobol' sequence. This way all the benefits of
using quasirandom over pseudorandom numbers transfer to the parallel case. For details see [2].

[1] Jäckel, Peter. Monte Carlo methods in finance. J. Wiley, 2002.

[2] Bromley, B. C. "Quasirandom number generators for parallel Monte Carlo algorithms." Journal of parallel and distributed computing 38.1 (1996): 101-104.

## Requirements

The number generator is implemented in C++ (C++14 support required) using the OpenMPI library.

## Usage

This is a header-only library. The header file `sobol_generator/sobol_generator.hpp` contains
the implementation of the `sobol_generator::sobol_generator` class template.

To use `sobol_generator::sobol_generator` you must include the `sobol_generatot.hpp` header file and instantiate
an object of this class.

The desired number of dimensions is sepcified as a template parameter, whereas the constructor accepts two arguments:
  * the path to the file containing direction integers; examples available at [3], and
  * an MPI Communicator that represents the processes where we wish to generate Sobol' numbers.

[3] Kuo, Frances and Joe, Stephen. [Sets of direction numbers](http://web.maths.unsw.edu.au/~fkuo/sobol/). 
