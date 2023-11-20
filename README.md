
# Armadillo Sparse circular_shift Function
Circular_shift is a Sparse implementation of the MATLAB circshift operator for the Armadillo C++ library. The standard operator works for dense matrixes, but we require
a sparse implementation. Because sparse matrices are stored in CSR format, a different technique is used to speed up the process. If the matrix is shifted in the left/right direction, we also can sort the indices faster than Armadillo can, so we help that out for rebuilding the returned matrix.
## Installation

Run the included makefile on your machine. Change the first four lines, including the location of the ARMA library and include or remove any libraries you may need.

```
ARMA = location_of_Armadillo_Library
INC = specific_include_path
LIBPATH = library_path
# this is dependant on your install of Armadillo, it could be much simpler
LIBS = -L$(ARMA) -larmadillo -L$(LIBPATH) -lsuperlu -llapack -lopenblas
```

The standard template to run is

```
./shift_example [NUM_ROWS_OF_MATRIX] [SHIFT_NUM] [AXIS_OF_SHIFT]
```
where NUM_ROWS_OF_MATRIX is a positive integer N, where the sample matrix will be of size [NxN]. SHIFT_NUM is the integer amount to shift the values, and must be less than NUM_ROWS_MATRIX. A negative value indicates shifting either left or down, depending on the axis, whereas poisitive would be a shift of up or right. And AXIS_OF_SHIFT is the direction of shift, either 0 (up/down) or 1 (left/right).
## Usage/Examples
Once built, the command

```
./shift_example
```

will run the basic example, building a 10x10 matrix with 5 diagonals. It will shift them 3 indices in the x-direction (axis==1). It will display the original matrix, Armadillos version, which uses a shift of the sparse matrix, and the new circshift for sparse matrices.

```
Using default size of 10x10 with 3 shifts
This can be run with ./shift_example NUM_ROWS NUM_SHIFTS AXIS to 
show an example of NUM_ROWSxNUM_ROWS shifted NUM_SHIFTS places on AXIS (0=up/down, 1=left/right).
A fun test for speed is to try ./shift_example 5000 2000 1.

Built Q matrix
Q matrix has 54 nonzero elements. 
trying four times to check the timing...


Armadillo shift took 12us
Sparse Circshift took 30us

Starting Q matrix 
   1.0000   1.0000   1.5000        0        0   2.5000        0        0        0        0
   1.0000   1.0000   1.0000   1.5000        0        0   2.5000        0        0        0
   1.5000   1.0000   1.0000   1.0000   1.5000        0        0   2.5000        0        0
        0   1.5000   1.0000   1.0000   1.0000   1.5000        0        0   2.5000        0
        0        0   1.5000   1.0000   1.0000   1.0000   1.5000        0        0   2.5000
   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000        0        0
        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000        0
        0        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000
        0        0        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000
        0        0        0        0   2.5000        0        0   1.5000   1.0000   1.0000


Armadillo shifted matrix 
        0        0        0   1.0000   1.0000   1.5000        0        0   2.5000        0
        0        0        0   1.0000   1.0000   1.0000   1.5000        0        0   2.5000
   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000        0        0
        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000        0
        0        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000
   1.5000        0        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000
   1.0000   1.5000        0        0   2.5000        0        0   1.5000   1.0000   1.0000
   1.0000   1.0000   1.5000        0        0   2.5000        0        0   1.5000   1.0000
   1.0000   1.0000   1.0000        0        0        0   2.5000        0        0   1.5000
   1.5000   1.0000   1.0000        0        0        0        0   2.5000        0        0


Sparse circshift shifted matrix 
        0        0        0   1.0000   1.0000   1.5000        0        0   2.5000        0
        0        0        0   1.0000   1.0000   1.0000   1.5000        0        0   2.5000
   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000        0        0
        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000        0
        0        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000   1.5000
   1.5000        0        0   2.5000        0        0   1.5000   1.0000   1.0000   1.0000
   1.0000   1.5000        0        0   2.5000        0        0   1.5000   1.0000   1.0000
   1.0000   1.0000   1.5000        0        0   2.5000        0        0   1.5000   1.0000
   1.0000   1.0000   1.0000        0        0        0   2.5000        0        0   1.5000
   1.5000   1.0000   1.0000        0        0        0        0   2.5000        0        0
Difference between functions shift: 0
```

You can select bigger sizes by passing command line arguments. Bigger matrices will only return the time and difference between the Armadillo shift operator and the circshift sparse operator.
```
$ ./shift_example 5000 1234 1
Built Q matrix
Q matrix has 34984 nonzero elements. 
trying four times to check the timing...


Armadillo shift took 171203us
Sparse Circshift took 2753us

Difference between functions shift: 0


Armadillo shift took 170666us
Sparse Circshift took 2593us

Difference between functions shift: 0


Armadillo shift took 169091us
Sparse Circshift took 979us

Difference between functions shift: 0


Armadillo shift took 168743us
Sparse Circshift took 541us

Difference between functions shift: 0

```


## Contributing

Contributions are always welcome!

Email Jared for updates or sugestions for future updates

