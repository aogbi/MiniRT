/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf_stubs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:52:33 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/05/20 17:09:25 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VASPRINTF_STUBS_H
# define FT_VASPRINTF_STUBS_H

# include "ft_vasprintf.h"

void	adjust_prc_cstrts(ssize_t *prc, t_cnv_type type);
void	init_cnv_len_dflts(t_cnv_len *len, t_cnv_fmt *fmt);

#endif