/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:48:41 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/16 11:48:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include "libft.h"

/**
 * - Parses the data points into the respective point
 *  - TODO: add color parsing functionality
 */
void	put_datapoint(t_map *map, char *token, int row, int col)
{
	map->z_values[row][col] = ft_atoi(token);
	map->colors[row][col] = 0xFF0000;
}

/**
 * - Initializes height and width to 0 and points to NULL
 */
void	init_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->z_values = NULL;
	map->colors = NULL;
	map->z_scale = 1.0;
	map->rot_x = 0.0;
	map->rot_y = 0.0;
	map->rot_z = 0.0;
}

/**
 * - Put the data tokens of the file into the points structure in map
 * - Returns 0 if ft_split fails
 * - Returns 1 if all good
 */
int	input_points(int file_fd, t_map *map)
{
	int		col;
	int		row;
	char	**tokens;
	char	*line;

	row = 0;
	line = get_next_line(file_fd);
	while (line != NULL)
	{
		col = 0;
		tokens = ft_split(line, ' ');
		if (!tokens)
			return(free_map(map), 0);
		while (col < map->width)
		{
			put_datapoint(map, tokens[col], row, col);
			free(tokens[col]);
			col++;
		}
		free(tokens);
		free(line);
		line = get_next_line(file_fd);
		row++;
	}
	return (1);
}

/**
 * - Initialize the mlx struct (not confused for mlx_init)
 * - sets 0 for ints, NULL for pointers
 */
void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img_ptr = NULL;
	mlx->img_data = NULL;
	mlx->bpp = 0;
	mlx->endian = 0;
	mlx->size_line = 0;
}

/**
 * - Extension of init_mlx_lib to put image data
 * - Frees things if NULL is returned
 */
int	put_img_data(t_mlx *mlx, int *bpp, int *size_line, int *endian)
{
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, bpp, size_line, endian);
	if (!mlx->img_data)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		write(2, "Error: mlx_get_data_addr failed\n", 33);
		return (0);
	}
	return (1);
}

/**
 * - Initializes the library into the struct
 * - Also attaches the used event hooks to the window
 * - NOTE: data is only for key events
 */
int	init_mlx_lib(t_mlx *mlx, t_fdf_data *data)
{
	init_mlx(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "Fils de Fer");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		return (0);
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	if (!mlx->img_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		return (0);
	}
	if (!put_img_data(mlx, &mlx->bpp, &mlx->size_line, &mlx->endian))
		return (0);
	init_mlx_events(data);
	return (1);
}
