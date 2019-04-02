/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:07:29 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/02 15:17:19 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	image_set_pixel(t_fctl *s, int x, int y, int color)
{
	if (x < 0 || x >= W || y < 0 || y >= H)
		return ;
	*(int *)(s->adr + ((x + y * W) * s->b_p_pix)) = color;
}

void	clear_image(t_fctl *s)
{
	ft_bzero(s->adr, W * H * s->b_p_pix);
}

int		new_image(t_fctl *s)
{
	int n;

	n = 0;
	if (!(s->image_cont = mlx_new_image(s->mlx_ptr, W, H)))
		return (0);
	s->adr = (int *)mlx_get_data_addr(s->image_cont, &(s->b_p_pix), &n, &n);
	s->b_p_pix /= 8;
	return (1);
}
