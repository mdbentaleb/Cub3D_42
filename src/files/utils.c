/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:12:54 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/27 12:37:03 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_close_hook(void *param)
{
	t_data	*dt;

	dt = (t_data *)param;
	ft_destroy(dt, 0);
	mlx_close_window(dt->window);
}

void	ft_destroy(t_data *dt, int flag)
{
	ft_delete_gun_textures(dt);
	ft_delet_images(dt);
	if (dt->frame)
		mlx_delete_image(dt->window, dt->frame);
	if (dt->gun_img)
		mlx_delete_image(dt->window, dt->gun_img);
	if (dt->window && flag)
		mlx_terminate(dt->window);
}

int	print_return(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

int	ft_print_error(char *msg, int count)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putnbr_fd(count, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	ft_free_double(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
