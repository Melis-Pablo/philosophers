/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:26:21 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/09 20:11:53 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
think(): A philosopher thinks.

Parameters: philo - A pointer to the philosopher structure.

Return value: 1 if the philosopher is dead, 0 otherwise.

How it works:
1. Sets the philosopher's state to THINKING.
2. Checks if the philosopher is dead.
3. If not, prints a message indicating the philosopher is thinking.
*/
int	think(t_philo *philo)
{
	push_philo_state(philo, THINKING);
	if (pull_philo_state(philo) == DEAD)
		return (1);
	print_changestate(philo->data, philo->id, "is thinking");
	return (0);
}

/*
ft_sleep(): A philosopher sleeps.

Parameters: philo - A pointer to the philosopher structure.

Return value: 1 if the philosopher is dead, 0 otherwise.

How it works:
1. Sets the philosopher's state to SLEEPING.
2. Checks if the philosopher is dead.
3. If not, prints a message indicating the philosopher is sleeping.
4. The philosopher sleeps for a certain amount of time.
*/
int	ft_sleep(t_philo *philo)
{
	push_philo_state(philo, SLEEPING);
	if (pull_philo_state(philo) == DEAD)
		return (1);
	print_changestate(philo->data, philo->id, "is sleeping");
	ft_usleep(pull_sleep_time(philo->data));
	return (0);
}

/*
eat(): A philosopher eats.

Parameters: philo - A pointer to the philosopher structure.

Return value: 1 if the philosopher is unable to take both forks, 0 otherwise.

How it works:
1. The philosopher attempts to take both forks.
2. If successful, sets the philosopher's state to EATING.
3. Prints a message indicating the philosopher is eating.
4. Updates the philosopher's last meal time.
5. The philosopher sleeps for the time it takes to eat.
6. Updates the number of meals the philosopher has had.
7. The philosopher drops both forks.
*/
int	eat(t_philo *philo)
{
	if (take_both(philo) != 0)
		return (1);
	push_philo_state(philo, EATING);
	print_changestate(philo->data, philo->id, "is eating");
	update_last_meal(philo);
	sleep_for_eating(philo);
	update_n_meals(philo);
	drop_both(philo);
	return (0);
}

/*
free_data(): Frees the memory allocated for the data structure
				and destroys the mutexes.

Parameters: data - A pointer to the data structure.

Return value: None.

How it works:
1. Retrieves the number of philosophers.
2. Iterates over each philosopher, destroying their individual mutexes.
3. Destroys the mutexes associated with the data structure.
4. Frees the memory allocated for the philosopher threads,
	the philosophers, and the forks.
*/
void	free_data(t_data *data)
{
	int	i;
	int	n_philos;

	i = -1;
	n_philos = pull_n_philos(data);
	while (++i < n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].n_meals_mu);
		pthread_mutex_destroy(&data->philo[i].last_meal_mu);
		pthread_mutex_destroy(&data->philo[i].state_mu);
	}
	pthread_mutex_destroy(&data->ms_toeat_mu);
	pthread_mutex_destroy(&data->ms_todie_mu);
	pthread_mutex_destroy(&data->ms_tosleep_mu);
	pthread_mutex_destroy(&data->keep_iter_mu);
	pthread_mutex_destroy(&data->n_philos_mu);
	pthread_mutex_destroy(&data->start_time_mu);
	pthread_mutex_destroy(&data->print_mu);
	free(data->philo_th);
	free(data->philo);
	free(data->forks);
}
