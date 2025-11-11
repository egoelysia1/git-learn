#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int inversionCount(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                count++;
            }
        }
    }
    return count;
}

double determinantByDefinition(double **matrix, int n) {
    double det = 0.0;

    int *permutation = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        permutation[i] = i;
    }
    
    int *c = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        c[i] = 0;
    }
    
    int inv_count = inversionCount(permutation, n);
    double product = 1.0;
    for (int i = 0; i < n; i++) {
        product *= matrix[i][permutation[i]];
    }
    det += (inv_count % 2 == 0) ? product : -product;
    
    int i = 0;
    while (i < n) {
        if (c[i] < i) {
            if (i % 2 == 0) {
                swap(&permutation[0], &permutation[i]);
            } else {
                swap(&permutation[c[i]], &permutation[i]);
            }
            
            inv_count = inversionCount(permutation, n);
            product = 1.0;
            for (int j = 0; j < n; j++) {
                product *= matrix[j][permutation[j]];
            }
            det += (inv_count % 2 == 0) ? product : -product;
            
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
    
    free(permutation);
    free(c);
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
    int n;;
    printf("请输入矩阵的阶数 : ");
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
    
    double det = determinantByDefinition(matrix, n);
    printf("行列式的值: %.10f\n", det);
    
    freeMatrix(matrix, n);
    
    return 0;
}
