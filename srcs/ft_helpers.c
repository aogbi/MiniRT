/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:43:14 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:43:28 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_isnum(char *str)
{
	if (!str || (str[0] == '\n' && str[1] == '\0'))
		return (0);
	else if (*str == '-' || *str == '+')
		str++;
	while (*str && (*str != '\n' && *(str + 1) != '\0'))
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_isfloat(char *str)
{
	int	flag;

	if (!str || (str[0] == '\n' && str[1] == '\0'))
		return (0);
	else if (*str == '-' || *str == '+')
		str++;
	flag = 0;
	while (*str && (*str != '\n' && *(str + 1) != '\0'))
	{
		if (!ft_isdigit(*str) && *str != '.')
			return (0);
		else if (*str == '.')
		{
			if (flag)
				return (0);
			flag = 1;
		}
		str++;
	}
	return (1);
}

void	ft_str_array_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	count_str_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] && array[i][0] != '\n')
		i++;
	return (i);
}
