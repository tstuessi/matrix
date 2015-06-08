#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <sstream>

const int ELEM_WIDTH = 8;

template<typename tElement>
void matrix<tElement>::deleteRow(int row) {
	mMatrix.erase(mMatrix.begin() + row);
	mRows -= 1;
}

template<typename tElement>
void matrix<tElement>::deleteColumn(int column) {
	for(int i = 0; i < mRows; i++) {
		mMatrix[i].erase(mMatrix[i].begin() + column);
	}
	mColumns -= 1;
}

template<typename tElement>
matrix<tElement>::matrix() {
	mRows = 0;
	mColumns = 0;
	operationsError = false;
}

template<typename tElement>
matrix<tElement>::matrix(vector< vector<tElement> > &matrix) {
	int i;
	int j;
	for(i = 0; i < matrix.size(); i++) {
		mMatrix.push_back(vector<tElement>());
		for(j = 0; j < matrix[i].size(); j++) {
			mMatrix[i].push_back(matrix[i][j]);
		}
	}
	mRows = i;
	mColumns = j;
	operationsError = false;
}

template<typename tElement>
matrix<tElement>::matrix(int rows, int columns) {
	mRows = rows;
	mColumns = columns;
	for(int i = 0; i < mRows; i++) {
		mMatrix.push_back(vector<tElement>());
		for(int j = 0; j < mColumns; j++) {
			if(i == j) {
				tElement b = 1;
				mMatrix[i].push_back(b);
			}
			else
				mMatrix[i].push_back(tElement());
		}
	}
	operationsError = false;
}

template<typename tElement>
matrix<tElement>::matrix(istream &in) {
	in >> mRows >> mColumns;
	//add check for []
	for(int i = 0; i < mRows; i++) {
		mMatrix.push_back(vector<tElement>());
		for(int j = 0; j < mColumns; j++) {
			tElement temp;
			in >> temp;
			mMatrix[i].push_back(temp);
		}
	}
	if(mMatrix.size() != mRows) {
		cerr << "input error code 1" << endl;
		exit(0);
	} else {
		for(int i = 0; i < mMatrix.size(); i++) {
			if(mMatrix[i].size() != mColumns) {
				cerr << "input error code 2" << endl;
				exit(0);
			}
		}
	}
	operationsError = false;
}

template<typename tElement1>
ostream & operator<<(ostream &out, const matrix<tElement1> &b) {
	if(b.operationsError)
		out << "operations error" << endl;
	else {
		out << "[";
		for(int i = 0; i < b.mRows; i++) {
			for(int j = 0; j < b.mColumns; j++) {
				out << setw(ELEM_WIDTH) << b.mMatrix[i][j];
			}
			if(i < b.mRows - 1)
				out << endl << " ";
		}
		out << " ]" << endl << endl;
	}
	return out;
}

template<typename tElement>
string matrix<tElement>::dimensions() const {
	stringstream ss;
	ss << mRows << "x" << mColumns;
	string s = ss.str();
	return s;
}

template<typename tElement>
int matrix<tElement>::getRows() const {
	return mRows;
}

template<typename tElement>
int matrix<tElement>::getColumns() const {
	return mColumns;
}

template<typename tElement>
void matrix<tElement>::switchRows(int row1, int row2) {
	vector<tElement> temp;
	for(int i = 0; i < mMatrix[row1].size(); i++)
		temp.push_back(mMatrix[row1][i]);
	for(int i = 0; i < mMatrix[row1].size(); i++)
		mMatrix[row1][i] = mMatrix[row2][i];
	for(int i = 0; i < temp.size(); i++)
		mMatrix[row2][i] = temp[i];
}

template<typename tElement>
void matrix<tElement>::multiplyRow(int row, const tElement &factor) {
	for(int i = 0; i < mMatrix[row].size(); i++)
		mMatrix[row][i] *= factor;
}

template<typename tElement>
void matrix<tElement>::divideRow(int row, tElement &dividor) {
	for(int i = 0; i < mMatrix[row].size(); i++) {
		mMatrix[row][i] /= dividor;
	}
}

