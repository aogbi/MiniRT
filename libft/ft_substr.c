/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:12:38 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/01/27 06:53:58 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, size_t idx, size_t sub_len)
{
	size_t	str_len;
	char	*sub;
	char	*p_sub;

	str_len = ft_strlen(str);
	if (idx >= str_len)
		sub_len = 0;
	if (sub_len > str_len - idx)
		sub_len = str_len - idx;
	sub = (char *)malloc((sub_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	str += idx;
	p_sub = sub;
	while (sub_len && *str)
	{
		*p_sub++ = *str++;
		--sub_len;
	}
	*p_sub = '\0';
	return (sub);
}
