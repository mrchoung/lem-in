/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:24:24 by mfranc            #+#    #+#             */
/*   Updated: 2017/07/13 20:54:26 by mfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void			ft_push_back_ways(t_ways **ways, t_ways *new_way)
{
	t_ways		*tmp_ways;

	if (!*ways)
		*ways = new_way;
	else
	{
		tmp_ways = *ways;
		while (tmp_ways && tmp_ways->next)
			tmp_ways = tmp_ways->next;
		tmp_ways->next = new_way;
	}
}

void			ft_push_back_room_way(t_ways *way, t_adj_list *next_room)
{
	t_adj_list	*tmp_rooms;

	tmp_rooms = way->rooms;
	while (tmp_rooms && tmp_rooms->next)
		tmp_rooms = tmp_rooms->next;
	tmp_rooms->next = next_room;
}

void			ft_new_way(t_adj_list *content_elem_list, t_datas_graph *datas_graph, int id)
{
	t_ways		*new_way;
	t_ways		*ways;
	t_adj_list	*content_elem_way;

	ways = datas_graph->ways;
	new_way = ft_memalloc(sizeof(t_ways));
	content_elem_way = ft_memalloc(sizeof(t_adj_list));
	new_way->id = id; 
	new_way->rooms = ft_memcpy(content_elem_way, content_elem_list, sizeof(t_adj_list));
	new_way->next = NULL;
	if (!datas_graph->ways)
		ft_push_back_ways(&datas_graph->ways, new_way);
	else
		ft_push_back_ways(&ways, new_way);
}

void			ft_init_start_ways(t_datas_graph *datas_graph)
{
	t_adj_list	*start_room;
	int			i;

	start_room = datas_graph->adj_list[0];
	i = -1;
	while (++i < datas_graph->adj_list[0]->nb_tunnels)
		ft_new_way(start_room, datas_graph, i);
}

void			ft_new_room_way(t_adj_list *content_elem_list, t_ways *ways)
{
	t_adj_list	*content_elem_way;

	content_elem_way = ft_memalloc(sizeof(t_adj_list));
	content_elem_way = ft_memcpy(content_elem_way, content_elem_list, sizeof(t_adj_list));
	content_elem_way->next = NULL;
	ft_push_back_room_way(ways, content_elem_way);
}

void			ft_init_second_room(t_datas_graph *datas_graph)
{
	t_adj_list	**second_rooms_ways;
	t_adj_list	*second_room;
	t_ways		*ways;
	int			i;

	ways = datas_graph->ways;
	second_rooms_ways = datas_graph->adj_list[0]->rooms_linked;
	i = 0;
	while (i < datas_graph->adj_list[0]->nb_tunnels && ways)
	{	
		second_room = second_rooms_ways[i];
		ft_new_room_way(second_rooms_ways[i], ways);
		ways = ways->next;
		i++;
	}
}

void			ft_build_ways(t_datas_graph *datas_graph)
{
	ft_init_start_ways(datas_graph);
	ft_init_second_room(datas_graph);
}
