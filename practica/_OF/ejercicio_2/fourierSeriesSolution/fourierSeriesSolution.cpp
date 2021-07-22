#include <iostream>
#include <cmath>
#include <array>

constexpr auto order = 10;
constexpr auto Lx = 1.0;
constexpr auto Ly = 1.0;
constexpr auto difussionCoefficient = 0.1;

auto concentration(double t, double x, double y, size_t order) {
    double concentration = 0.0;
    for (auto m = 1; m < order; m += 2) {
        auto ySineFactor = sin(m * M_PI * y / Ly);
        for (auto n = 1; n < order; ++n) {
            auto xSineFactor = sin(n * M_PI * x / Lx);
            auto coefficient = 8 / (n * m * M_PI*M_PI);
            auto lambda = - M_PI*M_PI * (n*n / (Lx*Lx) + m*m / (Ly*Ly));
            auto tExponentialFactor = exp(lambda * difussionCoefficient * t);
            concentration += coefficient * xSineFactor * ySineFactor * tExponentialFactor;
        }
    }

    return concentration;
}

int main() {
    std::array<double, 10> ts;
    for (auto i = 0; i < ts.size(); ++i) ts[i] = i * 0.1;

    std::array<double, 10> xs;
    for (auto i = 0; i < xs.size(); ++i) xs[i] = Ly * i / (double(xs.size()) - 1);

    std::array<double, 10> ys;
    for (auto i = 0; i < ys.size(); ++i) ys[i] = Ly * i / (double(ys.size()) - 1);

    std::cout << "t,x,y,z,concentration" << std::endl;
    for (auto t : ts) for (auto x : xs) for (auto y : ys)
        std::cout
            << t << "," << x << "," << y << "," << 0.5 <<  "," << concentration(t, x, y, order)
            << std::endl;
}