//self assignment operators
template<typename tElement>
void matrix<tElement>::operator+=(const matrix<tElement> &b) {
	if((mRows != b.mRows) || (mColumns != b.mColumns)) {
		operationsError = true;
		return;
	}
	for(int i = 0; i < mMatrix.size(); i++) {
		for(int j = 0; j < mMatrix[i].size(); j++)
			mMatrix[i][j] += b.mMatrix[i][j];
	}
}

template<typename tElement>
void matrix<tElement>::operator-=(const matrix<tElement> &b) {
	if((mRows != b.mRows) || (mColumns != b.mColumns)) {
		operationsError = true;
		return;
	}
	for(int i = 0; i < mMatrix.size(); i++) {
		for(int j = 0; j < mMatrix[i].size(); j++)
			mMatrix[i][j] -= b.mMatrix[i][j];
	}
}

template<typename tElement>
void matrix<tElement>::operator*=(const tElement &b) {
	for(int i = 0; i < mMatrix.size(); i++) {
		for(int j = 0; j < mMatrix[i].size(); j++)
			mMatrix[i][j] *= b;
	}
}

template<typename tElement>
void matrix<tElement>::operator/=(const tElement &b) {
	for(int i = 0; i < mMatrix.size(); i++) {
		for(int j = 0; j < mMatrix[i].size(); j++)
			mMatrix[i][j] /= b;
	}
}

template<typename tElement>
void matrix<tElement>::operator*=(const matrix<tElement> &b) {
	matrix<tElement> a = *this;
	if(a.mColumns != b.mRows) {
		operationsError = true;
		return;
	}

	mRows = a.mRows;
	mColumns = b.mColumns;
	mMatrix.clear();

	for(int i = 0; i < mRows; i++) {
		mMatrix.push_back(vector<tElement>());
		for(int j = 0; j < mColumns; j++) {
			tElement temp;
			for(int k = 0; k < a.mColumns; k++) {
				temp += a.mMatrix[i][k] * b.mMatrix[k][j];
			}
			mMatrix[i].push_back(temp);
		}
	}
}

//operations that return a matrix<tElement>
template<typename tElement>
matrix<tElement> matrix<tElement>::operator+(const matrix<tElement> &b) const {
	matrix<tElement> c = *this;
	c += b;
	return c;
}

template<typename tElement>
matrix<tElement> matrix<tElement>::operator-(const matrix<tElement> &b) const {
	matrix<tElement> c = *this;
	c -= b;
	return c;
}

template<typename tElement>
matrix<tElement> matrix<tElement>::operator*(const tElement &b) const {
	matrix<tElement> c = *this;
	c *= b;
	return c;
}

template<typename tElement>
matrix<tElement> matrix<tElement>::operator/(const tElement &b) const {
	matrix<tElement> c = *this;
	c /= b;
	return c;
}

template<typename tElement>
matrix<tElement> matrix<tElement>::operator*(const matrix<tElement> &b) const {
	matrix<tElement> c = *this;
	c *= b;
	return c;
}

template<typename tElement>
matrix<tElement> matrix<tElement>::operator!() const {
	matrix<tElement> c = *this;
	matrix<tElement> d;
	for(int i = 0; i < c.mMatrix[0].size(); i++) {
		d.mMatrix.push_back(vector<tElement>());
		for(int j = 0; j < c.mMatrix.size(); j++)
			d.mMatrix[i].push_back(c.mMatrix[j][i]);
	}
	d.mRows = c.mColumns;
	d.mColumns = c.mRows;

	return d;
}

template<typename tElement>
bool matrix<tElement>::operator==(const matrix<tElement> &b) const {
	if((mRows != b.mColumns) || (mColumns != b.mColumns))
		return false;
	for(int i = 0; i < mMatrix.size(); i++) {
		for(int j = 0; j < mMatrix[i].size(); j++) {
			if(mMatrix[i][j] != b.mMatrix[i][j])
				return false;
		}
	}
	return true;
}

template<typename tElement>
bool matrix<tElement>::operator!=(const matrix<tElement> &b) const {
	matrix c = *this;
	return !(c == b);
}

