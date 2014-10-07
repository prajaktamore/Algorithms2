/*
According to slides

Strassen’s matrix multiplication algorithm

     - partition n*n matrix into sub-matrices n/2 * n/2  
       (assume n is power of 2) 
     - apply the seven basic calculations:

     M1 = (A11 + A22)(B11+B22)
     M2 = (A21 + A22) B11
     M3 = A11 (B12 – B22)
     M4 = A22 (B21 – B11)
     M5 = (A11 + A12) B22
     M6 = (A21 – A11) (B11+B12)
     M7 = (A12 – A22)(B21 + B22)

*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*two dimentional Matrix creation n x n*/
int **matrixCreation(int n,int mode);
/*two dimentional Matrix disply n x n*/
void matrixDisplay(int **A,int n);
/*two dimentional Matrix multiplication A * B where columns of A should be equal to rows of B in normal way*/
int **matrixMultiplication(int n,int** A, int** B);
/* Strassen’s matrix multiplication algorithm */
void strassen(int **a, int **b, int **c, int tam);
/*Deallocate the Matrix*/
void matrixFree(int **A, int n);
/*Addition operation required in strassen's matrix multiplciation*/
void addition(int **a, int **b, int **result, int n);
/*Subtraction operation required in strassen's matrix multiplciation*/
void subtraction(int **a, int **b, int **result, int n);

int main(int argc, char **argv)
{

    if(argc<2 || argc !=2 )
    {
        printf("Enter in the following format \n '.slash program_name number'\n");
        exit(0);
    }

    srand (time(NULL));

    int **A,**B,**P,n,i,j;
    n = atoi(argv[1]);

	if(n == 0)
	{
        printf("Enter Value Greater than 0 and power of 2 such that n = 2 ^ k ");
        exit(0);
    }else if(n > 100){
		printf("Enter n < 100 as it can throw STACK OVERFLOW");
        exit(0);
	}
	
    A=matrixCreation(n,1);
    B=matrixCreation(n,1);
    printf("First Matrix\n");
    matrixDisplay(A,n);
    printf("\n\n\n");
    printf("Second Matrix\n");
    matrixDisplay(B,n);
    printf("\n\n\n");
    printf("Normal Matrix Multiplication\n");
    P=matrixMultiplication(n,A,B);
    matrixDisplay(P,n);
    printf("\n\n\n\n\n");

    printf("Strassen Multiplication\n");
    P=matrixCreation(n,1);
    strassen(A,B,P,n);
    matrixDisplay(P,n);
    printf("\n\n\n");

	if(n != 1 && n != 2 && n != 4 && n != 8 && n != 16 && n != 32 && n != 64)
	printf("Entered value is not power of 2. Hence Multiplication is different by Normal and Strassen Methods becuase Strassen works only for power of 2");
	
	return 0;
    }

int **matrixMultiplication(int n,int** A, int** B)
{

    int i,j,k,sum;

    int **P=matrixCreation(n,1);

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            sum = 0;
            for(k=0;k<n;k++)
            {
                sum += A[i][k] * B[k][j];
            }
            P[i][j]=sum;
        }
    }

    return P;
}

