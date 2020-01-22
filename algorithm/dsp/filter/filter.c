#include <assert.h>

int lfilter(const double *b, size_t blen, const double *a, size_t alen,
            const double *x, size_t xlen, double *y, const double *zi,
            double *zf) {
  size_t i, j;

  assert(b != NULL && blen > 0);
  assert(a != NULL && alen > 0);
  assert(x != NULL && xlen > 0);
  assert(y != NULL);

  if (a[0] != 1.0) {
    for (i = 0; i < blen; ++i) b[i] /= a[0];
    for (i = 1; i < alen; ++i) a[i] /= a[0];

    a[0] = 1.0;
  }

  for (i = 0; i < xlen; ++i) {
    y[i] = b[0] * x[i] + zi[0];

    for (j = 1; j < alen; ++j) {
      zi[j - 1] = b[j] * x[i] + zi[j] - a[j] * y[i];
    }
  }

  return 0;
}

// References:
// MATLAB: filter
// Python: scipy.signal.lfilter
// https://github.com/scipy/scipy/blob/aaa30d88ef360b50f523ef8651ba3eea5bc1e410/scipy/signal/lfilter.c.src#L558-L606
// https://ww2.mathworks.cn/matlabcentral/answers/313244-c-equivalent-to-matlab-filter
// https://codereview.stackexchange.com/questions/141798/optimizing-c-equivalent-of-matlab-filter-function
