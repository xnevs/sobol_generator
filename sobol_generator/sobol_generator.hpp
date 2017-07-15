#ifndef SOBOL_GENERATOR_HPP
#define SOBOL_GENERATOR_HPP

#include <fstream>
#include <memory>
#include <limits>
#include <vector>
#include <algorithm>

#include <mpi.h>

#include "type_to_mpi.hpp"

namespace sobol {

template <std::size_t num_dims,
          typename RealType = double>
class sobol_generator {
private:
    using x_t = unsigned long;
    static constexpr auto num_bits = std::numeric_limits<x_t>::digits;
    static constexpr RealType norm = 1 / (static_cast<RealType>(1) + std::numeric_limits<x_t>::max());

    int num_procs;
    int popcount;
    std::unique_ptr<int[]> pop_pos;

    int offset;

    std::unique_ptr<x_t[][num_bits]>           direction_integers;
    std::unique_ptr<x_t[][num_dims][num_bits]> leap_integers;

    unsigned long count;
    std::unique_ptr<x_t[]> x;

    void read_direction_integers(const char * filename) {
        std::ifstream infile(filename);
        infile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        // k=0
            for(unsigned long l=1; l<=num_bits; ++l) {
                x_t v = static_cast<x_t>(1) << (num_bits - l);
                direction_integers[0][l-1] = v;
            }
        for(std::size_t k=1; k<num_dims; ++k) {
            std::size_t d;
            std::size_t degree;
            x_t polynomial;

            infile >> d >> degree >> polynomial;
            for(std::size_t l=1; l<=degree; ++l) {
                x_t v;
                infile >> v;
                v <<= (num_bits - l);
                direction_integers[k][l-1] = v;
            }
            for(std::size_t l=degree+1; l<=num_bits; ++l) {
                x_t v = direction_integers[k][l-degree-1] >> degree;
                v ^= direction_integers[k][l-degree-1];
                auto p = polynomial;
                for(std::size_t j=degree-1; p; --j,p>>=1) {
                    if(p & 1) v ^= direction_integers[k][l-j-1];
                }
                direction_integers[k][l-1] = v;
            }
        }
    }

    void initialize_leap_integers() {
        for(std::size_t k=0; k<num_dims; ++k) {
            for(int pk=0; pk<popcount; ++pk) {
                for(std::size_t l=pop_pos[pk]; l<num_bits; ++l) {
                    x_t v = 0;
                    for(int i=0; i<(1<<pop_pos[pk]); ++i) {
                        auto j = __builtin_ctzl((1ul<<l)-i);
                        v ^= direction_integers[k][j];
                    }
                    leap_integers[pk][k][l] = v;
                }
            }
        }
    }


    void increment() {
        ++count;
        auto j = __builtin_ctzl(count);
        for(std::size_t k=0; k<num_dims; ++k)
            x[k] ^= direction_integers[k][j];
    }

    void frog_leap() {
        count += num_procs;
        unsigned long n = count;
        for(int pk=0; pk<popcount; ++pk) {
            auto j = __builtin_ctzl( (n>>pop_pos[pk])<<pop_pos[pk] );
            for(std::size_t k=0; k<num_dims; ++k) {
                x[k] ^= leap_integers[pk][k][j];
            }
            n -= 1<<pop_pos[pk];
        }
    }

public:

    sobol_generator(const char * filename, MPI_Comm mpi_comm)
      : direction_integers(new x_t[num_dims][num_bits])
      , count(0)
      , x(new x_t[num_dims]) {

        int mpi_comm_size;
        MPI_Comm_size(mpi_comm,&mpi_comm_size);
        num_procs = mpi_comm_size;

        popcount = __builtin_popcount(mpi_comm_size);
        pop_pos.reset(new int[popcount]);
        for(int num=mpi_comm_size,i=0,j=0; num; num>>=1,++i) {
            if(num & 1) pop_pos[j++] = i;
        }
        leap_integers.reset(new x_t[popcount][num_dims][num_bits]);

        int mpi_comm_rank;
        MPI_Comm_rank(mpi_comm,&mpi_comm_rank);
        offset = mpi_comm_rank + 1;  // +1 to skip 0

        if(mpi_comm_rank == 0) {
            read_direction_integers(filename);
        }
        MPI_Bcast(direction_integers.get(),
                  num_dims*num_bits,
                  detail::type_to_mpi<x_t>::datatype,
                  0,
                  mpi_comm);

        initialize_leap_integers();

        std::fill_n(x.get(),num_dims,0);
        for(int i=0; i<offset; ++i) {
            increment();
        }
        count = offset;
    }


    std::vector<RealType> operator()() {
        std::vector<RealType> y(x.get(),x.get()+num_dims);
        for(auto & y_k : y) {
            y_k *= norm;
        }
        frog_leap();
        return y;
    }

    template <typename ForwardIt>
    void generate(ForwardIt first) {
        std::transform(x.get(),x.get()+num_dims,first,[](auto x_k){
            return x_k*norm;
        });
        frog_leap();
    }
};

} // namespace sobol

#endif // SOBOL_GENERATOR_HPP
