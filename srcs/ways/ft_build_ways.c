/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: mfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2017/07/11 18:24:24 by mfranc            #+#    #+#             */
/*   Updated: 2017/08/21 11:51:41 by mfranc           ###   ########.fr       */
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

t_adj_list		*ft_get_next_room(t_adj_list *curr_room)
{
	int			nb_tunnels;
	int			shortter_dist_to_end_room;
	int			i_shortter_room_to_end;
	int			i;
	t_adj_list	**next_rooms;

	nb_tunnels = curr_room->nb_tunnels;
	next_rooms = curr_room->rooms_linked;
	shortter_dist_to_end_room = 2147483647;
	i = 0;
	while (i < nb_tunnels)
	{
		if (next_rooms[i]->end || (shortter_dist_to_end_room > next_rooms[i]->dist && next_rooms[i]->dist > 0))
		{
			shortter_dist_to_end_room = next_rooms[i]->dist;
			i_shortter_room_to_end = i;	
		}
		i++;
	}
//	ft_printf("index de la salle la plus proche : %d\n", shortter_to_end_room);
	return (next_rooms[i_shortter_room_to_end]);
}

int				ft_ant_in_map(t_datas_graph *datas_graph)
{
	int			i;

	i = 0;
	while (i < datas_graph->nb_rooms && datas_graph->adj_list[i]->ant_in)
		i++;
	if (i != datas_graph->nb_rooms)
		return (0);
	else
		return (1);
}

/*void			ft_print_ants_map(int ant_num_max, t_datas_graph *datas_graph)
{
	int			index_room;
	t_adj_list	**rooms;

	index_room = -1;
	rooms = datas_graph->adj_list;
	while (++index_room < datas_graph->nb_)
	{
		if (rooms[index_room]->ant_in)
		if (rooms[index_room]->ant_in != ant_num_max)
			ft_putchar(' ');
		else
			break ;
	}
}*/

void			ft_move_ants_map(t_datas_graph  *datas_graph)
{
	int			i;
	t_adj_list	*next_room;
	t_ants		**ants;

	i = 0;
	ants = datas_graph->ants;
	while (i < datas_graph->nb_ants)
	{
		next_room = ft_get_next_room(ants[i]->curr_room);
		if (!ants[i]->comed && (!next_room->ant_in || next_room->end))
		{
			next_room->ant_in += ants[i]->ant_number;
			ants[i]->curr_room->ant_in = 0;
			ants[i]->curr_room = next_room;
			if (ants[i]->curr_room->end)
				ants[i]->comed = 1;
			ft_printf("L%d-%s", ants[i]->ant_number, ants[i]->curr_room->name);
			ft_putchar(' ');
		}
		i++;
	}
}

int				ft_init_ants_at_end(t_ants **ants, int nb_ants)
{
	int			ants_at_end;
	int			i;

	i = -1;
	ants_at_end = 0;
	while (++i < nb_ants)
		ants_at_end += ants[i]->ant_number;
	return (ants_at_end);
}

void			ft_map_crosser(t_datas_graph *datas_graph)
{
	t_adj_list	**rooms;
	t_adj_list	*end_room;

	rooms = datas_graph->adj_list;
	end_room = datas_graph->adj_list[datas_graph->nb_rooms - 1];
	datas_graph->ants_at_end = ft_init_ants_at_end(datas_graph->ants, datas_graph->nb_ants);
	while (end_room->ant_in != datas_graph->ants_at_end)
	{	
//		sleep(1);
		ft_move_ants_map(datas_graph);
		ft_putchar('\n');
	}
}
