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

#include <iostream>            /* input */
#include <math.h>              /* norm */
#include <chrono>              /* Timing */
#include <iomanip>             /* For precision */
#include <armadillo>           /* Armadillo C++ Library */
#include "circular_shift.h"    /* circshift function */

using namespace arma;
using namespace std::chrono;

int main( int argc, char *argv[] ) {

    // Generic Values for testing with no commnad line input
    int s = 10;
    int shifts =  3;
    int axis = 1;
    // Parse the input
    if ( argc == 4 )
    {

        // Convert command line arguments to integers
        s = std::atoi(argv[1]);
        shifts = std::atoi(argv[2]);
        axis = std::atoi(argv[3]);

        // Check that matrix length is poitive
        if (s <= 0) {
            std::cerr << "Invalid input for size of matrix, please pick a positive integer value." << std::endl;
            return 1; // Exit with an error code
        }

        // Check shift amount if less than size of matrix
        if ( abs(shifts) >= s-1 ) {
            std::cerr << "Invalid input for number of shifts. Please pick a number less than the dimension of th matrix." << std::endl;
            return 1; // Exit with an error code
        }

        // Check axis is either 0 or 1
        if ( axis != 0 && axis != 1 ) {
            std::cerr << "Invalid input for axis. Please pick 0 for vertical, 1 for horizontal shifts" << std::endl;
            return 1; // Exit with an error code
        }
    }
    else
    {
        std::cout << "Using default size of 10x10 with 3 shifts" << endl;
        std::cout << "This can be run with " << argv[0] << " NUM_ROWS NUM_SHIFTS AXIS to " << endl;
        std::cout << "show an example of NUM_ROWSxNUM_ROWS shifted NUM_SHIFTS places on AXIS (0=up/down, 1=left/right)." << endl;
        std::cout << "A fun test for speed is to try ./shift_example 5000 2000 1." << endl << endl;
    }

    sp_mat Q(s,s);

    cout << "Built Q matrix" << endl;

    // Some diagonal values so we can test the circshift
    Q.diag(0).fill(1.0);
    Q.diag(1).fill(1.0);
    Q.diag(-1).fill(1.0);
    Q.diag(2).fill(1.5);
    Q.diag(-2).fill(1.5);
    Q.diag(5).fill(2.5);
    Q.diag(-5).fill(2.5);

    std::cout << "Q matrix has " << Q.n_nonzero << " nonzero elements. " << endl;

    // Some holders for comparison
    sp_mat RESULTA;
    sp_mat RESULTB;
    sp_mat Diff;

    std::cout << "trying four times to check the timing..." << endl << endl << endl;
    for (int i=0; i<4; ++i){

        mat Qd(Q); // make dense version for shift
        auto start = high_resolution_clock::now();
        RESULTA = arma::shift(Qd,shifts, axis);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Armadillo shift took " << duration.count() << "us" << endl;
        
        // sparse circshift
        auto start2 = high_resolution_clock::now();
        RESULTB = circshift(Q,shifts,axis);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        std::cout << "Sparse Circshift took " << duration2.count() << "us" << endl << endl;

        Diff = RESULTA-RESULTB;
        double max_of_diff = Diff.max();

        /* Print out the matrices if they are small enough ! */
        if ( Q.n_cols <= 10 && Q.n_rows <= 10 )
        {
            std::cout << "Starting Q matrix " << endl;
            Qd.print();

            std::cout << endl << endl;
            std::cout << "Armadillo shifted matrix " << endl;
            mat RESULTA_D(RESULTA);
            RESULTA_D.print();

            std::cout << endl << endl;
            std::cout << "Sparse circshift shifted matrix " << endl;
            mat RESULTB_D(RESULTB); // make dense
            RESULTB_D.print();
                           
        }
        std::cout << "Difference between functions shift: " << std::setprecision(8) << max_of_diff << endl << endl << endl;
    }
}

