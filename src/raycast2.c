/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:13:06 by seungiki          #+#    #+#             */
/*   Updated: 2022/02/27 09:46:50 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	if (angle >= 0)
	{
		while (angle >= TWO_PI)
			angle -= TWO_PI;
	}
	else
	{
		while (angle <= 0)
			angle += TWO_PI;
	}
	return (angle);
}

int	get_wall_dir(t_vars *vars, t_ray *ray)
{
	if (!ray->hit_v)
	{
		if (vars->player.py - ray->hity > 0)
			return (SO);
		else if (vars->player.py - ray->hity < 0)
			return (NO);
	}
	else
	{
		if (vars->player.px - ray->hitx > 0)
			return (EA);
		else if (vars->player.px - ray->hitx < 0)
			return (WE);
	}
	return (5);
}

double	get_distance(t_vars *vars, t_ray_util *hv)
{
	double	dist;

	if (hv->found_wall_hit)
	{
		dist = sqrt(((hv->wall_hitx - vars->player.px) * \
					(hv->wall_hitx - vars->player.px)) + \
				((hv->wall_hity - vars->player.py) * \
				(hv->wall_hity - vars->player.py)));
	}
	else
		dist = 9223372036854775807;
	return (dist);
}

void	rayfacing_init(t_ray *ray, double ra)
{
	ray->facing_down = (ra > 0 && ra < PI);
	ray->facing_up = !ray->facing_down;
	ray->facing_right = (ra < 0.5 * PI || ra > 1.5 * PI);
	ray->facing_left = !ray->facing_right;
}

void	ray_draw(t_vars *vars)
{
	double	ra;
	t_ray	ray;
	int		i;

	i = 0;
	ra = vars->player.pa - (FOV_ANGLE / 2.0);
	while (i < WINDOW_WIDTH)
	{
		raycast(vars, &ray, ra);
		draw_wall(vars, ray, i);
		ra += FOV_ANGLE / WINDOW_WIDTH;
		i++;
	}
}
