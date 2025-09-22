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
		return;
	offset = (y * mlx->size_line) + (x * (mlx->bpp / 8));
	*((unsigned int *)(mlx->img_data + offset)) = color;
}

/**
 * - Empties out the image buffer
 */
void clear_image(t_mlx *mlx)
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
 * - Manually draw the pixels of the map
 */
void draw_map(t_fdf_data *data)
{
	t_pixel	point;
	t_pixel	point_right;
	t_pixel	point_down;
	int		i;
	int		j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			point = calc_isometric(&data->map, j, i, data->map.z_values[i][j]);
			if (j + 1 < data->map.width)
			{
				point_right = calc_isometric(&data->map, j + 1, i, data->map.z_values[i][j + 1]);
				draw_bresenham_line(&data->mlx, point, point_right, 0x00FF00);
			}
			if (i + 1 < data->map.height)
			{
				point_down = calc_isometric(&data->map, j, i + 1, data->map.z_values[i + 1][j]);
				draw_bresenham_line(&data->mlx, point, point_down, 0xFF0000);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
}
