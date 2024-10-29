/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:58:04 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/12 20:05:45 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
drop_left(): Drops the left fork of a philosopher.

Parameters: philo - A pointer to the philosopher structure.

Return value: None.

How it works:
1. Unlocks the mutex associated with the left fork of the philosopher.
*/
void	drop_left(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
}

/*
drop_right(): Drops the right fork of a philosopher.

Parameters: philo - A pointer to the philosopher structure.

Return value: None.

How it works:
1. Unlocks the mutex associated with the right fork of the philosopher.
*/
void	drop_right(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_f);
}

/*
take_left(): A philosopher attempts to take the left fork.

Parameters: philo - A pointer to the philosopher structure.

Return value: 1 if the philosopher is dead or dying, 0 otherwise.

How it works:
1. Checks if the philosopher is dead or dying.
2. If not, locks the mutex associated with the left fork of the philosopher.
3. Prints a message indicating the philosopher has taken a fork.
*/
int	take_left(t_philo *philo)
{
	if (philo_death(philo) || pull_philo_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->left_f);
	print_changestate(philo->data, philo->id, "has taken a fork");
	return (0);
}

/*
take_right(): A philosopher attempts to take the right fork.

Parameters: philo - A pointer to the philosopher structure.

Return value: 1 if the philosopher is dead or dying, 0 otherwise.

How it works:
1. Checks if the philosopher is dead or dying.
2. If not, locks the mutex associated with the right fork of the philosopher.
3. Prints a message indicating the philosopher has taken a fork.
*/
int	take_right(t_philo *philo)
{
	if (philo_death(philo) || pull_philo_state(philo) == DEAD)
		return (1);
	pthread_mutex_lock(philo->right_f);
	print_changestate(philo->data, philo->id, "has taken a fork");
	return (0);
}

/*
take_both(): A philosopher attempts to take both forks.

Parameters: philo - A pointer to the philosopher structure.

Return value: 1 if the philosopher is unable to take both forks, 0 otherwise.

How it works:
1. Checks if there is only one philosopher.
	If so, handles this special case by calling `handle_1`.
2. Attempts to take the right fork by calling `take_right`.
	If unsuccessful, returns 1.
3. Attempts to take the left fork by calling `take_left`.
	If unsuccessful, drops the right fork by calling `drop_right` and returns 1.
4. If both forks are successfully taken, returns 0.
*/
int	take_both(t_philo *philo)
{
	if (pull_n_philos(philo->data) == 1)
		return (handle_1(philo));
	if (philo->id % 2 == 0)
	{
		if (take_right(philo) != 0)
			return (1);
		if (take_left(philo) != 0)
		{
			drop_right(philo);
			return (1);
		}
	}
	else
	{
		if (take_left(philo) != 0)
			return (1);
		if (take_right(philo) != 0)
		{
			drop_left(philo);
			return (1);
		}
	}
	return (0);
}
