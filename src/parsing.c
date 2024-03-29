/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:20:03 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/28 17:26:37 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_texture(t_game *game, char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (ft_strcmp(parts[0], "NO") == 0)
		if (load_anim(&game->map.north, 0, 10000, parts + 1, game->mlx) != 0)
			return (1);
	if (ft_strcmp(parts[0], "SO") == 0)
		if (load_anim(&game->map.south, 0, 10000, parts + 1, game->mlx) != 0)
			return (1);
	if (ft_strcmp(parts[0], "WE") == 0)
		if (load_anim(&game->map.west, 0, 10000, parts + 1, game->mlx) != 0)
			return (1);
	if (ft_strcmp(parts[0], "EA") == 0)
		if (load_anim(&game->map.east, 0, 10000, parts + 1, game->mlx) != 0)
			return (1);
	if (ft_strcmp(parts[0], "F") == 0)
		if (load_anim(&game->map.floor, 0, 10000, parts + 1, game->mlx) != 0)
			return (1);
	if (ft_strcmp(parts[0], "C") == 0)
		if (load_anim(&game->map.ceiling, 0, 10000, parts + 1, game->mlx) != 0)
			return (1);
	free_array(parts);
	return (0);
}

int	check_texture(int *counters, char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (ft_strcmp(parts[0], "NO") == 0)
		counters[0]++;
	if (ft_strcmp(parts[0], "SO") == 0)
		counters[1]++;
	if (ft_strcmp(parts[0], "WE") == 0)
		counters[2]++;
	if (ft_strcmp(parts[0], "EA") == 0)
		counters[3]++;
	if (ft_strcmp(parts[0], "F") == 0)
		counters[4]++;
	if (ft_strcmp(parts[0], "C") == 0)
		counters[5]++;
	free_array(parts);
	return (0);
}

int	check_texture_counts(int *counters)
{
	int	i;

	i = 0;
	while (i < 6)
		if (counters[i++] != 1)
			return (1);
	return (0);
}

int	measure_map(t_game *game, int fd)
{
	static int	counters[6] = {0, 0, 0, 0, 0, 0};
	char		*line;

	line = NULL;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_empty_line(line))
			continue ;
		if (ft_isalpha(line[0]))
		{
			line[ft_strlen(line) - 1] = '\0';
			check_texture(counters, line);
			continue ;
		}
		if ((int)ft_strlen(line) > game->map.width)
			game->map.width = ft_strlen(line);
		game->map.height++;
	}
	return (check_texture_counts(counters));
}

int	parse_map(t_game *game, int fd)
{
	char		*line;
	int			y;

	line = NULL;
	y = 0;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_empty_line(line))
			continue ;
		if (ft_isalpha(line[0]))
		{
			line[ft_strlen(line) - 1] = '\0';
			if (parse_texture(game, line) != 0)
				return (1);
			continue ;
		}
		ft_memcpy(game->map.bytes + (game->map.width * y),
			line, ft_strlen(line));
		y++;
	}
	return (0);
}
