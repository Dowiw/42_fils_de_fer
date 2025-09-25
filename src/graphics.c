/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:46:48 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/16 17:46:49 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"

/**
 * - Function to put the pixel into the image buffer
 */
void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	offset = (y * mlx->size_line) + (x * (mlx->bpp / 8));
	*((unsigned int *)(mlx->img_data + offset)) = color;
}

/**
 * - Empties out the image buffer
 */
void	clear_image(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			put_pixel(mlx, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

/**
 * - A helper to calculate the points of each row and col as iso_angles
 * - Using bresenham's algorithm to draw the line along the pixels
 */
static void	draw_points_and_lines(t_map *map, t_mlx *mlx, int row, int col)
{
	t_pixel	point;
	t_pixel	point_right;
	t_pixel	point_down;

	point = calc_iso(map, col, row, map->z_arr[row][col]);
	point.color = map->colors[row][col];
	if (col + 1 < map->width)
	{
		point_right = calc_iso(map, col + 1, row, map->z_arr[row][col + 1]);
		point_right.color = map->colors[row][col + 1];
		draw_bresenham_line(mlx, point, point_right);
	}
	if (row + 1 < map->height)
	{
		point_down = calc_iso(map, col, row + 1, map->z_arr[row + 1][col]);
		point_down.color = map->colors[row + 1][col];
		draw_bresenham_line(mlx, point, point_down);
	}
}

/**
 * - Manually draw the pixels of the map
 */
void	draw_map(t_fdf_data *data)
{
	t_mlx	*mlx;
	int		i;
	int		j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			draw_points_and_lines(&data->map, &data->mlx, i, j);
			j++;
		}
		i++;
	}
	mlx = &data->mlx;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
