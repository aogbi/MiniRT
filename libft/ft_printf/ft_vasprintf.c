/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:57:18 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/02 14:47:49 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vasprintf.h"

static ssize_t	process_fmt_toks(t_fmt_tok *toks, va_list *vargs,
					size_t *out_len);
static int		assemble_output(char **out, t_fmt_tok *toks, size_t *out_len);
static void		clear_fmt_toks(t_fmt_tok *toks);

int	ft_vasprintf(char **out, const char *fmt, va_list *vargs)
{
	t_fmt_tok	*toks;
	size_t		out_len;
	int			yld;
	bool		fail_occ;

	if (!fmt)
		return (-1);
	toks = parse_fmt(fmt);
	if (!toks)
		return (-1);
	yld = process_fmt_toks(toks, vargs, &out_len);
	fail_occ = false;
	if (!yld)
		fail_occ = true;
	if (!fail_occ)
	{
		yld = assemble_output(out, toks, &out_len);
		if (!yld)
			fail_occ = true;
	}
	clear_fmt_toks(toks);
	if (fail_occ)
		return (-1);
	return (out_len);
}

static ssize_t	process_fmt_toks(t_fmt_tok *toks, va_list *vargs,
					size_t *out_len)
{
	int		yld;

	yld = 1;
	*out_len = 0;
	while (toks && toks->str)
	{
		if (toks->len < 0)
			yld = format(toks, vargs);
		*out_len += ft_labs(toks->len);
		if (!yld)
			return (0);
		++toks;
	}
	return (1);
}

static int	assemble_output(char **out, t_fmt_tok *toks, size_t *out_len)
{
	char		*p_out;
	size_t		tok_len;

	*out = (char *)malloc((*out_len + 1) * sizeof(char));
	if (!*out)
		return (0);
	p_out = *out;
	while (toks && toks->str)
	{
		tok_len = ft_labs(toks->len);
		ft_memcpy(p_out, toks->str, tok_len);
		p_out += tok_len;
		++toks;
	}
	*p_out = '\0';
	return (1);
}

static void	clear_fmt_toks(t_fmt_tok *toks)
{
	t_fmt_tok	*p_toks;

	p_toks = toks;
	while (p_toks && p_toks->str)
	{
		if (p_toks->len < 0)
			free(p_toks->str);
		++p_toks;
	}
	free(toks);
}
