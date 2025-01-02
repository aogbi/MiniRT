/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:29:07 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/05/26 19:53:30 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

typedef unsigned char	t_byte;

typedef struct s_data_blk
{
	struct s_data_blk	*next;
	char				*data;
	size_t				len;
	size_t				off;
}	t_data_blk;

typedef struct s_data_strm
{
	t_data_blk	*root_blk;
	t_data_blk	*eol_blk;
	t_data_blk	*recent_blk;
	size_t		len;
}	t_data_strm;

void		clear_data_strm(t_data_strm *strm)
			__attribute__((nonnull(1)));

#endif
