/* 
 * 
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */
 
#include<stdio.h>
#include<stdlib.h>

// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);
// my method declarations
void freeMatrix(double **mat, int row);
double** createIdentity(int dimension);
void multiplyRow(double **mat, int row, int dimension, double f);
void addToRow(double **mat, int row, int factorRow, int dimension, double f);

// main method starts here
int main(int argc, char** argv){

    // your code goes here
    FILE *f1 = fopen(argv[1], "r");
    if (f1 == NULL) {
        printf("error");
        return 0;
    }
    FILE *f2 = fopen(argv[2], "r");
    if (f2 == NULL) {
        printf("error");
        return 0;
    }
    int k = 0; 
    fscanf(f1, "%d", &k);
    int n1 = 0;
    fscanf(f1, "%d", &n1);
    int n2 = 0;
    fscanf(f2, "%d", &n2);

    // creating training and prices matrix
    double** train = calloc(n1,sizeof(double*));
    double** prices = calloc(n1,sizeof(double*));
    int i = 0;
    int j = 0;
    for (i = 0; i < n1; i++) {
        train[i] = calloc((k + 1),sizeof(double));
        prices[i] = calloc(1, sizeof(double));
        for (j = 0; j < k + 1; j++) {
            train[i][j] = 0;
            if (j == 0) {
                train[i][j] = 1.0;
                continue;
            }
            fscanf(f1, "%lf", &train[i][j]);
            char ch = 0;
            fscanf(f1, "%c", &ch);
        }
        prices[i][0] = 0;
        fscanf(f1, "%lf", &prices[i][0]);
    }

    // creating testing matrix
    double** test = calloc(n2, sizeof(double*));
    for (i = 0; i < n2; i++) {
        test[i] = calloc((k + 1), sizeof(double));
        for (j = 0; j < k + 1; j++) {
            test[i][j] = 0;
            if (j == 0) {
                test[i][j] = 1.0;
                continue;
            }
            fscanf(f2, "%lf", &test[i][j]);
            char ch = 0;
            fscanf(f2, "%c", &ch);
        }
    }

    // creating transpose of train
    double** trainTran = transposeMatrix(train, n1, k + 1);

    // multiplying transpose by itself
    double** AAT = multiplyMatrix(trainTran, train, k + 1, n1, n1, k + 1);

    // getting inverse 
    double** inverse = inverseMatrix(AAT, k + 1);
   
    // multiply X^T by Y
    double** XtY = multiplyMatrix(trainTran, prices, k + 1, n1, n1, 1);

    // multiple inverse by XtY
    double** weight = multiplyMatrix(inverse, XtY, k + 1, k + 1, k + 1, 1);

    // final prices
    double** estimatedPrices = multiplyMatrix(test, weight, n2, k + 1, k + 1, 1);

    for (i = 0; i < n2; i++) {
        printf("%0.0lf \n", estimatedPrices[i][0]);
    }
    
    freeMatrix(train, n1);
    freeMatrix(prices, n1);
    freeMatrix(test, n2);
    freeMatrix(trainTran, k + 1);
    freeMatrix(AAT, k + 1);
    freeMatrix(inverse, k + 1);
    freeMatrix(XtY, k + 1);
    freeMatrix(weight, k + 1);
    freeMatrix(estimatedPrices, n2);

	fclose(f1);
    fclose(f2);
	return 0; 
}

void freeMatrix(double **mat, int row) {
    int i = 0;
    for (i = 0; i < row; i++) {
        free(mat[i]);
    }
    free(mat);
}

double** createIdentity(int dimension) {
    double** identity = calloc(dimension,sizeof(double*));
    int i = 0;
    for (i = 0; i < dimension; i++) {
        identity[i] = calloc(dimension,sizeof(double));
        identity[i][i] = 1;
    }
    return identity;
}

void multiplyRow(double** mat, int row, int dimension, double f) {
    int i = 0;
    for (i = 0; i < dimension; i++) {
        mat[row][i] = mat[row][i] * f;
    }
}

void addToRow(double** mat, int row, int factorRow, int dimension, double f) {
    int i = 0;
    for (i = 0; i < dimension; i++) {
        mat[row][i] = mat[row][i] - mat[factorRow][i]*f;
    }
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=calloc(r1,sizeof(double*)); 
    
    // your code goes here
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; i < r1; i++) {
        result[i] = calloc(c2,sizeof(double));
        for (j = 0; j < c2; j++) {
            double total = 0;
            for (k = 0; k < c1; k++) {
                total += (matA[i][k] * matB[k][j]);
            }
            result[i][j] = total;
        }
    }
    
    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{
	double** matTran=calloc(col,sizeof(double*)); 
    
    // your code goes here
    int i = 0;
    int j = 0;
    for (i = 0; i < col; i++) {
        matTran[i] = calloc(row,sizeof(double));
        for (j = 0; j < row; j++) {
            matTran[i][j] = mat[j][i];
        }
    }
    
    return matTran;        
}


double** inverseMatrix(double **matA, int dimension)
{

    double** matI=calloc(dimension,sizeof(double*)); 
    double** identity = createIdentity(dimension);

    int i = 0;
    int j = 0;

    for (i = 0; i < dimension; i++) {
        matI[i] = calloc(dimension,sizeof(double));
        for (j = 0; j < dimension; j++) {
            matI[i][j] = matA[i][j];
        }
    }

    for (i = 0; i < dimension; i++) {
        double f = matI[i][i];
        multiplyRow(matI, i, dimension, 1.0/f);
        multiplyRow(identity, i, dimension, 1.0/f);
        for (j = i + 1; j < dimension; j++) {
            f = matI[j][i];
            addToRow(matI, j, i, dimension, f);
            addToRow(identity, j, i, dimension, f);
        }
    }
    for (i = dimension - 1; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            double f = matI[j][i];
            addToRow(matI, j, i, dimension, f);
            addToRow(identity, j, i, dimension, f);
        }
    }

    // your code goes here
    freeMatrix(matI, dimension);
	return identity;
}