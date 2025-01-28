/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:16:20 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/28 16:31:12 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int get_map_width(t_data *data) {
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

int get_map_height(char *file) {
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

char **get_map(char *file) {
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
    return map;
}

int **get_pixel_map(t_data *data) {
    int i;
    int **pixel_map;

    i = 0;
    pixel_map = ft_calloc(sizeof(int *), SCREEN_H + 1);
    while(i < SCREEN_H) {
        pixel_map[i] = ft_calloc(sizeof(int), SCREEN_W);
        if (!pixel_map[i])
            print_error("Error: Can't allocate pixel map\n");
        i++;
    }
    return (pixel_map);
}
