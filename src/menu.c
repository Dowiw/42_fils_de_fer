/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:49:59 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/28 19:50:01 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include <mlx.h>
#include <unistd.h>

/**
 * - Return string of the selected mode
 */
static char	*find_viewpoint(t_map *map)
{
	if (map->rot_x != 0.0
		|| map->rot_y != 0.0
		|| map->rot_z != 0.0)
		return ("Rotated");
	else if (map->viewmode == MODE_Z_AXIS)
		return ("Orthrographic Plan View");
	else if (map->viewmode == MODE_ISOMETRIC)
		return ("Isometric View");
	else if (map->viewmode == MODE_Y_AXIS)
		return ("Y-Axis View");
	else if (map->viewmode == MODE_X_AXIS)
		return ("X-Axis View");
	else if (map->viewmode == MODE_TWO_POINT)
		return ("2-point central perspective");
	else
		return ("N/A");
}

void	init_details(char *details[23])
{
	details[0] = "Fils de Fer by kmonjard :)";
	details[1] = "View mode:";
	details[2] = "";
	details[3] = "How to use:";
	details[4] = "c : centralize";
	details[5] = "r : reset";
	details[6] = "w s  : rotate x-axis (pitch)";
	details[7] = "a d  : rotate y-axis (roll)";
	details[8] = "up down : z-magnitude control";
	details[9] = "left right : rotate z-axis (yaw)";
	details[10] = "t g f h : translate map";
	details[11] = "- : scale down map";
	details[12] = "= : scale up map";
	details[13] = "1 : isometric mode";
	details[14] = "2 : orthrographic plan mode";
	details[15] = "3 : X-axis mode";
	details[16] = "4 : Y-axis mode";
	details[17] = "5 : 2-point perspective";
	details[18] = "";
	details[19] = "Notes:";
	details[20] = "- Rotation values persist in all modes";
	details[21] = "- Z-magnitude persist";
	details[22] = NULL;
}

/**
 * - Drawing strings of texts after the image is rendered.
 * - Unfortunately, knowing where to put the pixels is all about magic numbers.
 * 	Maybe digging into how spaces and indents are formed in Word or Docs could
 * 	help but it will take more time. Maybe in the next graphic project.
 */
void	draw_menu(t_mlx *mlx, t_map *map)
{
	int		j;
	int		i;
	char	*viewpoint;
	void	*win_ptr;
	void	*mlx_ptr;

	j = 0;
	i = 50;
	win_ptr = mlx->win_ptr;
	mlx_ptr = mlx->mlx_ptr;
	viewpoint = find_viewpoint(map);
	while (i < WIN_H && mlx->details[j] != NULL)
	{
		mlx_string_put(mlx_ptr, win_ptr, 50, i, 0xFFFFFF, mlx->details[j]);
		j++;
		i += 20;
	}
	mlx_string_put(mlx_ptr, win_ptr, 150, 70, 0xFFFFFF, viewpoint);
}
