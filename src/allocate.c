#include "fils_de_fer.h"

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
	map->z_values = malloc(map->height * sizeof(int *));
	if (!map->z_values)
	{
		perror("Array height z_values allocation error");
		exit(EXIT_FAILURE);
	}
	while (i < map->height)
	{
		map->z_values[i] = malloc(map->width * sizeof(int));
		if (!map->z_values[i])
		{
			j = 0;
			while (j < i)
				free(map->z_values[j++]);
			free(map->z_values);
			perror("Array width z_values allocation error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (allocate_colors(map) + input_points(file_fd, map));
}
