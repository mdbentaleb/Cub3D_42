/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:00:37 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/27 13:01:27 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_rotate(t_data *dt, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = dt->dir_x;
	old_plane_x = dt->plane_x;
	dt->dir_x = dt->dir_x * cos(angle) - dt->dir_y * sin(angle);
	dt->dir_y = old_dir_x * sin(angle) + dt->dir_y * cos(angle);
	dt->plane_x = dt->plane_x * cos(angle) - dt->plane_y * sin(angle);
	dt->plane_y = old_plane_x * sin(angle) + dt->plane_y * cos(angle);
	dt->player.dir = atan2(dt->dir_y, dt->dir_x);
	if (dt->player.dir < 0)
		dt->player.dir += 2 * M_PI;
}

void	ft_handle_rotate(t_data *dt)
{
	if (mlx_is_key_down(dt->window, MLX_KEY_RIGHT))
		ft_rotate(dt, dt->rot_speed);
	else if (mlx_is_key_down(dt->window, MLX_KEY_LEFT))
		ft_rotate(dt, -dt->rot_speed);
}

void	ft_render(void *param)
{
	t_data	*dt;

	dt = (t_data *)param;
	ft_handle_rotate(dt);
	ft_player_moves(dt);
	ft_clear_img(dt->frame);
	ft_draw_sky_floor(dt);
	ft_draw_3d(dt);
	ft_draw_mini_map(dt);
	ft_player_animation(dt);
}

int	ft_init_game(t_data *dt)
{
	dt->window = mlx_init(WIN_WIDTH, WIN_HEIGHT, "CUB3D", false);
	if (!dt->window)
		return (ft_cleanup_path(dt), 1);
	dt->frame = mlx_new_image(dt->window, WIN_WIDTH, WIN_HEIGHT);
	dt->s_frame = mlx_new_image(dt->window, VIEW_RD * 2 * dt->shape_size,
			VIEW_RD * 2 * dt->shape_size);
	if (!dt->frame || !dt->s_frame)
		return (ft_cleanup_path(dt), 1);
	if (mlx_image_to_window(dt->window, dt->frame, 0, 0) == -1)
		return (ft_cleanup_path(dt), 1);
	if (mlx_image_to_window(dt->window, dt->s_frame, 60,
			1000 - (VIEW_RD * 2 * dt->shape_size) - 90) == -1)
		return (ft_cleanup_path(dt), 1);
	ft_init_player_direction(dt);
	dt->old_mouse_x = -1;
	if (ft_init_img(dt))
		return (1);
	if (mlx_image_to_window(dt->window, dt->gun_img,
			(WIN_WIDTH - dt->gun_t[0]->width) / 2,
			WIN_HEIGHT - dt->gun_t[0]->height) == -1)
		return (1);
	if (mlx_image_to_window(dt->window, dt->square_frame_img, 0, 0) == -1)
		return (print_return("Can't set square frame image to window"));
	return (0);
}

int	ft_start_game(t_data *dt)
{
	if (ft_init_game(dt))
		return (1);
	mlx_close_hook(dt->window, ft_close_hook, dt);
	mlx_cursor_hook(dt->window, cursor_handler, dt);
	mlx_mouse_hook(dt->window, mouse_handler, dt);
	mlx_loop_hook(dt->window, ft_render, dt);
	mlx_loop(dt->window);
	return (ft_destroy(dt, 1), 0);
}
