/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_data2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouzouini <ouzouini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:55:19 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/16 10:38:11 by ouzouini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_get_rgb(t_data *dt, char *rgb, int *color)
{
	char	*tmp;

	tmp = ft_strtrim(rgb, " \t\n");
	if (!tmp || tmp[0] == '\0' || !ft_is_all_digits(tmp))
	{
		free(tmp);
		return (ft_print_error("Invalid RGB format line ", dt->ln_err));
	}
	*color = ft_atoi(tmp);
	free(tmp);
	return (0);
}

int	ft_get_color(t_data *dt, t_rgb *color, char	*line, int *flag)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (print_return("allocation failed in ft_split"));
	if (ft_get_rgb(dt, rgb[0], &color->r) || ft_get_rgb(dt, rgb[1], &color->g) 
		|| ft_get_rgb(dt, rgb[2], &color->b))
		return (ft_free_double(rgb), 1);
	ft_free_double(rgb);
	if (!ft_in_range(color->r) || !ft_in_range(color->g)
		|| !ft_in_range(color->b))
		return (ft_print_error("RGB value out of range [0~255] line ",
				dt->ln_err));
	*flag = 1;
	dt->i++;
	return (0);
}

int	ft_get_texture_path(t_data *dt, char **tx, char *line, int *flag)
{
	char	*path;

	path = ft_strtrim(line, " \t\n");
	if (!path || !*path)
		return (ft_print_error("Missing or invalid texture path line ",
				dt->ln_err), 1);
	*tx = path;
	dt->i++;
	*flag = 1;
	return (0);
}

int	ft_start_with(char *line, char *need)
{
	int	i;

	i = 0;
	while (need[i])
	{
		if (line[i] != need[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_save_data(t_data *dt)
{
	if (ft_start_with(dt->line, "NO ") && dt->flags.nf == 0)
		return (ft_get_texture_path(dt, &dt->no, dt->line + 2, &dt->flags.nf));
	else if (ft_start_with(dt->line, "SO ") && dt->flags.sf == 0)
		return (ft_get_texture_path(dt, &dt->so, dt->line + 2, &dt->flags.sf));
	else if (ft_start_with(dt->line, "WE ") && dt->flags.wf == 0)
		return (ft_get_texture_path(dt, &dt->we, dt->line + 2, &dt->flags.wf));
	else if (ft_start_with(dt->line, "EA ") && dt->flags.ef == 0)
		return (ft_get_texture_path(dt, &dt->ea, dt->line + 2, &dt->flags.ef));
	else if (ft_start_with(dt->line, "F ") && dt->flags.ff == 0)
		return (ft_get_color(dt, &dt->floor, dt->line + 1, &dt->flags.ff));
	else if (ft_start_with(dt->line, "C ") && dt->flags.cf == 0)
		return (ft_get_color(dt, &dt->sky, dt->line + 1, &dt->flags.cf));
	return (-1);
}
