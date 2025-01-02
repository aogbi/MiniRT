/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:13:33 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/22 02:55:40 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *pat, size_t n)
{
	const char	*p_str = str;
	const char	*p_pat;
	size_t		off;

	if (!*pat)
		return ((char *)p_str);
	while (n && *p_str)
	{
		p_pat = pat;
		while (n && *p_pat == *p_str && *p_pat)
		{
			++p_str;
			++p_pat;
			--n;
		}
		off = p_pat - pat;
		p_str -= off;
		n += off - 1;
		if (!*p_pat)
			return ((char *)p_str);
		++p_str;
	}
	return (NULL);
}
