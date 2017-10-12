# very-neat-table
A 2d array that stays sorted both row-wise and column-wise

Description of the problem:

VNT 
Test your Matrix class by using it to implement a VNT class. 
We want a class called VNT (stands for “Very Neat Table” ) which is going to handle an m x n  matrix such that the entries of each row are in sorted order from left to right and the entries of each column are in sorted order from top to bottom. Some of the entries of a VNT may be INT_MAX , which we treat as nonexistent elements. Thus, a VNT
can be used to hold r ≤ mn integers.

We want the class to be able to do the following things:
- If A is a VNT object then A[i][j] is the i,j th element of the underlying 2 dimensional Matrix. So if A is empty then A[0][[0]=INT_MAX and if A is full then A[m-1][n-1] <INT_MAX.

- VNT(int m, int n) will create an m x n VNT object. VNT  A(5,7);

- A.add(25) will add 25 to a non-full VNT

- A.getMin(); will extract the smallest element for A and leave A a VNT.

- A.sort(int k[], int size)  sort the  n x n numbers in k using A and not calling any sort routine as a subroutine.

- A.find(int i) will return true if i is in A and false otherwise.

The Constraints
- function add() should work in time proportional to m+n. 
- function getMin() should work in time proportional to m+n. 
- function sort() should work in time proportional to n
- function find() should work in time proportional to m+n. 
