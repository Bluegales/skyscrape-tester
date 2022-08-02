/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:44:45 by pfuchs            #+#    #+#             */
/*   Updated: 2022/02/13 15:38:02 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	functions that test the validity of the given input from their respective
//	direction

//						map[16]							visibility_input[16]
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

//
//	Calculates the visibility of a single line and compares it with the input
//	Checks if all the numbers are present in a single line
//
int	check_line(int line[], int map[], int visible_input);

int	is_left_correct(int i, int map[], int visibility_input[]);
int	is_right_correct(int i, int map[], int visibility_input[]);
int	is_up_correct(int i, int map[], int visibility_input[]);
int	is_down_correct(int i, int map[], int visibility_input[]);

int	check_line(int line[], int map[], int visible_input)
{
	int	visible;
	int	highest;
	int	i;

	visible = 0;
	highest = -1;
	i = 0;
	while (i < 4)
	{
		if (highest < map[line[i]])
		{
			visible++;
			highest = map[line[i]];
		}
		i++;
	}
	if (visible != visible_input)
		return (0);
	if ((map[line[0]] + 1)
		* (map[line[1]] + 1)
		* (map[line[2]] + 1)
		* (map[line[3]] + 1) != 120)
		return (0);
	return (1);
}

int	is_left_correct(int i, int map[], int visibility_input[])
{
	int	line[4];

	line[0] = 4 * i + 0;
	line[1] = 4 * i + 1;
	line[2] = 4 * i + 2;
	line[3] = 4 * i + 3;
	return (check_line(line, map, visibility_input[8 + i]));
}

int	is_right_correct(int i, int map[], int visibility_input[])
{
	int	line[4];

	line[0] = 4 * i + 3;
	line[1] = 4 * i + 2;
	line[2] = 4 * i + 1;
	line[3] = 4 * i + 0;
	return (check_line(line, map, visibility_input[12 + i]));
}

int	is_up_correct(int i, int map[], int visibility_input[])
{
	int	line[4];

	line[0] = i + 0;
	line[1] = i + 4;
	line[2] = i + 8;
	line[3] = i + 12;
	return (check_line(line, map, visibility_input[i]));
}

int	is_down_correct(int i, int map[], int visibility_input[])
{
	int	line[4];

	line[0] = i + 12;
	line[1] = i + 8;
	line[2] = i + 4;
	line[3] = i + 0;
	return (check_line(line, map, visibility_input[4 + i]));
}
