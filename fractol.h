/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:34:44 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/29 13:56:48 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define W 1000
# define H 1000

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct	s_fctl
{
		void	*mlx_ptr;
		void	*win_ptr;
		float	scale;
}				t_fctl;

#endif