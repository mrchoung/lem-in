/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 18:14:02 by mfranc            #+#    #+#             */
/*   Updated: 2017/08/21 12:59:55 by mfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_ants			*ft_new_ant(int ant_number, t_adj_list *start_room)
{
	t_ants		*ant;

	if (!(ant = ft_memalloc(sizeof(t_ants))))
		return (NULL);
	ant->ant_number = ant_number;
	ant->curr_room = start_room;
	ant->comed = 0;
	return (ant);
}

int				ft_init_ants(t_datas_graph *datas_graph)
{
	int			ant_number;
	int			i;
	
	if (!(datas_graph->ants = ft_memalloc(sizeof(t_ants*) * datas_graph->nb_ants)))
		return (-1);
	i = -1;
	ant_number = 1;
	while (++i < datas_graph->nb_ants)
	{
		if (!(datas_graph->ants[i] = ft_new_ant(ant_number, datas_graph->adj_list[0])))
			return (-1);
		ant_number++;
	}
	return (1);
}

void			ft_init_way_ants(t_datas_graph *datas_graph)
{
	
}
