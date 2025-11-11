#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gaussDeterminant(double **matrix, int n) {
    double det = 1.0;
    
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(matrix[j][i]) > fabs(matrix[pivot][i])) {
                pivot = j;
            }
        }
        
        if (fabs(matrix[pivot][i]) < 1e-10) {
            return 0.0;
        }
        
        if (pivot != i) {
            det = -det; 
            double *temp = matrix[i];
            matrix[i] = matrix[pivot];
            matrix[pivot] = temp;
        }
        
        det *= matrix[i][i];
        
        for (int j = i + 1; j < n; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
    
    return det;
}

double** createMatrix(int n) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }
    return matrix;
}


void freeMatrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    
    printf("请输入矩阵的阶数: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("阶数必须大于0！\n");
        return 1;
    }
    
    double **matrix = createMatrix(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
    
    printf("\n输入的矩阵:\n");
    printMatrix(matrix, n);
    
    double det = gaussDeterminant(matrix, n);
    printf("\n行列式的值: %.6f\n", det);
    
    freeMatrix(matrix, n);
    
    return 0;
}
