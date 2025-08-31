/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:47:08 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/31 12:01:17 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_delete_gun_textures(t_data *dt)
{
	int	i;

	i = 0;
	while (i < 21)
	{
		if (dt->gun_t[i])
		{
			mlx_delete_texture(dt->gun_t[i]);
			dt->gun_t[i] = NULL;
		}
		i++;
	}
}

int	ft_load_gun_txt(t_data *dt)
{
	dt->gun_t[0] = mlx_load_png("./assetes/gun_shoot/1.png");
	dt->gun_t[1] = mlx_load_png("./assetes/gun_shoot/2.png");
	dt->gun_t[2] = mlx_load_png("./assetes/gun_shoot/3.png");
	dt->gun_t[3] = mlx_load_png("./assetes/gun_shoot/4.png");
	dt->gun_t[4] = mlx_load_png("./assetes/gun_shoot/5.png");
	dt->gun_t[5] = mlx_load_png("./assetes/gun_shoot/6.png");
	dt->gun_t[6] = mlx_load_png("./assetes/gun_shoot/7.png");
	dt->gun_t[7] = mlx_load_png("./assetes/gun_shoot/8.png");
	dt->gun_t[8] = mlx_load_png("./assetes/gun_shoot/9.png");
	dt->gun_t[9] = mlx_load_png("./assetes/gun_shoot/10.png");
	dt->gun_t[10] = mlx_load_png("./assetes/gun_shoot/11.png");
	dt->gun_t[11] = mlx_load_png("./assetes/gun_shoot/12.png");
	dt->gun_t[12] = mlx_load_png("./assetes/gun_shoot/13.png");
	dt->gun_t[13] = mlx_load_png("./assetes/gun_shoot/14.png");
	dt->gun_t[14] = mlx_load_png("./assetes/gun_shoot/15.png");
	dt->gun_t[15] = mlx_load_png("./assetes/gun_shoot/16.png");
	dt->gun_t[16] = mlx_load_png("./assetes/gun_shoot/17.png");
	dt->gun_t[17] = mlx_load_png("./assetes/gun_shoot/18.png");
	dt->gun_t[18] = mlx_load_png("./assetes/gun_shoot/19.png");
	dt->gun_t[19] = mlx_load_png("./assetes/gun_shoot/20.png");
	dt->gun_t[20] = mlx_load_png("./assetes/gun_shoot/21.png");
	while (++dt->i < 21)
		if (!dt->gun_t[dt->i])
			return (1);
	return (0);
}

void	ft_player_animation(t_data *dt)
{
	int	gun_total;
	int	x;
	int	y;

	gun_total = 21;
	x = (WIN_WIDTH - dt->gun_t[0]->width) / 2;
	y = WIN_HEIGHT - dt->gun_t[0]->height;
	if (!dt->shooting)
		return ;
	if (dt->gun_img)
		mlx_delete_image(dt->window, dt->gun_img);
	dt->gun_img = mlx_texture_to_image(dt->window, dt->gun_t[dt->gun_frame]);
	mlx_image_to_window(dt->window, dt->gun_img, x, y);
	if (dt->gun_frame < gun_total - 1)
		dt->gun_frame++;
	else
		dt->shooting = false;
}

void	mouse_handler(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param)
{
	t_data	*dt;

	(void)mods;
	dt = (t_data *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		if (!dt->shooting)
		{
			dt->shooting = true;
			dt->gun_frame = 1;
			play_sound("./assetes/sounds/pistol_shot.mp3");
		}
	}
}

void	cursor_handler(double xpos, double ypos, void *param)
{
	t_data	*dt;
	double	dx;
	double	sensit;

	(void)ypos;
	dt = (t_data *)param;
	if (dt->old_mouse_x == -1)
	{
		dt->old_mouse_x = xpos;
		return ;
	}
	dx = xpos - dt->old_mouse_x;
	sensit = 0.0150;
	if (dx != 0)
		ft_rotate(dt, dx * sensit);
	dt->old_mouse_x = xpos;
}
