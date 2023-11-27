// SPDX-License-Identifier: Apache-2.0
//
// Copyright 2023 Jared Brzenski
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------

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