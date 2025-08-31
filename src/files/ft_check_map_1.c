/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouzouini <ouzouini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:12:01 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/16 10:37:51 by ouzouini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_inside_map(t_data *dt)
{
	int	y;
	int	player_check;

	player_check = 0;
	y = 1;
	while (y < dt->map_height - 1)
	{
		if (check_map_flood(dt, y, &player_check))
			return (1);
		y++;
	}
	if (player_check != 1)
	{
		printf("Error\nMiss or Multiple players found in the map \n");
		return (1);
	}
	return (0);
}

int	split_map(t_data *dt, char **merge)
{
	(void)merge;
	dt->map = ft_split(*merge, '\n');
	if (!dt->map)
		return (free(*merge), 1);
	free(*merge);
	return (0);
}

int	check_top_wall(t_data *dt)
{
	int	i;

	dt->map_height = ft_get_map_height(dt);
	i = 0;
	while (dt->map[0] && dt->map[0][i]) 
	{
		if (dt->map[0][i] != ' ' && dt->map[0][i] != '1')
		{
			ft_print_error("Map should rounded by wall '1' in line: ",
				dt->fl_map);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_bottom_wall(t_data *dt)
{
	int	x;
	int	y;

	x = -1;
	y = dt->map_height; 
	while (dt->map[y - 1][++x])
	{
		if (dt->map[y - 1][x] != ' ' && dt->map[y - 1][x] != '1')
			return (ft_print_error("Map should rounded by wall in line ",
					dt->fl_map + (y - 1)));
	}
	return (0);
}

int	ft_check_map(t_data *dt, char **merge)
{
	if (split_map(dt, merge))
		return (1);
	if (check_top_wall(dt))
		return (1);
	if (check_bottom_wall(dt))
		return (1);
	if (check_inside_map(dt))
		return (1);
	return (0);
}
