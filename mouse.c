/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:05:19 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/03/29 16:42:33 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void	zoom_fdf(int key, t_fdf *st)
// {
// 	float	delta;

// 	delta = (100 / sqrt(pow(st->map->height, 2) + pow(st->map->width, 2)));
// 	if (key == PLUS)
// 		st->cam->scale += delta;
// 	if (key == MINUS && st->cam->scale > delta)
// 		st->cam->scale -= delta;
// 	st->cam->zoom = 1;
// 	copy_points(st->map);
// 	draw(st);
// }

int		init_mouse(t_fctl *s)
{
	MALLCHECK((s->mouse = (t_mouse *)malloc(sizeof(t_mouse))));
	s->mouse->button = -1;
	s->mouse->x = 0;
	s->mouse->y = 0;
	s->mouse->lastx = 0;
	s->mouse->lasty = 0;
	return (1);
}

int		mouse_press(int button, int x, int y, t_fctl *s)
{
	(void)x;
	if (button == 1 && y >= 0)
		s->mouse->button = 1;
	// if (button == PLUS || button == MINUS)
	// 	zoom_fdf(button, st);
	return (0);
}

int		mouse_release(int button, int x, int y, t_fctl *s)
{
	(void)x;
	(void)y;
	(void)button;
	if (button == 1)
		s->mouse->button = -1;
	return (0);
}

int		mouse_move(int x, int y, t_fctl *s)
{
	s->mouse->lastx = s->mouse->x;
	s->mouse->lasty = s->mouse->y;
	s->mouse->x = x;
	s->mouse->y = y;
	// if (s->mouse->button == 1)
	// {
	// 	s->cam->x += (s->mouse->lasty - y) / 150.0f;
	// 	s->cam->y -= (s->mouse->lastx - x) / 150.0f;
	// 	draw(s);
	// }
	return (0);
}
