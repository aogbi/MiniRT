/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:53:59 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/06/05 00:48:39 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VASPRINTF_H
# define FT_VASPRINTF_H

# include "libft.h"

# define CNV_FMT_CHRSET		"-+ #.cspdiuxX%"
# define CNV_SPCS_CHRSET	"cspdiuxX%"

typedef struct s_fmt_tok
{
	char	*str;
	ssize_t	len;
}	t_fmt_tok;

typedef struct s_fmt_mods
{
	int		vldty;
	ssize_t	prc;
	ssize_t	wid;
	t_byte	flgs;
}	t_fmt_mods;

typedef void	(*t_mods_hndlr)(t_fmt_mods *, t_fmt_tok *);

# define PROCESS_MODS	NIL

# ifndef NO_LIBFTPRINTF_BONUS

void		process_mods(t_fmt_mods *mods, t_fmt_tok *tok);

#  undef PROCESS_MODS
#  define PROCESS_MODS	process_mods

typedef enum e_mod_state
{
	CNV_FMT_OCC = -1,
	MOD_FLG_OCC,
	WID_MOD_OCC,
	PRC_MOD_OCC,
	INV_MOD_OCC,
	END_MOD_OCC,
}	t_mod_state;

#  define STTS_CNT	END_MOD_OCC

# endif

# define LFT_JFY	0x01
# define FRC_SGN	0x02
# define PAD_SGN	0x04
# define ALT_FRM	0x08
# define ZRO_PAD	0x10

# define XDGT	"0123456789abcdef"
# define UXDGT	"0123456789ABCDEF"

typedef enum e_cnv_type
{
	UNDEF,
	NPTR,
	XINT,
	UXINT,
	UINT,
	INT,
	XPTR,
	STR,
	CHAR,
	ESC,
}	t_cnv_type;

typedef struct s_cnv_fmt
{
	t_fmt_mods	mods;
	t_cnv_type	type;
	char		*arg;
}	t_cnv_fmt;

typedef struct s_cnv_off
{
	int		pad;
	int		pre;
	int		lead;
	size_t	arg;
	ssize_t	agg;
}	t_cnv_len;

typedef struct s_cnv
{
	char		*str;
	t_cnv_len	len;
}	t_cnv;

t_fmt_tok	*parse_fmt(const char *fmt);
int			format(t_fmt_tok *tok, va_list *vargs);
int			compose_cnv_str(t_cnv *cnv, t_cnv_fmt *fmt);

#endif