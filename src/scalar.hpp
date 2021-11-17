#ifndef SCALAR_HPP
#define SCALAR_HPP

#include "ffiasm/fr.hpp"
#include "context.hpp"

int64_t fe2n (RawFr &fr, RawFr::Element &fe);
void fea2bn (Context &ctx, mpz_t &result, RawFr::Element fe0, RawFr::Element fe1, RawFr::Element fe2, RawFr::Element fe3);

#endif