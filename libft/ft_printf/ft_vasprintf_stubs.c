/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf_stubs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 02:37:26 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/05/20 17:12:35 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vasprintf_stubs.h"

void	adjust_prc_cstrts(ssize_t *prc, t_cnv_type type)
{
	if (type == CHAR)
		*prc = -1;
	if (type == NPTR && *prc > 0 && ((size_t)(*prc) < ft_strlen("(nil)")
		|| (size_t)(*prc) < ft_strlen("(null)")))
		*prc = 0;
}

void	init_cnv_len_dflts(t_cnv_len *len, t_cnv_fmt *fmt)
{
	*len = (t_cnv_len){.arg = 1};
	if ((fmt->type == INT && *fmt->arg == '-')
		|| (fmt->mods.flgs & (FRC_SGN | PAD_SGN)))
		len->pre = 1;
	if (fmt->mods.flgs & ALT_FRM)
		len->pre += sizeof(char) * 2;
}
