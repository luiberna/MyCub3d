/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:44:25 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/07 16:45:05 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void img_to_texture_buff(t_cube *cube, t_data *data, t_image *img, int dir)
{
    int *pixels;
    int i;
    int j;

    pixels = ft_calloc(img->width * img->height, sizeof(int));
    if (!pixels)
        print_error(cube, "Error: Could not allocate pixels\n");
    i = 0;
    while (i < img->height)
    {
        j = 0;
        while (j < img->width)
        {
            pixels[i * img->width + j] = ((int *)img->addr)[i * img->width + j];
            j++;
        }
        i++;
    }
    if (data->texture_buffer[dir])
        free(data->texture_buffer[dir]);
    data->texture_buffer[dir] = pixels;
}

char *get_texture_loc(char *line)
{
    char *location;
    int i;
    int j;

    i = 0;
    j = 0;
    location = ft_calloc(ft_strlen(line) + 1, sizeof(char));
    while (line[i])
    {
        if (line[i] != ' ')
        {
            location[j] = line[i];
            j++;
        }
        i++;
    }
    free(line);
    return location;
}

char **get_textures(char *file)
{
    char *line;
    char **textures;
    int fd;
    int i;

    textures = ft_calloc(sizeof(char *), 4);
    fd = open(file, O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        if (ft_strncmp(line, "NO", 2) == 0) 
            textures[N] = get_texture_loc(ft_strtrim(line + 3, "\n"));
        else if (ft_strncmp(line, "EA", 2) == 0)
            textures[E] = get_texture_loc(ft_strtrim(line + 3, "\n"));
        else if (ft_strncmp(line, "SO", 2) == 0)
            textures[S] = get_texture_loc(ft_strtrim(line + 3, "\n"));
        else if (ft_strncmp(line, "WE", 2) == 0)
            textures[W] = get_texture_loc(ft_strtrim(line + 3, "\n"));
        i++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    return textures;
}

void	load_textures(t_cube *cube, t_data *data)
{
	t_image 	tmp;
	int		i;

	i = 0;
	while(i < 4)
	{	
		tmp.img = mlx_xpm_file_to_image(cube->mlx, data->textures[i], &tmp.width, &tmp.height);
		if(!tmp.img)
			print_error(cube, "Error on file to image\n");
		tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.size_line, &tmp.endian);
		if(!tmp.addr)
			print_error(cube, "Error on get data Addr\n");
		img_to_texture_buff(cube, data, &tmp, i);
		mlx_destroy_image(cube->mlx, tmp.img);
        i++;
	}
}
