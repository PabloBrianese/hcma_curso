#include <cstdio>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

// PDE parameters
constexpr auto difussionCoefficient = 4.0;

// Domain data
constexpr auto Lx = 20.0;
constexpr auto Ly = 10.0;

// Fourier series approximation order
constexpr auto order = 200;

// BEGIN Concentration computation

constexpr auto k_max = (order - 1) / 2;
constexpr auto ks {[]() constexpr {
    array<int, k_max> result {};
    for (auto k = 0; k < k_max; ++k) result[k] = k;

    return result;
}()};

constexpr auto ns {[]() constexpr {
    array<double, k_max> result {};
    for (auto k : ks) result[k] = double(2 * k + 1);

    return result;
}()};

constexpr auto signs {[]() constexpr {
    array<int, k_max> result {};
    for (auto k : ks) result[k] = (k % 2 == 0) ? 1 : - 1;

    return result;
}()};

constexpr auto coefficients {[]() constexpr {
    array<double, k_max> result {};
    for (auto k : ks) result[k] = 2.0 / (ns[k] * M_PI);

    return result;
}()};

constexpr auto reduced_lambdas {[]() constexpr {
    array<double, k_max> result {};
    for (auto k : ks) result[k] = M_PI * ns[k] / Lx;

    return result;
}()};

constexpr auto lambdaDs {[]() constexpr {
    array<double, k_max> result {};
    for (auto k : ks) {
        const auto lambda = - M_PI*M_PI * ns[k]*ns[k] / (Lx*Lx);
        result[k] = lambda * difussionCoefficient;
    }

    return result;
}()};


auto concentration(double t, double x) {
    vector<double> xCosFactors;
    xCosFactors.reserve(k_max);
    for (auto k : ks) xCosFactors.push_back(cos(reduced_lambdas[k] * x));

    vector<double> tExpFactors;
    tExpFactors.reserve(k_max);
    for (auto k : ks) tExpFactors.push_back(exp(lambdaDs[k] * t));

    double concentration = 0.5;
    for (auto k : ks)
        concentration += signs[k] * coefficients[k] * xCosFactors[k] * tExpFactors[k];

    return concentration;
}

// END Concentration computation

// BEGIN Domain Modelling

constexpr auto ts {[]() constexpr {
    constexpr auto size = 20;
    array<double, size> result {};
    for (auto i = 0; i < size; ++i) result[i] = double(i);

    return result;
}()};

constexpr auto xs {[]() constexpr {
    constexpr auto size = 200;
    array<double, size> result {};
    for (auto i = 0; i < size; ++i)
        result[i] = Lx * double(i) / double(size - 1);

    return result;
}()};

constexpr auto ys {[]() constexpr {
    constexpr auto size = 100;
    array<double, size> result {};
    for (auto i = 0; i < size; ++i)
        result[i] = Ly * double(i) / double(size - 1);
    
    return result;
}()};

// END Domain modelling

int main() {
    printf("t,x,y,concentration\n");
    for (auto t : ts) for (auto y : ys) for (auto x : xs)
        printf("%f,%f,%f,%f\n", t, x, y, concentration(t, x));
}
