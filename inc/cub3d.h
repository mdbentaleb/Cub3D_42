/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:54:01 by moben-ta          #+#    #+#             */
/*   Updated: 2025/08/31 12:42:45 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../src/get_next_line/get_next_line.h"
# include "../src/Libft/libft.h"

# define WIN_WIDTH 1400
# define WIN_HEIGHT 1000
# define VIEW_RD 6

# ifndef M_PI 
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
	int	flag;
}	t_rgb;

typedef struct s_flags
{
	int	nf;
	int	sf;
	int	wf;
	int	ef;
	int	ff;
	int	cf;
}	t_flags;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
}	t_player;

typedef struct s_ray {
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_x;
	double		delta_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			side;
	int			hit;
	double		perp_wall_dist;
}	t_ray;

typedef struct s_wall {
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_wall;

typedef struct s_square {
	int			x;
	int			y;
	int			size;
	uint32_t	color;
}	t_square;

typedef struct s_data
{
	char			*map_name;
	char			**map;
	char			*line;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;

	int				player_x;
	int				player_y;
	int				i;
	int				j;
	int				fl_map;
	int				map_height;
	int				map_width;
	int				ln_err;
	int				index;
	int				tmp_x;
	int				tmp_y;
	int				shape_size;
	int				old_mouse_x;
	int				gun_frame;

	double			plane_x;
	double			plane_y;
	double			dir_x;
	double			dir_y;
	double			move_speed;
	double			rot_speed;
	long			last_step_time;

	t_rgb			floor;
	t_rgb			sky;
	t_flags			flags;
	t_player		player;

	mlx_t			*window;

	mlx_texture_t	*nt;
	mlx_texture_t	*st;
	mlx_texture_t	*wt;
	mlx_texture_t	*et;
	mlx_texture_t	*gun_txt;
	mlx_texture_t	*gun_t[21];
	mlx_texture_t	*square_frame_txt;

	mlx_image_t		*ni;
	mlx_image_t		*si;
	mlx_image_t		*wi;
	mlx_image_t		*ei;
	mlx_image_t		*frame;
	mlx_image_t		*s_frame;
	mlx_image_t		*gun_img;
	mlx_image_t		*square_frame_img;

	bool			shooting;

}	t_data;

void		ft_get_position(t_data *dt);
int			ft_isempty_line(const char *line);
int			ft_extract_map(t_data *dt, int fd, char **merge);
void		ft_destroy(t_data *dt, int flag);
void		ft_delet_images(t_data *dt);
int			print_return(char *msg);
void		ft_draw_3d(t_data *dt);
int			ft_print_error(char *msg, int count);
int			ft_init_data(t_data *dt, char *map_name);
int			ft_extract_data(t_data *dt, int *fd);
void		ft_free_double(char **arr);
int			ft_check_map(t_data *dt, char **merge);
int			ft_start_game(t_data *dt);
int			check_map_flood(t_data *dt, int y, int *pch);
int			ft_get_map_height(t_data *dt);
void		ft_calc_wall_height(t_ray *ray, t_wall *wall);
int			ft_is_all_digits(char *str);
int			ft_in_range(int val);
int			ft_save_data(t_data *dt);
mlx_image_t	*ft_select_texture(t_data *dt, t_ray *ray);
void		draw_wall_col(t_data *dt, t_ray *ray, t_wall *wall,
				mlx_image_t *texture);
uint32_t	ft_rgb_to_uint32(int r, int g, int b);
void		ft_draw_sky_floor(t_data *dt);
void		ft_render(void *param);
void		ft_move_left(t_data *dt);
void		ft_move_right(t_data *dt);
void		ft_move_back(t_data *dt);
void		ft_move_forward(t_data *dt);
int			ft_is_valid_pos(t_data *dt, double x, double y);
void		ft_clear_img(mlx_image_t *img);
int			ft_init_img(t_data *dt);
void		ft_close_hook(void *param);
void		ft_init_player_direction(t_data *dt);
void		ft_rotate(t_data *dt, double angle);

void		ft_cleanup_path(t_data *dt);
void		ft_draw_mini_map(t_data *dt);

void		mouse_handler(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		cursor_handler(double xpos, double ypos, void *param);

void		ft_player_animation(t_data *dt);
int			ft_load_gun_txt(t_data *dt);
void		ft_delete_gun_textures(t_data *dt);
void		ft_player_moves(t_data *dt);
void		play_sound(const char *path);

#endif
