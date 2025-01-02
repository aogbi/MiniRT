/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:42:36 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/02 15:22:24 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	vargs;
	ssize_t	yld;

	va_start(vargs, fmt);
	yld = ft_vprintf_fd(fmt, &vargs, STDOUT_FILENO);
	va_end(vargs);
	return (yld);
}
