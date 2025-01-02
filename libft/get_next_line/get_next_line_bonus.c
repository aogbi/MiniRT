/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/05/13 20:05:52 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		read_data_blk(t_data_strm *strm, int fd);
char	*seek_eol(t_data_strm *strm);
char	*retrieve_line(t_data_strm *strm, char *eol);
void	extract_line(char **line, t_data_strm *strm, size_t eol_blk_off);

char	*get_next_line(int fd)
{
	static t_strm_store	store;
	int					yld;
	char				*eol;
	char				*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	yld = get_data_strm(&store, fd);
	while (yld)
	{
		if (store.active_strm->root_blk
			&& store.active_strm->root_blk->len == 0)
			break ;
		eol = seek_eol(store.active_strm);
		if (eol)
		{
			line = retrieve_line(store.active_strm, eol);
			if (!line)
				break ;
			return (line);
		}
		if (!read_data_blk(store.active_strm, fd))
			break ;
	}
	return (clear_data_strm(&store), NULL);
}

int	read_data_blk(t_data_strm *strm, int fd)
{
	ssize_t	read_yld;

	strm->recent_blk = (t_data_blk *)malloc(sizeof(t_data_blk));
	if (!strm->recent_blk)
		return (0);
	*strm->recent_blk = (t_data_blk){};
	strm->recent_blk->data = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!strm->recent_blk->data)
		return (free(strm->recent_blk), strm->recent_blk = NULL, 0);
	read_yld = read(fd, strm->recent_blk->data, BUFFER_SIZE);
	if (read_yld == -1)
		return (free(strm->recent_blk->data), free(strm->recent_blk),
			strm->recent_blk = NULL, 0);
	strm->recent_blk->len = read_yld;
	strm->len += strm->recent_blk->len;
	if (strm->root_blk && strm->eol_blk)
		strm->eol_blk->next = strm->recent_blk;
	else
		strm->root_blk = strm->recent_blk;
	return (1);
}

char	*seek_eol(t_data_strm *strm)
{
	char	*eol;

	if (!strm->root_blk)
		return (NULL);
	if (strm->recent_blk->len > 0)
	{
		strm->eol_blk = strm->recent_blk;
		eol = ft_memchr(strm->eol_blk->data + strm->eol_blk->off,
				10, strm->eol_blk->len - strm->eol_blk->off);
		if (!eol)
			return (NULL);
	}
	else
		eol = strm->eol_blk->data + (strm->eol_blk->len - 1);
	return (eol);
}

char	*retrieve_line(t_data_strm *strm, char *eol)
{
	size_t	eol_blk_off;
	size_t	line_len;
	char	*line;

	eol_blk_off = eol - strm->eol_blk->data;
	line_len = strm->len - (strm->eol_blk->len - (eol_blk_off + 1));
	line = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	return (extract_line(&line, strm, eol_blk_off), line);
}

void	extract_line(char **line, t_data_strm *strm, size_t eol_blk_off)
{
	t_data_blk	*strm_blk;
	char		*p_line;
	size_t		chunk_len;

	strm_blk = strm->root_blk;
	p_line = *line;
	while (strm_blk)
	{
		if (strm_blk == strm->eol_blk)
			chunk_len = eol_blk_off - strm_blk->off + 1;
		else
			chunk_len = strm_blk->len - strm_blk->off;
		ft_memcpy(p_line, strm_blk->data + strm_blk->off, chunk_len);
		p_line += chunk_len;
		strm_blk->off += chunk_len;
		strm->len -= chunk_len;
		if (strm_blk->off != strm_blk->len)
			break ;
		strm->root_blk = strm_blk->next;
		free(strm_blk->data);
		free(strm_blk);
		strm_blk = strm->root_blk;
	}
	*p_line = '\0';
}
