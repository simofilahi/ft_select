/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:10:12 by mfilahi           #+#    #+#             */
/*   Updated: 2018/10/18 14:24:54 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	len_s1;
	int		i;

	len_s1 = ft_strlen(s1);
	i = 0;
	while ((s1[len_s1 + i] = s2[i]))
		i++;
	return (s1);
}
