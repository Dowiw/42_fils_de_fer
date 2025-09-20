/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:11:55 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/16 12:11:56 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"

/**
 * - Frees the allocated arrays inside map
 */
void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->z_values)
	{
		i = 0;
		while (i < map->height)
			free(map->z_values[i++]);
		free(map->z_values);
	}
	i = 0;
	if (map->colors)
	{
		i = 0;
		while (i < map->height)
			free(map->colors[i++]);
		free(map->colors);
	}
}

/**
 * - Frees the whole data structure
 * - NOTE: only points** and the mlx library is allocated in heap memory
 * 	everything else is in stack memory
 */
void	free_data(t_fdf_data *data)
{
	free_map(&data->map);
	if (data->mlx.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	if (data->mlx.win_ptr)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	if (data->mlx.mlx_ptr)
	{
		mlx_destroy_display(data->mlx.mlx_ptr);
		free(data->mlx.mlx_ptr);
	}
}
