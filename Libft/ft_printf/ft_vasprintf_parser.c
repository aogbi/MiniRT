/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:53:56 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/02 14:47:52 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vasprintf.h"

static size_t	count_fmt_toks(const char *fmt);
static int		count_fmt_toks_act(size_t *i, char **fmt, va_list *vargs,
					void *yld);
static void		skip_fmt_tok(int spc_occ, char **fmt);
static int		parse_fmt_act(size_t *i,	char **fmt, va_list *vargs,
					void *yld);

t_fmt_tok	*parse_fmt(const char *fmt)
{
	size_t		toks_cnt;
	t_fmt_tok	*toks;
	t_fmt_tok	*p_toks;
	int			spc_occ;

	toks_cnt = count_fmt_toks(fmt);
	toks = (t_fmt_tok *)malloc((toks_cnt + 1) * sizeof(t_fmt_tok));
	if (!toks)
		return (NULL);
	p_toks = toks;
	spc_occ = -1;
	ft_vstriteri((char *)fmt, parse_fmt_act, &p_toks, &spc_occ);
	p_toks->str = NULL;
	p_toks->len = 0;
	return (toks);
}

static int	parse_fmt_act(size_t *i __attribute__ ((unused)),
	char **fmt, va_list *vargs, void *yld)
{
	int			*spc_occ;
	t_fmt_tok	**toks;

	spc_occ = va_arg(*vargs, int *);
	toks = (t_fmt_tok **)yld;
	if (**fmt == '%' && (ft_isdigit(*(*fmt + 1))
			|| ft_strchr(CNV_FMT_CHRSET, *(*fmt + 1) | -!*(*fmt + 1))))
	{
		*spc_occ = 1;
		(*toks)->str = *fmt + 1;
		skip_fmt_tok(*spc_occ, fmt);
		(*toks)->len = -(*fmt - (*toks)->str);
		++*toks;
		return (FLOW_CONTINUE);
	}
	*spc_occ = 0;
	(*toks)->str = *fmt;
	skip_fmt_tok(*spc_occ, fmt);
	(*toks)->len = *fmt - (*toks)->str;
	++*toks;
	return (FLOW_CONTINUE);
}

static size_t	count_fmt_toks(const char *fmt)
{
	size_t	toks_cnt;
	int		spc_occ;

	toks_cnt = 0;
	spc_occ = -1;
	ft_vstriteri((char *)fmt, count_fmt_toks_act, &toks_cnt, &spc_occ);
	return (toks_cnt);
}

static int	count_fmt_toks_act(size_t *i __attribute__ ((unused)),
	char **fmt, va_list *vargs, void *yld)
{
	int		*spc_occ;
	size_t	*toks_cnt;

	spc_occ = va_arg(*vargs, int *);
	toks_cnt = (size_t *)yld;
	if (**fmt == '%' && (ft_isdigit(*(*fmt + 1))
			|| ft_strchr(CNV_FMT_CHRSET, *(*fmt + 1) | -!*(*fmt + 1))))
	{
		*spc_occ = 1;
		++*toks_cnt;
		skip_fmt_tok(*spc_occ, fmt);
		return (FLOW_CONTINUE);
	}
	if (*spc_occ)
	{
		*spc_occ = 0;
		++*toks_cnt;
	}
	return (FLOW_ITERATE);
}

static void	skip_fmt_tok(int spc_occ, char **fmt)
{
	if (spc_occ)
	{
		++*fmt;
		while (**fmt && (ft_isdigit(**fmt) || **fmt == '-' || **fmt == '+'
				|| **fmt == 32 || **fmt == '#' || **fmt == '.'))
			++*fmt;
		if (**fmt && ft_strchr(CNV_SPCS_CHRSET, **fmt))
			++*fmt;
		return ;
	}
	while (**fmt && !(**fmt == '%' && (ft_isdigit(*(*fmt + 1))
				|| ft_strchr(CNV_FMT_CHRSET, *(*fmt + 1) | -!*(*fmt + 1)))))
		++*fmt;
}
