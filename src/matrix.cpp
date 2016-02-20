//
//  rowreduction.cpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 19/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#include "matrix.hpp"
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
    for (int iter = 0; iter < numRows; iter++)
    {
        // find and swap rows
        int largestElement = iter;
        for (int row = iter; row < numRows; row++)
            if (abs(matrixExtended[row][iter]) >= abs(matrixExtended[largestElement][iter]))
                largestElement = row;
        

        if (!(largestElement == iter))
            swap(matrixExtended[iter],matrixExtended[largestElement]);
        
        // subtract scalar multiple of current row from every row below, so that only one non-zero value in column
        for (int row = iter + 1; row < numRows; row++)
        {
            double multiplier = matrixExtended[row][iter] / matrixExtended[iter][iter];
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

/*
 * Given a matrix A, invert it (B) such that AB = I. The matrix must be square.
 */
vector<vector<double>> Invert(vector<vector<double>> &matrix)
{
    // Generate an extended matrix, by adding the relevant Identity matrix to the right
    vector<vector<double>> toInvert;
    toInvert.resize(matrix.size());
    for (int row = 0; row < matrix.size(); row++)
    {
        toInvert[row].resize(matrix.size() * 2);
        for (int col = 0; col < toInvert[row].size(); col++)
        {
            if (col < matrix.size())
                toInvert[row][col] = matrix[row][col];
            else if ((col - matrix.size()) == row)
                toInvert[row][col] = 1;
            else
                toInvert[row][col] = 0;
        }
    }
    // Row reduce to get the inverted matrix, and extract the inverted matrix
    RowReduce(toInvert);
    vector<vector<double>> inverted;
    inverted.resize(matrix.size());
    for (int row = 0; row < matrix.size(); row++)
    {
        inverted[row].resize(matrix.size());
        for (int col = 0; col < matrix.size(); col++)
            inverted[row][col] = toInvert[row][col + matrix.size()];
    }
    
    
    return inverted;
}

/*
 * Given a matrix A, and a vector b, solve for x the equation Ax = b.
 */
vector<double> Solve(vector<vector<double>> &matrix, vector<double> &vector)
{
    // Generate an extended matrix, by adding the vector as a column of the matrix
    std::vector<std::vector<double>> toSolve;
    toSolve.resize(matrix.size());
    for (int row = 0; row < matrix.size(); row++)
    {
        toSolve[row].resize(matrix.size() + 1);
        for (int col = 0; col < toSolve[row].size(); col++)
        {
            if (col < matrix.size())
                toSolve[row][col] = matrix[row][col];
            else
                toSolve[row][col] = vector[row];
        }
    }
    // Perform row reduction to solve, and extract the last column as the solution
    RowReduce(toSolve);
    std::vector<double> result;
    result.resize(matrix.size());
    for (int row = 0; row < matrix.size(); row++)
        result[row] = toSolve[row][matrix.size()];
    

    return result;
    
}

/*
 * Given an NxN matrix A, calculate the determinant
 */
double Determinant(std::vector<std::vector<double>> &matrix)
{
    // make a copy of the matrix
    vector<vector<double>> toDeterminate;
    toDeterminate.resize(matrix.size());
    for (int row = 0; row < matrix.size(); row++)
    {
        toDeterminate[row].resize(matrix[row].size());
        for (int col = 0; col < matrix[row].size(); col++)
            toDeterminate[row][col] = matrix[row][col];
    }
    
    // use row operations to get into row echelon form
    // yes code is duplicated, but meh
    int numRows = static_cast<int>(toDeterminate.size());
    int numCols = static_cast<int>(toDeterminate[0].size());
    double determinant = 1;
    // Operate into echelon form
    for (int iter = 0; iter < numRows; iter++)
    {
        // find and swap rows
        int largestElement = iter;
        for (int row = iter; row < numRows; row++)
            if (abs(toDeterminate[row][iter]) >= abs(toDeterminate[largestElement][iter]))
                largestElement = row;
        
        
        if (!(largestElement == iter))
        {
            // each row swap multiplies the determinant by -1
            swap(toDeterminate[iter],toDeterminate[largestElement]);
            determinant *= -1;
        }
        
        // subtract scalar multiple of current row from every row below, so that only one non-zero value in column
        for (int row = iter + 1; row < numRows; row++)
        {
            double multiplier = toDeterminate[row][iter] / toDeterminate[iter][iter];
            for (int col = 0; col < numCols; col++)
                toDeterminate[row][col] -= multiplier * toDeterminate[iter][col];
        }
    }
    // final determinant is then the product of the diagonal values
    for (int diag = 0; diag < toDeterminate.size(); diag++)
        determinant *= toDeterminate[diag][diag];
    return determinant;
}