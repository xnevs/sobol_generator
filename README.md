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
an object of this class:

```c++
sobol_generator::sobol_generator<n_dims> sg(direction_integers_path, mpi_communicator);
```

The desired number of dimensions is sepcified as a template parameter and the constructor accepts two arguments:
  * the path to the file containing direction integers; examples available at [[3]](http://web.maths.unsw.edu.au/~fkuo/sobol/), and
  * an MPI Communicator that represents the processes where we wish to generate Sobol' numbers, usually `MPI_COMM_WORLD`.

To generate sample there are two methods available: using the `operator ()`, as in

```c++
vector<double> sample = sg();
```,

or using the `sg.generate` method

```c++
double[n_dims] sample;
sg.generate(sample);
```

[3] Kuo, Frances and Joe, Stephen. [Sets of direction numbers](http://web.maths.unsw.edu.au/~fkuo/sobol/). 

## Example

A very simple example of Monte Carlo integration using `sobol_generator` is available in the file `example.cpp`.

There we integrate the function `f(x,y) = sin(x) · y²` on the unit square `[0,1]×[0,1]`.

### Building

Run `make` in the root directory.

The result of building is the `./example` binary.

### Running

To run the Monte Carlo integration example with 4 processes issue the command

```bash
mpirun -np 4 ./example direction-integers.txt
```.

A set of direction integers (`direction-integers.txt` above) must be supplied as a command line argument. High quality sets of direction integers are available at [[3]](http://web.maths.unsw.edu.au/~fkuo/sobol/). The format of the file is the same as at [[3]](http://web.maths.unsw.edu.au/~fkuo/sobol/).
