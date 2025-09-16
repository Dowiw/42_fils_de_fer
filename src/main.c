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

typedef struct s_2d {
	int x;
	int y;
}		t_2d;

/**
 * - Function that projects 3d points into 2d renderable points
 */
t_2d	project_point(int x, int y, int z)
{
	t_2d	p;
	double scale = 100.0;
	double angle_x = 0.6;
	double angle_y = 0.4;

	p.x = (int)(scale * (x * cos(angle_x) - y * cos(angle_y)));
	p.y = (int)(scale * (x * sin(angle_x) + y * sin(angle_y)));
	(void)z;
	return (p);
}

/**
 * - Draw the line between the points
 */
void draw_line(t_mlx *mlx, t_2d a, t_2d b, int color)
{
	int steps = abs(b.x - a.x) > abs(b.y - a.y) ? abs(b.x - a.x) : abs(b.y - a.y);
	double dx = (b.x - a.x) / (double)steps;
	double dy = (b.y - a.y) / (double)steps;
	double x = a.x;
	double y = a.y;

	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, (int)x, (int)y, color);
		x += dx;
		y += dy;
	}
}

/**
 * - Manually draw the pixels of the map
 */
void draw_map(const t_map *map, t_mlx *mlx)
{
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			t_2d p = project_point(x, y, map->points[y][x].z);
			if (x + 1 < map->width)
			{
				t_2d p_right = project_point(x + 1, y, map->points[y][x + 1].z);
				draw_line(mlx, p, p_right, 0xFFFFFF);
			}
			if (y + 1 < map->height)
			{
				t_2d p_down = project_point(x, y + 1, map->points[y + 1][x].z);
				draw_line(mlx, p, p_down, 0xFFFFFF);
			}
		}
	}
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

	// print map for debug
	for (int i = 0; i < data.map.height; i++)
	{
		printf("row %i: ", i);
		for (int j = 0; j < data.map.width; j++)
			printf(": %i,%i,%i :", data.map.points[i][j].x, data.map.points[i][j].y, data.map.points[i][j].z);
		printf("\n");
	}
	if (!init_mlx_lib(&data.mlx))
	{
		free_map(&data.map);
		perror("Error: failed initializing library");
		return (1);
	}
	mlx_key_hook(data.mlx.win_ptr, handle_key, &data); // handle keys (first do ESC)
	mlx_hook(data.mlx.win_ptr, 17, 0, handle_close, &data);
	mlx_loop(data.mlx.mlx_ptr);
}
