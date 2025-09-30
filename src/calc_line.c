/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:15:36 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 09:15:37 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include <stdlib.h>

static int	determine_color_low(t_pixel p0, t_pixel p1, t_pixel start_p)
{
	int		color;
	double	ratio;

	ratio = (p0.x - start_p.x) / (double)(p1.x - start_p.x);
	color = interpolate_color(start_p.color, p1.color, ratio);
	return (color);
}

static int	determine_color_high(t_pixel p0, t_pixel p1, t_pixel start_p)
{
	int		color;
	double	ratio;

	ratio = (p0.y - start_p.y) / (double)(p1.y - start_p.y);
	color = interpolate_color(start_p.color, p1.color, ratio);
	return (color);
}

static void	draw_line_high(t_mlx *mlx, t_pixel p0, t_pixel p1, t_pixel start_p)
{
	int	dx;
	int	dy;
	int	xi;
	int	delta;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	delta = (2 * dx) - dy;
	while (p0.y <= p1.y)
	{
		put_pixel(mlx, p0.x, (p0.y)++, determine_color_high(p0, p1, start_p));
		if (delta > 0)
		{
			p0.x += xi;
			delta += (2 * (dx - dy));
		}
		else
			delta += 2 * dx;
	}
}

static void	draw_line_low(t_mlx *mlx, t_pixel p0, t_pixel p1, t_pixel start_p)
{
	int	yi;
	int	dx;
	int	dy;
	int	delta;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	delta = (2 * dy) - dx;
	while (p0.x <= p1.x)
	{
		put_pixel(mlx, (p0.x)++, p0.y, determine_color_low(p0, p1, start_p));
		if (delta > 0)
		{
			p0.y += yi;
			delta += (2 * (dy - dx));
		}
		else
			delta += 2 * dy;
	}
}

/**
 * - Optimized form of the Bresenham Line Algorithm
 */
void	draw_bresenham_line(t_mlx *mlx, t_pixel start, t_pixel end)
{
	int	dx;
	int	dy;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	if (dy < dx)
	{
		if (start.x > end.x)
			draw_line_low(mlx, end, start, end);
		else
			draw_line_low(mlx, start, end, start);
	}
	else
	{
		if (start.y > end.y)
			draw_line_high(mlx, end, start, end);
		else
			draw_line_high(mlx, start, end, start);
	}
}

// /**
//  * NOTE: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
//  * - Bresenham's algorithm in plain code
//  * - This is one of the implementation examples on considering a principle on
//  *	integer incremental error
//  */
// void	draw_bresenham_line(t_mlx *mlx, t_pixel start, t_pixel end, int color)
// {
// 	int	dx;
// 	int	dy;
// 	int	x_step;
// 	int	y_step;
// 	int	delta;
// 	int	delta2;

// 	dx = abs(end.x - start.x);
// 	dy = abs(end.y - start.y);
// 	x_step = (start.x < end.x) ? 1 : -1;
// 	y_step = (start.y < end.y) ? 1 : -1;
// 	delta = dx - dy;
// 	while (start.x != end.x || start.y != end.y)
// 	{
// 		put_pixel(mlx, start.x, start.y, color);
// 		delta2 = 2 * delta;
// 		if (delta2 > -dy)
// 		{
// 			delta -= dy;
// 			start.x += x_step;
// 		}
// 		if (delta2 < dx)
// 		{
// 			delta += dx;
// 			start.y += y_step;
// 		}
// 	}
// 	put_pixel(mlx, end.x, end.y, color); // draw the last point
// }
