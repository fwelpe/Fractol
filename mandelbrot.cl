__kernel void mandelbrot(__global double *A, __global double *B, __global int *C)
{
    int		q;
	double	j;
	double	im;
	double	re;
    // // Get the index of the current element
    int i = get_global_id(0);
	im = 0;
	re = 0;
	q = -1;
	while (++q < 255)
	{
		j = re * re - im * im + A[i];
		im = 2 * re * im + B[i];
		re = j;
		if ((re * re + im * im) > 4)
		{
			C[i] = 0x202020;
			return ;
		}
	}
	C[i] = 0xF5DEB3;

    // Do the operation
    // C[i] = A[i] + B[i];
}
