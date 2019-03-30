/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:02:03 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/03/30 15:55:10 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		deal_key(int key, t_fctl *s)
{
	(void)s;
	if (key == ESC)
		exit(0);

	if (key == SPACE)
	{
		zero_cam(s);
		draw(s);
	}
	return (0);
}

int		red_button(void *param)
{
	(void)param;
	exit(0);
	return (0);
}
