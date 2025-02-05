/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:38:52 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/05 19:09:45 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void clear_pixel_map(t_data *data)
{
    int x;
    int y;

    y = 0;
    while(y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            data->pixel_map[y][x] = 0;
            x++;
        }
        y++;
    }
}

void clear_image(t_cube *cube)
{
    int x;
    int y;

    y = 0;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W) 
        {
            put_pixel(x, y, 0x000000, cube);
            x++;
        }
        y++;
    }
}
int close_window(t_cube *cube)
{
    free_cube(cube);
    exit(0);
    return 0;
}
