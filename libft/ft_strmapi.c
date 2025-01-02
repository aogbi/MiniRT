/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:44:42 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/01/26 01:33:02 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*apply)(size_t, char))
{
	char	*map;
	size_t	i;

	map = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!map)
		return (NULL);
	i = 0;
	while (*str)
	{
		map[i] = apply(i, *str++);
		++i;
	}
	map[i] = '\0';
	return (map);
}
