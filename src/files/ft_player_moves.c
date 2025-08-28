/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_moves.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:35:16 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/21 10:46:51 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_is_valid_pos(t_data *dt, double x, double y)
{
	double	player_radius;
	double	check_points[4][2];
	int		map_x;
	int		map_y;

	player_radius = 0.15;
	check_points[0][0] = x - player_radius;
	check_points[0][1] = y - player_radius;
	check_points[1][0] = x - player_radius;
	check_points[1][1] = y + player_radius;
	check_points[2][0] = x + player_radius;
	check_points[2][1] = y - player_radius;
	check_points[3][0] = x + player_radius;
	check_points[3][1] = y + player_radius;
	dt->i = -1;
	while (++dt->i < 4)
	{
		map_y = (int)check_points[dt->i][1];
		map_x = (int)check_points[dt->i][0];
		if (map_y < 0 || map_y >= dt->map_height || map_x < 0
			|| map_x >= (int)ft_strlen(dt->map[map_y])
			|| dt->map[map_y][map_x] == '1')
			return (0);
	}
	return (1);
}

void	ft_move_forward(t_data *dt)
{
	double	new_x;
	double	new_y;

	new_x = dt->player.x + dt->dir_x * dt->move_speed;
	new_y = dt->player.y + dt->dir_y * dt->move_speed;
	if (ft_is_valid_pos(dt, new_x, dt->player.y))
		dt->player.x = new_x;
	if (ft_is_valid_pos(dt, dt->player.x, new_y))
		dt->player.y = new_y;
}

void	ft_move_back(t_data *dt)
{
	double	new_x;
	double	new_y;

	new_x = dt->player.x - dt->dir_x * dt->move_speed;
	new_y = dt->player.y - dt->dir_y * dt->move_speed;
	if (ft_is_valid_pos(dt, new_x, dt->player.y))
		dt->player.x = new_x;
	if (ft_is_valid_pos(dt, dt->player.x, new_y))
		dt->player.y = new_y;
}

void	ft_move_right(t_data *dt)
{
	double	new_x;
	double	new_y;

	new_x = dt->player.x - dt->dir_y * dt->move_speed;
	new_y = dt->player.y + dt->dir_x * dt->move_speed;
	if (ft_is_valid_pos(dt, new_x, dt->player.y))
		dt->player.x = new_x;
	if (ft_is_valid_pos(dt, dt->player.x, new_y))
		dt->player.y = new_y;
}

void	ft_move_left(t_data *dt)
{
	double	new_x;
	double	new_y;

	new_x = dt->player.x + dt->dir_y * dt->move_speed;
	new_y = dt->player.y - dt->dir_x * dt->move_speed;
	if (ft_is_valid_pos(dt, new_x, dt->player.y))
		dt->player.x = new_x;
	if (ft_is_valid_pos(dt, dt->player.x, new_y))
		dt->player.y = new_y;
}
