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
    printf("k is: %d \n", k);
    int n1 = 0;
    fscanf(f1, "%d", &n1);
    printf("n1 is: %d \n", n1);
    int n2 = 0;
    fscanf(f2, "%d", &n2);
    printf("n2 is: %d \n", n2);

    // creating training matrix
    double** train = malloc(n1*sizeof(double*));
    int i = 0;
    int j = 0;
    for (i = 0; i < n1; i++) {
        train[i] = malloc((k + 1)*sizeof(double));
        for (j = 0; j < k + 1; j++) {
            train[i][j] = 0;
            fscanf(f1, "%lf", &train[i][j]);
            char ch = 0;
            fscanf(f1, "%c", &ch);
        }
    }

    // creating testing matrix
    double** test = malloc(n2*sizeof(double*));
    for (i = 0; i < n2; i++) {
        test[i] = malloc(k*sizeof(double));
        for (j = 0; j < k; j++) {
            test[i][j] = 0;
            fscanf(f2, "%lf", &test[i][j]);
            printf("%lf \t", test[i][j]);
            char ch = 0;
            fscanf(f2, "%c", &ch);
        }
        printf("\n");
    }

    // creating transpose of train
    double** trainTran = NULL;
    trainTran = transposeMatrix(train, n2, k);
    
    // freeing training
    for (i = 0; i < n1; i++) {
        free(train[i]);
    }
    free(train);

    // freeing testing
    for (i = 0; i < n2; i++) {
        free(test[i]);
    }
    free(test);

	fclose(f1);
    fclose(f2);
	return 0; 
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=malloc(r1*sizeof(double*)); 
    
    // your code goes here
    int i = 0;
    int j = 0;
    for (i = 0; i < r1; i++) {
        result[i] = malloc(c2*sizeof(double));
    }
    
    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{
	double** matTran=malloc(col*sizeof(double*)); 
    
    // your code goes here
    int i = 0;
    int j = 0;
    for (i = 0; i < col; i++) {
        matTran[i] = malloc(row*sizeof(double));
        for (j = 0; j < row; j++) {
            matTran[i][j] = mat[j][i];
            printf("%lf \t", matTran[i][j]);
        }
        printf("\n");
    }
    
    return matTran;        
}


double** inverseMatrix(double **matA, int dimension)
{

    double** matI=malloc(dimension*sizeof(double*)); 

    // your code goes here
    
	return matI;
}

