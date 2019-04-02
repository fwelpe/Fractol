/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:34 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/02 19:08:36 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	cl_init(t_fctl *s)
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
	l->context = clCreateContext( NULL, 1, &l->device_id, NULL, NULL, &l->ret);
    l->command_queue = clCreateCommandQueue(l->context, l->device_id,
			0, &l->ret);
}

void	cl_init_pt2(t_fctl *s)
{
	t_cl *l;

	l = &s->cl;
    cl_mem a_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY, 
            s->pxs * sizeof(double), NULL, &l->ret);
    cl_mem b_mem_obj = clCreateBuffer(l->context, CL_MEM_READ_ONLY,
            s->pxs * sizeof(double), NULL, &l->ret);
    cl_mem c_mem_obj = clCreateBuffer(l->context, CL_MEM_WRITE_ONLY, 
            s->pxs * sizeof(int), NULL, &l->ret);

}