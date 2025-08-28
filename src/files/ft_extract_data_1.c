/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_data1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouzouini <ouzouini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:50:56 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/16 10:38:06 by ouzouini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_in_range(int val)
{
	return (val >= 0 && val <= 255);
}

int	ft_is_all_digits(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isempty_line(const char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_extract_data(t_data *dt, int *fd)
{
	int	check;

	check = 0;
	dt->line = get_next_line(*fd);
	if (!dt->line)
		return ((void)close(*fd),
			print_return("Map file is empty"));
	while (dt->line && dt->i < 6)
	{
		if (dt->line && !ft_isempty_line(dt->line))
			check = ft_save_data(dt);
		if (check == 1)
			return (1);
		else if (check == -1)
			return (ft_print_error("All textures and floor/ceiling colors \
must be defined before the map issue at line ", dt->ln_err));
		dt->ln_err++;
		free(dt->line);
		dt->line = get_next_line(*fd);
	}
	if (dt->i < 6)
		return (print_return("Incomplete Info"));
	return (0);
}
