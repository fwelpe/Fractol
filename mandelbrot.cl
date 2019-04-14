__kernel void mandelbrot(__global double *A, __global double *B, __global int *C, __global double *D)
{
    int		q;
	double	j;
	double	im;
	double	re;
	int		e;
	int		cl_shift;

	cl_shift = (int)D[5];
    int i = get_global_id(0);
	im = 0;
	re = 0;
	q = 0;
	while (++q <= (int)D[0])
	{
		j = re * re - im * im + A[i];
		im = 2 * re * im + B[i];
		re = j;
		if ((re * re + im * im) > 4)
		{
			if (cl_shift == 0)
			{
				e = 0;
				C[i] = 0;
				while (++e < 4)
				{
					C[i] += 0xff * q / (int)D[0];
					if (e != 3)
						C[i] = C[i] << 8;
				}
			}
			else if (cl_shift == 1)
				C[i] = q * q * q / D[0];
			return ;
		}
	}
	C[i] = D[1];
}
