/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 16:11:58 by mfranc            #+#    #+#             */
/*   Updated: 2017/08/17 17:36:29 by mfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int						ft_exit_function(int return_value, void *st_elem, void *nd_elem, void *rd_elem)
{
	ft_memdel(&st_elem);
	ft_memdel(&nd_elem);
	ft_memdel(&rd_elem);
	return (return_value);
}

t_data_store			*ft_data_store_init(void)
{
	t_data_store 		*data_store;

	if (!(data_store = ft_memalloc(sizeof(t_data_store))))
		return (NULL);
	data_store->nb_ants = 0;
	data_store->start_mark = 0;
	data_store->end_mark = 0;
	data_store->rooms = NULL;
	data_store->last_rooms = NULL;
	data_store->nb_rooms = 0;
	data_store->tunnels = NULL;
	data_store->last_tunnels = NULL;
	data_store->nb_tunnels = 0;
	data_store->commands = NULL;
	data_store->last_commands = NULL;
	data_store->nb_commands = 0;
	return (data_store);
}

void					ft_exit_error(void)
{
	ft_putstrcolor("ERROR\n", RED);
	exit(1);
}



/*int			ft_kbonacci(int n, int k)
{
	int		term;

	term = 0;
	while (k-- > 0)
		term += ft_fibonacci((n + k) - 1);
	return (term / 10);
}
*/
int 					main(void)
{
	t_data_store		*data_store;
	int					parsing_ret;
	t_datas_graph		*datas_graph;
	
	if (!(data_store = ft_data_store_init()))
		ft_exit_error();
	if ((parsing_ret = ft_parse_file(data_store)) == -1)
		ft_exit_error();
	if (!(datas_graph = ft_init_datas_graph(data_store)))		
		ft_exit_error();
	if ((ft_build_graph(data_store, datas_graph)) == -1)
		ft_exit_error();
	ft_init_dist(datas_graph->adj_list[datas_graph->nb_rooms - 1], 0);
	ft_sort_link_graph(datas_graph->adj_list, data_store->nb_rooms);
	ft_init_ants(datas_graph);
	ft_put_adj_list_dist(datas_graph);
	ENDL
	ft_map_crosser(datas_graph);
//	ft_put_adj_matrix(datas_graph);
	return (0);
}
