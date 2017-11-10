/*
    Name: Strassen
    Copyright: 
    Author: Json Lee
    Description: 
    Divide and Conquer,
    P1=A11*(B12-B22)
    P2=(A11+A12)*B22
    P3=(A21+A22)*B11
    P4=A22*(B21-B11)
    P5=(A11+A22)*(B11+B22)
    P6=(A12-A22)*(B21+B22)
    P7=(A11-A21)*(B11+B12)
    
    C11=P4+P5+P6-P2
    C12=P1+P2
    C21=P3+P4
    C22=P1+P5-P3-P7
*/
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sys/time.h>
using namespace std;

//add two matrices 
void add(double** MatrixA, double** MatrixB, double** MatrixResult, int MatrixSize)
{
    for (int i = 0; i < MatrixSize; i++)
    {
        for (int j = 0; j < MatrixSize; j++)
        {
            MatrixResult[i][j] = MatrixA[i][j] + MatrixB[i][j];
        }
    }
}

//two matrices subtraction operation  
void sub(double** MatrixA, double** MatrixB, double** MatrixResult, int MatrixSize)
{
    for (int i = 0; i < MatrixSize; i++)
    {
        for (int j = 0; j < MatrixSize; j++)
        {
            MatrixResult[i][j] = MatrixA[i][j] - MatrixB[i][j];
        }
    }
}

