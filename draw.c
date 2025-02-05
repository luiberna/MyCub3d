/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:58:05 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/05 17:58:36 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void draw_ceiling(t_cube *cube, t_data *data, int ceiling_color)
{
    int x;
    int y;

    y = 0;
    while (y < SCREEN_H / 2)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            put_pixel(x, y, ceiling_color, cube);
            x++;
        }
        y++;
    }
}

void draw_floor(t_cube *cube, t_data *data, int floor_color)
{
    int x;
    int y;

    y = SCREEN_H / 2;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            put_pixel(x, y, floor_color, cube);
            x++;
        }
        y++;
    }
}

void draw_pixel_map_content(t_cube *cube, t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            if (data->pixel_map[y][x] > 0)
                put_pixel(x, y, data->pixel_map[y][x], cube);
            x++;
        }
        y++;
    }
}

void draw_pixel_map(t_cube *cube, t_data *data)
{
    int ceiling_color;
    int floor_color;

    ceiling_color = get_hex_color(data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
    floor_color = get_hex_color(data->floor_color[0], data->floor_color[1], data->floor_color[2]);
    draw_ceiling(cube, data, ceiling_color);
    draw_floor(cube, data, floor_color);
    draw_pixel_map_content(cube, data);
}
