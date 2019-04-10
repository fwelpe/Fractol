/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:50:06 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/10 18:22:29 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	full_l;
	char	*rt;

	if (!s1 || !s2)
		return (NULL);
	full_l = ft_strlen(s1) + ft_strlen(s2) + 1;
	rt = (char *)malloc(full_l);
	if (!rt)
		return (NULL);
	rt = ft_strcpy(rt, s1);
	rt = ft_strcat(rt, s2);
	return (rt);
}
