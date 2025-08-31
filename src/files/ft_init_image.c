/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:10:22 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/23 13:59:51 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_delet_images(t_data *dt)
{
	if (dt->ni)
		mlx_delete_image(dt->window, dt->ni);
	if (dt->si)
		mlx_delete_image(dt->window, dt->si);
	if (dt->ei)
		mlx_delete_image(dt->window, dt->ei);
	if (dt->wi)
		mlx_delete_image(dt->window, dt->wi);
	if (dt->square_frame_img)
		mlx_delete_image(dt->window, dt->square_frame_img);
	if (dt->gun_img)
		mlx_delete_image(dt->window, dt->gun_img);
}

int	ft_texture_to_image(t_data *dt)
{
	dt->ni = mlx_texture_to_image(dt->window, dt->nt);
	dt->si = mlx_texture_to_image(dt->window, dt->st);
	dt->wi = mlx_texture_to_image(dt->window, dt->wt);
	dt->ei = mlx_texture_to_image(dt->window, dt->et);
	dt->square_frame_img = mlx_texture_to_image(dt->window,
			dt->square_frame_txt);
	dt->gun_img = mlx_texture_to_image(dt->window, dt->gun_t[0]);
	if (!dt->ni || !dt->si || !dt->wi || !dt->ei
		|| !dt->square_frame_img || !dt->gun_img)
	{
		ft_delet_images(dt);
		return (print_return("❌ Failed to convert texture to image!"));
	}
	return (0);
}

void	ft_delete_texture(t_data *dt)
{
	if (dt->nt)
		mlx_delete_texture(dt->nt);
	if (dt->st)
		mlx_delete_texture(dt->st);
	if (dt->wt)
		mlx_delete_texture(dt->wt);
	if (dt->et)
		mlx_delete_texture(dt->et);
	if (dt->square_frame_txt)
		mlx_delete_texture(dt->square_frame_txt);
}

int	ft_load_textures(t_data *dt)
{
	dt->nt = mlx_load_png(dt->no);
	dt->st = mlx_load_png(dt->so);
	dt->wt = mlx_load_png(dt->we);
	dt->et = mlx_load_png(dt->ea);
	dt->square_frame_txt = mlx_load_png("./assetes\
/textures/square_frame.png");
	if (!dt->nt || !dt->st || !dt->wt || !dt->et || !dt->square_frame_txt)
	{
		ft_delete_texture(dt);
		return (print_return("❌Failed to load texture! \
Incorrect Path or not found"));
	}
	dt->i = -1;
	if (ft_load_gun_txt(dt))
	{
		ft_delete_texture(dt);
		return (print_return("❌Failed to load texture!"));
	}
	ft_cleanup_path(dt);
	return (0);
}

int	ft_init_img(t_data *dt)
{
	if (ft_load_textures(dt))
		return (ft_cleanup_path(dt), 1);
	if (ft_texture_to_image(dt))
	{
		ft_delete_texture(dt);
		return (1);
	}
	ft_delete_texture(dt);
	return (0);
}
