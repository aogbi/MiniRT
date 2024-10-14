/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:19:32 by aogbi             #+#    #+#             */
/*   Updated: 2024/06/04 02:17:51 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_spaces(const char *nptr)
{
	while (*nptr)
	{
		if (*nptr != ' ')
			return (0);
		nptr++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int		signal;
	ssize_t	result;

	signal = 1;
	result = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		result *= 10;
		result += (*nptr++) - '0';
	}
	if (!is_spaces(nptr) || *(nptr - 1) == '-' || *(nptr - 1) == '+')
		return (-1);
	result *= signal;
	if ((ssize_t)result > INT_MAX || (ssize_t)result < INT_MIN)
		return (-1);
	return ((int)result);
}
