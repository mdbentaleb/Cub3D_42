/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_3d_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouzouini <ouzouini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:08:49 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/16 10:37:55 by ouzouini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	ft_init_ray(t_data *dt, t_ray *ray)
{
	ray->camera_x = 2 * dt->index / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = dt->dir_x + dt->plane_x * ray->camera_x;
	ray->ray_dir_y = dt->dir_y + dt->plane_y * ray->camera_x;
	ray->map_x = (int)dt->player.x;
	ray->map_y = (int)dt->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->ray_dir_y);
}

static void	ft_init_dda(t_data *dt, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (dt->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - dt->player.x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (dt->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - dt->player.y) * ray->delta_y;
	}
}

static void	ft_perform_dda(t_data *dt, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (dt->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	ft_calc_distance(t_data *dt, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - dt->player.x
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - dt->player.y
				+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
}

void	ft_draw_3d(t_data *dt)
{
	t_ray		ray;
	t_wall		wall;
	int			x;
	mlx_image_t	*ch_text;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		dt->index = x;
		ft_init_ray(dt, &ray);
		ft_init_dda(dt, &ray);
		ft_perform_dda(dt, &ray);
		ft_calc_distance(dt, &ray);
		ft_calc_wall_height(&ray, &wall);
		ch_text = ft_select_texture(dt, &ray);
		draw_wall_col(dt, &ray, &wall, ch_text);
	}
}
