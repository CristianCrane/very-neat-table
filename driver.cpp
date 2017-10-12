#include <iostream>
#include "SM.h"
#include <climits>
#include <time.h>
#include <string>
using namespace std;

class VNT
{
private:
	SM<int> matrix;
	int rows, cols;
	void swap(int&,int&);
	void floatUp(int curRow, int curCol);
	void sinkDown(int curRow, int curCol);
public:
	// constructors
	VNT(int rows, int cols);
	void add(int i);
	int getMin();
	void sort(int arr[], int size);
	bool find(int i);


	friend ostream& operator<<(ostream &os, VNT &vnt)
	{
		for (int r = 0; r < vnt.rows; r++)
		{
			for (int c = 0; c < vnt.cols; c++)
			{
				if (vnt.matrix[r][c] == INT_MAX)
					os << "- ";
				else
					os << vnt.matrix[r][c] << " ";
			}
			os << endl;
		}
		return os;
	}

};

VNT::VNT(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	matrix = SM<int>(rows,cols);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			matrix[r][c] = INT_MAX;
}

void VNT::sort(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		this->add(arr[i]);

	for (int i = 0; i < size; i++)
		arr[i] = this->getMin();

}

void VNT::swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

bool VNT::find(int i)
{
	// start at top right of matrix
	int row = 0, col = cols-1;

	// search till we find or go out of bounds
	while(row < rows && col >= 0)
	{
		int cur = matrix[row][col];
		if (cur == i)
			return true;
		else if (cur < i)
			row++;
		else
			col--;
	}

	return false;
}

void VNT::add(int i)
{
	// start bottom right
	int row = rows-1, col = cols-1;

	// if there's an element already, the matrix is full
	if (matrix[row][col] < INT_MAX)
	{
		cout << "add("<<i<<") failed. Matrix full.";
		return;
	}

	// go up till end or element
	while (row-1 >= 0 && matrix[row-1][col] == INT_MAX)
		row--;

	// go left till end or element
	while (col-1 >= 0 && matrix[row][col-1] == INT_MAX)
			col--;

	// place element
	matrix[row][col] = i;
	floatUp(row,col);

}

void VNT::floatUp(int curRow, int curCol)
{
	// if left and up are ok were done
	if ( (curCol-1 < 0 || matrix[curRow][curCol-1] <= matrix[curRow][curCol]) // if left ok
		 && 												   				  // and
	     (curRow-1 < 0 || matrix[curRow-1][curCol] <= matrix[curRow][curCol]))// if up ok
		return;


	/* else swap with biggest of either up or left then move in that direction.
	 * Recursively repeat process from that new current pos till ok
	 */

	// if there is no up value, swap with left
	if (curRow-1 < 0)
	{
		swap(matrix[curRow][curCol], matrix[curRow][curCol-1]);
		floatUp(curRow,curCol-1); // go left
	}

	// else if there is no left value, swap with up
	else if (curCol-1 < 0)
	{
		swap(matrix[curRow][curCol], matrix[curRow-1][curCol]); // swap
		floatUp(curRow-1,curCol); // go up
	}

	// else there is left and up value so find max of the two and swap accordingly
	else
	{
		// if left is largest swap with that
		if (matrix[curRow][curCol-1] > matrix[curRow-1][curCol])
		{
			swap(matrix[curRow][curCol], matrix[curRow][curCol-1]);
			floatUp(curRow,curCol-1); // go left
		}

		// else swap with up
		else
		{
			swap(matrix[curRow][curCol], matrix[curRow-1][curCol]);
			floatUp(curRow-1,curCol); // go up
		}
	}

}

int VNT::getMin()
{
	// start top left
	int row = 0, col = 0;

	// if top left element = int_max, the matrix is empty
	if (matrix[row][col] == INT_MAX)
	{
		cout << "getMin() failed. Matrix empty.";
		return INT_MAX;
	}

	// otherwise, extract top left element and replace with INT_MAX.
	int extracted = matrix[row][col];
	matrix[row][col] = INT_MAX;

	// now 'sink' this element to the bottom to keep 2d array sorted
	sinkDown(row,col);

	return extracted;
}

void VNT::sinkDown(int curRow, int curCol)
{
	// if right and down ok were done
	if ( (curCol+1 == cols || matrix[curRow][curCol+1] >= matrix[curRow][curCol]) // if right ok
		 && 												   				      // and
	     (curRow+1 == rows || matrix[curRow+1][curCol] >= matrix[curRow][curCol]))    // if down ok
		return;


	/* else swap with smallest of either down or right then move in that direction.
	 * Recursively repeat process from that new current pos till ok
	 */

	// if there is no down value, swap with right
	if (curRow+1 == rows)
	{
		swap(matrix[curRow][curCol], matrix[curRow][curCol+1]);
		sinkDown(curRow,curCol+1); // go right
	}

	// else if there is no right value, swap with down
	else if (curCol+1 == cols)
	{
		swap(matrix[curRow][curCol], matrix[curRow+1][curCol]); // swap
		sinkDown(curRow+1,curCol); // go down
	}

	// else there is right and down value so find min of the two and swap accordingly
	else
	{
		// if right is smallest swap with that
		if (matrix[curRow][curCol+1] < matrix[curRow+1][curCol])
		{
			swap(matrix[curRow][curCol], matrix[curRow][curCol+1]);
			sinkDown(curRow,curCol+1); // go right
		}

		// else swap with down
		else
		{
			swap(matrix[curRow][curCol], matrix[curRow+1][curCol]);
			sinkDown(curRow+1,curCol); // go down
		}
	}

}


int main()
{
	VNT a(5,7);
	if(a.find(10))
		cout<<"Find the number 16 in the VNT"<<endl<<endl;
	else
		cout<<"Cannot find the number 16 in the VNT"<<endl<<endl;
	cout<<"Using add function:"<<endl;
	a.add(14);
	cout<<a<<endl;
	a.add(7);
	cout<<a<<endl;
	a.add(11);
	cout<<a<<endl;
	a.add(5);
	cout<<a<<endl;
	a.add(9);
	cout<<a<<endl;
	a.add(6);
	cout<<a<<endl;
	a.add(8);
	cout<<a<<endl;
	a.add(19);
	cout<<a<<endl;
	a.add(16);
	cout<<a<<endl;
	if(a.find(16))
		cout<<"Find the number 16 in the VNT"<<endl<<endl;
	else
		cout<<"Cannot find the number 16 in the VNT"<<endl<<endl;

	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;

	cout<<"Using getMin() function:"<<endl;
	for(int i=0; i<9; i++) {
		cout<<"NO."<<(i+1)<<" : "<<a.getMin()<<endl<<a<<endl;
	}
	int w[7]= {4,7,2,32,75,21,6};
	cout<<"Sort w[7]={4,7,2,32,75,21,6}:"<<endl;
	a.sort(w,7);
	for(int i=0; i<7; i++) {
		cout<<w[i]<<" ";
	}
	cout<<endl;

	return 0;
}
