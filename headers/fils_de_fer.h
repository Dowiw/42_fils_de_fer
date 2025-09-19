/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fils_de_fer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:20:12 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/15 22:20:13 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILS_DE_FER_H
# define FILS_DE_FER_H

#include <mlx.h> // minilibx library

#include <math.h> // sin, cos, tan, etc.

#include <unistd.h> // write

#include <limits.h> // maxs and mins

#include <X11/keysym.h> // declarations of keys in X11 library

#include <stdlib.h>

#include <fcntl.h> // open, read,

#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// enumeration of events that are represented in mlx
typedef enum e_event
{
	EVENT_KEY_PRESS = 2,
	EVENT_KEY_RELEASE = 3,
	EVENT_MOUSE_PRESS = 4,
	EVENT_MOUSE_RELEASE = 5,
	EVENT_MOUSE_MOVE = 6,
	EVENT_EXPOSE = 12,
	EVENT_DESTROY = 17
}	t_event;

// each point in the map
typedef struct s_point
{
	int	x; // abscissa
	int	y; // ordinate
	int	z; // altitude
	int	color; // hex value in decimal
}		t_point;

// structure to store point data and render values
typedef struct s_map
{
	int		width;
	int		height;
	double	z_scale; // scale of magnitude for z value
	double	rot_x; // angle of rotation for X
	double	rot_y; // angle of rotation for y
	double	rot_z; // angle of rotation for z
	t_point	**points;
}			t_map;

// structure for mlx data
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}			t_mlx;

typedef struct s_fdf_data
{
	t_mlx	mlx;
	t_map	map;
}			t_fdf_data;

#define	WIN_W 1000
#define	WIN_H 1000

// events.c

int		handle_key(int keycode, t_fdf_data *data);
int		handle_close(t_fdf_data *data);
void	init_mlx_events(t_fdf_data *data);

// free.c

void	free_map(t_map *map);
void	free_data(t_fdf_data *data);

// graphics.c

void	draw_map(t_fdf_data *data);
void 	clear_image(t_mlx *mlx);

// initializers.c

int		init_mlx_lib(t_mlx *mlx, t_fdf_data *data);
int		input_points(int file_fd, t_map *map);
void	init_map(t_map *map);
void	init_mlx(t_mlx *mlx);

// parse.c

int	is_valid_format(char *filepath);
int	parse_map(char *filepath, t_map *map);

#endif
