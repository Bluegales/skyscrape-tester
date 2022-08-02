/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:19:54 by pfuchs            #+#    #+#             */
/*   Updated: 2022/02/16 10:45:17 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_left_correct(int i, int map[], int visibility_input[]);
int	is_right_correct(int i, int map[], int visibility_input[]);
int	is_up_correct(int i, int map[], int visibility_input[]);
int	is_down_correct(int i, int map[], int visibility_input[]);

int	check_input(int argc, char **argv, int visibility_input[]);

//		+--------+------+------+------+------+		+----+---+---+---+---+----+
//		|        | Col0 | Col1 | Col2 | Col3 |		|    | 0 | 1 | 2 | 3 |    |
//		|        |      |      |      |      |		|    |   |   |   |   |    |
//		+--------+------+------+------+------+		+----+---+---+---+---+----+
//		| Row0   |   0  |   1  |   2  |   3  |		|  8 |   |   |   |   | 12 |
//		+--------+------+------+------+------+		+----+---+---+---+---+----+
//		| Row1   |   4  |   5  |   6  |   7  |		|  9 |   |   |   |   | 13 |
//		+--------+------+------+------+------+		+----+---+---+---+---+----+
//		| Row2   |   8  |   9  |  10  |  11  |		| 10 |   |   |   |   | 14 |
//		+--------+------+------+------+------+		+----+---+---+---+---+----+
//		| Row3   |  12  |  13  |  14  |  15  |		| 11 |   |   |   |   | 15 |
//		+--------+------+------+------+------+		+----+---+---+---+---+----+
//		|        |      |      |      |      |		|    | 4 | 5 | 6 | 7 |    |
//		+--------+------+------+------+------+		+----+---+---+---+---+----+

//const combinations[24][4] = {1,2,3,4},{1,2,4,3},{1,2};

void	write_map(int map[])
{
	int		i;
	char	map_print[8 * 4];

	i = 0;
	while (i < 8 * 4)
	{
		map_print[i] = ' ';
		i++;
	}
	i = 0;
	while (i < 4)
	{
		map_print[8 * i + 0] = map[4 * i] + '0';
		map_print[8 * i + 2] = map[4 * i + 1] + '0';
		map_print[8 * i + 4] = map[4 * i + 2] + '0';
		map_print[8 * i + 6] = map[4 * i + 3] + '0';
		map_print[8 * i + 7] = '\n';
		i++;
	}
	write(1, map_print, 8 * 4);
}

void	change_map(int map_hash, int map[])
{
	int			i;
	int			line_hash[4];
	const int	combinations[24][4] = {{1, 2, 3, 4}, {1, 2, 4, 3},
	{1, 3, 2, 4}, {1, 3, 4, 2}, {1, 4, 2, 3}, {1, 4, 3, 2},
	{2, 1, 3, 4}, {2, 1, 4, 3}, {2, 3, 1, 4}, {2, 3, 4, 1},
	{2, 4, 1, 3}, {2, 4, 3, 1},
	{3, 2, 1, 4}, {3, 2, 4, 1}, {3, 1, 2, 4}, {3, 1, 4, 2},
	{3, 4, 2, 1}, {3, 4, 1, 2},
	{4, 2, 3, 1}, {4, 2, 1, 3}, {4, 3, 2, 1}, {4, 3, 1, 2},
	{4, 1, 2, 3}, {4, 1, 3, 2}};

	i = 0;
	line_hash[0] = map_hash % 24;
	line_hash[1] = map_hash / 24 % 24;
	line_hash[2] = map_hash / (24 * 24) % 24;
	line_hash[3] = map_hash / (24 * 24 * 24) % 24;
	while (i < 4)
	{
		map[0 + i] = combinations[line_hash[0]][i];
		map[4 + i] = combinations[line_hash[1]][i];
		map[8 + i] = combinations[line_hash[2]][i];
		map[12 + i] = combinations[line_hash[3]][i];
		i++;
	}
}

int	check_map(int map[], int visibility_input[])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!is_left_correct(i, map, visibility_input)
			|| !is_right_correct(i, map, visibility_input)
			|| !is_up_correct(i, map, visibility_input)
			|| !is_down_correct(i, map, visibility_input))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int	visibility_input[16];
	int	map[16];
	int	i;

	i = 0;
	if (check_input(argc, argv, visibility_input) == 1)
	{
		write(1, "Error Input\n", 12);
		return (0);
	}
	while (i < 331776)
	{
		change_map(i, map);
		if (check_map(map, visibility_input))
		{
			write_map(map);
			return (0);
		}
	i++;
	}
	write(1, "Error\n", 6);
	return (0);
}
