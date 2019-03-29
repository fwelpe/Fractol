/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:34:44 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/28 19:21:29 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define W 1000
# define H 1000

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct	s_mlx
{	
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

#endif