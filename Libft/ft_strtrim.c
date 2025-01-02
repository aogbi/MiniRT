/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:17:35 by yhadhadi          #+#    #+#             */
/*   Updated: 2023/12/08 15:36:57 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	const char	*p_str;
	char		*seg;
	char		*p_seg;

	while (ft_strchr(set, *str) && *str)
		++str;
	p_str = str;
	while (*p_str)
		++p_str;
	while (ft_strchr(set, *p_str) && p_str >= str)
		--p_str;
	seg = (char *)malloc(((p_str + 1) - str + 1) * sizeof(char));
	if (!seg)
		return (NULL);
	p_seg = seg;
	while (str <= p_str)
		*p_seg++ = *str++;
	*p_seg = '\0';
	return (seg);
}
