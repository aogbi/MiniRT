/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf_formatter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 05:18:22 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/05/20 17:09:09 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vasprintf.h"
#include "ft_vasprintf_stubs.h"

static t_cnv_type	process_cnv_type(char **arg, char spc, va_list *vargs);
static void			adjust_cnv_cstrts(t_cnv_fmt *fmt);
static size_t		compute_cnv_len(t_cnv_len *len, t_cnv_fmt *fmt);

int	format(t_fmt_tok *tok, va_list *vargs)
{
	t_cnv_fmt		fmt;
	t_mods_hndlr	mods_hndlr;
	t_cnv			cnv;

	fmt = (t_cnv_fmt){.mods.vldty = 1, .mods.prc = -1};
	mods_hndlr = PROCESS_MODS;
	if (mods_hndlr)
		mods_hndlr(&fmt.mods, tok);
	if (fmt.mods.vldty == -1)
		return (tok->str = "", tok->len = 0, 0);
	if (!fmt.mods.vldty)
		return (--tok->str, tok->len = -tok->len + 1, 1);
	fmt.type = process_cnv_type(&fmt.arg, tok->str[-tok->len - 1], vargs);
	if (!fmt.type)
		return (--tok->str, tok->len = -tok->len + 1, 1);
	adjust_cnv_cstrts(&fmt);
	cnv.len.agg = compute_cnv_len(&cnv.len, &fmt);
	if (!cnv.len.agg)
		return (tok->len = 0, 1);
	if (!compose_cnv_str(&cnv, &fmt))
		return (tok->str = "", tok->len = 0, 0);
	if (fmt.type != ESC && fmt.type != CHAR && fmt.type != STR
		&& fmt.type != NPTR)
		free(fmt.arg);
	return (tok->str = cnv.str, tok->len = -cnv.len.agg, 1);
}

static t_cnv_type	process_cnv_type(char **arg, char spc, va_list *vargs)
{
	if (spc == '%')
		return (*arg = (char *)(intptr_t)spc, ESC);
	if (spc == 'c')
		return (*arg = (char *)(intptr_t)va_arg(*vargs, int), CHAR);
	if (spc == 's' || spc == 'p')
	{
		*arg = va_arg(*vargs, void *);
		if (!*arg && spc == 's')
			return (*arg = "(null)", NPTR);
		if (spc == 's')
			return (STR);
		if (!*arg && spc == 'p')
			return (*arg = "(nil)", NPTR);
		if (spc == 'p')
			return (*arg = ft_ultoa_base((uintptr_t)(*arg), XDGT), XPTR);
	}
	if (spc == 'd' || spc == 'i')
		return (*arg = ft_itoa(va_arg(*vargs, int)), INT);
	if (spc == 'u')
		return (*arg = ft_utoa(va_arg(*vargs, unsigned)), UINT);
	if (spc == 'x')
		return (*arg = ft_utoa_base(va_arg(*vargs, unsigned), XDGT), XINT);
	if (spc == 'X')
		return (*arg = ft_utoa_base(va_arg(*vargs, unsigned), UXDGT), UXINT);
	return (*arg = NULL, UNDEF);
}

static void	adjust_cnv_cstrts(t_cnv_fmt *fmt)
{
	if (fmt->type == ESC)
		fmt->mods.flgs &= ~(LFT_JFY | FRC_SGN | PAD_SGN | ALT_FRM | ZRO_PAD);
	else if (fmt->type == CHAR || fmt->type == STR || fmt->type == NPTR)
	{
		fmt->mods.flgs &= ~(FRC_SGN | PAD_SGN | ALT_FRM | ZRO_PAD);
		adjust_prc_cstrts(&fmt->mods.prc, fmt->type);
	}
	else if (fmt->type == INT || fmt->type == UINT)
	{
		fmt->mods.flgs &= ~ALT_FRM;
		if (*fmt->arg == '-' || fmt->type == UINT)
			fmt->mods.flgs &= ~(FRC_SGN | PAD_SGN);
	}
	else if (fmt->type == XINT || fmt->type == UXINT)
	{
		fmt->mods.flgs &= ~(FRC_SGN | PAD_SGN);
		if (*fmt->arg == '0')
			fmt->mods.flgs &= ~ALT_FRM;
	}
	else if (fmt->type == XPTR)
		fmt->mods.flgs |= ALT_FRM;
}

static size_t	compute_cnv_len(t_cnv_len *len, t_cnv_fmt *fmt)
{
	init_cnv_len_dflts(len, fmt);
	if (fmt->type == ESC)
		return (len->arg);
	if (fmt->type != CHAR)
		len->arg = ft_strlen(fmt->arg);
	if (fmt->type == CHAR || fmt->type == STR || fmt->type == NPTR)
	{
		if (fmt->mods.prc >= 0 && (size_t)fmt->mods.prc < len->arg)
			len->arg = fmt->mods.prc;
		if ((size_t)fmt->mods.wid <= len->arg)
			fmt->mods.wid = len->arg;
		len->pad = fmt->mods.wid - len->arg;
		return (len->pad + len->arg);
	}
	if ((fmt->mods.prc == 0) && *fmt->arg == '0')
		len->arg = 0;
	if (fmt->type == INT && *fmt->arg == '-')
		len->arg -= sizeof(char);
	if (fmt->mods.prc >= 0 && (size_t)fmt->mods.prc >= len->arg)
		len->lead = fmt->mods.prc - len->arg;
	if ((size_t)fmt->mods.wid <= (len->pre + len->lead + len->arg))
		fmt->mods.wid = len->pre + len->lead + len->arg;
	if (fmt->mods.wid > fmt->mods.prc)
		len->pad = fmt->mods.wid - (len->pre + len->lead + len->arg);
	return (len->pad + len->pre + len->lead + len->arg);
}
