/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:42:32 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/02 14:47:47 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vprintf_fd(const char *fmt, va_list *vargs, int fd)
{
	ssize_t	yld;
	char	*out;

	out = NULL;
	yld = ft_vasprintf(&out, fmt, vargs);
	if (yld == -1)
		return (-1);
	yld = write(fd, out, yld);
	free(out);
	return (yld);
}
