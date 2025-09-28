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

typedef enum e_viewmode
{
	MODE_ISOMETRIC = 0,
	MODE_Z_AXIS = 1,
	MODE_Y_AXIS = 2,
	MODE_X_AXIS = 3,
	MODE_CONIC = 4
}	t_viewmode;

/**
 * - Structure for a pixel
 *
 * @param x coordinate from 0 to the window width
 * @param y coordiamte from 0 to the window height
 * @param color color of the pixel
 */
typedef struct s_pixel
{
	int	x;
	int	y;
	int	color;
}		t_pixel;

/**
 * - Structure for the map, rotations, offsets, views
 *
 * @param viewmode boolean of views (0 = iso, 1 = z, 2 = y, 3 = x, 4 = conic)
 * @param width map's width
 * @param height map's height
 * @param z_arr array of z values from the map
 * @param colors array of colors for each respective point
 * @param offset_w offset from the width of the window
 * @param offset_h offset from the height of the window
 * @param view the initial angle of interest (set to M_PI / 6 by default)
 * @param size the scale of which to render the map
 * @param z_scale the magnitude of the z value
 * @param rot_x angle of rotation for x
 * @param rot_y angle of rotation for y
 * @param rot_z angle of rotation for z
 */
typedef struct s_map
{
	int		viewmode;
	int		width;
	int		height;
	int		**z_arr;
	int		**colors;
	double	offset_w;
	double	offset_h;
	double	view;
	double	size;
	double	z_scale;
	double	rot_x;
	double	rot_y;
	double	rot_z;
}			t_map;

/**
 * - Structure for mlx data
 * - Panning variables might be unnecessary
 * @param mlx_ptr pointer to the mlx library that allocates an XWindow display
 * @param win_ptr pointer to the window allocated
 * @param img_ptr pointer to the image buffer
 * @param img_data pointer to the same img but as characters
 * @param bpp bits per pixel
 * @param size_line size of each line of pixels
 * @param endian necessary for alignment
 */
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		pan_left;
	int		pan_right;
	int		pan_up;
	int		pan_down;
}			t_mlx;

// structure for fdf data
typedef struct s_fdf_data
{
	t_mlx	mlx;
	t_map	map;
}			t_fdf_data;

// window sizes

#define	WIN_W 1920
#define	WIN_H 1080

// allocate.c

int		allocate_and_input(int file_fd, t_map *map);
void	put_datapoint(t_map *map, char *token, int row, int col);

// calc_angles.c

t_pixel	calc_iso(t_map *map_data, int x, int y, int z);

// calc_line.c

void	draw_bresenham_line(t_mlx *mlx, t_pixel start, t_pixel end);

// calc_size.c

double	calc_size(t_map *map);

// calc_view.c

t_pixel do_iso_view(t_map *map, double *x, double *y, double *z);
t_pixel do_x_view(t_map *map, double *y, double *z);
t_pixel do_y_view(t_map *map, double *x, double *z);
t_pixel do_z_view(t_map *map, double *x, double *y);
// t_pixel do_conic_view(t_map *map, double *x, double *y, double *z);

// color.c

int		interpolate_color(int color1, int color2, double ratio);

// events_keys,c

int		key_press(int keycode, t_fdf_data *data);
int		loop_hook(t_fdf_data *data);

// events.c

void	init_mlx_events(t_fdf_data *data);

// free.c

void	free_map(t_map *map);
void	free_data(t_fdf_data *data);

// graphics.c

void	draw_map(t_fdf_data *data);
void	clear_image(t_mlx *mlx);
void	put_pixel(t_mlx *mlx, int x, int y, int color);

// initializers.c

int		init_mlx_lib(t_mlx *mlx, t_fdf_data *data);
void	init_map(t_map *map);
void	init_mlx(t_mlx *mlx);
void	init_angles(t_map *map);

// menu.c

void	draw_menu(t_mlx *mlx, t_map *map);

// parse_map.c

int		is_valid_format(char *filepath);
int		input_points(int file_fd, t_map *map);
int		parse_map(char *filepath, t_map *map);

// redraw.c

void	redraw(t_fdf_data *data);
void	reset(t_fdf_data *data);
void	draw_plan_view(t_fdf_data *data);
void	centralize(t_map *map);

#endif
