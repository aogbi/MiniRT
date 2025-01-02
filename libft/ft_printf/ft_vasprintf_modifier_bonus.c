/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf_modifier_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:53:56 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/02 14:47:58 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vasprintf.h"
#include "ft_vasprintf_stubs_bonus.h"

static t_mod_state	eval_mod_stt(char **mod, t_mod_state stt);
static int			adjust_mods(t_fmt_mods *mods, char **mod, t_mod_state stt);

void	process_mods(t_fmt_mods *mods, t_fmt_tok *tok)
{
	t_mod_state	stt;
	char		*mod;
	int			ctrl;

	stt = CNV_FMT_OCC;
	mod = tok->str;
	while (mod - tok->str < -tok->len && (ft_isdigit(*mod) || *mod == '-'
			|| *mod == '+' || *mod == 32 || *mod == '#' || *mod == '.'))
	{
		stt = eval_mod_stt(&mod, stt);
		ctrl = adjust_mods(mods, &mod, stt);
		if (ctrl == FLOW_CONTINUE)
			continue ;
		else if (!ctrl)
			break ;
		++mod;
	}
}

static t_mod_state	eval_mod_stt(char **mod, t_mod_state stt)
{
	if ((stt == CNV_FMT_OCC || stt == MOD_FLG_OCC)
		&& (**mod == '-' || **mod == '+' || **mod == 32 || **mod == '#'
			|| **mod == '0'))
		return (MOD_FLG_OCC);
	if ((stt == CNV_FMT_OCC || stt == MOD_FLG_OCC) && ft_isdigit(**mod))
		return (WID_MOD_OCC);
	if ((stt == CNV_FMT_OCC || stt == MOD_FLG_OCC || stt == WID_MOD_OCC)
		&& (**mod == '.' && (ft_isdigit(*(*mod + 1))
				|| ft_strchr(CNV_SPCS_CHRSET, *(*mod + 1)))))
		return (++*mod, PRC_MOD_OCC);
	return (INV_MOD_OCC);
}

static int	adjust_mods(t_fmt_mods *mods, char **mod, t_mod_state stt)
{
	if (stt == INV_MOD_OCC)
		return (mods->vldty = 0, FLOW_BREAK);
	if (stt == MOD_FLG_OCC)
		return (adjust_flgs(mods, **mod), FLOW_ITERATE);
	if (stt == WID_MOD_OCC)
	{
		mods->wid = ft_atol(*mod);
		if (mods->wid > INT_MAX)
			return (mods->vldty = -1, FLOW_BREAK);
	}
	else if (stt == PRC_MOD_OCC && ft_isdigit(**mod))
	{
		mods->prc = ft_atol(*mod);
		if (mods->prc > INT_MAX)
			return (mods->vldty = -1, FLOW_BREAK);
	}
	else
		mods->prc = 0;
	while (ft_isdigit(**mod))
		++*mod;
	return (FLOW_CONTINUE);
}
