#include "circular_shift.h"

int handleCyclicShift(ivec &indices, const uint size)
{
    int shifted = 0;
    for (uint i = 0; i < indices.size(); ++i)
    {
        if (indices(i) >= size)
        {
            indices(i) -= size;
            shifted += 1;
        }
        else if (indices(i) < 0)
        {
            indices(i) += size;
            shifted -= 1;
        }
    }
    return shifted;
}

sp_mat circshift(const sp_mat &Q, const s32 shift, const u16 axes)
{
    /* circshift is a Sparse implementation of the circshift operator for 
       Armadillo. The standard operator works for dense matrixes, but we require
       a sparse implementation. Because sparse matrices are stored in CSR format,
       a different technique is used to speed up the process. If the matrix is
       shifted in the left/right direction, we also can sort the indices faster
       than Armadillo can, so we help that out for rebuilding the returned matrix.

       INPUT:

            Q       A sparse matrix to shift,
            shift   The amount to shift, positive indicates up/right, negative indicates down/left
            axes    The axes of shifting, 0=up/down, 1=left/right

        OUTPUT:

            returns shifted version of Q

    */

    bool sort_locations = false;  // We are sorting the locations for axis == 1
    bool check_for_zeros = false; // And we are not adding any zero members, so do not check.

    uint size = (axes == 1) ? Q.n_cols : Q.n_rows; // Size is number of cols or rows
    uint elements = Q.n_nonzero;

    // Armadillo uses uvecs for building sparse matrices
    uvec r(elements);
    uvec c(elements);
    vec val(elements);

    // Populate r, c, and val vectors
    int count = 0;
    for (sp_mat::const_iterator it = Q.begin(); it != Q.end(); ++it)
    {
        r(count) = it.row();
        c(count) = it.col();
        val(count) = *it;
        count += 1;
    }

    // uvec may need indices higher than it can go, or may
    // need to subtract, so convert to ivec
    ivec cc = conv_to<ivec>::from(c);
    ivec rr = conv_to<ivec>::from(r);

    // Shift columns or rows based on axes
    int shifted = 0;
    if ( axes == 1 ) // Shift columns
    {
        cc += shift;
        shifted = handleCyclicShift( cc, size );
        c = conv_to<uvec>::from(cc);
    }
    else // shift rows
    {
        rr+=shift;
        shifted = handleCyclicShift( rr, size );
        r = conv_to<uvec>::from(rr);
    }

    // Build shifted sparse matrix
    umat Loc(2, elements);
    umat LocShift(arma::size(Loc));
    vec ValShift(arma::size(val));

    // Build dense location matrix
    Loc = arma::join_vert(r.t(), c.t());

    // For shifts in left/right direction (axis==1)
    // cut bottom off and put on top, or cut top off and put on bottom
    if ( axes == 1 )
    {
        LocShift = arma::shift(Loc,shifted,1);
        ValShift = arma::shift(val,shifted);
    }
    else  // Otherwise we assume that Armadillo will be able to sort the entries for use
    {
        LocShift = Loc;
        ValShift = val;
        sort_locations = true;
    } 

    return sp_mat( LocShift, ValShift, Q.n_rows, Q.n_cols, sort_locations, check_for_zeros );
}
