/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:29:24 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/12 20:09:23 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
handle_1(): Handles the scenario where there is only one philosopher.

Parameters: philo - A pointer to the philosopher structure.

Return value: Always returns 1.

How it works: 
1. The philosopher takes the left fork using the `take_left` function.
2. The philosopher sleeps for the amount of time to die
	using the `ft_usleep` function and `pull_death_time` function.
3. The philosopher's state is set to DEAD using the `push_philo_state` function.
*/
int	handle_1(t_philo *philo)
{
	take_left(philo);
	ft_usleep(pull_death_time(philo->data));
	push_philo_state(philo, DEAD);
	drop_left(philo);
	return (1);
}

/*
n_meal_trigger(): Checks if the number of meals is greater than 0.

Parameters: data - A pointer to the data structure that holds
				the simulation data.

Return value: 1 if the number of meals is greater than 0, otherwise 0.

How it works: 
1. Checks if the number of meals in the data structure is greater than 0.
2. If it is, returns 1.
3. If it's not, returns 0.
*/
int	n_meal_trigger(t_data *data)
{
	if (data->n_meals > 0)
		return (1);
	return (0);
}

/*
print_changestate(): Prints a message about a philosopher's state change with
						mutual exclusion.

Parameters: data - A pointer to the data structure that holds
					the simulation data.
            id - The id of the philosopher.
            msg - The message to be printed.

Return value: None.

How it works:
1. Calculates the time since the start of the simulation.
2. Locks the print mutex.
3. If the simulation is still running, prints the time, philosopher id,
	and message.
4. Unlocks the print mutex.
*/
void	print_changestate(t_data *data, int id, char *msg)
{
	u_int64_t	time;

	pthread_mutex_lock(&data->print_mu);
	time = get_time() - pull_start_time(data);
	if (pull_keep_iter(data))
		printf("%llu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->print_mu);
}
