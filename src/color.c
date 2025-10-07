/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:35:50 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 10:35:51 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * - Interpolate color based on the ratio value given
 * - This link was super helpful:
 *   https://stackoverflow.com/questions/13488957
 * @param color1    integer containing color as 0x00RRGGBB
 * @param color2    integer containing color as 0x00RRGGBB
 * @param ratio  how much interpolation (0..1)
 * - 0: full color 1
 * - 1: full color 2
 * @return the new color after interpolation
 */
int	interpolate_color(int color1, int color2, double ratio)
{
	int	r;
	int	g;
	int	b;
	int	color1_arr[3];
	int	color2_arr[3];

	if (ratio < 0.0)
		ratio = 0.0;
	if (ratio > 1.0)
		ratio = 1.0;
	color1_arr[0] = (color1 >> 16) & 0xFF;
	color1_arr[1] = (color1 >> 8) & 0xFF;
	color1_arr[2] = color1 & 0xFF;
	color2_arr[0] = (color2 >> 16) & 0xFF;
	color2_arr[1] = (color2 >> 8) & 0xFF;
	color2_arr[2] = color2 & 0xFF;
	r = (int)(color1_arr[0] + (color2_arr[0] - color1_arr[0]) * ratio);
	g = (int)(color1_arr[1] + (color2_arr[1] - color1_arr[1]) * ratio);
	b = (int)(color1_arr[2] + (color2_arr[2] - color1_arr[2]) * ratio);
	return ((r << 16) | (g << 8) | b);
}
