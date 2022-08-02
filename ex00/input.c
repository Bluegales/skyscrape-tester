/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:21:12 by pfuchs            #+#    #+#             */
/*   Updated: 2022/02/13 15:04:34 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	functions that test the validity of the given arguments
//	and copy them into an array

int	check_input(int argc, char **argv, int visibility_input[])
{
	int		i;
	char	*input;

	if (argc != 2)
		return (1);
	input = argv[1];
	i = 0;
	while (i < 16)
	{
		if (input[i * 2] < '1' || input[i * 2] > '4')
			return (1);
		visibility_input[i] = input[i * 2] - '0';
		if (i != 15)
			if (input[i * 2 + 1] != ' ')
				return (1);
		i++;
	}
	if (input[31] != '\0')
		return (1);
	return (0);
}
