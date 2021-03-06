/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:58:51 by mfranc            #+#    #+#             */
/*   Updated: 2017/09/06 19:57:19 by mfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_line_is_command	g_line_is_command[] =
{
	ft_line_is_ants_number,
	ft_line_is_room,
	ft_line_is_tunnel,
	ft_line_is_modif_command,
	ft_line_is_comment
};

t_data_store		*ft_data_store_init(void)
{
	t_data_store	*data_store;

	if (!(data_store = malloc(sizeof(t_data_store))))
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
	data_store->gnl_error = 0;
	return (data_store);
}

t_list				*ft_new_command(t_data_store *data_store, char *line)
{
	t_list			*new_command;

	if (!(new_command = ft_lstnew(line, ft_strlen(line) + 1)))
	{
		ft_strdel(&line);
		return (NULL);
	}
	data_store->nb_commands++;
	return (new_command);
}

int					ft_line_is_command(t_data_store *data_store, char *line)
{
	int				i;
	int				line_is_command;

	i = -1;
	while (++i < 5)
	{
		line_is_command = g_line_is_command[i](line, data_store);
		if (line_is_command == 1)
			return (1);
		else if (line_is_command == -1)
			return (-1);
	}
	if (i == 5)
		return (5);
	return (1);
}

int					ft_parse_file(t_data_store *data_store)
{
	int				gnl;
	char			*line;
	int				line_is_command;
	t_list			*new_command;

	while ((gnl = get_next_line(0, &line)) == 1)
	{
		if (!(new_command = ft_new_command(data_store, line)))
			return (-1);
		ft_push_back_command(data_store, new_command);
		line_is_command = ft_line_is_command(data_store, line);
		ft_strdel(&line);
		if (line_is_command == -1)
			return (-1);
		else if (line_is_command == 5)
			break ;
	}
	if (gnl == -1)
		data_store->gnl_error = 1;
	if (gnl == -1 || data_store->nb_commands == 0 || data_store->nb_ants == 0)
		return (-1);
	return (1);
}
