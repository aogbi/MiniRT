/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf_compositor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 05:31:35 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/02/24 22:01:37 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vasprintf.h"

static void	set_pad(char **str, bool *pad_occ, t_cnv_len *len, t_cnv_fmt *fmt);
static void	set_pre(char **str, t_cnv_fmt *fmt);

int	compose_cnv_str(t_cnv *cnv, t_cnv_fmt *fmt)
{
	char	*p_str;
	bool	pad_occ;
	int		off;

	cnv->str = (char *)malloc(cnv->len.agg * sizeof(char));
	if (!cnv->str)
		return (0);
	p_str = cnv->str;
	pad_occ = false;
	set_pad(&p_str, &pad_occ, &cnv->len, fmt);
	set_pre(&p_str, fmt);
	ft_memset(p_str, '0', cnv->len.lead);
	p_str += cnv->len.lead;
	if (fmt->type == ESC || fmt->type == CHAR)
		*p_str = (char)(intptr_t)fmt->arg;
	else
	{
		off = 0;
		if (fmt->type == INT && *fmt->arg == '-')
			off = sizeof(char);
		ft_memcpy(p_str, fmt->arg + off, cnv->len.arg);
	}
	p_str += cnv->len.arg;
	set_pad(&p_str, &pad_occ, &cnv->len, fmt);
	return (1);
}

static void	set_pad(char **str, bool *pad_occ, t_cnv_len *len, t_cnv_fmt *fmt)
{
	int		pad_len;

	pad_len = 0;
	if (!*pad_occ)
	{
		*pad_occ = true;
		if (!(fmt->mods.flgs & LFT_JFY))
			pad_len = len->pad;
		if (fmt->mods.prc == -1 && fmt->mods.flgs & ZRO_PAD && !len->lead)
		{
			len->lead = pad_len;
			pad_len = 0;
		}
	}
	else
		if (fmt->mods.flgs & LFT_JFY)
			pad_len = len->pad;
	ft_memset(*str, 32, pad_len);
	*str += pad_len;
}

static void	set_pre(char **str, t_cnv_fmt *fmt)
{
	char	sgn;

	sgn = '\0';
	if (fmt->type == INT && *fmt->arg == '-')
		sgn = *fmt->arg;
	if (fmt->mods.flgs & (FRC_SGN | PAD_SGN))
		sgn = 32 + !!(fmt->mods.flgs & FRC_SGN) * ('+' - 32);
	if (sgn)
		*(*str)++ = sgn;
	if (fmt->mods.flgs & ALT_FRM)
	{
		*(*str)++ = '0';
		*(*str)++ = 'x' - (fmt->type == UXINT) * 32;
	}
}
