/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_pullers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:50:23 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/09 19:20:33 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
pull_n_meals_had(): Returns the number of meals a philosopher has had.

Parameters: philo - A pointer to the philosopher structure.

Return value: The number of meals the philosopher has had.

How it works:
1. Locks the mutex associated with the number of meals data of the philosopher.
2. Reads the number of meals data of the philosopher.
3. Unlocks the mutex.
4. Returns the number of meals data.
*/
int	pull_n_meals_had(t_philo *philo)
{
	int	n_meals;

	pthread_mutex_lock(&philo->n_meals_mu);
	n_meals = philo->n_meals;
	pthread_mutex_unlock(&philo->n_meals_mu);
	return (n_meals);
}

/*
pull_n_philos(): Returns the number of philosophers in the simulation.

Parameters: data - A pointer to the data structure that holds
				the simulation data.

Return value: The number of philosophers in the simulation.

How it works:
1. Locks the mutex associated with the number of philosophers data.
2. Reads the number of philosophers data.
3. Unlocks the mutex.
4. Returns the number of philosophers data.
*/
int	pull_n_philos(t_data *data)
{
	int	n_philos;

	pthread_mutex_lock(&data->n_philos_mu);
	n_philos = data->n_philos;
	pthread_mutex_unlock(&data->n_philos_mu);
	return (n_philos);
}

/*
pull_keep_iter(): Returns the keep_iter flag of the simulation.

Parameters: data - A pointer to the data structure that holds
				the simulation data.

Return value: The keep_iter flag of the simulation.

How it works:
1. Locks the mutex associated with the keep_iter data.
2. Reads the keep_iter data.
3. Unlocks the mutex.
4. Returns the keep_iter data.
*/
int	pull_keep_iter(t_data *data)
{
	int	keep_iter;

	pthread_mutex_lock(&data->keep_iter_mu);
	keep_iter = data->keep_iter;
	pthread_mutex_unlock(&data->keep_iter_mu);
	return (keep_iter);
}

/*
pull_philo_state(): Returns the state of a philosopher.

Parameters: philo - A pointer to the philosopher structure.

Return value: The state of the philosopher.

How it works:
1. Locks the mutex associated with the state data of the philosopher.
2. Reads the state data of the philosopher.
3. Unlocks the mutex.
4. Returns the state data.
*/
t_state	pull_philo_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->state_mu);
	state = philo->state;
	pthread_mutex_unlock(&philo->state_mu);
	return (state);
}
