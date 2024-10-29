/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:43:33 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/12 20:08:03 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
is_full(): Checks if a philosopher has eaten the required number of meals.

Parameters: 
- data: A pointer to the data structure.
- philo: A pointer to the philosopher structure.

Return value: 1 if the philosopher has eaten the required number of meals,
				0 otherwise.

How it works:
1. Compares the number of meals the philosopher has had with the required
	number of meals.
2. Returns 1 if the philosopher has had enough meals, 0 otherwise.
*/
int	is_full(t_data *data, t_philo *philo)
{
	int	result;

	result = 0;
	if (pull_n_meals_had(philo) >= data->n_meals)
		result = 1;
	return (result);
}

/*
philo_death(): Checks if a philosopher is dead.

Parameters: philo - A pointer to the philosopher structure.

Return value: 1 if the philosopher is dead, 0 otherwise.

How it works:
1. Checks if the time since the philosopher's last meal is greater than the
	time it takes for a philosopher to die and the philosopher is not eating.
2. If so, sets the philosopher's state to DEAD and returns 1.
3. If not, returns 0.
*/
int	philo_death(t_philo *philo)
{
	int		result;
	t_data	*data;

	data = philo->data;
	result = 0;
	if (get_time() - pull_last_meal(philo) > pull_death_time(data)
		&& pull_philo_state(philo) != EATING)
	{
		push_philo_state(philo, DEAD);
		result = 1;
	}
	return (result);
}

/*
notify_all(): Sets all philosophers' state to DEAD.

Parameters: data - A pointer to the data structure.

Return value: None.

How it works:
1. Iterates over each philosopher and sets their state to DEAD.
*/
void	notify_all(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		n_philos;

	n_philos = pull_n_philos(data);
	philo = data->philo;
	i = -1;
	while (++i < n_philos)
		push_philo_state(&philo[i], DEAD);
}

/*
get_time(): Gets the current time.

Parameters: None.

Return value: The current time in milliseconds.

How it works:
1. Calls the gettimeofday function to get the current time.
2. Converts the time to milliseconds and returns it.
*/
u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

/*
ft_usleep(): Pauses the execution of the program for a specified amount of time.

Parameters: sleep_time - The amount of time to sleep in milliseconds.

Return value: None.

How it works:
1. Gets the start time.
2. Continuously checks if the time since the start time is less than the
	sleep time.
3. If so, sleeps for 500 microseconds.
*/
void	ft_usleep(u_int64_t sleep_time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}
