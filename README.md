# Dynamic Sparse N-Dimensional Matrix
A dynamic sparse matrix with arbitrary number of dimensions.

It's also generic, so you can use it for any kind of value.


# How does it work
The structure is a pretty normal sparse vector, implemented as a binary tree.

There is a particular variable: "level".

Let's say you have a 3D matrix.

You can see it as a vector (level 2) of vectors (level 1) of actual vectors (level 0) of element.

So this n-dimensional matrix is implemented as a sparse vector (level n-1) of sparse vetors (level n-2) of sparse vectors, etc...

All the levels are dynamic, you can always add a new element in any position.
