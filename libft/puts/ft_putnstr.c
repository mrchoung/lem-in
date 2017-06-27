/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:45:00 by mfranc            #+#    #+#             */
/*   Updated: 2017/01/18 17:36:12 by mfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr(const char *s, size_t n)
{
	if (!s)
		return ;
	if (n > ft_strlen(s))
		ft_putstr(s);
	else
		write(1, s, n);
}
