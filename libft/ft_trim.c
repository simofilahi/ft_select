/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:34:17 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/05 13:11:55 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(char *str, char delim)
{
	int	i;

	i = 0;
	while (str[i] != delim)
		i++;
	return (i);
}

char		*ft_trim(char *str, char delim)
{
	char	*tmp;
	int		i;

	if (!(tmp = (char *)malloc(sizeof(char) * len(str, delim) + 1)))
		return (NULL);
	i = 0;
	while (*str != delim)
	{
		tmp[i++] = *str++;
	}
	tmp[i] = '\0';
	return (tmp);
}
