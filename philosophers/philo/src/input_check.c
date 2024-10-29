/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:19:15 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/09 20:42:28 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
print_error():	Prints the correct usage of the program and the valid range 
				for each argument.

Parameters: None.

Return value: None.

How it works:	1. Prints the correct usage of the program.
				2. Prints the valid range for each argument.
				3. Prints the conditions under which the simulation stops.
*/
void	print_error(void)
{
	printf("\n./philo ");
	printf("<n_philos> <ms_todie> <ms_toeat> <ms_tosleep> (n_meals)\n\n");
	printf("n_philos: (1-200)\n");
	printf("ms_todie: (60-2147483647)\n");
	printf("ms_toeat: (60-2147483647)\n");
	printf("ms_tosleep: (60-2147483647)\n");
	printf("n_meals(optional): (1-2147483647)\n\n");
	printf("The simulation stops when someone dies or everyone is full.\n\n");
}

/*
ft_atoi():	Converts the initial portion of the string pointed to by str to int.

Parameters:		str - pointer to the string to be converted.

Return value:	int - converted value.

How it works:	1. Skips all white-space characters as defined by isspace().
				2. Checks for an optional sign character.
				3. Converts the initial portion of the string to int.
				4. Returns the converted value.
*/
int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == (' ') || str[i] == ('\t') || str[i] == ('\n')
		|| str[i] == ('\v') || str[i] == ('\f') || str[i] == ('\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + str[i++] - '0';
	return (sign * result);
}

/*
is_digit():		Checks if all command-line arguments are digits.

Parameters:		ac - The count of command-line arguments.
				av - An array of the command-line arguments.

Return value:	1 if any argument is not a digit, 0 otherwise.

How it works:
1. Iterates over all command-line arguments.
2. For each argument, checks each character to see if it's a digit.
3. If a non-digit character is found, returns 1.
4. If no non-digit characters are found in any argument, returns 0.
*/
int	is_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
wrong_input():	Checks if the command-line arguments are valid.

Parameters:		ac - The count of command-line arguments.
				av - An array of the command-line arguments.

Return value:	1 if any argument is invalid, 0 otherwise.

How it works:	1. If there are 6 arguments and the last one is less than
					or equal to 0, returns 1.
				2. If the first argument is less than 1 or greater than 200,
					returns 1.
				3. Iterates over the next 3 arguments, if any is less than 60,
					returns 1.
				4. If no invalid arguments are found, returns 0.
*/
int	wrong_input(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (1);
	if (ft_atoi(av[i]) < 1 || ft_atoi(av[i]) > 200)
		return (1);
	while (++i < 5)
	{
		if (ft_atoi(av[i]) < 60)
			return (1);
	}
	return (0);
}

/*
input_check():	Validates the command-line arguments.

Parameters:		ac - The count of command-line arguments.
				av - An array of the command-line arguments.

Return value:	1 if any argument is invalid, 0 otherwise.

How it works:	1. If the number of arguments is not 5 or 6, returns 1.
				2. Checks if all arguments are digits using is_digit function.
				3. Checks if any argument is invalid using wrong_input function.
				4. If no invalid arguments are found, returns 0.
*/
int	input_check(int ac, char **av)
{
	if (!(ac >= 5 && ac <= 6))
		return (1);
	if (is_digit(ac, av))
		return (1);
	if (wrong_input(ac, av))
		return (1);
	return (0);
}
