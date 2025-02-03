/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:16:20 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/30 23:21:58 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int get_map_width(t_data *data)
{
    int i;
    unsigned long len;

    i = 0;
    len = 0;
    while(data->map[i]) {
        if(ft_strlen(data->map[i]) > len)
            len = ft_strlen(data->map[i]);
        i++;
    }
    return (len);
}

int get_map_height(char *file)
{
    int i;
    char *line;
    int fd;

    i = 0;
    fd = open(file, O_RDONLY);
    line = get_next_line(fd);
    while(i != 8) {
        free(line);
        line = get_next_line(fd);
        i++;
    }
    i = 0;
    while (line) {
        free(line);
        line = get_next_line(fd);
        i++;
    }
    free(line);
    close(fd);
    return i;
}

char **get_map(char *file)
{
    int i;
    char **map;
    char *line;
    int fd;

    i = get_map_height(file);
    map = malloc(sizeof(char *) * (i + 1));
    fd = open(file, O_RDONLY);
    line = get_next_line(fd);
    i = 0;
    while (i != 8) {
        free(line);
        line = get_next_line(fd);
        i++;
    }
    i = 0;
    while (line) {
        map[i++] = ft_strtrim(line, "\n");
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    map[i] = NULL;
    close(fd);
    return (map);
}

