/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:24:53 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 08:24:56 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * - Allocates colors array
 */
static int	allocate_colors(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->colors = malloc(map->height * sizeof(int *));
	if (!map->colors)
	{
		perror("Array height color allocation error");
		return (0);
	}
	while (i < map->height)
	{
		map->colors[i] = malloc(map->width * sizeof(int));
		if (!map->colors[i])
		{
			j = 0;
			while (j < i)
				free(map->colors[j++]);
			free(map->colors);
			perror("Array width color allocation error");
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * - Function responsible for allocating size into the points array
 * - Checks for malloc fails and frees everything
 */
int	allocate_and_input(int file_fd, t_map *map)
{
	int	j;
	int	i;

	i = 0;
	map->z_arr = malloc(map->height * sizeof(int *));
	if (!map->z_arr)
	{
		perror("Array height z_arr allocation error");
		exit(EXIT_FAILURE);
	}
	while (i < map->height)
	{
		map->z_arr[i] = malloc(map->width * sizeof(int));
		if (!map->z_arr[i])
		{
			j = 0;
			while (j < i)
				free(map->z_arr[j++]);
			free(map->z_arr);
			perror("Array width z_arr allocation error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (allocate_colors(map) + input_points(file_fd, map));
}

/**
 * - Parses the data points into the respective point
 */
void	put_datapoint(t_map *map, char *token, int row, int col)
{
	char	*after_z;

	map->z_arr[row][col] = ft_atoi(token);
	after_z = ft_strchr(token, ',');
	if (after_z++)
		map->colors[row][col] = ft_strtol_hex(after_z);
	else
		map->colors[row][col] = 0xFFFFFF;
}
