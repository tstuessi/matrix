#include <vector>
#include <iostream>

using namespace std;

template<typename tElement>
void matrix<tElement>::multRowThenAddToRow(int row1, const tElement &constant, int row2) {
	vector<tElement> temp; //create temp row, fill it with row that is being multiplied, multiply it by constant, add it to last one
	for(int i = 0; i < mMatrix[row1].size(); i++)
		temp.push_back(mMatrix[row1][i]);
	for(int i = 0; i < temp.size(); i++)
		temp[i] *= constant;
	for(int i = 0; i < mMatrix[row2].size(); i++)
		mMatrix[row2][i] += temp[i];
}

template<typename tElement>
void matrix<tElement>::shiftRowToBottom(int row) {
	if(row == mRows -1)
		return;
	switchRows(row, mRows - 1); //switch row that needs to be moved to bottom row
	for(int i = row; i < mRows -2; i++) //shift the row that was switched with original row back to second spot
		switchRows(i, i+1);
}

template<typename tElement>
void matrix<tElement>::solve() {
	for(int i = 0; (i < mColumns - 1 /*cycle to second to last column*/) && (i < mRows); i++) {
		int k = i; //make i a manipulatable number
		while((k < (mColumns -1)) && (mMatrix[i][k] == 0)) { //find leading nonzero number
			int m = k; //again, make k usable
			while((mMatrix[i][k] == 0) && (m < mRows - 1)) { //test for leading nonzero number in same column but in lower rows
				switchRows(m, m+1);
				m++;
			}
			while((k < (mColumns - 1)) && (mMatrix[i][k] == 0)) { //shift to the next column that has a nonzero number
				k++;
			}
			if(k == mColumns) //if row is all zeros
				shiftRowToBottom(i);
		}
		if(k != mColumns) {
			if(mMatrix[i][k] != 0) { 
				tElement y = mMatrix[i][k];
				divideRow(i, y);
			}

			for(int j = 0; j < mRows; j++) {
				if(i == j)
					continue;
				else { //clear the rest of the column (make them be zero)
					tElement b = mMatrix[j][k] * -1;
					multRowThenAddToRow(i, b, j);
				}
			}
		}
	}
}

