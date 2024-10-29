/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:49:09 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/09 19:45:28 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
push_philo_state(): Sets the state of a philosopher.

Parameters: philo - A pointer to the philosopher structure.
            state - The state to set the philosopher to.

Return value: None.

How it works:
1. Locks the mutex associated with the state data of the philosopher.
2. If the philosopher is not dead, sets the state data of the philosopher.
3. Unlocks the mutex.
*/
void	push_philo_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->state_mu);
	if (philo->state != DEAD)
		philo->state = state;
	pthread_mutex_unlock(&philo->state_mu);
}

/*
push_keep_iter(): Sets the keep_iter flag of the simulation.

Parameters: data - A pointer to the data structure that holds
				the simulation data.
            set_to - The value to set the keep_iter flag to.

Return value: None.

How it works:
1. Locks the mutex associated with the keep_iter data.
2. Sets the keep_iter data.
3. Unlocks the mutex.
*/
void	push_keep_iter(t_data *data, int set_to)
{
	pthread_mutex_lock(&data->keep_iter_mu);
	data->keep_iter = set_to;
	pthread_mutex_unlock(&data->keep_iter_mu);
}
