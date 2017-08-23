/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: mfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2017/07/11 18:24:24 by mfranc            #+#    #+#             */
/*   Updated: 2017/08/22 21:09:24 by mfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void			ft_init_dist(t_adj_list *current_room, int dist)
{
	t_adj_list	**next_rooms;
	int			i;

	current_room->dist = dist;
	if (current_room->start == 1)
		return ;
	i = -1;
	next_rooms = current_room->rooms_linked;
	while (++i < current_room->nb_tunnels)
	{
		if (!next_rooms[i]->end)
			if (!next_rooms[i]->dist || next_rooms[i]->dist > (dist + 1))
				ft_init_dist(next_rooms[i], dist + 1);
	}
}

t_adj_list		*ft_get_next_room_way(t_adj_list *curr_room, int way_id)
{

	int			nb_tunnels;
	int			i_shortter_room_to_end;
	int			i;
	t_adj_list	**next_rooms;

	nb_tunnels = curr_room->nb_tunnels;
	next_rooms = curr_room->rooms_linked;
	i = 0;
	i_shortter_room_to_end = 0;
	while (i < nb_tunnels)
	{
		if (next_rooms[i]->end || (next_rooms[i]->way_id == way_id && curr_room->dist > next_rooms[i]->dist))
			i_shortter_room_to_end = i;	
		i++;
	}
	return (next_rooms[i_shortter_room_to_end]);
}

void			ft_delete_ant(t_datas_graph *datas_graph, t_ants **ant)
{
	t_ants		*tmp_ant;
	t_ants		*ant_to_free;

	tmp_ant = *ant;
	ant_to_free = *ant;
	if (datas_graph->nb_ants == 1)
	{
		*ant = NULL;
		datas_graph->ants = NULL;
		datas_graph->last_ant = NULL;
	}
	else if (!tmp_ant->prev)
	{
		(*ant)->next->prev = NULL;
		datas_graph->ants = (*ant)->next;
		*ant = datas_graph->ants;
	}
	else if (!tmp_ant->next)
	{
		(*ant)->prev->next = NULL;
		datas_graph->last_ant = datas_graph->last_ant->prev;
		*ant = datas_graph->last_ant;
	}
	else
	{
		*ant = (*ant)->next;
		(*ant)->prev = tmp_ant->next;
		(*ant)->next->prev = tmp_ant->prev;
	}
	datas_graph->nb_ants--;
	ft_memdel((void**)&ant_to_free);
}

void			ft_move_ant_room(t_adj_list *next_room, t_ants *ant)
{
	next_room->ant_in += ant->ant_number;			
	ant->curr_room->ant_in = 0;
	ant->curr_room = next_room;
	ft_printf("L%d-%s", ant->ant_number, ant->curr_room->name);
	ft_putchar(' ');
}

void			ft_move_ants_map(t_datas_graph  *datas_graph)
{
	t_adj_list	*next_room;
	t_ants		*ants;

	ants = datas_graph->ants;
	while (ants)
	{
		next_room = ft_get_next_room_way(ants->curr_room, ants->way_id);
		if (!next_room->ant_in || next_room->end)
			ft_move_ant_room(next_room, ants);
		if (ants->curr_room->end)
			ft_delete_ant(datas_graph, &ants);
		else
			ants = ants->next;
	}
}
/*
int				ft_init_ants_at_end(t_ants **ants, int nb_ants)
{
	int			ants_at_end;
	int			i

	i = -1;
	ants_at_end = 0;
	while (++i < nb_ants)
		ants_at_end += ants[i]->ant_number;
	return (ants_at_end);
}
*/
void			ft_map_crosser(t_datas_graph *datas_graph)
{
	t_adj_list	**rooms;
	t_adj_list	*end_room;

	rooms = datas_graph->adj_list;
	end_room = datas_graph->adj_list[datas_graph->nb_rooms - 1];
	while (datas_graph->ants)
	{	
		ft_move_ants_map(datas_graph);
		ft_putchar('\n');
	}
}