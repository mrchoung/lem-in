/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_adj_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:40:18 by mfranc            #+#    #+#             */
/*   Updated: 2017/07/11 15:02:48 by mfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_adj_list			*ft_init_elem_list_adj(t_data_rooms *tmp_rooms, int id, int nb_tunnels)
{
	t_adj_list		*elem_list;

	elem_list = ft_memalloc(sizeof(t_adj_list));
	elem_list->id = id;
	elem_list->name = tmp_rooms->name;
	elem_list->dist = 0;
	elem_list->ant_in = 0;
	elem_list->x = tmp_rooms->x;
	elem_list->y = tmp_rooms->y;
	elem_list->start = (tmp_rooms->start == 1) ? 1 : 0;
	elem_list->end = (tmp_rooms->end == 1) ? 1 : 0;
	elem_list->nb_tunnels = nb_tunnels;
	if (elem_list->start && elem_list->nb_tunnels == 0)
		return (NULL);
	elem_list->rooms_linked = NULL;
	elem_list->next = NULL;
	return (elem_list);
}

int				ft_build_adj_list(t_data_store *data_store, t_datas_graph *datas_graph)
{
	t_data_rooms	*tmp_rooms;
	t_adj_list		**list;
	int				i;

	list = datas_graph->adj_list;
	tmp_rooms = data_store->rooms;
	i = 0;
	while (tmp_rooms)
	{
		if (!(list[i] = ft_init_elem_list_adj(tmp_rooms, i, tmp_rooms->tunnels)))
			return (-1);
		tmp_rooms = tmp_rooms->next;
		i++;
	}
	return (1);
}

t_adj_list			*ft_get_room_by_name(char *room_to_find, t_datas_graph *datas_graph)
{
	int				i;
	t_adj_list		**list;

	i = 0;
	list = datas_graph->adj_list;
	while (i < datas_graph->nb_rooms)
	{
		if (ft_strequ(list[i]->name, room_to_find))
			return (list[i]);
		i++;
	}
	return (NULL);
}

t_adj_list			**ft_init_rooms_linked(t_data_rooms *rooms, t_datas_graph *datas_graph)
{
	int				o;
	t_adj_list		**rooms_linked;
	t_list			*tmp_rooms_linked;

	o = 0;
	rooms_linked = ft_memalloc(sizeof(t_adj_list*) * rooms->tunnels);
	tmp_rooms_linked = rooms->rooms_linked;
	while (tmp_rooms_linked)
	{	
		rooms_linked[o] = ft_get_room_by_name(tmp_rooms_linked->content, datas_graph);
		tmp_rooms_linked = tmp_rooms_linked->next;
		o++;
	}
	return (rooms_linked);
}

int				ft_build_tunnels_adj_list(t_data_rooms *rooms, t_datas_graph *datas_graph)
{
	t_adj_list		**list;
	t_data_rooms	*tmp_rooms;
	int				i;
	int			no_link;

	list = datas_graph->adj_list;
	tmp_rooms = rooms;
	i = 0;
	no_link = 0;
	while (i < datas_graph->nb_rooms && tmp_rooms)
	{
		if (list[i]->nb_tunnels > 0)
			list[i]->rooms_linked = ft_init_rooms_linked(tmp_rooms, datas_graph);	
		else
			no_link++;
		tmp_rooms = tmp_rooms->next;
		i++;
	}
	if (no_link == (datas_graph->nb_rooms -1))
		return (-1);
	return (1);
}
