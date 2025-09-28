/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_angles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:25:48 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 08:26:05 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"

/**
 * - Calculate rotations in the x-axis
 */
static void	rotate_x(t_map *map, double *y, double *z)
{
	double	y_x;
	double	z_x;

	y_x = *y * cos(map->rot_x) - *z * sin(map->rot_x);
	z_x = *y * sin(map->rot_x) + *z * cos(map->rot_x);
	*y = y_x;
	*z = z_x;
}

/**
 * - Calculate rotations in the y-axis
 */
static void	rotate_y(t_map *map, double *x, double *z)
{
	double	x_y;
	double	z_y;

	x_y = *x * cos(map->rot_y) + *z * sin(map->rot_y);
	z_y = -(*x) * sin(map->rot_y) + *z * cos(map->rot_y);
	*x = x_y;
	*z = z_y;
}

/**
 * - Calculate rotations in the z-axis
 */
static void	rotate_z(t_map *map, double *x, double *y)
{
	double	x_z;
	double	y_z;

	x_z = *x * cos(map->rot_z) - *y * sin(map->rot_z);
	y_z = *x * sin(map->rot_z) + *y * cos(map->rot_z);
	*x = x_z;
	*y = y_z;
}

/**
 * - Rotation calculations based on the rotation matrices
 * - NOTE: https://en.wikipedia.org/wiki/Rotation_matrix
 * - EXPLANATION: using matrix multiplication, one can combine all angles of
 * 	a 3D point for it to be transformed by some angle theta.
 */
static void	calc_rotations(t_map *map, double *x, double *y, double *z)
{
	rotate_x(map, y, z);
	rotate_y(map, x, z);
	rotate_z(map, x, y);
}

/**
 * - Calculate the views of each renderable perspective
 *
 * @param x the abscissa
 * @param y the ordinate
 * @param z the altitude
 * @param map data of rotations, scaling and offset
 */
t_pixel	calc_iso(t_map *map, int x, int y, int z)
{
	double	x_d;
	double	y_d;
	double	z_d;

	x_d = (double)x;
	y_d = (double)y;
	z_d = (double)z * map->z_scale;
	calc_rotations(map, &x_d, &y_d, &z_d);
	if (map->viewmode == MODE_ISOMETRIC)
		return (do_iso_view(map, &x_d, &y_d, &z_d));
	else if (map->viewmode == MODE_Z_AXIS)
		return (do_z_view(map, &x_d, &y_d));
	else if (map->viewmode == MODE_X_AXIS)
		return (do_x_view(map, &y_d, &z_d));
	else if (map->viewmode == MODE_Y_AXIS)
		return (do_y_view(map, &x_d, &z_d));
	// else if (map->viewmode == MODE_CONIC)
	// 	return (do_conic_view(map, &x_d, &y_d, &z_d));
	return (do_iso_view(map, &x_d, &y_d, &z_d));
}
