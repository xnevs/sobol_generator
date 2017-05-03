#include <vector>
#include <limits>
#include <random>

#define PPMT_MAX_DIM 30
#include "PrimitivePolynomialsModuloTwo/PrimitivePolynomialsModuloTwoUpToDegree27.h"

template <std::size_t num_dims = PPMT_MAX_DIM>
class sobol_generator {
public:
    using x_t = unsigned long;
    static constexpr auto num_bits = std::numeric_limits<x_t>::digits;
    static constexpr double norm = 1 / (1.0 + std::numeric_limits<x_t>::max());

    decltype(new x_t[num_dims][num_bits]) direction_integers;

    unsigned long count;
    std::vector<x_t> x;

    void increment() {
        ++count;
        int j = __builtin_ctzl(count);
        for(std::size_t k=0; k<num_dims; ++k)
            x[k] ^= direction_integers[k][j];
    }

public:

    template <typename URNG>
    sobol_generator(URNG && gen)
      : direction_integers(new x_t[num_dims][num_bits])
      , count(0)
      , x(num_dims) {
        
        std::uniform_int_distribution<x_t> dis;

        // k=0
            for(int l=1; l<=num_bits; ++l) {
                x_t v = static_cast<x_t>(1) << (num_bits - l);
                direction_integers[0][l-1] = v;
            }
        for(std::size_t k=1, pi=0, degree=1; k<num_dims; ++k, ++pi) {
            auto polynomial = PrimitivePolynomials[degree-1][pi];
            if(polynomial < 0) polynomial = PrimitivePolynomials[degree++][pi=0];

            direction_integers[k][0] = static_cast<x_t>(1) << (num_bits - 1);
            for(std::size_t l=2; l<=degree; ++l) {
                x_t v = ((dis(gen) << 1) | 1) << (num_bits - l);
                direction_integers[k][l-1] = v;
            }
            for(std::size_t l=degree+1; l<=num_bits; ++l) {
                x_t v = direction_integers[k][l-degree-1] >> degree;
                v ^= direction_integers[k][l-degree-1];
                auto p = polynomial;
                for(std::size_t j=degree-1; p; --j, p >>= 1) {
                    if(p & 1) v ^= direction_integers[k][l-j-1];
                }
                direction_integers[k][l-1] = v;
            }
        }
    }

    ~sobol_generator() {
        delete[] direction_integers;
    }

    std::vector<double> operator()() {
        increment();
        std::vector<double> y(begin(x),end(x));
        for(double & y_k : y) y_k *= norm;
        return y;
    }

    template <typename ForwardIt>
    void generate(ForwardIt first) {
        increment();
        for(auto x_k : x) *(first++) = x_k * norm;
    }
};

using namespace std;

int main(int argc, char *argv[]) {
    default_random_engine gen(1234);

    sobol_generator<3> sg(gen);

    double y[3];
    for(int i=0; i<atoi(argv[1]); ++i) {
        sg.generate(y);
        printf("%.4lf %.4lf\n", y[1], y[2]);
    }
}
