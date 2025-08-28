/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:00:07 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/23 12:16:54 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_is_map_line(char	*line)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	c = 0;
	tmp = ft_strtrim(line, "\n");
	while (tmp && tmp[i])
	{
		c = tmp[i];
		if (c != ' ' && c != '1' && c != '0' && c != 'N' && c != 'S'
			&& c != 'W' && c != 'E')
		{
			free(tmp);
			return (0);
		}
		i++;
	}
	free(tmp);
	return (1);
}

void	ft_skip_empylines(t_data *dt, int fd)
{
	while (dt->line && ft_isempty_line(dt->line)) 
	{
		free(dt->line);
		dt->line = get_next_line(fd);
		dt->ln_err++;
	}
}

int	ft_extract_map(t_data *dt, int fd, char **merge)
{
	char	*tmp;

	ft_skip_empylines(dt, fd);
	dt->fl_map = dt->ln_err;
	while (dt->line)
	{
		if (ft_is_map_line(dt->line) && (ft_strcmp(dt->line, "\n") != 0))
		{
			tmp = ft_strjoin(*merge, dt->line);
			if (!tmp)
				return (print_return("allocation failed in ft_strjoin"));
			*merge = tmp;
		}
		else
			break ;
		free(dt->line);
		dt->line = get_next_line(fd);
		dt->ln_err++;
	}
	ft_skip_empylines(dt, fd);
	if (!ft_isempty_line(dt->line))
		return (ft_print_error("Incorrect info line ", dt->ln_err));
	if (dt->fl_map == dt->ln_err)
		return (print_return("There is no map"));
	return (0);
}
