#include "cub3d.h"

int	count_lines(char *map_path)
{
	int	i;
	int	fd;
	char *buff;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cub3d: Error: invalid fd\n", 25);
		return (-1);
	}
	i = 0;
	while (1)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		free(buff);
		i++;
	}
	close(fd);
	return (i);
}

void remove_endl(t_map *map)
{
	int i;
	char **map_read;

	i = 0;
	map_read = (char **)malloc(sizeof(char *) * (map->file_lines + 1));
	while (i < map->file_lines)
	{
		map_read[i] = ft_strdup_no_endl(map->file_read[i]);
		i++;
	}
	map_read[i] = NULL;
	free_array(map->file_read);
	map->file_read = map_read;
}

void get_textures_path(t_map *map)
{
	int i;

	i = -1;
	map->textures = (char **)malloc(sizeof(char *) * 5);
	while (map->file_read[++i] != NULL)
	{
		if (ft_strnstr(map->file_read[i], "NO ", ft_strlen(map->file_read[i])) != NULL)
			map->textures[NO] = ft_strdup(map->file_read[i]);
		else if (ft_strnstr(map->file_read[i], "SO ", ft_strlen(map->file_read[i])) != NULL)
			map->textures[SO] = ft_strdup(map->file_read[i]);
		else if (ft_strnstr(map->file_read[i], "WE ", ft_strlen(map->file_read[i])) != NULL)
			map->textures[WE] = ft_strdup(map->file_read[i]);
		else if (ft_strnstr(map->file_read[i], "EA ", ft_strlen(map->file_read[i])) != NULL)
			map->textures[EA] = ft_strdup(map->file_read[i]);
	}
	map->textures[4] = NULL;
}

void get_colors(t_map *map)
{
	int i;

	i = -1;
	map->colors = (char **)malloc(sizeof(char *) * 3);
	while (map->file_read[++i] != NULL)
	{
		if (ft_strnstr(map->file_read[i], "F ", ft_strlen(map->file_read[i])) != NULL)
			map->colors[0] = ft_strdup(map->file_read[i]);
		else if (ft_strnstr(map->file_read[i], "C ", ft_strlen(map->file_read[i])) != NULL)
			map->colors[1] = ft_strdup(map->file_read[i]);
	}
	map->colors[2] = NULL;
}


static int is_element(char *line)
{
	if (ft_strnstr(line, "NO ",  ft_strlen(line)) != NULL\
	 || ft_strnstr(line, "SO ", ft_strlen(line)) != NULL\
	|| ft_strnstr(line, "WE ", ft_strlen(line)) != NULL\
	 || ft_strnstr(line, "EA ", ft_strlen(line)) != NULL\
	|| ft_strnstr(line, "F ", ft_strlen(line)) != NULL\
	 || ft_strnstr(line, "C ", ft_strlen(line)) != NULL)
	{
		return (1);
	}
	return (0);
}

void get_map(t_map *map)
{
	int i;
	int flag;
	int len;
	int j;

	i = 0;
	flag = 0;
	while(map->file_read[i])
	{
		if (is_element(map->file_read[i]))
			flag++;
		i++;
		if (flag == 6)
		{
			while (map->file_read[i][0] == '\0'\
			 && map->file_read[i] != NULL)
				i++;
			break;
		}
	}
	len = map->file_lines - i;
	map->map = (char **)malloc(sizeof(char *) * (len + 1));
	j = 0;
	while (j < len)
		map->map[j++] = ft_strdup(map->file_read[i++]);
	map->map[j] = NULL;
}

void read_map(char *map_path, t_map *map)
{
	int i;
	int fd;

	i = 0;
	fd = open(map_path, O_RDONLY);
	map->file_lines = count_lines(map_path);
	map->file_read = (char **)malloc(sizeof(char *) * (map->file_lines + 1));
	while (i < map->file_lines)
	{
		map->file_read[i] = get_next_line(fd);
		i++;
	}
	map->file_read[i] = NULL;
	close(fd);
	remove_endl(map);
	get_textures_path(map);
	get_colors(map);
	get_map(map);
}
