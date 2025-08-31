/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_game_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:38:00 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/27 12:12:20 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_init_player_dir(t_data *dt, double dir_y,
								double plane_x, double plane_y)
{
	dt->dir_y = dir_y;
	dt->plane_x = plane_x;
	dt->plane_y = plane_y;
}

void	ft_init_player_direction(t_data *dt)
{
	if (dt->player.dir == M_PI)
	{
		dt->dir_x = 0;
		ft_init_player_dir(dt, -1, 0.66, 0);
	}
	else if (dt->player.dir == 0)
	{
		dt->dir_x = 0;
		ft_init_player_dir(dt, 1, -0.66, 0);
	}
	else if (dt->player.dir == M_PI / 2)
	{
		dt->dir_x = 1;
		ft_init_player_dir(dt, 0, 0, 0.66);
	}
	else if (dt->player.dir == 3 * M_PI / 2)
	{
		dt->dir_x = -1;
		ft_init_player_dir(dt, 0, 0, -0.66);
	}
	dt->move_speed = 0.1;
	dt->rot_speed = 0.1;
}

void	ft_clear_img(mlx_image_t *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

uint32_t	ft_rgb_to_uint32(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	ft_draw_sky_floor(t_data *dt)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				mlx_put_pixel(dt->frame, x, y,
					ft_rgb_to_uint32(dt->sky.r, dt->sky.g, dt->sky.b));
			else
				mlx_put_pixel(dt->frame, x, y,
					ft_rgb_to_uint32(dt->floor.r, dt->floor.g, dt->floor.b));
		}
	}
}
