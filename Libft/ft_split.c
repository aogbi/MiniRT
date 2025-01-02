/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:58:34 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/22 02:54:55 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_subs(const char *str, char sep);
static char		**extract_sub(char **strs, const char **str, char sep);

char	**ft_split(const char *str, char sep)
{
	char	**strs;
	char	**p_strs;

	strs = (char **)malloc((count_subs(str, sep) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	p_strs = strs;
	while (*str)
	{
		if (*str != sep)
		{
			p_strs = extract_sub(p_strs, &str, sep);
			if (!*p_strs)
			{
				while (p_strs > strs)
					free(*(--p_strs));
				return (free(strs), NULL);
			}
			++p_strs;
			continue ;
		}
		++str;
	}
	*p_strs = NULL;
	return (strs);
}

static size_t	count_subs(const char *str, char sep)
{
	size_t	subs_cnt;
	int		sep_occ;

	subs_cnt = 0;
	sep_occ = -1;
	while (*str)
	{
		if (*str == sep)
			sep_occ = 1;
		else if (sep_occ)
		{
			sep_occ = 0;
			++subs_cnt;
		}
		++str;
	}
	return (subs_cnt);
}

static char	**extract_sub(char **strs, const char **str, char sep)
{
	const char	*p_str = *str;
	char		*sub;

	while (*p_str != sep && *p_str)
		++p_str;
	*strs = (char *)malloc((p_str - *str + 1) * sizeof(char));
	if (!*strs)
		return (NULL);
	sub = *strs;
	while (*str < p_str)
		*sub++ = *(*str)++;
	*sub = '\0';
	return (strs);
}
