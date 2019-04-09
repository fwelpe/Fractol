__kernel void mandelbrot(__global double *A, __global double *B, __global int *C, __global int *D)
{
    int		q;
	double	j;
	double	im;
	double	re;
	int		e;
	int		color1;
	char	*crwr;
	char	*crwr_result;
	int 	tmp;

    int i = get_global_id(0);
	im = 0;
	re = 0;
	q = 0;
	color1 = D[1];
	crwr = &color1;
	crwr_result = &(C[i]);
	while (++q < D[0])
	{
		j = re * re - im * im + A[i];
		im = 2 * re * im + B[i];
		re = j;
		if ((re * re + im * im) > 4)
		{
			e = -1;
			C[i] = 0;
			while (++e < 3)
				crwr_result[e] = crwr[e] * q /D[0];
			// C[i] = (((color1 * q / D[0]) & 0xff0000) + ((color1 * q / D[0]) & 0x00ff00) + ((color1 * q / D[0]) & 0x0000ff)) % 0xffffff;
			// C[i] = color1;
			tmp = *((int *)crwr_result);
			C[i] = tmp;
			return ;
		}
	}
	C[i] = D[2];
	// C[i] = 0xF5DEB3;
}
