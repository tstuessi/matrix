#include <vector>
#include <cmath>

using namespace std;

template<typename tElement>
matrix<tElement> matrix<tElement>::inverse() {
	if(mRows != mColumns) {
		operationsError = true;
		return *this;
	}
	matrix<tElement> c = *this;
	matrix<tElement> d(c.mRows, c.mColumns);

	for(int i = 0; (i < c.mRows) && (i < c.mColumns); i++) {
		int k = i;
		while((k < c.mColumns) && (c.mMatrix[i][k] == 0)) {
			int m = k;
			while((m < c.mRows - 1) && (c.mMatrix[i][k] == 0)) {
				c.switchRows(m, m+1);
				d.switchRows(m, m+1);
				m++;
			}
			while((k < mColumns) && (c.mMatrix[i][k] == 0)) 
				k++;
			if(k == mColumns) {
				c.shiftRowToBottom(i);
				d.operationsError = true;
				return d;
			}
		}
		if(k != mColumns) {
			if(c.mMatrix[i][k] != 0) {
				tElement b = c.mMatrix[i][k];
				c.divideRow(i, b);
				d.divideRow(i, b);
			}
			for(int j = 0; j < c.mRows; j++) {
				if(i == j)
					continue;
				else {
					tElement b = c.mMatrix[j][k] * -1;
					c.multRowThenAddToRow(i, b, j);
					d.multRowThenAddToRow(i, b, j);
				}
			}
		}
	}
	return d;
}

template<typename tElement>
tElement matrix<tElement>::determinant() {
	if(mRows != mColumns) {
		operationsError = true;
		return tElement();
	}
	if((mRows == 1) && (mColumns == 1)) {
		return mMatrix[0][0];
	} else {
		matrix b = *this;
		tElement determinant = 0;
		for(int j = 0; j < b.mColumns; j++) {
			matrix c = b;
			c.deleteRow(0);
			c.deleteColumn(j);
			determinant += mMatrix[0][j] * (c.determinant() * (int)pow(-1, j));
		}
		return determinant;
	}
}