//two matrices multiply operation
void mul(double** MatrixA, double** MatrixB, double** MatrixResult, int MatrixSize)
{
    for (int i = 0; i<MatrixSize; i++)
    {
        for (int j = 0; j<MatrixSize; j++)
        {
            MatrixResult[i][j] = 0;
            for (int k = 0; k<MatrixSize; k++)
            {
                MatrixResult[i][j] = MatrixResult[i][j] + MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }
}

void strassen(int N, double** MatrixA, double** MatrixB, double** MatrixC)
{
    int HalfSize = N / 2;
    int newSize = N / 2;

    if (N <= 64)    //n<=64 take normal method
    {
        mul(MatrixA, MatrixB, MatrixC, N);
    }
    else
    {
        double** A11;double** A12;double** A21;double** A22;
        double** B11;double** B12;double** B21;double** B22;
        double** C11;double** C12;double** C21;double** C22;
        double** M1;double** M2;double** M3;double** M4;double** M5;double** M6;double** M7;
        double** AResult;double** BResult;

        //making a 1 diminsional pointer based array.
        A11 = new double *[newSize];A12 = new double *[newSize];A21 = new double *[newSize];A22 = new double *[newSize];
        B11 = new double *[newSize];B12 = new double *[newSize];B21 = new double *[newSize];B22 = new double *[newSize];
        C11 = new double *[newSize];C12 = new double *[newSize];C21 = new double *[newSize];C22 = new double *[newSize];
        M1 = new double *[newSize];M2 = new double *[newSize];M3 = new double *[newSize];M4 = new double *[newSize];M5 = new double *[newSize];M6 = new double *[newSize];M7 = new double *[newSize];
        AResult = new double *[newSize];BResult = new double *[newSize];

        int newLength = newSize;

        //making that 1 diminsional pointer based array , a 2D pointer based array
        for (int i = 0; i < newSize; i++)
        {
            A11[i] = new double[newLength];
            A12[i] = new double[newLength];
            A21[i] = new double[newLength];
            A22[i] = new double[newLength];

            B11[i] = new double[newLength];
            B12[i] = new double[newLength];
            B21[i] = new double[newLength];
            B22[i] = new double[newLength];

            C11[i] = new double[newLength];
            C12[i] = new double[newLength];
            C21[i] = new double[newLength];
            C22[i] = new double[newLength];

            M1[i] = new double[newLength];
            M2[i] = new double[newLength];
            M3[i] = new double[newLength];
            M4[i] = new double[newLength];
            M5[i] = new double[newLength];
            M6[i] = new double[newLength];
            M7[i] = new double[newLength];

            AResult[i] = new double[newLength];
            BResult[i] = new double[newLength];
        }
        //splitting input Matrixes, into 4 submatrices each.
        for (int i = 0; i < N / 2; i++)
        {
            for (int j = 0; j < N / 2; j++)
            {
                A11[i][j] = MatrixA[i][j];
                A12[i][j] = MatrixA[i][j + N / 2];
                A21[i][j] = MatrixA[i + N / 2][j];
                A22[i][j] = MatrixA[i + N / 2][j + N / 2];

                B11[i][j] = MatrixB[i][j];
                B12[i][j] = MatrixB[i][j + N / 2];
                B21[i][j] = MatrixB[i + N / 2][j];
                B22[i][j] = MatrixB[i + N / 2][j + N / 2];

            }
        }

        //P5[][]
        add(A11, A22, AResult, HalfSize);
        add(B11, B22, BResult, HalfSize);
        strassen(HalfSize, AResult, BResult, M1);

        //P3[][]
        add(A21, A22, AResult, HalfSize);
        strassen(HalfSize, AResult, B11, M2);

        //P1[][]
        sub(B12, B22, BResult, HalfSize);
        strassen(HalfSize, A11, BResult, M3);

        //P4[][]
        sub(B21, B11, BResult, HalfSize);
        strassen(HalfSize, A22, BResult, M4);

        //P2[][]
        add(A11, A12, AResult, HalfSize);
        strassen(HalfSize, AResult, B22, M5);


        //P7[][]
        sub(A21, A11, AResult, HalfSize);
        add(B11, B12, BResult, HalfSize);
        strassen(HalfSize, AResult, BResult, M6);

        //P6[][]
        sub(A12, A22, AResult, HalfSize);
        add(B21, B22, BResult, HalfSize);
        strassen(HalfSize, AResult, BResult, M7);

        //C11
        add(M1, M4, AResult, HalfSize);
        sub(M7, M5, BResult, HalfSize);
        add(AResult, BResult, C11, HalfSize);

        //C12
        add(M3, M5, C12, HalfSize);

        //C21
        add(M2, M4, C21, HalfSize);

        //C22
        add(M1, M3, AResult, HalfSize);
        sub(M6, M2, BResult, HalfSize);
        add(AResult, BResult, C22, HalfSize);

        //combine c11 c12 c21 c22 to get the result Matrix.
        for (int i = 0; i < N / 2; i++)
        {
            for (int j = 0; j < N / 2; j++)
            {
                MatrixC[i][j] = C11[i][j];
                MatrixC[i][j + N / 2] = C12[i][j];
                MatrixC[i + N / 2][j] = C21[i][j];
                MatrixC[i + N / 2][j + N / 2] = C22[i][j];
            }
        }

        // release
        for (int i = 0; i < newLength; i++)
        {
            delete[] A11[i]; delete[] A12[i]; delete[] A21[i];
            delete[] A22[i];

            delete[] B11[i]; delete[] B12[i]; delete[] B21[i];
            delete[] B22[i];
            delete[] C11[i]; delete[] C12[i]; delete[] C21[i];
            delete[] C22[i];
            delete[] M1[i]; delete[] M2[i]; delete[] M3[i]; delete[] M4[i];
            delete[] M5[i]; delete[] M6[i]; delete[] M7[i];
            delete[] AResult[i]; delete[] BResult[i];
        }
        delete[] A11; delete[] A12; delete[] A21; delete[] A22;
        delete[] B11; delete[] B12; delete[] B21; delete[] B22;
        delete[] C11; delete[] C12; delete[] C21; delete[] C22;
        delete[] M1; delete[] M2; delete[] M3; delete[] M4; delete[] M5;
        delete[] M6; delete[] M7;
        delete[] AResult;
        delete[] BResult;
    }
}

void dump_result(double** result, int size)
{
    for(int i=0; i<size; ++i) 
    {
        for(int j=0; j<size; ++j)
        {
            printf("%lf ", result[i][j]);
        }
        printf("\n");
    }
}

//generate test matrices
void fill_matrix(double** MatrixA, double** MatrixB, double** MatrixC, int length)
{
    for (int i = 0; i<length; ++i)
    {
        for (int j = 0; j<length; ++j)
        {
            MatrixB[i][j] = MatrixA[i][j] = 1.0+(i+1)/(j+1);
            MatrixC[i][j] = 0.0;
        }
    }
}

int main()
{
    freopen("result.txt", "w", stdout);
    int MatrixSize = 4096;
    double** MatrixA;
    double** MatrixB;
    double** MatrixC;
    
    int N = MatrixSize;

    MatrixA = new double *[MatrixSize];
    MatrixB = new double *[MatrixSize];
    MatrixC = new double *[MatrixSize];
    
    for (int i = 0; i < MatrixSize; i++)
    {
        MatrixA[i] = new double[MatrixSize];
        MatrixB[i] = new double[MatrixSize];
        MatrixC[i] = new double[MatrixSize];
    }
    
    //generate test matrices
    fill_matrix(MatrixA, MatrixB, MatrixC, MatrixSize);
    
    struct timeval start,end;
    gettimeofday(&start,NULL);
    
    strassen(N, MatrixA, MatrixB, MatrixC);
    gettimeofday(&end,NULL);
    double diff = (1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec)/1000.0;
    printf("strassen method single thread time consuming: %lf ms\n", diff);

    dump_result(MatrixC, MatrixSize);

    fclose(stdout);
    return 0;
}

