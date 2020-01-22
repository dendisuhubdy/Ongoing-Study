#ifndef FILTER_H_
#define FILTER_H_

#include <stddef.h>

#include "../../algutils.h"

C_API_BEGIN

int lfilter(const double *b, size_t blen, const double *a, size_t alen,
           const double *x, size_t xlen, double *y, const double *zi,
           double *zf);

C_API_END

#endif  // FILTER_H_
