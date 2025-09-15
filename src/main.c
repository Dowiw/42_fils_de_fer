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

#include "libft.h"
#include "fils_de_fer.h"

/**
 * - Checks if av[1] is in valid .fdf format
 * - Prints out respective errors
 * - filepath should be below 256 by default
 */
static int	is_valid_format(char *filepath)
{
	int	len;

	len = 0;
	while (filepath[len] != '\0')
		len++;
	if (len > 255)
		return (write(2, "Filepath too large\n", 20), 0);
	if (len < 4)
		return (write(2, "Filepath too short\n", 20), 0);
	if (filepath[len - 4] == '.'
		&& filepath[len - 3] == 'f'
		&& filepath[len - 2] == 'd'
		&& filepath[len - 1] == 'f')
		return (1);
	return (write(2, "Error: file is not in .fdf format\n", 35), 0);
}

/**
 * - Function to parse the file into a map in memory
 */
t_map	parse_map(char *filepath)
{
	t_map map = {0};
	int fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{ perror("Cannot open file"); exit(EXIT_FAILURE); }

	// pass: width and height
	char	*line;
	size_t	width = 0, height = 0;
	while ((line = get_next_line(fd)))
	{
		if (height == 0)
		{
			char	**tokens = ft_split(line, ' ');
			while (tokens[width])
				width++;
			for (size_t i = 0; tokens[i]; i++) free(tokens[i]);
			free(tokens);
		}
		height++;
		free(line);
	}
	close (fd);

	// second pass: allocate map based on size
	map.width = width;
	map.height = height;
	map.points = malloc(height * sizeof(t_point *));
	for (size_t i = 0; i < height; i++)
		map.points[i] = malloc(width * sizeof(t_point));
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{ perror("Cannot open file"); exit(EXIT_FAILURE); }
	size_t row = 0;
	while ((line = get_next_line(fd)))
	{
		char **tokens = ft_split(line, ' ');
		for (size_t col = 0; col < width; col++)
		{
			map.points[row][col].x = col;
			map.points[row][col].z = ft_atoi(tokens[col]);
			map.points[row][col].y = row;
			map.points[row][col].color = 0xFFFFFF;
			free(tokens[col]);
		}
		free(tokens);
		free(line);
		row++;
	}
	close(fd);
	return (map);
}

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
	for (size_t y = 0; y < map->height; y++)
	{
		for (size_t x = 0; x < map->width; x++)
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

int	handle_key(int keycode, void *param)
{
	if (keycode == XK_Escape)
		exit(1);
	return (0);
}

/**
 * - Main (assumes maps are in correct format)
 */
int main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx;

	if (ac != 2 || !is_valid_format(av[1]))
		return (write(2 ,"Usage: ./fdf <valid file in .fdf format>\n", 42), 1);
	map = parse_map(av[1]);

	// print map for debug
	for (size_t i = 0; i < map.height; i++)
	{
		printf("row %zu: ", i);
		for (size_t j = 0; j < map.width; j++)
			printf(": %i,%i,%i :", map.points[i][j].x, map.points[i][j].y, map.points[i][j].z);
		printf("\n");
	}

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, "Fil de Fer");

	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_W, WIN_H);
	mlx.img_data = mlx_get_data_addr(mlx.img_ptr, mlx.bpp, mlx.size_line, mlx.endian);

	draw_map(&map, &mlx); // draw angles in isometric projection using pixels

	mlx_key_hook(mlx.win_ptr, handle_key, NULL); // handle keys (first do ESC)
	mlx_loop(mlx.mlx_ptr);

	// eventually put to a separate function
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr);
	mlx_destroy_display(mlx.mlx_ptr); // very important frees for 0 leaks
	free(mlx.mlx_ptr);
}
