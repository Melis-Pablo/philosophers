/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:18:23 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/12 20:09:22 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset(): fill memory with a constant byte
# include <stdio.h> //printf(): Prints message.
# include <stdlib.h> //malloc(): Allocates memory to heap.
						//free(): frees memory from heap.
# include <unistd.h> //write()
						//usleep(): suspend execution for microsecond intervals
# include <sys/time.h> //gettimeofday(): returns microseconds since 1970
# include <pthread.h> //pthread_create(): create a new thread
						//pthread_detach(): detach a thread
						//pthread_join(): join with a terminated thread
						//pthread_mutex_init(): initialize mutex
						//pthread_mutex_destroy(): destroy mutex
						//pthread_mutex_lock(): locks mutex
						//pthread_mutex_unlock(): unlocks mutex

typedef enum e_philo_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	IDLE = 5
}	t_state;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	struct s_data	*data;
	u_int64_t		last_meal;
	t_state			state;
	pthread_mutex_t	n_meals_mu;	
	pthread_mutex_t	last_meal_mu;
	pthread_mutex_t	state_mu;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
	u_int64_t		ms_todie;
	u_int64_t		ms_toeat;
	u_int64_t		ms_tosleep;
	int				n_meals;
	u_int64_t		start_time;
	int				keep_iter;
	pthread_mutex_t	ms_todie_mu;
	pthread_mutex_t	ms_toeat_mu;
	pthread_mutex_t	ms_tosleep_mu;
	pthread_mutex_t	start_time_mu;
	pthread_mutex_t	n_philos_mu;
	pthread_mutex_t	keep_iter_mu;
	pthread_mutex_t	print_mu;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_t		*philo_th;
	pthread_t		monit_all_alive;
	pthread_t		monit_all_full;
}	t_data;

////////////////////
/////activities/////
////////////////////
int			think(t_philo *philo);
int			ft_sleep(t_philo *philo);
int			eat(t_philo *philo);
void		free_data(t_data *data);

///////////////////
/////data_init/////
///////////////////
int			fork_init(t_data *data);
int			philo_init(t_data *data);
int			data_malloc(t_data *data);
int			data_init(t_data *data, int ac, char **av);

/////////////
/////eat/////
/////////////
void		update_last_meal(t_philo *philo);
void		drop_both(t_philo *philo);
void		update_n_meals(t_philo *philo);
void		sleep_for_eating(t_philo *philo);

///////////////
/////forks/////
///////////////
void		drop_left(t_philo *philo);
void		drop_right(t_philo *philo);
int			take_left(t_philo *philo);
int			take_right(t_philo *philo);
int			take_both(t_philo *philo);

/////////////////
/////handler/////
/////////////////
int			handle_1(t_philo *philo);
int			n_meal_trigger(t_data *data);
void		print_changestate(t_data *data, int id, char *msg);

/////////////////////
/////input_check/////
/////////////////////
int			input_check(int ac, char **av);
int			wrong_input(int ac, char **av);
int			is_digit(int ac, char **av);
int			ft_atoi(char *str);
void		print_error(void);

//////////////////////
/////more_pullers/////
//////////////////////
int			pull_n_meals_had(t_philo *philo);
int			pull_n_philos(t_data *data);
int			pull_keep_iter(t_data *data);
t_state		pull_philo_state(t_philo *philo);

/////////////////
/////pullers/////
/////////////////
u_int64_t	pull_death_time(t_data *data);
u_int64_t	pull_sleep_time(t_data *data);
u_int64_t	pull_eat_time(t_data *data);
u_int64_t	pull_last_meal(t_philo *philo);
u_int64_t	pull_start_time(t_data *data);

///////////////////
/////pushers.c/////
///////////////////
void		push_philo_state(t_philo *philo, t_state state);
void		push_keep_iter(t_data *data, int set_to);

/////////////////
/////routine/////
/////////////////
void		*routine(void *philo_p);
void		*all_full_routine(void *data_p);
void		*all_alive_routine(void *data_p);

////////////////////
/////supervisor/////
////////////////////
int			is_full(t_data *data, t_philo *philo);
int			philo_death(t_philo *philo);
void		notify_all(t_data *data);
u_int64_t	get_time(void);
void		ft_usleep(u_int64_t sleep_time);

#endif
