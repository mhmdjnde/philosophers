/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:24:35 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/12 12:49:55 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*is_alive_lock;
	pthread_mutex_t	*nte_lock;
	long			nop;
	long			ttd;
	long			tte;
	long			tts;
	long			start_time;
	long			last_meal;
	int				is_alive;
	int				one_dead;
	long			nte;
}	t_philo;

typedef struct s_mutexes
{
	pthread_mutex_t	print_lock;
	pthread_mutex_t	is_alive_lock;
	pthread_mutex_t	nte_lock;
}	t_mutexes;
long	ft_atoi(const char *nptr);
int		is_num(char *str);
int		val(char **av);
long	get_timestamp(long start_time);
void	print_status(t_philo *philo, char *status);
void	set_one_dead(t_philo *philos);
void	routine_case2_helper2(t_philo *philo, int left, int right);
int		routine_case2_helper1(t_philo *philo, int left, int right);
int		routine_case2(t_philo *philo, int left, int right);
void	routine_case1_helper1(t_philo *philo, int left, int right);
int		routine_case1_helper2(t_philo *philo, int left, int right);
int		routine_case1(t_philo *philo, int left, int right);
int		routine_loop(t_philo *philo, int left, int right);
void	*philosopher_routine(void *arg);
int		check_if_any_death(t_philo *philo, int *i, long *t);
int		check_alive_and_nte(t_philo *philo);
void	*monitor_routine(void *arg);
void	init_mutexes(t_mutexes *mutexes);
void	destroy_mutexes(t_mutexes *mutexes);
void	philo_ini_helper(t_philo *philo_data, int i, char **av, long stime);
void	philo_ini(t_philo *philo, char **av, pthread_mutex_t *f, t_mutexes *m);
void	main_helper(char **av, pthread_t *p, t_philo *philos);
void	clear(t_mutexes *m, t_philo *ps, pthread_mutex_t *forks, pthread_t *p);
int		main(int ac, char **av);

#endif
