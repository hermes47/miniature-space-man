//
//  rowreduction.hpp
//  miniature-space-man
//
//  Created by Ivan Welsh on 19/02/16.
//  Copyright © 2016 Ivan Welsh. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <vector>
/*
 * Given an NxM matrix (vector of vectors) perform Gauss-Jordan row reduction (in place) to convert the matrix into
 * reduced row echelon form.
 */
void RowReduce(std::vector<std::vector<double>> &matrix);

/*
 * Given a matrix A, invert it (B) such that AB = I. The matrix must be square.
 */
std::vector<std::vector<double>> Invert(std::vector<std::vector<double>> &matrix);

/*
 * Given a matrix A, and a vector b, solve for x the equation Ax = b.
 */
std::vector<double> Solve(std::vector<std::vector<double>> &matrix, std::vector<double> &vector);

#endif /* matrix_hpp */
