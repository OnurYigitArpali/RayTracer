#include <stdexcept>
/*
 * m represents a 4x4 matrix stored as a 1D array in row-major-order.
 * For instance m[6] represents the element at the second row third column
 * of the matrix. 
 *
 * inv contains the inverse of this matrix stored in the same
 * format as the input.
 */

void multiply(double A[], double B[])
{
    double C[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };

    for(int i=0; i<4; i++)  //C0,1,2,3
        C[i] = A[0]*B[i] + A[1]*B[i+4] + A[2]*B[i+8] + A[3]*B[i+12];

    for(int i=0; i<4; i++)
        C[i+4] = A[4]*B[i] + A[5]*B[i+4] + A[6]*B[i+8] + A[7]*B[i+12];

    for(int i=0; i<4; i++)
        C[i+8] = A[8]*B[i] + A[9]*B[i+4] + A[10]*B[i+8] + A[11]*B[i+12];

    for(int i=0; i<4; i++)
        C[i+12] = A[12]*B[i] + A[13]*B[i+4] + A[14]*B[i+8] + A[15]*B[i+12];

    for(int i=0; i<16; i++)
        B[i] = C[i];
}

void transpose(double m[], double t_m[])
{
    t_m[0] = m[0]; t_m[1] = m[4]; t_m[2] = m[8]; t_m[3] = m[12];
    t_m[4] = m[1]; t_m[5] = m[5]; t_m[6] = m[9]; t_m[7] = m[13];
    t_m[8] = m[2]; t_m[9] = m[6]; t_m[10] = t_m[10]; t_m[11] = m[14];
    t_m[12] = m[13]; t_m[13] = m[7]; t_m[14] = m[11]; t_m[15] = m[15];
}

void invert(double m[], double inv[])
{
    //
    // This code is taken from the GLU library 
    //    
    double det;

    inv[0] = m[5]  * m[10] * m[15] - 
        m[5]  * m[11] * m[14] - 
        m[9]  * m[6]  * m[15] + 
        m[9]  * m[7]  * m[14] +
        m[13] * m[6]  * m[11] - 
        m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
        m[4]  * m[11] * m[14] + 
        m[8]  * m[6]  * m[15] - 
        m[8]  * m[7]  * m[14] - 
        m[12] * m[6]  * m[11] + 
        m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
        m[4]  * m[11] * m[13] - 
        m[8]  * m[5] * m[15] + 
        m[8]  * m[7] * m[13] + 
        m[12] * m[5] * m[11] - 
        m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
        m[4]  * m[10] * m[13] +
        m[8]  * m[5] * m[14] - 
        m[8]  * m[6] * m[13] - 
        m[12] * m[5] * m[10] + 
        m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
        m[1]  * m[11] * m[14] + 
        m[9]  * m[2] * m[15] - 
        m[9]  * m[3] * m[14] - 
        m[13] * m[2] * m[11] + 
        m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
        m[0]  * m[11] * m[14] - 
        m[8]  * m[2] * m[15] + 
        m[8]  * m[3] * m[14] + 
        m[12] * m[2] * m[11] - 
        m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
        m[0]  * m[11] * m[13] + 
        m[8]  * m[1] * m[15] - 
        m[8]  * m[3] * m[13] - 
        m[12] * m[1] * m[11] + 
        m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
        m[0]  * m[10] * m[13] - 
        m[8]  * m[1] * m[14] + 
        m[8]  * m[2] * m[13] + 
        m[12] * m[1] * m[10] - 
        m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
        m[1]  * m[7] * m[14] - 
        m[5]  * m[2] * m[15] + 
        m[5]  * m[3] * m[14] + 
        m[13] * m[2] * m[7] - 
        m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
        m[0]  * m[7] * m[14] + 
        m[4]  * m[2] * m[15] - 
        m[4]  * m[3] * m[14] - 
        m[12] * m[2] * m[7] + 
        m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
        m[0]  * m[7] * m[13] - 
        m[4]  * m[1] * m[15] + 
        m[4]  * m[3] * m[13] + 
        m[12] * m[1] * m[7] - 
        m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
        m[0]  * m[6] * m[13] + 
        m[4]  * m[1] * m[14] - 
        m[4]  * m[2] * m[13] - 
        m[12] * m[1] * m[6] + 
        m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
        m[1] * m[7] * m[10] + 
        m[5] * m[2] * m[11] - 
        m[5] * m[3] * m[10] - 
        m[9] * m[2] * m[7] + 
        m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
        m[0] * m[7] * m[10] - 
        m[4] * m[2] * m[11] + 
        m[4] * m[3] * m[10] + 
        m[8] * m[2] * m[7] - 
        m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
        m[0] * m[7] * m[9] + 
        m[4] * m[1] * m[11] - 
        m[4] * m[3] * m[9] - 
        m[8] * m[1] * m[7] + 
        m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
        m[0] * m[6] * m[9] - 
        m[4] * m[1] * m[10] + 
        m[4] * m[2] * m[9] + 
        m[8] * m[1] * m[6] - 
        m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
    {
        throw std::runtime_error("Error: Determinant is zero.");
    }

    det = 1.0 / det;

    for (int i = 0; i < 16; ++i)
    {
        inv[i] *= det;
    }
}
