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

#include <stdio.h>

#include "libft.h"

#include <mlx.h>

#include <math.h>

#include <unistd.h>

#include <limits.h>

#include <stdlib.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color; // hex value in decimal
}		t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}			t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}			t_mlx;

/**
 * - Checks if av[1] is in valid .fdf format
 * - Prints out respective errors
 * - Filename should be below 255 by default
 */
static int	is_valid_format(char *filename)
{
	int	len;

	len = 0;
	while (filename[len] != '\0')
		len++;
	if (len > 255)
		return (write(2, "Filename too large\n", 20), 0);
	if (len < 4)
		return (write(2, "Filename too short\n", 20), 0);
	if (filename[len - 4] == '.'
		&& filename[len - 3] == 'f'
		&& filename[len - 2] == 'd'
		&& filename[len - 1] == 'f')
		return (1);
	return (write(2, "Error: Filename is not in .fdf format\n", 39), 0);
}

/**
 * - Main (assumes maps are in correct format)
 */
int main(int ac, char **av)
{
	void	*mlx_ptr;

	if (ac != 2 || !is_valid_format(av[1]))
		return (write(2 ,"Usage: ./fdf <valid file in .fdf format>\n", 42), 1);
	printf("arg: %s\n", av[1]);
	mlx_ptr = mlx_init();
	mlx_destroy_display(mlx_ptr); // very important frees for 0 leaks
	free(mlx_ptr);
}
