#include <iostream>
#include <cmath>
#include <array>

using namespace std;

constexpr auto order = 100;
constexpr auto Lx = 20.0;
constexpr auto Ly = 10.0;
constexpr auto difussionCoefficient = 4.0;
constexpr auto dt = 0.001;

auto concentration(double t, double x, double y, size_t order) {
    double concentration = 0.0;
    for (auto m = 1; m < order; m += 2) {
        const auto ySineFactor = sin(m * M_PI * y / Ly);
        for (auto n = 1; n < order; ++n) {
            const auto xSineFactor = sin(n * M_PI * x / Lx);
            const auto coefficient = 8 / (n * m * M_PI*M_PI);
            const auto lambda = - M_PI*M_PI * (n*n / (Lx*Lx) + m*m / (Ly*Ly));
            const auto tExponentialFactor = exp(lambda * difussionCoefficient * t);
            concentration += coefficient * xSineFactor * ySineFactor * tExponentialFactor;
        }
    }

    return concentration;
}

int main() {
    array<double, 20> ts;
    for (auto i = 0; i < ts.size(); ++i) ts[i] = i * dt;

    array<double, 200> xs;
    for (auto i = 0; i < xs.size(); ++i)
        xs[i] = Lx * double(i) / double(xs.size() - 1);

    array<double, 100> ys;
    for (auto i = 0; i < ys.size(); ++i)
        ys[i] = Ly * double(i) / double(ys.size() - 1);

    cout << "t,x,y,z,concentration" << endl;
    for (auto t : ts) for (auto x : xs) for (auto y : ys)
        cout
            << t << "," << x << "," << y << "," << 0.5 <<  "," << concentration(t, x, y, order)
            << endl;
}
