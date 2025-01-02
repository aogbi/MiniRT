/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:20:49 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/05/26 19:38:34 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_data_strm(t_data_strm *strm)
{
	t_data_blk	*strm_blk;

	while (strm->root_blk)
	{
		strm_blk = strm->root_blk;
		strm->root_blk = strm_blk->next;
		free(strm_blk->data);
		free(strm_blk);
	}
	*strm = (t_data_strm){};
}
