/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 05:52:23 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/01/25 04:06:34 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *str, int fd)
{
	ssize_t	yld;
	int		chr_cnt;

	if (fd < 0)
		return (-1);
	yld = write(fd, str, ft_strlen(str));
	if (yld == -1)
		return (-1);
	chr_cnt = yld;
	yld = write(fd, "\n", sizeof(char));
	if (yld == -1)
		return (-1);
	chr_cnt += yld;
	return (chr_cnt);
}
