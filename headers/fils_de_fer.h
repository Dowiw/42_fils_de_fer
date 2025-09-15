/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fils_de_fer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:20:12 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/15 22:20:13 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h> // minilibx library

#include <math.h> // sin, cos, tan, etc.

#include <unistd.h> // write

#include <limits.h> // maxs and mins

#include <X11/keysym.h> // declarations of keys in X11 library

#include <stdlib.h>

#include <fcntl.h> // open, read,

#include <stdio.h>

// each point in the map
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color; // hex value in decimal
}		t_point;

// structure to store point data and render values
typedef struct s_map
{
	size_t	width;
	size_t	height;
	t_point	**points;
}			t_map;

// structure for mlx data
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

#define	WIN_W 800
#define	WIN_H 800
