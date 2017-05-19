#ifndef TYPE_TO_MPI_H
#define TYPE_TO_MPI_H

#include <mpi.h>

namespace sobol { namespace detail {

template <typename T>
struct type_to_mpi {
    static constexpr auto datatype = MPI_DATATYPE_NULL;
};
template <>
struct type_to_mpi<int> {
    static constexpr auto datatype = MPI_INT;
};
template <>
struct type_to_mpi<long> {
    static constexpr auto datatype = MPI_LONG;
};
template <>
struct type_to_mpi<unsigned int> {
    static constexpr auto datatype = MPI_UNSIGNED;
};
template <>
struct type_to_mpi<unsigned long> {
    static constexpr auto datatype = MPI_UNSIGNED_LONG;
};

}} // namespace sobol::detail

#endif // TYPE_TO_MPI_H
