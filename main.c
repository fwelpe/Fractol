/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:11:04 by fwlpe             #+#    #+#             */
/*   Updated: 2019/04/09 20:22:56 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int ac, char **av)
{
	t_fctl	s;

	if (!start(&s, ac, av))
		return (1);
	draw(&s);
	mlx_key_hook(s.win_ptr, deal_key, &s);
	mlx_mouse_hook(s.win_ptr, mouse, (void *)&s);
	mlx_hook(s.win_ptr, DELETE_WINDOW, 0, red_button, NULL);
	if (ft_strequ(s.f_name, "julia"))
		mlx_loop_hook(s.mlx_ptr, (void *)draw, (void *)&s);
	mlx_hook(s.win_ptr, 6, 0, mouse_move, (void *)&s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
