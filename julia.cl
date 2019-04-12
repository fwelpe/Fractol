__kernel void julia(__global double *A, __global double *B, __global int *C, __global double *D)
{
    int		q;
	double	j;
	double	im;
	double	re;
	int		e;

    int i = get_global_id(0);
	re = A[i];
	im = B[i];
	q = 0;
	while (++q <= (int)D[0])
	{
		j = re * re - im * im + D[10];
		im = 2 * re * im + D[11];
		re = j;
		if ((re * re + im * im) > 4)
		{
			e = 0;
			C[i] = 0;
			while (++e < 4)
			{
				C[i] += 0xff * q / (int)D[0];
				if (e != 3)
					C[i] = C[i] << 8;
			}
			return ;
		}
	}
	C[i] = D[1];
}
