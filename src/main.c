/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouzouini <ouzouini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:53:58 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/23 10:34:10 by ouzouini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_check_args(int arc, char *arv)
{
	int	len;

	if (arc != 2)
		return (print_return("Usage: ./cub3d <map>"));
	len = ft_strlen(arv);
	if ((ft_strcmp(arv + len - 4, ".cub") != 0) || len < 4)
		return (print_return("Map file must have [.cub] extension"));
	return (0);
}

int	main(int arc, char **arv)
{
	t_data	dt;

	if (ft_check_args(arc, arv[1]))
		return (0);
	if (ft_init_data(&dt, arv[1]))
	{
		ft_cleanup_path(&dt);
		if (dt.line)
			free(dt.line);
		return (1);
	}
	ft_get_position(&dt);
	if (ft_start_game(&dt))
	{
		ft_destroy(&dt, 1);
		ft_free_double(dt.map);
		return (1);
	}
	ft_free_double(dt.map);
	return (0);
}
