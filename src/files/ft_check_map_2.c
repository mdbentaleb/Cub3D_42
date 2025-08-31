/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:07:07 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/23 12:18:47 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_get_map_height(t_data *dt)
{
	int	i;

	i = 0;
	while (dt->map[i] != NULL)
		i++;
	return (i);
}

int	ft_my_flood_fill(t_data *dt, int x, int y)
{
	char	*up;
	char	*down;
	char	*line;
	int		width;

	up = dt->map[y - 1];
	down = dt->map[y + 1];
	line = dt->map[y];
	width = ft_strlen(line);
	if (x == 0 || x >= width - 1)
		return (1);
	if ((x >= (int)ft_strlen(up) || up[x] == ' ')
		|| (x >= (int)ft_strlen(down) || down[x] == ' ')
		|| (x + 1 >= width || line[x + 1] == ' ')
		|| (x - 1 < 0 || line[x - 1] == ' '))
		return (1);
	return (0);
}

int	check_map_flood(t_data *dt, int y, int *pch)
{
	int	x;

	x = 0;
	while (dt->map[y][x] != '\0')
	{
		if (dt->map[y][x] == '0' || dt->map[y][x] == 'N'
			|| dt->map[y][x] == 'S' || dt->map[y][x] == 'W'
			|| dt->map[y][x] == 'E')
		{
			if (ft_my_flood_fill(dt, x, y))
			{
				ft_print_error("Bound Error in Line: ", dt->fl_map + y);
				return (1);
			}
		}
		if (dt->map[y][x] == 'W' || dt->map[y][x] == 'S' 
				|| dt->map[y][x] == 'E' || dt->map[y][x] == 'N')
			(*pch)++;
		x++;
	}
	return (0);
}
