/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:31 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/11 15:25:21 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include "libft.h"
#include <math.h>

typedef struct s_2d
{
	int	x;
	int	y;
}		t_2d;

/**
 * - Function to put the pixel into the image buffer
 */
void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return;
	offset = (y * mlx->size_line) + (x * (mlx->bpp / 8));
	*((unsigned int *)(mlx->img_data + offset)) = color;
}

/**
 * - TODO: add reference and info
 */
t_2d calc_isometric(t_map *map_data, int x, int y, int z)
{
	t_2d p;
	double scale = 20.0;
	double angle = 0.523599; // 30 degrees in radians

	// Convert to double for math
	double xd = (double)x;
	double yd = (double)y;
	double zd = (double)z * map_data->z_scale;

	// Apply rotation around X axis
	double y1 = yd * cos(map_data->rot_x) - zd * sin(map_data->rot_x);
	double z1 = yd * sin(map_data->rot_x) + zd * cos(map_data->rot_x);

	// Apply rotation around Y axis
	double x2 = xd * cos(map_data->rot_y) + z1 * sin(map_data->rot_y);
	double z2 = -xd * sin(map_data->rot_y) + z1 * cos(map_data->rot_y);

	// Apply rotation around Z axis
	double x3 = x2 * cos(map_data->rot_z) - y1 * sin(map_data->rot_z);
	double y3 = x2 * sin(map_data->rot_z) + y1 * cos(map_data->rot_z);

	// Isometric projection
	double iso_x = (x3 - y3) * cos(angle);
	double iso_y = -z2 + (x3 + y3) * sin(angle);

	p.x = (int)(iso_x * scale + WIN_W / 2);
	p.y = (int)(iso_y * scale + WIN_H / 2);
	return p;
}

/**
 * - Empties out the image buffer
 */
void clear_image(t_mlx *mlx)
{
	int x, y;
	for (y = 0; y < WIN_H; y++)
		for (x = 0; x < WIN_W; x++)
			put_pixel(mlx, x, y, 0x000000);
}

/**
 * - Bresenham's algorithm in plain code
 *
 * EXPLANATION: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void	draw_bresenham_line(t_mlx *mlx, t_2d start, t_2d end, int color)
{
	int	dx;
	int	dy;
	int	x_step;
	int	y_step;
	int	delta;
	int	delta2;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	x_step = (start.x < end.x) ? 1 : -1;
	y_step = (start.y < end.y) ? 1 : -1;
	delta = dx - dy; // delta variable decides which pixel is closest
	while (start.x != end.x || start.y != end.y)
	{
		put_pixel(mlx, start.x, start.y, color);
		delta2 = 2 * delta;
		if (delta2 > -dy)
		{
			delta -= dy;
			start.x += x_step;
		}
		if (delta2 < dx)
		{
			delta += dx;
			start.y += y_step;
		}
	}
	put_pixel(mlx, end.x, end.y, color); // draw the last point
}

/**
 * - Manually draw the pixels of the map
 */
void draw_map(t_fdf_data *data)
{
	t_2d	point;
	t_2d	point_right;
	t_2d	point_down;
	int		i;
	int		j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			point = calc_isometric(&data->map, data->map.points[i][j].x, data->map.points[i][j].y, data->map.points[i][j].z);
			if (j + 1 < data->map.width)
			{
				point_right = calc_isometric(&data->map, data->map.points[i][j+1].x, data->map.points[i][j+1].y, data->map.points[i][j+1].z);
				draw_bresenham_line(&data->mlx, point, point_right, 0x00FF00);
			}
			if (i + 1 < data->map.height)
			{
				point_down = calc_isometric(&data->map, data->map.points[i+1][j].x, data->map.points[i+1][j].y, data->map.points[i+1][j].z);
				draw_bresenham_line(&data->mlx, point, point_down, 0xFF0000);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
}

/**
 * - Main (assumes maps are in correct format)
 */
int main(int ac, char **av)
{
	t_fdf_data	data;

	if (ac != 2 || !is_valid_format(av[1]))
		return (write(2 ,"Usage: ./fdf <valid file in .fdf format>\n", 42), 1);
	if (!parse_map(av[1], &data.map))
		return (1);
	if (!init_mlx_lib(&data.mlx, &data))
	{
		free_map(&data.map);
		perror("Error: failed initializing library");
		return (1);
	}
	draw_map(&data);
	mlx_loop(data.mlx.mlx_ptr);
}
