/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:01:29 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/09 19:51:42 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
update_last_meal(): Updates the last meal time of a philosopher.

Parameters: philo - A pointer to the philosopher structure.

Return value: None.

How it works:
1. Locks the mutex associated with the last meal time data of the philosopher.
2. Updates the last meal time data of the philosopher with the current time.
3. Unlocks the mutex.
*/
void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mu);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mu);
}

/*
drop_both(): Drops both forks of a philosopher.

Parameters: philo - A pointer to the philosopher structure.

Return value: None.

How it works:
1. Unlocks the mutex associated with the left fork of the philosopher.
2. Unlocks the mutex associated with the right fork of the philosopher.
*/
void	drop_both(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

/*
update_n_meals(): Updates the number of meals a philosopher has had.

Parameters: philo - A pointer to the philosopher structure.

Return value: None.

How it works:
1. Locks the mutex associated with the number of meals data of the philosopher.
2. Increments the number of meals data of the philosopher.
3. Unlocks the mutex.
*/
void	update_n_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->n_meals_mu);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->n_meals_mu);
}

/*
sleep_for_eating(): Makes a philosopher sleep for the time it takes to eat.

Parameters: philo - A pointer to the philosopher structure.

Return value: None.

How it works:
1. Calls the `ft_usleep` function with the time it takes for a philosopher
	to eat.
*/
void	sleep_for_eating(t_philo *philo)
{
	ft_usleep(pull_eat_time(philo->data));
}
