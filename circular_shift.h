#ifndef CIRCULAR_SHIFT_H
#define CIRCULAR_SHIFT_H

#include <math.h>   
#include <armadillo>

using namespace arma;
using namespace std::chrono;

// shift the row or column indices
int handleCyclicShift(ivec &indices, const uint size);

// Main circshift operator
sp_mat circshift(const sp_mat &Q, const s32 shift, const u16 axes);

#endif