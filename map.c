/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:16:20 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/05 18:12:04 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

char **get_map(t_data *data, char *file)
{
    int i;
    char **map;
    char *line;
    int fd;

    map = malloc(sizeof(char *) * (get_map_height(data,file) + 1));
    fd = open(file, O_RDONLY);
    line = get_next_line(fd);
    i = 0;
    while (i++ != data->map_position)
    {
        free(line);
        line = get_next_line(fd);
    }
    i = 0;
    while (line)
    {
        map[i++] = ft_strtrim(line, "\n");
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    map[i] = NULL;
    close(fd);
    return (map);
}

void count_config_lines(t_data *data, int fd, int *count, int *flag)
{
    char *line;

    while ((line = get_next_line(fd)) && *flag < 6)
    {
        if (ft_strncmp(line, "C", 1) == 0)
            (*flag)++;
        else if (ft_strncmp(line, "F", 1) == 0)
            (*flag)++;
        else if (ft_strncmp(line, "NO", 2) == 0)
            (*flag)++;
        else if (ft_strncmp(line, "SO", 2) == 0)
            (*flag)++;
        else if (ft_strncmp(line, "WE", 2) == 0)
            (*flag)++;
        else if (ft_strncmp(line, "EA", 2) == 0)
            (*flag)++;
        (*count)++;
        free(line);
    }
    if (line)
        free(line);
}

void count_empty_lines(int fd, int *count)
{
    char *line;

    while ((line = get_next_line(fd)) && ft_strncmp(line, "\n", 1) == 0)
    {
        (*count)++;
        free(line);
    }
    if (line)
        free(line);
}

void map_position(t_data *data, char *file)
{
    int flag;
    int count;
    int fd;

    count = 0;
    flag = 0;
    fd = open(file, O_RDONLY);
    count_config_lines(data, fd, &count, &flag);
    count_empty_lines(fd, &count);
    count++;
    close(fd);
    data->map_position = count;
}
