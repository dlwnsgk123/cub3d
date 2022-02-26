/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:26 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/26 14:57:26 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_render
{
	int	width;
	int	wall_start;
	int	wall_end;
	int	y;
	double wall_height;
} 				t_render;

int	get_texture_color(t_vars *vars, t_ray ray,  t_render r, int	y_point)
{
	int tex_x;
	int tex_y;
	int tex_type;
	int tex_width;
	int distance_from_top;

	tex_type = ray.wall_dir;
	tex_width = vars->texture[tex_type].width;
	if (ray.hit_v)
		tex_x = (int)ray.hity % TILE_SIZE * (vars->texture[tex_type].width / TILE_SIZE);
	else
		tex_x = (int)ray.hitx % TILE_SIZE * (vars->texture[tex_type].width / TILE_SIZE);
	distance_from_top = y_point + r.wall_start - (WINDOW_HEIGHT / 2) + (r.wall_height / 2);
	tex_y = distance_from_top * (vars->texture[tex_type].height / r.wall_height) * (vars->texture[tex_type].height / TILE_SIZE);
	return (vars->texture[tex_type].data[tex_y * tex_width + tex_x]);
}

void	render_init(t_render *r, t_ray ray, t_vars *vars)
{
	ray.dist *= cos(ray.ra - vars->player.pa);
	r->wall_height = TILE_SIZE / ray.dist * DIST_PROJ_PLANE;
	r->wall_start = (WINDOW_HEIGHT / 2) - (r->wall_height / 2);
	if (r->wall_start < 0)
		r->wall_start = 0;
	r->wall_end = (r->wall_height / 2) + (WINDOW_HEIGHT / 2);
	if (r->wall_end > WINDOW_HEIGHT)
		r->wall_end = WINDOW_HEIGHT;
}

void draw_wall(t_vars *vars, t_ray ray, int ray_index)
{
	int	y;
	t_render r;

	y = 0;
	render_init(&r, ray, vars);
	while (y + r.wall_start < r.wall_end)
	{
		vars->screen.data[((y + r.wall_start) * WINDOW_WIDTH) + ray_index] = get_texture_color(vars, ray, r, y);
		y++;
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
			return (0);
		else if (vars->player.py - ray->hity < 0)
			return (1);
	}
	else
	{
		if (vars->player.px - ray->hitx > 0)
			return (2);
		else if (vars->player.px - ray->hitx < 0)
			return (3);
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
		dist = 9223372036854775807;
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
	double 		check_x;
	double 		check_y;

	vert_init(vars, ray, v, ra);
	next_x = v->xintercept;
	next_y = v->yintercept;
	while (next_x >= 0 && next_x <= vars->map.x * TILE_SIZE
		&& next_y >= 0 && next_y <= vars->map.y * TILE_SIZE)
	{
		check_x = next_x + (ray->facing_left ? -1 : 1);
        check_y = next_y;
		if (is_wall(vars, check_x, check_y))
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
	double		check_x;
	double		check_y;

	horz_init(vars, ray, h, ra);
	next_x = h->xintercept;
	next_y = h->yintercept;
	while (next_x >= 0 && next_x <= vars->map.x * TILE_SIZE
		&& next_y >= 0 && next_y <= vars->map.y * TILE_SIZE)
	{
		check_x = next_x;
		check_y = next_y + (ray->facing_up ? -1 : 1);
		if (is_wall(vars, check_x, check_y))
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

void	raycast(t_vars *vars, t_ray *ray, double ra)
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
	if (ray->dist == 9223372036854775807)
		put_error("error");
	ray->wall_dir = get_wall_dir(vars, ray);
}
/*
void	draw_line(t_vars *vars, t_p start, t_p end)
{
	int x = start.x;
	int y = start.y;
	int Xfactor = end.x < start.x ? -1 : 1;
	int Yfactor = end.y < start.y ? -1 : 1;

	int w = fabs(end.x - start.x);
	int h = fabs(end.y - start.y);
	int f;
	
	if (w > h)
	{
		f = (2 * h) - w;
		for (x = start.x; x != end.x; x += Xfactor)
		{
			if (f < 0)
				f += 2 * h;
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			vars->screen.data[x + y * vars->screen.size_line] = 0x0000FF;
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = start.y; y != end.y; y += Yfactor)
		{
			if (f < 0)
				f += 2 * w;
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			vars->screen.data[x + y * vars->screen.size_line] = 0x0000FF;
		}
	}
}
*/

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
		start.x = vars->player.px / TILE_SIZE * 10;
		start.y = vars->player.py / TILE_SIZE * 10;
		raycast(vars, &ray, ra);
		end.x = ray.hitx / TILE_SIZE * 10;
		end.y = ray.hity / TILE_SIZE * 10;
	//	draw_line(vars, start, end);
		draw_wall(vars, ray, i);
		ra += FOV_ANGLE / WINDOW_WIDTH;
		i++;
	}
}
