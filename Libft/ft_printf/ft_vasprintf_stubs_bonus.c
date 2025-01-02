/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf_stubs_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:42:56 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/02/24 10:52:51 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vasprintf_stubs_bonus.h"

void	adjust_flgs(t_fmt_mods *mods, char flg)
{
	if (flg == '-')
		mods->flgs = (mods->flgs | LFT_JFY) & ~ZRO_PAD;
	else if (flg == '+')
		mods->flgs = (mods->flgs | FRC_SGN) & ~PAD_SGN;
	else if (flg == ' ')
		mods->flgs |= !(mods->flgs & FRC_SGN) * PAD_SGN;
	else if (flg == '#')
		mods->flgs |= ALT_FRM;
	else if (flg == '0')
		mods->flgs |= !(mods->flgs & LFT_JFY) * ZRO_PAD;
}
