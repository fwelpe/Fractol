__kernel void mandelbrot(__global double *A, __global double *B, __global int *C)
{
    
    // Get the index of the current element
    int i = get_global_id(0);



    // Do the operation
    // C[i] = A[i] + B[i];
}
