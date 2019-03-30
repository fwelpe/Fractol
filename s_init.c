/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:31:13 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/03/30 12:41:50 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	zero_cam(t_fctl *s)
{
	s->cam.scale = H / 5;
	s->cam.x_shift = 0;
	s->cam.y_shift = 0;
	return (0);
}

int	s_init(t_fctl *s)
{
	if (!(s->image = new_image(s)))
		return (0);
	if (!(init_mouse(s)))
		return (0);
	zero_cam(s);
	return (1);
}