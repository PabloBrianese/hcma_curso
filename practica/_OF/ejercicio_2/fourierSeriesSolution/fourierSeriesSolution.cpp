#include <iostream>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

constexpr auto order = 100;
constexpr auto Lx = 20.0;
constexpr auto Ly = 10.0;
constexpr auto difussionCoefficient = 4.0;
constexpr auto dt = 1;

auto concentration(double t, double x, double y, size_t order) {
    double concentration = 0.5;
    for (auto n = 1; n < order; ++n) {
        const auto coefficient = 2.0 / (n * M_PI) * sin(n * M_PI_2);
        const auto xCosFactor = cos(n * M_PI * x / Lx);
        const auto lambda = - M_PI*M_PI * n*n / (Lx*Lx);
        const auto tExpFactor = exp(lambda * difussionCoefficient * t);
        concentration += coefficient * xCosFactor * tExpFactor;
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
    for (auto t : ts) for (auto y : ys) for (auto x : xs)
        cout
            << t << "," << x << "," << y << "," << 0.5 <<  "," << concentration(t, x, y, order)
            << endl;
}
