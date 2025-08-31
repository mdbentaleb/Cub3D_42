/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_position.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:39:27 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/23 13:50:19 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void play_sound(const char *path)
{
	if (fork() == 0)
	{
#if defined(__APPLE__)
		execlp("afplay", "afplay", path, (char)NULL);
#elif defined(__linux__)
		execlp("aplay", "aplay", path, (char )NULL);
		execlp("paplay", "paplay", path, (char)NULL);
#endif
		perror("Sound player not found");
		_exit(1);
	}
}

#include <sys/time.h>

long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void try_play_step(t_data *dt)
{
    long now = get_time_ms();

    if (now - dt->last_step_time > 350) // 300 ms between steps
    {
        play_sound("./assetes/sounds/step.mp3");
        dt->last_step_time = now;
    }
}

void	ft_player_moves(t_data *dt)
{
	if (mlx_is_key_down(dt->window, MLX_KEY_ESCAPE))
		mlx_close_window(dt->window);
	if (mlx_is_key_down(dt->window, MLX_KEY_W))
	{
		ft_move_forward(dt);
		try_play_step(dt);
	}
	if (mlx_is_key_down(dt->window, MLX_KEY_S))
	{
		ft_move_back(dt);
		try_play_step(dt);
	}
	if (mlx_is_key_down(dt->window, MLX_KEY_A))
	{
		ft_move_left(dt);
		try_play_step(dt);
	}
	if (mlx_is_key_down(dt->window, MLX_KEY_D))
	{
		ft_move_right(dt);
		try_play_step(dt);
	}
	if (mlx_is_key_down(dt->window, MLX_KEY_SPACE))
	{
		if (!dt->shooting)
		{
			dt->shooting = true;
			dt->gun_frame = 1;
			play_sound("./assetes/sounds/pistol_shot.mp3");
		}
		
	}
}

void	save_player_pos(t_data *dt, int x, int y, char dir)
{
	dt->player_x = x;
	dt->player_y = y;
	dt->player.x = dt->player_x + 0.5;
	dt->player.y = dt->player_y + 0.5;
	if (dir == 'N')
		dt->player.dir = M_PI;
	if (dir == 'S')
		dt->player.dir = 0;
	if (dir == 'E')
		dt->player.dir = M_PI / 2;
	if (dir == 'W')
		dt->player.dir = 3 * M_PI / 2;
}

int	get_highest_width(t_data *dt)
{
	int	y;
	int	tmp;
	int	len;

	y = 0;
	tmp = 0;
	len = 0;
	while (dt->map[y] != NULL)
	{
		tmp = (int)ft_strlen(dt->map[y]);
		if (tmp > len)
			len = tmp;
		y++;
	}
	return (len);
}

void	ft_get_position(t_data *dt)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (dt->map[y] != NULL)
	{
		x = 0;
		while (dt->map[y][x])
		{
			c = dt->map[y][x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				save_player_pos(dt, x, y, c);
				dt->map[y][x] = 'P';
			}
			x++;
		}
		y++;
	}
	dt->map_width = get_highest_width(dt);
	dt->shape_size = 20;
}
