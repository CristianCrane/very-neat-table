#ifndef SAFEMATRIX_H_
#define SAFEMATRIX_H_

#include<iostream>
#include <cstdlib>
#include<cassert>
using namespace std;

template<class T> // forward declaration
class SA;
template<class T> //forward declaration
ostream& operator<<(ostream& os, SA<T> s);

template<class T>
class SA {
private:
	int low, high;
	T* p;
public:
// default constructor
// allows for writing things like SA a;
	SA() {
		low = 0;
		high = -1;
		p = NULL;
	}
// 2 parameter constructor lets us write
// SA x(10,20);
	SA(int l, int h) {
		if ((h - l + 1) <= 0) {
			cout << "constructor error in bounds definition" << endl;
			exit(1);
		}
		low = l;
		high = h;
		p = new T[h - l + 1];
	}
// single parameter constructor lets us
// create a SA almost like a "standard" one by writing
// SA x(10); and getting an array x indexed from 0 to 9
	SA(int i) {
		low = 0;
		high = i - 1;
		p = new T[i];
	}
// copy constructor for pass by value and
// initialization
	SA(const SA & s) {
		int size = s.high - s.low + 1;
		p = new T[size];
		for (int i = 0; i < size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
	}
// destructor
	~SA() {
		delete[] p;
	}
//overloaded [] lets us write
//SA x(10,20); x[15]= 100;
	T& operator[](int i) {
		if (i < low || i > high) {
			cout << "index " << i << " out of range" << endl;
			exit(1);
		}
		return p[i - low];
	}
// overloaded assignment lets us assign
// one SA to another
	SA & operator=(const SA s) {
		if (this == &s)
			return *this;
		delete[] p;
		int size = s.high - s.low + 1;
		p = new T[size];
		for (int i = 0; i < size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
		return *this;
	}
// overloads << so we can directly print SAs
//template <class T>
	friend ostream& operator<<<T>(ostream& os, SA<T> s);
};
template<class T>
ostream& operator<<(ostream& os, SA<T> s) {
	int size = s.high - s.low + 1;
	for (int i = 0; i < size; i++)
		cout << s.p[i] << " ";
	return os;
};

template<class T>
class SM {
private:
	SA< SA<T> > matrix;
public:
	int rlo, rhi, clo, chi, rows, cols;
	// default constructor does nothing i guess?
	SM() {
		rlo = 0;
		rhi = 0;
		clo = 0;
		chi = 0;
		rows = 0;
		cols = 0;
	}

	// 2 arg constructor specifies higher bounds only.
	SM(int rows, int cols)
	{
		rlo = 0;
		rhi = rows-1;
		clo = 0;
		chi = cols-1;
		this->rows = rows;
		this->cols = cols;

		matrix = SA< SA<T> >(rows);
		for (int r = 0; r < rows; r++)
			matrix[r] = SA<T>(cols);
	}

	// 4 arg constructor specifies lower and upper bounds for each dimension.
	SM(int rl, int rh, int cl, int ch)
	{
		rlo = rl;
		rhi = rh;
		clo = cl;
		chi = ch;
		rows = rhi-rlo+1;
		cols = chi-clo+1;

		matrix = SA< SA<T> >(rl,rh);
		for (int r = rl; r <= rhi; r++)
			matrix[r] = SA<T>(cl,ch);
	}

	// operator[] to access 1st dimension of matrix
	SA<T>& operator[](int row)
	{
		return matrix[row];
	}

	// operator*
	SM operator*(SM& m2)
	{
		// check if matrix multiplication can be done
		if (cols != m2.rows) {
			cout << "Can't multiply matrices. Invalid dimensions.\n";
			exit(1);
		}

		// if so do matrix multiplication
		SM product(rows,m2.cols);
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < m2.cols; c++) {
				int sum = 0;
				for (int i = 0; i < cols; i++){
					sum += (matrix[r][i]*m2[i][c]);
				}
				product[r][c] = sum;
			}
		}
		return product;
	}

	// operator+
	SM operator+(SM& m2)
	{
		// check if matrix addition can be done
		if (rows != m2.rows || cols != m2.cols) {
			cout << "Can't add matrices. Not same dimensions.\n";
			exit(1);
		}

		// if so, do matrix addition
		SM sum(rows,cols);
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				sum[r][c] = matrix[r][c] + m2[r][c];
			}
		}

		return sum;
	}

	// operator-
	SM operator-(SM& m2)
	{
		// check if matrix subtraction can be done
		if (rows != m2.rows || cols != m2.cols) {
			cout << "Can't subtract matrices. Not same dimensions.\n";
			exit(1);
		}

		// if so, do matrix subtraction
		SM difference(rows,cols);
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c <	 cols; c++) {
				difference[r][c] = matrix[r][c] - m2[r][c];
			}
		}

		return difference;
	}

	// operator<<
	friend ostream& operator<<(ostream& os, SM& sm)
	{
		for (int r = sm.rlo; r <= sm.rhi; r++)
		{
			for (int c = sm.clo; c <= sm.chi; c++)
			{
				os << sm.matrix[r][c] << " ";
			}
			os << endl;
		}
		return os;
	}

};

#endif
