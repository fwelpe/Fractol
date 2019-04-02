/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:11:04 by fwlpe             #+#    #+#             */
/*   Updated: 2019/04/02 19:06:33 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		is_white(double re, double im, double re_start, double im_start, int depth)
{
	double	re_new;
	double	im_new;
	
	if ((re * re + im * im) > 4)
		return (0);
	if (!depth)
		return (1);
	re_new = re * re - im * im + re_start;
	im_new = 2 * re * im + im_start;
	return (is_white(re_new, im_new, re_start, im_start, --depth));
}


void	tempfn(t_fctl *s)
{
	
    int i;

	i = -1;
	while (++i < s->pxs)
	{
		if (is_white(0, 0, s->re[i], s->im[i], 255))
			s->adr[i] = 0xFFFFFF;
		else
			s->adr[i] = 0x000000;
	}
}

void	field_iter(t_fctl *s)
{
	int i;
	int j;

	i = -1;
	while (++i < W)
	{
		j = -1;
		while (++j < H)
		{
			// if (is_white(0, 0, (float)i / s->cam.scale + s->cam.re_add - (W / 2) / s->cam.scale, -(float)j / s->cam.scale + s->cam.im_add + (H / 2) / s->cam.scale, 255))
			// 	image_set_pixel(s, i, j, 0xF5DEB3);
			s->re[i + W * j] = (i - W / 2) / s->cam.scale + s->cam.re_add;
			s->im[i + W * j] = (H / 2 - j) / s->cam.scale + s->cam.im_add;
		}
	}
}

int		start(t_fctl *s)
{
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, W, H, "w!h0oy");
	if (!new_image(s))
		return (0);
	s->pxs = W * H;
	MALLCHECK((s->re = (double *)malloc(sizeof(double) * s->pxs)));
	MALLCHECK((s->im = (double *)malloc(sizeof(double) * s->pxs)));
	zero_cam(s);
	field_iter(s);
	return (1);
}

int		main(int ac, char **av)
{
	t_fctl	s;

	(void)ac;
	(void)av;
	if (!start(&s))
		return (1);

    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;

    fp = fopen("mandelbrot.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, 
            &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            s.pxs * sizeof(double), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            s.pxs * sizeof(double), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            s.pxs * sizeof(int), NULL, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
            s.pxs * sizeof(double), s.re, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, 
            s.pxs * sizeof(double), s.im, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "mandelbrot", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
    
    // Execute the OpenCL kernel on the list
    size_t global_item_size = s.pxs; // Process the entire lists
    size_t local_item_size = 64; // Process in groups of 64
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);

    // Read the memory buffer C on the device to the local variable C
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, 
            s.pxs * sizeof(int), (void *)s.adr, 0, NULL, NULL);

	// for (int j = 0; j < s.pxs; j++)
	// 	s.adr[j] = 0xFFFFFF;
	// tempfn(&s);

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
	
	draw(&s);
	mlx_key_hook(s.win_ptr, deal_key, &s);
	mlx_mouse_hook(s.win_ptr, mouse, (void *)&s);
	mlx_hook(s.win_ptr, 17, 0, red_button, NULL);
	mlx_loop(s.mlx_ptr);

	return (0);
}
