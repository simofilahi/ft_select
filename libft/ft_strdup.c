/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:27:44 by mfilahi           #+#    #+#             */
/*   Updated: 2018/10/18 13:50:19 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*s2;
	size_t		s1_len;

	s1_len = ft_strlen(s1);
	if (!(s2 = (char *)malloc(sizeof(char) * s1_len + 1)))
		return (NULL);
	s2 = ft_strcpy(s2, s1);
	return (s2);
}
