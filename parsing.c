#include "../incs/cub3d.h"

static bool	check_spaces(char **matrix)
{
	int i;
	int j;

	i = -1;
	while (matrix[++i])
	{
		j = 0;
		while (matrix[i][j] == ' ')
			j++;
		while (matrix[i][j])
		{
			if (matrix[i][j] == ' ')
				if (matrix[i][j - 1] != '1' && matrix[i][j] - 1 != ' ' 
			 	&& matrix[i][j + 1] && matrix[i][j + 1] != ' ' 
				&& matrix[i][j + 1] != '1'
			 	&& matrix[i + 1][j] && matrix[i + 1][j] != ' ' 
				&& matrix[i + 1][j] != '1'
			 	&& matrix[i - 1] && matrix[i - 1][j] != ' ' 
				&& matrix[i - 1][j] != '1')
						return (printf("Error\n invalid map spaces"), FALSE);
			j++;
		}
	}
	return (TRUE);
}

bool	parse_map(t_data *data)
{
	int row;
	int col;

	row = -1;
	col = -1;

	if (check_spaces(data->map->matrix) == FALSE)
		return (FALSE);

	// while (data->map.matrix[++row])
	// {
	// 	while (data->map.matrix[row][col])
	// }
	return (TRUE);
}

/*bool	parse_map(t_data *data)*/
/*{*/
/*	int		row;*/
/*	int		col;*/
/*	bool	is_valid;*/
/**/
/*	is_valid = FALSE;*/
/*	row = 0;*/
/*	col = 0;*/
/*	while (data->map.matrix[row][col] == ' ')*/
/*	{*/
/*		if (data->map.matrix[row + 1][col] == '1')*/
/*			row++;*/
/*		else*/
/*			col++;*/
/*	}*/
/*	int *start_pos = malloc(sizeof(int) * 2);*/
/*	start_pos[0] = row;*/
/*	start_pos[1] = col;*/
/*	while (data->map.matrix[row][col] == '1')*/
/*	{*/
/*		while (data->map.matrix[row][col + 1] == '1')*/
/*		{*/
/*			data->map.matrix[row][col] = 2;*/
/*			col++;*/
/*		}*/
/*		while (col > 0 && data->map.matrix[row][col - 1] == '1' )*/
/*		{*/
/*			data->map.matrix[row][col] = 2;*/
/*			col--;*/
/*		}*/
/*		if (row + 1 < data->map.max_height && data->map.matrix[row + 1][col] == '1' )*/
/*		{*/
/*			data->map.matrix[row][col] = 2;*/
/*			row++;*/
/*			continue;*/
/*		}*/
/*		if (row > 0 && data->map.matrix[row - 1][col] == '1' )*/
/*		{*/
/*			data->map.matrix[row][col] = 2;*/
/*			row--;*/
/*			continue;*/
/*		}*/
/*		if (col > 0 && ((data->map.matrix[row][col -1] == 2 && data->map.matrix[row][col + 1] == '\0') */
/*			|| (data->map.matrix[row][col - 1] == '1' && data->map.matrix[row][col + 1] == '\0')))*/
/*		{*/
/*		 data->map.matrix[row][col] = 2;*/
/*		 col--;*/
/*		 	continue;*/
/*		 }*/
/*		if (data->map.matrix[row][col + 1] == 2 && data->map.matrix[row][col - 1] == '\0') */
/*			|| (data->map.matrix[row][col + 1] == '1' && data->map.matrix[row][col - 1] == '\0'))*/
/*		{*/
/*		 data->map.matrix[row][col] = 2;*/
/*		 col++;*/
/*		 continue;*/
/*		}*/
/*		else if ((data->map.matrix[row - 1][col] == 2 && row == start_pos[0] - 1 && col == start_pos[1]) */
/*			|| (data->map.matrix[row][col] == 2 && row == start_pos[0] && col == start_pos[1]))*/
/*			return (is_valid = TRUE);*/
/*		else*/
/*			break;*/
/*	}*/
/*	return (is_valid);*/
/*}*/
// @brief	Function to check if the map is valid
// @param	data	Pointer to the data structure
// @return	Returns true if the map is valid, false otherwise
// @note i = -2 because of the first and last line

static int	size_map(char *file)
{
	int fd;
	int i;
	char	*line;


	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	i = -2;
	line = get_next_line(fd);
	i++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd), i);
}

void	copy_map(t_data *data, char *file)
{
	int		i;
	int		fd;
	char	*line;
	
	fd = open(file, O_RDONLY);
	i = (size_map(file) - data->map_data.line_position);
	data->map->max_height = i;
	data->map->map = malloc(sizeof(t_map) * i);
	data->map->matrix = malloc(sizeof(t_map) * i);
	i = -1;
	while (i++ <= data->map_data.line_position)
		line = get_next_line(fd);
	i = 0;
	while (line)
	{
		data->map->map[i] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		data->map->matrix[i] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		data->map->map[i] = line;
		data->map->matrix[i] = line;
		line = get_next_line(fd);
		i++;
	}
	data->map->map[i] = NULL;
	data->map->matrix[i] = NULL;
	close(fd);
}
