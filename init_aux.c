/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:23:47 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/03 21:28:07 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void init_texture_buffer(t_data *data)
{
    int i;
    i = 0;
    data->texture_buffer = ft_calloc(4, sizeof(int *));
    while (i < 4)
    {
        data->texture_buffer[i] = ft_calloc(CUBE * CUBE, sizeof(int));
        if (!data->texture_buffer[i])
            print_error("Error: Could not allocate texture buffer\n");
        i++;
    }
}

void init_color(t_data *data, char *file)
{
    int *ceiling_color;
    int *floor_color;

    ceiling_color = get_color(file, "C");
    floor_color = get_color(file, "F");
    if (ceiling_color)
    {
        data->ceiling_color[0] = ceiling_color[0];
        data->ceiling_color[1] = ceiling_color[1];
        data->ceiling_color[2] = ceiling_color[2];
        free(ceiling_color);
    }
    if (floor_color)
    {
        data->floor_color[0] = floor_color[0];
        data->floor_color[1] = floor_color[1];
        data->floor_color[2] = floor_color[2];
        free(floor_color);
    }
}

void    init_pixel_map(t_data *data)
{
    int i;
    
    i = 0;
    data->pixel_map = ft_calloc(SCREEN_H, sizeof(int *));
    if (!data->pixel_map)
        print_error("Error: Could not allocate pixel_map\n");
    while(i < SCREEN_H)
    {
        data->pixel_map[i] = ft_calloc(SCREEN_W, sizeof(int));
        if (!data->pixel_map[i])
            print_error("Error: Could not allocate row for pixel_map\n");
        i++;
    } 
}
