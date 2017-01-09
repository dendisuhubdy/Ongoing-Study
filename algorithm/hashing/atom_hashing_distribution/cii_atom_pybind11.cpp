// 2017-01-09T18:27:26+08:00
#include <pybind11/pybind11.h>

#include "cii_atom.h"
#include "cii_atom_config.h"


#include "../../../cpp/common.h"

PYBIND11_PLUGIN(CII_ATOM_MODULE) {
    pybind11::module m(STR(CII_ATOM_MODULE));

    m.def("Atom_length", &Atom_length);
    m.def("Atom_new_from_buffer", &Atom_new);
    m.def("Atom_new_from_string", &Atom_string);
    m.def("Atom_new_from_int", &Atom_int);

    m.def("Atom_bench_buckets_size", &Atom_bench_buckets_size);
    m.def("Atom_bench_bucket_len", &Atom_bench_bucket_len);

    return m.ptr();
}