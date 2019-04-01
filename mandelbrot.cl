__kernel void mandelbrot(__global double *A, __global double *B, __global char *C)
{
    int		q;
	double	j;
	double	im_start;
	double	re_start;
    // Get the index of the current element
    int i = get_global_id(0);
	im_start = A[i];
	re_start = B[i];
	q = -1;
	while (++q < 255)
	{
		j = A[i];
		A[i] = A[i] * A[i] - B[i] * B[i] + re_start;
		B[i] = 2 * j * B[i] + im_start;
		if ((A[i] * A[i] + B[i] * B[i]) > 4)
		{
			*(int *)(C + ((i * 4)) = 0x000000;
			return ;
		}
	}
	*(int *)(C + ((i * 4)) = 0xFFFFFF;

    // Do the operation
    // C[i] = A[i] + B[i];
}
