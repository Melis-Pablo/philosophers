/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:43:28 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/09 20:33:12 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
routine(): The main routine of a philosopher.

Parameters: philo_p - A void pointer to the philosopher structure.
					This is cast to a t_philo pointer within the function.

Return value: NULL.

How it works:
1. Updates the philosopher's last meal time.
2. If the philosopher's ID is even, the philosopher sleeps for a short
	duration to avoid deadlock.
3. Enters a loop that continues until the philosopher's state is DEAD.
4. In each iteration of the loop:
	- The philosopher attempts to eat. If unsuccessful, breaks the loop.
	- Checks if the philosopher's state is DEAD. If so, breaks the loop.
	- The philosopher sleeps. If the philosopher dies during sleep,
		breaks the loop.
	- Checks if the philosopher's state is DEAD. If so, breaks the loop.
	- The philosopher thinks. If the philosopher dies during thinking,
		breaks the loop.
*/
void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	update_last_meal(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->ms_toeat - 10);
	while (pull_philo_state(philo) != DEAD)
	{
		if (eat(philo))
			break ;
		if (pull_philo_state(philo) == DEAD)
			break ;
		if (ft_sleep(philo))
			break ;
		if (pull_philo_state(philo) == DEAD)
			break ;
		if (think(philo))
			break ;
	}
	return (NULL);
}

/*
all_full_routine(): Checks if all philosophers have eaten the required number
					of meals.

Parameters: data_p - A void pointer to the data structure.
			This is cast to a t_data pointer within the function.

Return value: NULL.

How it works:
1. Retrieves the number of philosophers.
2. Enters a loop that continues until all philosophers have eaten the
	required number of meals.
3. In each iteration of the loop:
	- Sleeps for 1 millisecond.
	- Checks if the current philosopher has eaten the required number of meals.
		If not, resets the index to -1.
4. If all philosophers have eaten the required number of meals,
	sets the keep_iter flag to 0 and notifies all philosophers.
*/
void	*all_full_routine(void *data_p)
{
	t_data	*data;
	int		i;
	int		n_philo;

	data = (t_data *)data_p;
	i = -1;
	n_philo = pull_n_philos(data);
	while (++i < n_philo && pull_keep_iter(data))
	{
		usleep(1000);
		if (!is_full(data, &data->philo[i]))
			i = -1;
	}
	if (pull_keep_iter(data))
	{
		push_keep_iter(data, 0);
		notify_all(data);
	}
	return (NULL);
}

/*
all_alive_routine(): Checks if all philosophers are alive.

Parameters: data_p - A void pointer to the data structure.
			This is cast to a t_data pointer within the function.

Return value: NULL.

How it works:
1. Retrieves the number of philosophers.
2. Enters a loop that continues until a philosopher dies
	or all philosophers have stopped eating.
3. In each iteration of the loop:
	- Checks if the current philosopher is dead. If so, prints a message,
	stops all philosophers from eating, notifies all philosophers,
	and breaks the loop.
	- If the end of the philosopher array is reached, resets the index to -1.
	- Sleeps for 1 millisecond.
*/
void	*all_alive_routine(void *data_p)
{
	int		i;
	int		n_philos;
	t_data	*data;
	t_philo	*philo;

	i = -1;
	data = (t_data *)data_p;
	philo = data->philo;
	n_philos = pull_n_philos(data);
	while (++i < n_philos && pull_keep_iter(data))
	{
		if (philo_death(&philo[i]) && pull_keep_iter(data))
		{
			print_changestate(data, philo[i].id, "died");
			push_keep_iter(data, 0);
			notify_all(data);
			break ;
		}
		if (i == n_philos - 1)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}
