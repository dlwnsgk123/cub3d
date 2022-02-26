/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:26 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/26 20:34:05 by seungiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	vert_init(t_vars *vars, t_ray *ray, t_ray_util *v, double ra)
{
	t_player	player;

	player = vars->player;
	v->found_wall_hit = 0;
	v->wall_hitx = 0;
	v->wall_hity = 0;
	v->xintercept = floor(player.px / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_right)
		v->xintercept += TILE_SIZE;
	v->yintercept = player.py + (v->xintercept - player.px) * tan(ra);
	v->xstep = TILE_SIZE;
	if (ray->facing_left)
		v->xstep *= -1;
	v->ystep = TILE_SIZE * tan(ra);
	if (ray->facing_up && v->ystep > 0)
		v->ystep *= -1;
	if (ray->facing_down && v->ystep < 0)
		v->ystep *= -1;
}

static void	vert_check(t_vars *vars, t_ray *ray, t_ray_util *v, double ra)
{
	t_point	next;
	t_point	check;

	vert_init(vars, ray, v, ra);
	next.x = v->xintercept;
	next.y = v->yintercept;
	while (next.x >= 0 && next.x <= vars->map.x * TILE_SIZE
		&& next.y >= 0 && next.y <= vars->map.y * TILE_SIZE)
	{
		if (ray->facing_left == 1)
			check.x = next.x - 1;
		else
			check.x = next.x + 1;
		check.y = next.y;
		if (is_wall(vars, check.x, check.y))
		{
			v->found_wall_hit = 1;
			v->wall_hitx = next.x;
			v->wall_hity = next.y;
			break ;
		}
		next.x += v->xstep;
		next.y += v->ystep;
	}
	v->distance = get_distance(vars, v);
}

static void	horz_init(t_vars *vars, t_ray *ray, t_ray_util *h, double ra)
{
	t_player	player;

	player = vars->player;
	h->wall_hitx = 0;
	h->wall_hity = 0;
	h->found_wall_hit = 0;
	h->yintercept = floor(player.py / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_down)
		h->yintercept += TILE_SIZE;
	h->xintercept = player.px + (h->yintercept - player.py) / tan(ra);
	h->ystep = TILE_SIZE;
	if (ray->facing_up)
		h->ystep *= -1;
	h->xstep = TILE_SIZE / tan(ra);
	if (ray->facing_left && h->xstep > 0)
		h->xstep *= -1;
	if (ray->facing_right && h->xstep < 0)
		h->xstep *= -1;
}

static void	check_horz(t_vars *vars, t_ray *ray, t_ray_util *h, double ra)
{
	t_point	next;
	t_point	check;

	horz_init(vars, ray, h, ra);
	next.x = h->xintercept;
	next.y = h->yintercept;
	while (next.x >= 0 && next.x <= vars->map.x * TILE_SIZE
		&& next.y >= 0 && next.y <= vars->map.y * TILE_SIZE)
	{
		check.x = next.x;
		if (ray->facing_up == 1)
			check.y = next.y - 1;
		else
			check.y = next.y + 1;
		if (is_wall(vars, check.x, check.y))
		{
			h->found_wall_hit = 1;
			h->wall_hitx = next.x;
			h->wall_hity = next.y;
			break ;
		}
		next.x += h->xstep;
		next.y += h->ystep;
	}
	h->distance = get_distance(vars, h);
}

void	raycast(t_vars *vars, t_ray *ray, double ra)
{
	t_ray_util	v;
	t_ray_util	h;

	ra = normalize_angle(ra);
	ray->ra = ra;
	rayfacing_init(ray, ra);
	check_horz(vars, ray, &h, ra);
	vert_check(vars, ray, &v, ra);
	if (v.distance < h.distance)
	{
		ray->hitx = v.wall_hitx;
		ray->hity = v.wall_hity;
		ray->dist = v.distance;
		ray->hit_v = 1;
	}
	else
	{
		ray->hitx = h.wall_hitx;
		ray->hity = h.wall_hity;
		ray->dist = h.distance;
		ray->hit_v = 0;
	}
	if (ray->dist == 9223372036854775807)
		put_error("error");
	ray->wall_dir = get_wall_dir(vars, ray);
}
