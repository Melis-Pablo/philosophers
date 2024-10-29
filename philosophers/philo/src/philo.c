/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:52:22 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/09 20:42:53 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
run_threads():		Creates and runs threads for each philosopher.

Parameters:	data - A pointer to the data structure that holds the simulation
					data.

Return value: 0 if the threads are created and run successfully,
				1 if there's an error.

How it works: 
1. Retrieves the number of philosophers from the data structure.
2. Records the start time of the simulation.
3. Creates a thread for each philosopher using pthread_create. 
	Each thread runs the routine function, simulating a philosopher's life cycle.
4. Creates a thread that runs the all_alive_routine function, 
	which checks if all philosophers are alive.
5. If the number of meals is specified, creates a thread that runs 
	the all_full_routine function, which checks if all philosophers 
	have eaten the specified number of meals.
6. If any thread is not created successfully, returns 1.
7. If all threads are created and run successfully, returns 0.
*/
int	run_threads(t_data *data)
{
	int	i;
	int	n_philos;

	i = -1;
	n_philos = pull_n_philos(data);
	data->start_time = get_time();
	while (++i < n_philos)
	{
		if (pthread_create(&data->philo_th[i], NULL, &routine, &data->philo[i]))
			return (1);
	}
	if (pthread_create(&data->monit_all_alive, NULL, &all_alive_routine, data))
		return (1);
	if (n_meal_trigger(data)
		&& pthread_create(&data->monit_all_full, NULL, &all_full_routine, data))
		return (1);
	return (0);
}

/*
join_threads(): Waits for all threads to finish.

Parameters: data - A pointer to the data structure that holds
				the simulation data.

Return value: 0 if all threads finish successfully, 1 if there's an error.

How it works: 
1. Retrieves the number of philosophers from the data structure.
2. Waits for the all_alive_routine thread to finish using the pthread_join
	function.
3. If the number of meals is specified, waits for the all_full_routine thread
	to finish.
4. Waits for each philosopher's thread to finish.
5. If any thread does not finish successfully, returns 1.
6. If all threads finish successfully, returns 0.
*/
int	join_threads(t_data *data)
{
	int	i;
	int	n_philos;

	i = -1;
	n_philos = pull_n_philos(data);
	if (pthread_join(data->monit_all_alive, NULL))
		return (1);
	if (n_meal_trigger(data) && pthread_join(data->monit_all_full, NULL))
		return (1);
	while (++i < n_philos)
	{
		if (pthread_join(data->philo_th[i], NULL))
			return (1);
	}
	return (0);
}

/*
philo(): Simulates the philosopher's problem.

Parameters: ac - The count of command-line arguments.
            av - An array of the command-line arguments.

Return value: 0 if the simulation runs successfully, 2 if there's an error.

How it works: 
1. Initializes the data structure using the data_init function.
2. If the data structure is not initialized correctly, returns 2.
3. Initializes the philosophers using the philo_init function.
4. Initializes the forks using the fork_init function.
5. Runs the simulation by creating and running threads using the run_threads
	function.
6. Waits for all threads to finish using the join_threads function.
7. Frees the allocated memory using the free_data function.
8. If the simulation runs successfully, returns 0.
*/
int	philo(int ac, char **av)
{
	t_data	data;

	if (data_init(&data, ac, av))
		return (2);
	philo_init(&data);
	fork_init(&data);
	run_threads(&data);
	join_threads(&data);
	free_data(&data);
	return (0);
}

/*
main():		Entry point of the program. It simulates the philosopher's problem.

Parameters:	ac - The count of command-line arguments.
			av - An array of the command-line arguments.

Return value: 0 if the program runs successfully, 1 if there's an input error,
				2 if there's an error in the philo function.

How it works: 
1. Checks the validity of the command-line arguments using input_check function.
	This function checks if the number of arguments is correct and if
	all arguments are digits and within the valid range.
2. If the arguments are invalid, it calls the print_error function to print an 
	error message detailing the correct usage of the program and the valid range 
	for each argument, and then returns 1.
3. If the arguments are valid, it calls the philo function to simulate the 
	philosopher's problem. This function creates a number of threads equal to the
	number of philosophers, and each thread simulates a philosopher's life cycle.
4. If the philo function returns a non-zero value, indicating an error occurred 
	during the simulation, the main function returns 2.
5. If the philo function runs successfully, the main function returns 0.
*/
int	main(int ac, char **av)
{
	if (input_check(ac, av))
	{
		print_error();
		return (1);
	}
	if (philo(ac, av))
		return (2);
	return (0);
}
