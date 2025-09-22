/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:00:45 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/16 10:00:46 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include "libft.h"

/**
 * - Checks if av[1] is in valid .fdf format
 * - Prints out respective errors
 * - filepath should be below 256 by default
 */
int	is_valid_format(char *filepath)
{
	int	len;

	len = 0;
	while (filepath[len] != '\0')
		len++;
	if (len > 255)
		return (write(2, "Error: Filepath too large\n", 27), 0);
	if (len < 4)
		return (write(2, "Error: Filepath too short\n", 27), 0);
	if (filepath[len - 4] == '.'
		&& filepath[len - 3] == 'f'
		&& filepath[len - 2] == 'd'
		&& filepath[len - 1] == 'f')
		return (1);
	return (write(2, "Error: file is not in .fdf format\n", 35), 0);
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
 * - Helper function to get the width of the map
 */
static int	get_width(char *line)
{
	int	token;
	int	width;
	int	i;

	token = 0;
	width = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] != ' ' && line[i] != '\n') && !token)
		{
			token = 1;
			width++;
		}
		else if (line[i] == ' ' || line[i] == '\n')
			token = 0;
		i++;
	}
	return (width);
}

/**
 * - Places the height and the width of the file into the map
 * - Uses get_next_line which uses read
 */
static void	get_map_size(int file_fd, t_map *map)
{
	int		current_width;
	char	*line;

	line = get_next_line(file_fd);
	while (line != NULL)
	{
		current_width = get_width(line);
		if (map->height == 0)
			map->width = current_width;
		else if (current_width != map->width)
		{
			write(2, "Error: Map is not rectangular\n", 31);
			if (line)
				free(line);
			get_next_line(-1);
			exit(EXIT_FAILURE);
		}
		map->height++;
		free(line);
		line = get_next_line(file_fd);
	}
	get_next_line(-1);
}

/**
 * - Function to parse the file into a map in memory
 * - Returns 0 for open fails and allocation fails
 */
int	parse_map(char *filepath, t_map *map)
{
	int		exit;
	int		file_fd;

	file_fd = open(filepath, O_RDONLY);
	if (file_fd == -1)
	{
		perror("Cannot open file");
		return (0);
	}
	init_map(map);
	get_map_size(file_fd, map);
	close(file_fd);
	file_fd = open(filepath, O_RDONLY);
	if (file_fd == -1)
	{
		perror("Cannot open file");
		return (0);
	}
	exit = allocate_and_input(file_fd, map);
	if (exit == 0 || exit == 1)
		free_map(map);
	close(file_fd);
	init_angles(map);
	return (exit);
}
