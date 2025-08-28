/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_3d_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouzouini <ouzouini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:36:21 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/16 10:37:59 by ouzouini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_calc_wall_height(t_ray *ray, t_wall *wall)
{
	wall->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + WIN_HEIGHT / 2;
	wall->draw_end = wall->line_height / 2 + WIN_HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= WIN_HEIGHT)
		wall->draw_end = WIN_HEIGHT - 1;
}

mlx_image_t	*ft_select_texture(t_data *dt, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (dt->ei);
		else
			return (dt->wi);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (dt->si);
		else
			return (dt->ni);
	}
}

static void	draw_pixel_from_texture(t_data *dt, mlx_image_t *texture,
										int tex_x, int tex_y)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	dt->tmp_x = (tex_y * texture->width + tex_x) * 4;
	r = texture->pixels[dt->tmp_x + 0];
	g = texture->pixels[dt->tmp_x + 1];
	b = texture->pixels[dt->tmp_x + 2];
	a = texture->pixels[dt->tmp_x + 3];
	if (a > 0)
		mlx_put_pixel(dt->frame, dt->index, dt->tmp_y,
			(r << 24 | g << 16 | b << 8 | a));
}

void	draw_wall_col(t_data *dt, t_ray *ray, t_wall *wall,
							mlx_image_t *texture)
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		d;

	if (ray->side == 0)
		wall_x = dt->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = dt->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	dt->tmp_y = wall->draw_start;
	while (dt->tmp_y < wall->draw_end)
	{
		d = dt->tmp_y * 256 - WIN_HEIGHT * 128 + wall->line_height * 128;
		tex_y = (d * texture->height) / wall->line_height / 256;
		if (tex_x >= 0 && tex_x < (int)texture->width
			&& tex_y >= 0 && tex_y < (int)texture->height)
			draw_pixel_from_texture(dt, texture, tex_x, tex_y);
		dt->tmp_y++;
	}
}
