#include <stdio.h>
#define max 10

int sparse(int a[][max], int b[][max], int row, int col);
void add(int a[][max], int aSize, int b[][max], int bSize, int sum[][max], int *sumSize, int rows, int cols);
void display(int a[][max], int size);
void transpose(int a[][max], int transposed[][max], int row, int col, int *transposedSize);

int main() {
    int mat[max][max], s[max][max], sum[max][max];
    int i, j, row, col, con, ch, sr, sumSize, transposedSize;

    printf("Enter number of rows and columns in the matrix: ");
    scanf("%d%d", &row, &col);

    printf("Enter the numbers:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    printf("The matrix is:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }

    sr = sparse(mat, s, row, col);
    printf("\nSparse Matrix Representation:\n");
    display(s, sr);

    do {
        printf("\nChoose an option:\n1. Addition\n2. Transpose\n");
        scanf("%d", &ch);

        switch (ch) {
            case 1: {
                int b[max][max], sec[max][max], l;
                printf("Enter the number of rows and columns of the second matrix: ");
                scanf("%d%d", &row, &col);

                printf("Enter the numbers:\n");
                for (i = 0; i < row; i++) {
                    for (j = 0; j < col; j++) {
                        scanf("%d", &b[i][j]);
                    }
                }

                printf("The matrix is:\n");
                for (i = 0; i < row; i++) {
                    for (j = 0; j < col; j++) {
                        printf("%d\t", b[i][j]);
                    }
                    printf("\n");
                }

                l = sparse(b, sec, row, col);
                printf("\n-Sparse Matrix Representation-\n");
                display(sec, l);

                if (s[0][0] == sec[0][0] && s[0][1] == sec[0][1]) {
                    sumSize = 0;
                    int rows = s[0][0], cols = s[0][1];
                    add(s, sr, sec, l, sum, &sumSize, rows, cols);
                    printf("\nSum of Sparse Matrices:\n");
                    display(sum, sumSize);
                } else {
                    printf("Matrix dimensions do not match for addition.\n");
                }
            }
            break;

            case 2: {
                int transposed[max][max];
                transpose(mat, transposed, row, col, &transposedSize);
                printf("\nTranspose Sparse Matrix Representation:\n");
                display(transposed, transposedSize);
            }
            break;

            default:
                printf("Invalid Choice\n");
        }

        printf("\nDo you wish to continue? If Yes Press 1: ");
        scanf("%d", &con);
    } while (con == 1);

    return 0;
}

int sparse(int a[][max], int b[][max], int row, int col) {
    int k = 1, i, j;
    b[0][0] = row;
    b[0][1] = col;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (a[i][j] != 0) {
                b[k][0] = i;
                b[k][1] = j;
                b[k][2] = a[i][j];
                k++;
            }
        }
    }

    b[0][2] = k - 1;
    return k - 1;
}

void display(int a[][max], int size) {
    int i, j;
    for (i = 0; i <= size; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

void add(int a[][max], int aSize, int b[][max], int bSize, int sum[][max], int *sumSize, int rows, int cols) {
    int i = 1, j = 1, k = 1;

    while (i <= aSize && j <= bSize) {
        if (a[i][0] == b[j][0] && a[i][1] == b[j][1]) {
            sum[k][0] = a[i][0];
            sum[k][1] = a[i][1];
            sum[k][2] = a[i][2] + b[j][2];
            i++;
            j++;
        } else if (a[i][0] < b[j][0] || (a[i][0] == b[j][0] && a[i][1] < b[j][1])) {
            sum[k][0] = a[i][0];
            sum[k][1] = a[i][1];
            sum[k][2] = a[i][2];
            i++;
        } else {
            sum[k][0] = b[j][0];
            sum[k][1] = b[j][1];
            sum[k][2] = b[j][2];
            j++;
        }
        k++;
    }

    while (i <= aSize) {
        sum[k][0] = a[i][0];
        sum[k][1] = a[i][1];
        sum[k][2] = a[i][2];
        i++;
        k++;
    }

    while (j <= bSize) {
        sum[k][0] = b[j][0];
        sum[k][1] = b[j][1];
        sum[k][2] = b[j][2];
        j++;
        k++;
    }

    *sumSize = k - 1;
    sum[0][0] = rows;
    sum[0][1] = cols;
    sum[0][2] = *sumSize;
}

void transpose(int a[][max], int transposed[][max], int row, int col, int *transposedSize) {
    int i, j;
    transposed[0][0] = col;
    transposed[0][1] = row;
    int k = 1;

    for (i = 0; i < col; i++) {
        for (j = 0; j < row; j++) {
            if (a[j][i] != 0) {
                transposed[k][0] = i;
                transposed[k][1] = j;
                transposed[k][2] = a[j][i];
                k++;
            }
        }
    }

    transposed[0][2] = k - 1;
    *transposedSize = k - 1;
}

OUPUT

Enter number of rows and columns in the matrix: 3
3
Enter the numbers:
0 0 1 0 1 0 2 0 0
The matrix is:
0	0	1	
0	1	0	
2	0	0	

Sparse Matrix Representation:
3	3	3	
0	2	1	
1	1	1	
2	0	2	

Choose an option:
1. Addition
2. Transpose
1
Enter the number of rows and columns of the second matrix: 3
3
Enter the numbers:
0 0 1 0 2 0 2 0 0
The matrix is:
0	0	1	
0	2	0	
2	0	0	

-Sparse Matrix Representation-
3	3	3	
0	2	1	
1	1	2	
2	0	2	

Sum of Sparse Matrices:
3	3	3	
0	2	2	
1	1	3	
2	0	4	

Do you wish to continue? If Yes Press 1: 1

Choose an option:
1. Addition
2. Transpose
2

Transpose Sparse Matrix Representation:
3	3	3	
0	2	2	
1	1	1	
2	0	1	

Do you wish to continue? If Yes Press 1: 0
ubuntu@ubuntu:~/SCS1051123$ 
