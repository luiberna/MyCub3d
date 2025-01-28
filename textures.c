/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:44:25 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/28 17:11:11 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

char **get_textures(char *file)
{
    char *line;
    char **textures;
    int fd;
    int i;

    i = 0;
    textures = malloc((sizeof(char *) * 4));
    fd = open(file, O_RDONLY);
    line = get_next_line(fd);
    while (line && i < 4) {
        if (ft_strncmp(line, "NO", 2) == 0)
            textures[N] = (ft_strtrim(line + 3, "\n"));
        else if (ft_strncmp(line, "EA", 2) == 0)
            textures[E] = (ft_strtrim(line + 3, "\n"));
        else if (ft_strncmp(line, "SO", 2) == 0)
            textures[S] = (ft_strtrim(line + 3, "\n"));
        else if (ft_strncmp(line, "WE", 2) == 0)
            textures[W] = (ft_strtrim(line + 3, "\n"));
        i++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    return textures;
}
