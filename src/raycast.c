/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:26 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/24 11:11:45 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void draw_wall(t_vars *vars, t_ray ray, int x)
{
	int	width;
	int	height;
	int	drawStart;
	int	drawEnd;
	float lineH;

	width = 1;
	height = WINDOW_HEIGHT;
	ray.dist *= cos(ray.ra - vars->player.pa);
	lineH = DIST_PROJ_PLANE / ray.dist * TILE_SIZE;
	if (lineH > height)
		lineH = height;
	drawStart = -(lineH / 2) + (height / 2);
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = (lineH / 2) + (height / 2);
	if (drawEnd >= height)
		drawEnd = height - 1;

	int	h;
	int	sw, ew;
	int	y = vars->screen.size_line;
	int	green = 0x00CD00;
	int	blue = 0x0000CD;

	h = 0;
	while (h + drawStart < drawEnd)
	{
		sw = x * width;
		ew = sw + width;
		while (sw <= ew)
		{
			if (ray.wall_dir == 1)
				vars->screen.data[((h + drawStart) * y) + sw] = 0xFF0000;
			if (ray.wall_dir == 2)
				vars->screen.data[((h + drawStart) * y) + sw] = 0xFF00FF;
			if (ray.wall_dir == 3)
				vars->screen.data[((h + drawStart) * y) + sw] = 0x00FF00;
			if (ray.wall_dir == 4)
				vars->screen.data[((h + drawStart) * y) + sw] = 0x0000FF;
			sw++;
		}
		h++;
	}
}

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

int		get_wall_dir(t_vars *vars, t_ray *ray)
{
	if (!ray->hit_v)
	{
		if (vars->player.py - ray->hity > 0)
			return (1);
		else if (vars->player.py - ray->hity < 0)
			return (2);
	}
	else
	{
		if (vars->player.px - ray->hitx > 0)
			return (3);
		else if (vars->player.px - ray->hitx < 0)
			return (4);
	}
}

double	get_distance(t_vars *vars, t_ray_util *hv)
{
	double dist;

	if (hv->found_wall_hit)
	{
		dist = sqrt((hv->wall_hitx - vars->player.px) 
		* (hv->wall_hitx - vars->player.px) 
		+ (hv->wall_hity - vars->player.py) 
		* (hv->wall_hity - vars->player.py));
	}
	else
		dist = 10000000000000;
	return (dist);
}

void	vert_init(t_vars *vars, t_ray *ray, t_ray_util *v, double ra)
{
	t_player	player;

	player = vars->player;
	v->found_wall_hit = false;
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

void	vert_check(t_vars *vars, t_ray *ray, t_ray_util *v, double ra)
{
	double		next_x;
	double		next_y;

	vert_init(vars, ray, v, ra);
	next_x = v->xintercept;
	next_y = v->yintercept;
	while (next_x >= 0 && next_x <= vars->map.x * TILE_SIZE
		&& next_y >= 0 && next_y <= vars->map.y * TILE_SIZE)
	{
        float xToCheck = next_x + (ray->facing_left ? -1 : 0);
        float yToCheck = next_y;
		if (is_wall(vars, xToCheck, yToCheck))
		{
			v->found_wall_hit = true;
			v->wall_hitx = next_x;
			v->wall_hity = next_y;
			break ;
		}
		next_x += v->xstep;
		next_y += v->ystep;
	}
	v->distance = get_distance(vars, v);
}

void	horz_init(t_vars *vars, t_ray *ray, t_ray_util *h, double ra)
{
	t_player	player;

	player = vars->player;
	h->wall_hitx = 0;
	h->wall_hity = 0;
	h->found_wall_hit = false;
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

void	check_horz(t_vars *vars, t_ray *ray, t_ray_util *h, double ra)
{
	double		next_x;
	double		next_y;

	horz_init(vars, ray, h, ra);
	next_x = h->xintercept;
	next_y = h->yintercept;
	while (next_x >= 0 && next_x <= vars->map.x * TILE_SIZE
		&& next_y >= 0 && next_y <= vars->map.y * TILE_SIZE)
	{
        float xToCheck = next_x;
        float yToCheck = next_y + (ray->facing_up ? -1 : 0);
		if (is_wall(vars, xToCheck, yToCheck))
		{
			h->found_wall_hit = true;
			h->wall_hitx = next_x;
			h->wall_hity = next_y;
			break ;
		}
		next_x += h->xstep;
		next_y += h->ystep;
	}
	h->distance = get_distance(vars, h);
}

void	cast_one_ray(t_vars *vars, t_ray *ray, double ra)
{
	t_ray_util v;
	t_ray_util h;

	ra = normalize_angle(ra);
	ray->ra = ra;
	ray->facing_down = ra > 0 && ra < PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = ra < 0.5 * PI || ra > 1.5 * PI;
	ray->facing_left = !ray->facing_right;
	check_horz(vars, ray, &h, ra);
	vert_check(vars, ray, &v, ra);
	if (v.distance < h.distance)
	{
		ray->hitx = v.wall_hitx;
		ray->hity = v.wall_hity;
		ray->dist = v.distance;
		ray->hit_v = true;
	}
	else
	{
		ray->hitx = h.wall_hitx;
		ray->hity = h.wall_hity;
		ray->dist = h.distance;
		ray->hit_v = false;
	}
	ray->wall_dir = get_wall_dir(vars, ray);
}

void	ray_draw(t_vars *vars)
{
	double	ca;
	double	ra;
	t_ray	ray;
	int i;

	t_p start;
	t_p end;

	i = 0;
    ra = vars->player.pa - (FOV_ANGLE / 2.0);
	while (i < WINDOW_WIDTH)
	{
		start.x = vars->player.px;
		start.y = vars->player.py;
		cast_one_ray(vars, &ray, ra);
		end.x = ray.hitx;
		end.y = ray.hity;
//		draw_line(vars, start, end);
		draw_wall(vars, ray, i);
		ra += FOV_ANGLE / WINDOW_WIDTH;
		i++;
	}
}
