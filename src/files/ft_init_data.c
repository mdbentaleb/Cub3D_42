/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouzouini <ouzouini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:12:57 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/16 10:38:22 by ouzouini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_arr_len(char **arr)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while (arr && arr[i])
	{
		tmp = ft_strtrim(arr[i], " \t\n");
		if (tmp)
		{
			if (tmp[0] != '\0')
				count++;
			free(tmp);
		}
		i++;
	}
	return (count);
}

void	ft_cleanup_path(t_data *dt)
{
	if (dt->no)
		free(dt->no);
	if (dt->so)
		free(dt->so);
	if (dt->we)
		free(dt->we);
	if (dt->ea)
		free(dt->ea);
	dt->no = NULL;
	dt->so = NULL;
	dt->ea = NULL;
	dt->we = NULL;
}

void	ft_cleanup(char *merge, int fd)
{
	if (fd != -1)
		close(fd);
	if (merge)
		free(merge);
	merge = NULL;
}

int	ft_init_data(t_data *dt, char *map_name)
{
	int		fd;
	char	*merge;

	ft_memset(dt, 0, sizeof(t_data));
	dt->ln_err = 1;
	merge = ft_strdup("");
	if (!merge)
		return (print_return("allocation failed in ft_strdup"));
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (free(merge), print_return("Failed to open map file"));
	if (ft_extract_data(dt, &fd))
		return (ft_cleanup(merge, fd), 1);
	if (ft_extract_map(dt, fd, &merge))
		return (ft_cleanup(merge, fd), 1);
	close(fd);
	if (ft_check_map(dt, &merge))
		return (ft_free_double(dt->map), 1);
	return (0);
}
