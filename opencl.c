/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:34 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/13 15:53:19 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		opencl_error(void)
{
	ft_putendl_fd("OpenCL mysterious error! Just try again.", 2);
	exit(1);
}

void		init_cl(t_fctl *s)
{
	t_cl	*l;
	char	*f;

	l = &s->cl;
	f = ft_strjoin(s->f_name, ".cl");
	l->fp = fopen(f, "r");
	if (!l->fp)
	{
		ft_putendl_fd("Failed to load kernel.", 2);
		exit(1);
	}
	free(f);
	l->source_str = (char*)malloc(MAX_SOURCE_SIZE);
	l->source_size = fread(l->source_str, 1, MAX_SOURCE_SIZE, l->fp);
	fclose(l->fp);
	l->platform_id = NULL;
	l->device_id = NULL;
	l->ret = clGetPlatformIDs(1, &l->platform_id, &l->ret_num_platforms);
	l->ret = clGetDeviceIDs(l->platform_id, CL_DEVICE_TYPE_GPU, 1,
			&l->device_id, &l->ret_num_devices);
	l->context = clCreateContext(NULL, 1, &l->device_id, NULL, NULL, &l->ret);
	if (l->ret != CL_SUCCESS)
		opencl_error();
	init_cl_pt2(s, l);
}

void		init_cl_pt2(t_fctl *s, t_cl *l)
{
	l->command_queue = clCreateCommandQueue(l->context, l->device_id,
			0, &l->ret);
	l->a_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY,
			s->pxs * sizeof(double), NULL, &l->ret);
	l->b_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY,
			s->pxs * sizeof(double), NULL, &l->ret);
	l->c_mem_obj = clCreateBuffer(l->context, CL_MEM_WRITE_ONLY,
			s->pxs * sizeof(int), NULL, &l->ret);
	l->d_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_WRITE,
			sizeof(double) * CLSTORE_SIZE, NULL, &l->ret);
	l->program = clCreateProgramWithSource(l->context, 1, (const char **)
			&l->source_str, (const size_t *)&l->source_size, &l->ret);
	l->ret = clBuildProgram(l->program, 1, &l->device_id, NULL, NULL, NULL);
	if (l->ret != CL_SUCCESS)
		opencl_error();
}

void		go_cl(t_fctl *s)
{
	t_cl	*l;

	l = &s->cl;
	l->ret = clReleaseMemObject(l->a_mem_obj);
	l->ret = clReleaseMemObject(l->b_mem_obj);
	l->ret = clReleaseMemObject(l->c_mem_obj);
	l->a_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY,
			s->pxs * sizeof(double), NULL, &l->ret);
	l->b_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY,
			s->pxs * sizeof(double), NULL, &l->ret);
	l->c_mem_obj = clCreateBuffer(l->context, CL_MEM_WRITE_ONLY,
			s->pxs * sizeof(int), NULL, &l->ret);
	l->d_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_WRITE,
			sizeof(double) * CLSTORE_SIZE, NULL, &l->ret);
	l->ret = clEnqueueWriteBuffer(l->command_queue, l->a_mem_obj, CL_TRUE, 0,
			s->pxs * sizeof(double), s->re, 0, NULL, NULL);
	l->ret = clEnqueueWriteBuffer(l->command_queue, l->b_mem_obj, CL_TRUE, 0,
			s->pxs * sizeof(double), s->im, 0, NULL, NULL);
	l->ret = clEnqueueWriteBuffer(l->command_queue, l->d_mem_obj, CL_TRUE, 0,
			sizeof(double) * CLSTORE_SIZE, s->cl_store, 0, NULL, NULL);
	l->kernel = clCreateKernel(l->program, s->f_name, &l->ret);
	if (l->ret != CL_SUCCESS)
		opencl_error();
	go_cl_pt_2(s);
}

void		go_cl_pt_2(t_fctl *s)
{
	t_cl	*l;

	l = &s->cl;
	l->ret = clSetKernelArg(l->kernel, 0, sizeof(cl_mem),
			(void *)&l->a_mem_obj);
	l->ret = clSetKernelArg(l->kernel, 1, sizeof(cl_mem),
			(void *)&l->b_mem_obj);
	l->ret = clSetKernelArg(l->kernel, 2, sizeof(cl_mem),
			(void *)&l->c_mem_obj);
	l->ret = clSetKernelArg(l->kernel, 3, sizeof(cl_mem),
			(void *)&l->d_mem_obj);
	l->global_item_size = s->pxs;
	l->local_item_size = 64;
	l->ret = clEnqueueNDRangeKernel(l->command_queue, l->kernel, 1, NULL,
			&l->global_item_size, &l->local_item_size, 0, NULL, NULL);
	l->ret = clEnqueueReadBuffer(l->command_queue, l->c_mem_obj, CL_TRUE, 0,
			s->pxs * sizeof(int), s->adr, 0, NULL, NULL);
	l->ret = clFlush(l->command_queue);
	l->ret = clFinish(l->command_queue);
	l->ret = clReleaseKernel(l->kernel);
	if (l->ret != CL_SUCCESS)
		opencl_error();
}
