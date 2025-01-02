/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/05/26 19:38:37 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	store_strm(t_strm_store *store, t_data_strm *anchor);

int	get_data_strm(t_strm_store *store, int fd)
{
	t_data_strm	*stored_strm;

	stored_strm = store->root_strm;
	if (stored_strm)
	{
		while (stored_strm->next && stored_strm->fd < fd)
			stored_strm = stored_strm->next;
		if (stored_strm->fd == fd)
			return (store->active_strm = stored_strm, 1);
	}
	store->active_strm = (t_data_strm *)malloc(sizeof(t_data_strm));
	if (!store->active_strm)
		return (store->active_strm = NULL, 0);
	*store->active_strm = (t_data_strm){.fd = fd};
	store_strm(store, stored_strm);
	return (1);
}

void	store_strm(t_strm_store *store, t_data_strm *anchor)
{
	if (anchor)
	{
		if (anchor->fd < store->active_strm->fd)
		{
			store->active_strm->next = anchor->next;
			store->active_strm->prev = anchor;
			anchor->next = store->active_strm;
			return ;
		}
		store->active_strm->next = anchor;
		store->active_strm->prev = anchor->prev;
		if (anchor->prev)
			anchor->prev->next = store->active_strm;
		else
			store->root_strm = store->active_strm;
		anchor->prev = store->active_strm;
		return ;
	}
	store->root_strm = store->active_strm;
}

void	clear_data_strm(t_strm_store *store)
{
	t_data_blk	*strm_blk;

	if (!store->active_strm)
		return ;
	while (store->active_strm->root_blk)
	{
		strm_blk = store->active_strm->root_blk;
		store->active_strm->root_blk = strm_blk->next;
		free(strm_blk->data);
		free(strm_blk);
	}
	if (store->active_strm == store->root_strm)
	{
		if (store->active_strm->next)
			store->root_strm = store->active_strm->next;
		else
			store->root_strm = NULL;
	}
	if (store->active_strm->next)
		store->active_strm->next->prev = store->active_strm->prev;
	if (store->active_strm->prev)
		store->active_strm->prev->next = store->active_strm->next;
	free(store->active_strm);
	store->active_strm = NULL;
}
