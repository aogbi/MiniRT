/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/05/26 19:53:51 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
	struct s_data_strm	*prev;
	struct s_data_strm	*next;
	t_data_blk			*root_blk;
	t_data_blk			*eol_blk;
	t_data_blk			*recent_blk;
	size_t				len;
	int					fd;
}	t_data_strm;

typedef struct s_strm_store
{
	t_data_strm	*root_strm;
	t_data_strm	*active_strm;
}	t_strm_store;

void	clear_data_strm(t_strm_store *store)
		__attribute__((nonnull(1)));
int		get_data_strm(t_strm_store *store, int fd)
		__attribute__((nonnull(1)));

#endif
