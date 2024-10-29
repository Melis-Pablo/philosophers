/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pullers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:24:32 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/12 20:09:25 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
pull_death_time(): Returns the time in milliseconds a philosopher when a
					philosopher will die if he doesn't eat.

Parameters: data - A pointer to the data structure that holds
					the simulation data.

Return value: The time in milliseconds a philosopher will die if he doesn't eat.

How it works:
1. Locks the mutex associated with the time to die data.
2. Reads the time to die data.
3. Unlocks the mutex.
4. Returns the time to die data.
*/
u_int64_t	pull_death_time(t_data *data)
{
	u_int64_t	ms_todie;

	pthread_mutex_lock(&data->ms_todie_mu);
	ms_todie = data->ms_todie;
	pthread_mutex_unlock(&data->ms_todie_mu);
	return (ms_todie);
}

/*
pull_sleep_time(): Returns the time in milliseconds a philosopher will sleep.

Parameters: data - A pointer to the data structure that holds
					the simulation data.

Return value: The time in milliseconds a philosopher will sleep.

How it works:
1. Locks the mutex associated with the time to sleep data.
2. Reads the time to sleep data.
3. Unlocks the mutex.
4. Returns the time to sleep data.
*/
u_int64_t	pull_sleep_time(t_data *data)
{
	u_int64_t	ms_tosleep;

	pthread_mutex_lock(&data->ms_tosleep_mu);
	ms_tosleep = data->ms_tosleep;
	pthread_mutex_unlock(&data->ms_tosleep_mu);
	return (ms_tosleep);
}

/*
pull_eat_time(): Returns the time in milliseconds a philosopher will eat.

Parameters: data - A pointer to the data structure that holds
				the simulation data.

Return value: The time in milliseconds a philosopher will eat.

How it works:
1. Locks the mutex associated with the time to eat data.
2. Reads the time to eat data.
3. Unlocks the mutex.
4. Returns the time to eat data.
*/
u_int64_t	pull_eat_time(t_data *data)
{
	u_int64_t	ms_toeat;

	pthread_mutex_lock(&data->ms_toeat_mu);
	ms_toeat = data->ms_toeat;
	pthread_mutex_unlock(&data->ms_toeat_mu);
	return (ms_toeat);
}

/*
pull_last_meal(): Returns the time of the last meal of a philosopher.

Parameters: philo - A pointer to the philosopher structure.

Return value: The time of the last meal of the philosopher.

How it works:
1. Locks the mutex associated with the last meal data of the philosopher.
2. Reads the last meal data of the philosopher.
3. Unlocks the mutex.
4. Returns the last meal data.
*/
u_int64_t	pull_last_meal(t_philo *philo)
{
	u_int64_t	last_meal;

	pthread_mutex_lock(&philo->last_meal_mu);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mu);
	return (last_meal);
}

/*
pull_start_time(): Returns the start time of the simulation.

Parameters: data - A pointer to the data structure that holds
			the simulation data.

Return value: The start time of the simulation.

How it works:
1. Locks the mutex associated with the start time data.
2. Reads the start time data.
3. Unlocks the mutex.
4. Returns the start time data.
*/
u_int64_t	pull_start_time(t_data *data)
{
	u_int64_t	time;

	pthread_mutex_lock(&data->start_time_mu);
	time = data->start_time;
	pthread_mutex_unlock(&data->start_time_mu);
	return (time);
}
