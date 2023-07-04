/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:20:00 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/04 15:00:57 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	central_draw_one_block(t_info *info, int draw_x, int draw_y,
		int color)
{
	int	x;
	int	y;

	x = draw_x;
	while (x < draw_x + BLOCK_SIZE)
	{
		y = draw_y;
		while (y < (draw_y + BLOCK_SIZE))
		{
			my_mlx_pixel_put(info->data, x, y, color);
			y++;
		}
		x++;
	}
}

void	player_draw_ray(t_info *info, t_vars *vars)
{
	double	x_direction;
	double	y_direction;
	double	line_length;
	double	end_x;
	double	end_y;
	int		mini_map_scale;

	// プレイヤーの現在位置と向きの取得
	x_direction = vars->x_direction;
	y_direction = vars->y_direction;
	mini_map_scale = mapdata_maxwidth_length(info->map);
	// 線の長さを計算（ここでは仮に10とする）
	line_length = 10;
	// 線の終点の座標を計算
	end_x = (info->map->player_x + line_length * x_direction);
	end_y = (info->map->player_y + line_length * y_direction);
	my_mlx_pixel_put(info->data, end_x, end_y, RED);
}

void draw_ray_player_fov(t_info *info, int start_x, int start_y)
{
	// FOVの範囲のrayを出力。
	int	ray_len;
	int	middle_ray_x;
	int	middle_ray_y;

	ray_len = BLOCK_SIZE / 2;
	middle_ray_x = 0;
	middle_ray_y = 0;
	
	ray_len = 0;
	while (ray_len < 100)
	{
		//-1はFOVの一番左を指している
		middle_ray_x = (ray_len * (info->vars->y_direction
				+ (info->vars->y_camera_plane * -1)));
		middle_ray_y = (ray_len * (info->vars->x_direction
				+ (info->vars->x_camera_plane * -1)));
		my_mlx_pixel_put(info->data,start_x + (info->map->player_x * BLOCK_SIZE
				+ (BLOCK_SIZE / 2)) + middle_ray_x\
		,start_y + (info->map->player_y * BLOCK_SIZE + (BLOCK_SIZE / 2)) + middle_ray_y,RED);
		ray_len++;
	}
	ray_len = 0;
	while (ray_len < 100)
	{
		//-1はFOVの一番左を指している
		middle_ray_x = (ray_len * (info->vars->y_direction
				+ (info->vars->y_camera_plane * 1)));
		middle_ray_y = (ray_len * (info->vars->x_direction
				+ (info->vars->x_camera_plane * 1)));
		my_mlx_pixel_put(info->data,start_x + (info->map->player_x * BLOCK_SIZE
				+ (BLOCK_SIZE / 2)) + middle_ray_x\
		,start_y + (info->map->player_y * BLOCK_SIZE + (BLOCK_SIZE / 2)) + middle_ray_y,RED);
		ray_len++;
	}
	player_draw_ray(info, info->vars);
}

void	draw_ray_player_direction(t_info *info, int start_x, int start_y)
{
	int	ray_len;
	int	middle_ray_x;
	int	middle_ray_y;

	ray_len = BLOCK_SIZE / 2;
	middle_ray_x = 0;
	middle_ray_y = 0;
	while (ray_len < 100)
	{
		middle_ray_x = (ray_len * info->vars->y_direction);
		middle_ray_y = (ray_len * info->vars->x_direction);
		my_mlx_pixel_put(info->data, start_x + (info->map->player_x * BLOCK_SIZE
				+ (BLOCK_SIZE / 2)) + middle_ray_x, start_y
			+ (info->map->player_y * BLOCK_SIZE + (BLOCK_SIZE / 2))
			+ middle_ray_y, BLACK);
		ray_len++;
	}
}

/*
map中央を求める
mapの縦横の大きさか描画スタート地点を決める
列ごとに描画する
*/
void	central_map(t_info *info)
{
	int x;
	int y;
	int start_x;
	int start_y;
	int end_x;
	int end_y;

	//描画開始地点を求める
	start_x = (WIN_WIDTH / 2) - ((mapdata_maxwidth_length(info->map)
			* BLOCK_SIZE) / 2);
	start_y = (WIN_HEIGHT / 2) - (((info->map->height) * BLOCK_SIZE) / 2);
	end_y = info->map->height;
	y = 0;

	while (y < end_y)
	{
		x = 0;
		end_x = mapdata_width_length(info->map->map_data[y]);
		while (x < end_x + 1)
		{
			if (info->map->map_data[y][x] == ' ')
				;
			else if (info->map->map_data[y][x] == '1'
				|| info->map->map_data[y][x] == '2'
				|| info->map->map_data[y][x] == '3'
				|| info->map->map_data[y][x] == '4')
			{
				central_draw_one_block(info, start_x + (x * BLOCK_SIZE),
					start_y + (y * BLOCK_SIZE), MAP_GREEN);
			}
			else if (info->map->map_data[y][x] == '0')
			{
				central_draw_one_block(info, start_x + (x * BLOCK_SIZE),
					start_y + (y * BLOCK_SIZE), MAP_WHITE);
			}
			else if (info->map->map_data[y][x] == 'N'
				|| info->map->map_data[y][x] == 'S'
				|| info->map->map_data[y][x] == 'E'
				|| info->map->map_data[y][x] == 'W')
			{
				central_draw_one_block(info, start_x + (x * BLOCK_SIZE),
					start_y + (y * BLOCK_SIZE), BLUE);
				info->map->player_x = x;
				info->map->player_y = y;
			}
			else
				central_draw_one_block(info, start_x + (x * BLOCK_SIZE),
					start_y + (y * BLOCK_SIZE), MAP_RED);
			x++;
		}
		y++;
	}
	draw_ray_player_direction(info, start_x, start_y);
	draw_ray_player_fov(info, start_x, start_y);

	return ;
}