/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_mini_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:50:24 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/23 13:22:48 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_draw_line_direction(mlx_image_t *img, int center,
									int x1, int y1)
{
	int		x;
	int		y;
	float	t;
	int		i;

	i = -1;
	while (++i <= 200)
	{
		t = (float)i / 200;
		x = center + (x1 - center) * t;
		y = center + (y1 - center) * t;
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
			mlx_put_pixel(img, x, y, ft_rgb_to_uint32(0, 0, 0));
	}
}

void	ft_draw_square(mlx_image_t *img, t_square sq)
{
	int	px;
	int	py;
	int	i;
	int	j;

	i = -1;
	while (++i < sq.size)
	{
		j = -1;
		while (++j < sq.size)
		{
			px = sq.x + i;
			py = sq.y + j;
			if (px >= 0 && px < (int)img->width && py >= 0
				&& py < (int)img->height)
				mlx_put_pixel(img, px, py, sq.color);
		}
	}
}

void	ft_draw_grids(t_data *dt)
{
	t_square	wall_sq;
	int			x;
	int			y;

	y = (int)dt->player.y - VIEW_RD;
	while (y <= (int)dt->player.y + VIEW_RD)
	{
		x = (int)dt->player.x - VIEW_RD;
		while (x <= (int)dt->player.x + VIEW_RD)
		{
			if (y >= 0 && y < dt->map_height && x >= 0 && x < dt->map_width)
			{
				if (dt->map[y][x] == '1')
				{
					wall_sq.x = (x - dt->player.x + VIEW_RD) * dt->shape_size;
					wall_sq.y = (y - dt->player.y + VIEW_RD) * dt->shape_size;
					wall_sq.size = dt->shape_size;
					wall_sq.color = ft_rgb_to_uint32(84, 204, 154);
					ft_draw_square(dt->s_frame, wall_sq);
				}
			}
			x++;
		}
		y++;
	}
}

void	ft_draw_player(t_data *dt)
{
	t_square	player_sq;
	int			center;
	int			line_x;
	int			line_y;

	center = VIEW_RD * dt->shape_size;
	player_sq.x = center - 2;
	player_sq.y = player_sq.x;
	player_sq.size = 4;
	player_sq.color = ft_rgb_to_uint32(255, 0, 0);
	ft_draw_square(dt->s_frame, player_sq);
	line_x = center + dt->dir_x * dt->shape_size;
	line_y = center + dt->dir_y * dt->shape_size;
	ft_draw_line_direction(dt->s_frame, center, line_x, line_y);
}

void	ft_draw_mini_map(t_data *dt)
{
	int	size;
	int	y;
	int	x;

	size = VIEW_RD * 2 * dt->shape_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_put_pixel(dt->s_frame, x, y, ft_rgb_to_uint32(41, 77, 118));
			x++;
		}
		y++;
	}
	ft_draw_grids(dt);
	ft_draw_player(dt);
}
