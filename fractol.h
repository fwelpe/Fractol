/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:34:44 by fwlpe             #+#    #+#             */
/*   Updated: 2019/04/07 14:04:45 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdio.h>
# include "defines.h"
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define MAX_SOURCE_SIZE (0x100000)
# define MALLCHECK(x) if (!x) return (0)
# define CL_USE_DEPRECATED_OPENCL_1_2_APIS

typedef struct	s_cam
{
	double	re_add;
	double	im_add;
	double	scale;
}				t_cam;

typedef struct	s_cl
{
	FILE				*fp;
	char				*source_str;
	size_t				source_size;
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				a_mem_obj;
	cl_mem				b_mem_obj;
	cl_mem				c_mem_obj;
	cl_mem				d_mem_obj;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_item_size;
	size_t				local_item_size;
}				t_cl;

typedef struct	s_fctl
{
	void		*mlx_ptr;
	void		*win_ptr;
	double		scale;
	void		*image_cont;
	int			*adr;
	int			b_p_pix;
	double		*re;
	double		*im;
	t_cam		cam;
	int			pxs;
	int			cl_iters;
	t_cl		cl;
	char		*f_name;
}				t_fctl;

int				red_button(void *param);
int				deal_key(int key, t_fctl *s);
void			image_set_pixel(t_fctl *s, int x, int y, int color);
void			clear_image(t_fctl *s);
int				new_image(t_fctl *s);
void			field_iter(t_fctl *s);
void			draw(t_fctl *s);
int				mouse(int button, int x, int y, t_fctl *s);
void			zero_cam(t_fctl *s);
void			zoom(int key, t_fctl *s, int x, int y);
void			init_cl(t_fctl *s);
void			usage(void);
char			*parse_name(char **av);
int				start(t_fctl *s, int ac, char **av);
void			init_cl(t_fctl *s);
void			init_cl_pt2(t_fctl *s, t_cl *l);
void			go_cl(t_fctl *s);
void			end_cl(t_fctl *s);

#endif
