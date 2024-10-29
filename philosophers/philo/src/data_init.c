/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:30:54 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/09 19:06:28 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
fork_init(): Initializes the forks.

Parameters: data - A pointer to the data structure that holds
				the simulation data.

Return value: 0 if the forks are initialized successfully.

How it works: 
1. Retrieves the philosophers array from the data structure.
2. Initializes a mutex for each fork using the pthread_mutex_init function.
3. Sets the left and right forks for each philosopher.
*/
int	fork_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philo;
	while (++i < data->n_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	philo[0].left_f = &data->forks[0];
	philo[0].right_f = &data->forks[data->n_philos - 1];
	while (++i < data->n_philos)
	{
		philo[i].left_f = &data->forks[i];
		philo[i].right_f = &data->forks[i - 1];
	}
	return (0);
}

/*
philo_init(): Initializes the philosophers.

Parameters: data - A pointer to the data structure that holds
				the simulation data.

Return value: 0 if the philosophers are initialized successfully.

How it works: 
1. Retrieves the philosophers array from the data structure.
2. For each philosopher, sets the data, id, number of meals, and state.
3. Initializes several mutexes for synchronizing access to shared data.
4. Updates the last meal time for each philosopher.
*/
int	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philo;
	while (++i < data->n_philos)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].n_meals = 0;
		philo[i].state = IDLE;
		pthread_mutex_init(&philo[i].state_mu, NULL);
		pthread_mutex_init(&philo[i].n_meals_mu, NULL);
		pthread_mutex_init(&philo[i].last_meal_mu, NULL);
		update_last_meal(&philo[i]);
	}
	return (0);
}

/*
data_malloc(): Allocates memory for the philosophers and their threads.

Parameters: data - A pointer to the data structure that holds
			the simulation data.

Return value: 0 if the memory is allocated successfully, 2 if there's an error.

How it works: 
1. Allocates memory for the philosophers array using the malloc function.
2. If the memory allocation fails, returns 2.
3. Allocates memory for the forks array using the malloc function.
4. If the memory allocation fails, frees the philosophers array and returns 2.
5. Allocates memory for the philosopher threads array using the malloc function.
6. If the memory allocation fails, frees the philosophers and forks arrays
	and returns 2.
7. If the memory is allocated successfully for all arrays, returns 0.
*/
int	data_malloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (data->philo == NULL)
		return (2);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (data->forks == NULL)
		return (free(data->philo), 2);
	data->philo_th = malloc(sizeof(pthread_t) * data->n_philos);
	if (data->philo_th == NULL)
		return (free(data->philo), free(data->forks), 2);
	return (0);
}

/*
data_init(): Initializes the data structure for the simulation.

Parameters: data - A pointer to the data structure that holds the
				simulation data.
            ac - The count of command-line arguments.
            av - An array of the command-line arguments.

Return value:	0 if the data structure is initialized successfully,
				1 if there's an error.

How it works: 
1. Sets the keep_iter field to 1.
2. Sets the number of philosophers, time to die, time to eat, and time to sleep 
	from the command-line arguments.
3. If the number of meals is specified in the command-line arguments, sets it.
4. Initializes several mutexes for synchronizing access to shared data.
5. Calls the data_malloc function to allocate memory for the philosophers
	and their threads.
*/
int	data_init(t_data *data, int ac, char **av)
{
	data->keep_iter = 1;
	data->n_philos = ft_atoi(av[1]);
	data->ms_todie = (u_int64_t) ft_atoi(av[2]);
	data->ms_toeat = (u_int64_t) ft_atoi(av[3]);
	data->ms_tosleep = (u_int64_t) ft_atoi(av[4]);
	data->n_meals = -1;
	if (ac == 6)
		data->n_meals = ft_atoi(av[5]);
	pthread_mutex_init(&data->ms_toeat_mu, NULL);
	pthread_mutex_init(&data->ms_tosleep_mu, NULL);
	pthread_mutex_init(&data->ms_todie_mu, NULL);
	pthread_mutex_init(&data->print_mu, NULL);
	pthread_mutex_init(&data->n_philos_mu, NULL);
	pthread_mutex_init(&data->keep_iter_mu, NULL);
	pthread_mutex_init(&data->start_time_mu, NULL);
	return (data_malloc(data));
}
