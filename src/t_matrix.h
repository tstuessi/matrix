/*------------------------------------------
This is the header file for the entire library. I originally intended for square and augmented matrices to be subclasses of the general matrix class, but subclassing a template did not work as I intended it to work. All the header code is here, and at the bottom it imports the implementations for the functions. This library is especially useful when combined with my fraction library, but since it is template based it can be used with all numerical data types. I would advise against using anything other than numerical data types.
--tstuessi
------------------------------------------*/
#include <iostream>
#include <vector>

using namespace std;

template<typename tElement>
class matrix {
	protected:
		vector< vector<tElement> > mMatrix;
		int mRows;
		int mColumns;
		void deleteRow(int row);
		void deleteColumn(int column);

	public:
		bool operationsError; 

		//constructors
		matrix();
		matrix(vector< vector<tElement> > &matrix);
		matrix(int rows, int columns); //default matrix
		matrix(istream &in); //file constructor

		//output operator
		template<typename tElement1>
		friend ostream & operator<<(ostream &out, const matrix<tElement1> &b);

		//formatted dimensions
		string dimensions() const;

		//accessors
		int getRows() const;
		int getColumns() const;
/*GENERAL MATRIX OPERATIONS---------------------------------*/
		//operations
		void switchRows(int row1, int row2);
		void multiplyRow(int row, const tElement &factor);
		void divideRow(int row, tElement &dividor);

		//operator overloads
		void operator+=(const matrix<tElement> &b);
		void operator-=(const matrix<tElement> &b);
		void operator*=(const tElement &b);
		void operator/=(const tElement &b);
		void operator*=(const matrix<tElement> &b);

		matrix<tElement> operator+(const matrix<tElement> &b) const;
		matrix<tElement> operator-(const matrix<tElement> &b) const;
		matrix<tElement> operator*(const tElement &b) const;
		matrix<tElement> operator/(const tElement &b) const;
		matrix<tElement> operator*(const matrix<tElement> &b) const;

		//transpose
		matrix<tElement> operator!() const;

		//boolean operators
		bool operator==(const matrix<tElement> &b) const;
		bool operator!=(const matrix<tElement> &b) const;

/*---------------augmented matrix operations-----------------------*/
		void multRowThenAddToRow(int row1, const tElement &constant, int row2);
		void shiftRowToBottom(int row);
		void solve();

/*----------------square matrix operations--------------------------*/
		matrix<tElement> inverse();
		tElement determinant();

};

#include "matrix.tpp"
#include "augmentedMatrix.tpp"
#include "squareMatrix.tpp"
