/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:05:20 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/07 16:42:59 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void free_color(char **color_parts)
{
    int i;

    i = 0;
    while (color_parts[i])
    {
        free(color_parts[i]);
        i++;
    }
    free(color_parts);
}

int	get_hex_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void get_rgb(t_cube *cube, char *line, int *color)
{
    char **color_parts;
    int i;

    i = 0;
    color_parts = ft_split(line + 2, ',');
    if (!color_parts)
        return;
    color[0] = ft_atoi(color_parts[0]);
    color[1] = ft_atoi(color_parts[1]);
    color[2] = ft_atoi(color_parts[2]);
    while (color_parts[i])
    {
        free(color_parts[i]);
        i++;
    }
    free(color_parts);
}

int *get_color(t_cube *cube, char *file, char *type)
{
    int fd;
    char *row;
    int *color;

    color = ft_calloc(3, sizeof(int));
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return NULL;
    }
    row = get_next_line(fd);
    while (row)
    {
        if (strncmp(row, type, 1) == 0)
            get_rgb(cube, row, color);
        free(row);
        row = get_next_line(fd);
    }
    free(row);
    close(fd);
    return color;
}