void strassen(int **a, int **b, int **c, int tam)
{
    // trivial case: when the matrix is 1 X 1:
    if (tam == 1)
    {
        c[0][0] = a[0][0] * b[0][0];
        return;
    }

    // other cases are treated here:
    int newTam = tam/2;
    int **a11, **a12, **a21, **a22;
    int **b11, **b12, **b21, **b22;
    int **c11, **c12, **c21, **c22;
    int **p1, **p2, **p3, **p4, **p5, **p6, **p7;

    // memory allocation:
    a11 = matrixCreation(newTam, -1);
    a12 = matrixCreation(newTam, -1);
    a21 = matrixCreation(newTam, -1);
    a22 = matrixCreation(newTam, -1);

    b11 = matrixCreation(newTam, -1);
    b12 = matrixCreation(newTam, -1);
    b21 = matrixCreation(newTam, -1);
    b22 = matrixCreation(newTam, -1);

    c11 = matrixCreation(newTam, -1);
    c12 = matrixCreation(newTam, -1);
    c21 = matrixCreation(newTam, -1);
    c22 = matrixCreation(newTam, -1);

    p1 = matrixCreation(newTam, -1);
    p2 = matrixCreation(newTam, -1);
    p3 = matrixCreation(newTam, -1);
    p4 = matrixCreation(newTam, -1);
    p5 = matrixCreation(newTam, -1);
    p6 = matrixCreation(newTam, -1);
    p7 = matrixCreation(newTam, -1);

    int **aResult = matrixCreation(newTam, -1);
    int **bResult = matrixCreation(newTam, -1);

    int i, j;

    //dividing the matrices in 4 sub-matrices:
    for (i = 0; i < newTam; i++)
    {
        for (j = 0; j < newTam; j++)
        {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + newTam];
            a21[i][j] = a[i + newTam][j];
            a22[i][j] = a[i + newTam][j + newTam];

            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + newTam];
            b21[i][j] = b[i + newTam][j];
            b22[i][j] = b[i + newTam][j + newTam];
        }
    }

    // Calculating p1 to p7:

    addition(a11, a22, aResult, newTam); // a11 + a22
    addition(b11, b22, bResult, newTam); // b11 + b22
    strassen(aResult, bResult, p1, newTam); // p1 = (a11+a22) * (b11+b22)

    addition(a21, a22, aResult, newTam); // a21 + a22
    strassen(aResult, b11, p2, newTam); // p2 = (a21+a22) * (b11)

    subtraction(b12, b22, bResult, newTam); // b12 - b22
    strassen(a11, bResult, p3, newTam); // p3 = (a11) * (b12 - b22)

    subtraction(b21, b11, bResult, newTam); // b21 - b11
    strassen(a22, bResult, p4, newTam); // p4 = (a22) * (b21 - b11)

    addition(a11, a12, aResult, newTam); // a11 + a12
    strassen(aResult, b22, p5, newTam); // p5 = (a11+a12) * (b22)

    subtraction(a21, a11, aResult, newTam); // a21 - a11
    addition(b11, b12, bResult, newTam); // b11 + b12
    strassen(aResult, bResult, p6, newTam); // p6 = (a21-a11) * (b11+b12)

    subtraction(a12, a22, aResult, newTam); // a12 - a22
    addition(b21, b22, bResult, newTam); // b21 + b22
    strassen(aResult, bResult, p7, newTam); // p7 = (a12-a22) * (b21+b22)

    // calculating c21, c21, c11 e c22:

    addition(p3, p5, c12, newTam); // c12 = p3 + p5
    addition(p2, p4, c21, newTam); // c21 = p2 + p4

    addition(p1, p4, aResult, newTam); // p1 + p4
    addition(aResult, p7, bResult, newTam); // p1 + p4 + p7
    subtraction(bResult, p5, c11, newTam); // c11 = p1 + p4 - p5 + p7

    addition(p1, p3, aResult, newTam); // p1 + p3
    addition(aResult, p6, bResult, newTam); // p1 + p3 + p6
    subtraction(bResult, p2, c22, newTam); // c22 = p1 + p3 - p2 + p6

    // Grouping the results obtained in a single matrix:
    for (i = 0; i < newTam ; i++) {
    for (j = 0 ; j < newTam ; j++) {
    c[i][j] = c11[i][j];
    c[i][j + newTam] = c12[i][j];
    c[i + newTam][j] = c21[i][j];
    c[i + newTam][j + newTam] = c22[i][j];
    }
    }

    // deallocating memory (free):
    matrixFree(a11, newTam);
    matrixFree(a12, newTam);
    matrixFree(a21, newTam);
    matrixFree(a22, newTam);

    matrixFree(b11, newTam);
    matrixFree(b12, newTam);
    matrixFree(b21, newTam);
    matrixFree(b22, newTam);

    matrixFree(c11, newTam);
    matrixFree(c12, newTam);
    matrixFree(c21, newTam);
    matrixFree(c22, newTam);

    matrixFree(p1, newTam);
    matrixFree(p2, newTam);
    matrixFree(p3, newTam);
    matrixFree(p4, newTam);
    matrixFree(p5, newTam);
    matrixFree(p6, newTam);
    matrixFree(p7, newTam);
    matrixFree(aResult, newTam);
    matrixFree(bResult, newTam);

} // end of Strassen function

//Add two matrices
void addition(int **a, int **b, int **result, int n)
{

    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
        }
    }

// Subtract two matrices
void subtraction(int **a, int **b, int **result, int n)
{

    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

void matrixDisplay(int **A,int n)
{

    int i,j;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d \t",A[i][j]);
        }
        printf("\n\n");
    }

}

int **matrixCreation(int n,int mode)
{

    int i,j;
    int num;
    int** A = (int**)malloc(n*sizeof(int*));

    for (i = 0; i < n; i++)
    {
        A[i] = (int*)malloc(n*sizeof(int));
    }

    if(mode==1)
    {

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                num = rand()%100 + 1; //Allocate random numbers from 1-100 to n*n matrix
                A[i][j] = num;
            }
        }
    }

    return A;
}

void matrixFree(int **A, int n)
{

    int i;

    if (A == NULL)
    {
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (A[i])
        {
            free(A[i]); // frees a row of the matrix
            A[i] = NULL;
        }
    }

    free(A); // frees the pointer /
    A = NULL;

}
