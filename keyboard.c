/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:02:03 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/03/29 14:33:00 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void	handle_space(t_fctl *s)
// {
// 	zero_cam(st);
// 	copy_points(st->map);
// 	draw(st);
// }

int		deal_key(int key, t_fctl *s)
{
	(void)s;
	if (key == ESC)
		exit(0);

	if (key == SPACE)
	{
		// handle_space(s);
	}
	return (0);
}

int		red_button(void *param)
{
	(void)param;
	exit(0);
	return (0);
}
