/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:34 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/04 18:27:29 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	go_cl(t_fctl *s)
{
	t_cl *l;

	l = &s->cl;
	l->fp = fopen("mandelbrot.cl", "r");
	if (!l->fp)
	{
		ft_putendl_fd("Failed to load kernel.\n", 2);
		exit(1);
	}
	l->source_str = (char*)malloc(MAX_SOURCE_SIZE);
	l->source_size = fread(l->source_str, 1, MAX_SOURCE_SIZE, l->fp);
	fclose(l->fp);
	l->platform_id = NULL;
	l->device_id = NULL;
	l->ret = clGetPlatformIDs(1, &l->platform_id, &l->ret_num_platforms);
	l->ret = clGetDeviceIDs(l->platform_id, CL_DEVICE_TYPE_ALL, 1,
			&l->device_id, &l->ret_num_devices);
	l->context = clCreateContext(NULL, 1, &l->device_id, NULL, NULL, &l->ret);
	l->command_queue = clCreateCommandQueue(l->context, l->device_id,
			0, &l->ret);
	l->a_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY,
			s->pxs * sizeof(double), NULL, &l->ret);
	l->b_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY,
			s->pxs * sizeof(double), NULL, &l->ret);
	go_cl_pt2(s, l);
}

void	go_cl_pt2(t_fctl *s, t_cl *l)
{
	l->c_mem_obj = clCreateBuffer(l->context, CL_MEM_WRITE_ONLY,
			s->pxs * sizeof(int), NULL, &l->ret);
	l->d_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY,
			sizeof(int), NULL, &l->ret);
	l->ret = clEnqueueWriteBuffer(l->command_queue, l->a_mem_obj, CL_TRUE, 0,
			s->pxs * sizeof(double), s->re, 0, NULL, NULL);
	l->ret = clEnqueueWriteBuffer(l->command_queue, l->b_mem_obj, CL_TRUE, 0,
			s->pxs * sizeof(double), s->im, 0, NULL, NULL);
	l->ret = clEnqueueWriteBuffer(l->command_queue, l->d_mem_obj, CL_TRUE, 0,
			sizeof(int), &s->cl_iters, 0, NULL, NULL);
	l->program = clCreateProgramWithSource(l->context, 1, (const char **)
			&l->source_str, (const size_t *)&l->source_size, &l->ret);
	l->ret = clBuildProgram(l->program, 1, &l->device_id, NULL, NULL, NULL);
	l->kernel = clCreateKernel(l->program, "mandelbrot", &l->ret);
	l->ret = clSetKernelArg(l->kernel, 0, sizeof(cl_mem),
			(void *)&l->a_mem_obj);
	l->ret = clSetKernelArg(l->kernel, 1, sizeof(cl_mem),
			(void *)&l->b_mem_obj);
	l->ret = clSetKernelArg(l->kernel, 2, sizeof(cl_mem),
			(void *)&l->c_mem_obj);
	l->ret = clSetKernelArg(l->kernel, 3, sizeof(cl_mem),
			(void *)&l->d_mem_obj);
	l->global_item_size = s->pxs;
	l->local_item_size = 1;
	go_cl_pt3(s, l);
}

void	go_cl_pt3(t_fctl *s, t_cl *l)
{
	l->ret = clEnqueueNDRangeKernel(l->command_queue, l->kernel, 1, NULL,
			&l->global_item_size, &l->local_item_size, 0, NULL, NULL);
	l->ret = clEnqueueReadBuffer(l->command_queue, l->c_mem_obj, CL_TRUE, 0,
			s->pxs * sizeof(int), s->adr, 0, NULL, NULL);
	l->ret = clFlush(l->command_queue);
	l->ret = clFinish(l->command_queue);
	l->ret = clReleaseKernel(l->kernel);
	l->ret = clReleaseProgram(l->program);
	l->ret = clReleaseMemObject(l->a_mem_obj);
	l->ret = clReleaseMemObject(l->b_mem_obj);
	l->ret = clReleaseMemObject(l->c_mem_obj);
	l->ret = clReleaseCommandQueue(l->command_queue);
	l->ret = clReleaseContext(l->context);
}
