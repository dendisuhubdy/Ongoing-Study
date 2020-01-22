#include "filter_cpp.h"


FilterResults Filter(const valarray<double> &b,
    const valarray<double> &a, const valarray<double> &x, const valarray<double> &z)
{
    valarray<double> y(x.size());
    // Pad z
    valarray<double> zOut(a.size());
    std::copy(std::begin(z), std::end(z), std::begin(zOut));

    double Xm, Ym;
    size_t i, n = a.size();
    for (size_t m = 0; m < y.size(); m++)
    {
        Xm = x[m];
        y[m] = b[0] * Xm + zOut[0];
        Ym = y[m];
        for (i = 1; i < n; i++)
        {
            zOut[i - 1] = b[i] * Xm + zOut[i] - a[i] * Ym;
        }
    }
    valarray<double> s = zOut[std::slice(0, zOut.size() - 1, 1)];
    FilterResults r;
    r.filteredSignal = std::move(y);
    r.finalConditions = std::move(s);
    return r;
}


void lfiltic(
    const valarray<double> &b,
    const valarray<double> &a,
    const valarray<double> &y,
    const valarray<double> &x)
{

}
