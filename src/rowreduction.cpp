//
//  rowreduction.cpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 19/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#include "rowreduction.hpp"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/*
 * Given an NxM matrix (vector of vectors) perform Gauss-Jordan row reduction (in place) to convert the matrix into 
 * reduced row echelon form.
 */
void RowReduce(vector<vector<double>> &matrixExtended)
{
    int numRows = static_cast<int>(matrixExtended.size());
    int numCols = static_cast<int>(matrixExtended[0].size());
    // Operate into echelon form
    for (int iter = 0; iter < numRows; iter++)  // for each diagonal element in the initial matrix
    {   // find the row with the highest magnitude element in that column, but only below the diagonal
        int largestElement = iter;
        for (int row = iter; row < numRows; row++)
            if (abs(matrixExtended[row][iter]) >= abs(matrixExtended[largestElement][iter]))
                largestElement = row;
        
        // swap that row with the diagonal element row, if needed (so that dividing by large numbers later)
        if (!(largestElement == iter))
            swap(matrixExtended[iter],matrixExtended[largestElement]);
        
        // to every row below the current, add a multiple of the current, so that the row in current col = 0
        // for all rows except current
        for (int row = iter + 1; row < numRows; row++)
        {   // determine the scalar multiplier to use
            double multiplier = matrixExtended[row][iter] / matrixExtended[iter][iter];
            // subtract the multiplier*iterRow from the row, element wise
            for (int col = 0; col < numCols; col++)
                matrixExtended[row][col] -= multiplier * matrixExtended[iter][col];
        }
    }
    
    // Further operate into reduced row echelon form, this time starting from the bottom
    for (int iter = numRows - 1; iter >= 0; iter--)
    {   // Determine the divisor so that the row can be multiplied to a leading 1
        double divisor = matrixExtended[iter][iter];
        // divide each col in the row by the divisor
        for (int col = iter; col < numCols; col++)
            matrixExtended[iter][col] = matrixExtended[iter][col] / divisor;
        // to every row above the current, add a multiple of the current,
        for (int row = iter - 1; row >= 0; row--)
        {   // determine the scalar multiplier to use
            double multiplier = matrixExtended[row][iter] / matrixExtended[iter][iter];
            // subtract the multiplier*terRow from the row, element wise
            for (int col = 0; col < numCols; col++)
                matrixExtended[row][col] -= multiplier * matrixExtended[iter][col];
        }
        
    }
}
