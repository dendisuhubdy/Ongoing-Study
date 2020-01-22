#include <valarray>
using std::valarray;

struct FilterResults
{
    valarray<double> filteredSignal;
    valarray<double> finalConditions;
};

void lfiltic(
    const valarray<double> &b,
    const valarray<double> &a,
    const valarray<double> &y,
    const valarray<double> &x);

FilterResults Filter(const valarray<double> &b,
    const valarray<double> &a, const valarray<double> &x, const valarray<double> &z);
