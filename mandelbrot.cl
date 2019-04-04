__kernel void mandelbrot(__global double *A, __global double *B, __global int *C, __global int *D)
{
    int		q;
	double	j;
	double	im;
	double	re;
	unsigned long long int t;

    int i = get_global_id(0);
	im = 0;
	re = 0;
	q = -1;
	while (++q < *D)
	{
		j = re * re - im * im + A[i];
		im = 2 * re * im + B[i];
		re = j;
		if ((re * re + im * im) > 4)
		{
			// t = (q * 0xFFFFFF / *D);
			// C[i] = t;
			C[i] = q * q * q % 0xffffff;
			return ;
		}
	}
	C[i] = 0xFFFFFF;
	// C[i] = 0xF5DEB3;
}
