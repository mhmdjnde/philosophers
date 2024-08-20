/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:04:54 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/12 13:06:07 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	init_mutexes(t_mutexes *mutexes)
{
	pthread_mutex_init(&mutexes->print_lock, NULL);
	pthread_mutex_init(&mutexes->is_alive_lock, NULL);
	pthread_mutex_init(&mutexes->nte_lock, NULL);
}

void	destroy_mutexes(t_mutexes *mutexes)
{
	pthread_mutex_destroy(&mutexes->print_lock);
	pthread_mutex_destroy(&mutexes->is_alive_lock);
	pthread_mutex_destroy(&mutexes->nte_lock);
}

void	philo_ini_helper(t_philo *philo_data, int i, char **av, long stime)
{
	philo_data[i].nop = ft_atoi(av[1]);
	philo_data[i].ttd = ft_atoi(av[2]);
	philo_data[i].tte = ft_atoi(av[3]);
	philo_data[i].tts = ft_atoi(av[4]);
	philo_data[i].start_time = stime;
	philo_data[i].last_meal = stime;
}

void	philo_ini(t_philo *philo, char **av, pthread_mutex_t *f, t_mutexes *m)
{
	int				i;
	long			stime;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	stime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&f[i], NULL);
		philo[i].id = i;
		philo[i].forks = f;
		philo[i].print_lock = &m->print_lock;
		philo[i].nte_lock = &m->nte_lock;
		philo[i].is_alive_lock = &m->is_alive_lock;
		philo_ini_helper(philo, i, av, stime);
		philo[i].is_alive = 1;
		philo[i].one_dead = 0;
		if (av[5])
			philo[i].nte = ft_atoi(av[5]);
		else
			philo[i].nte = -1;
		i++;
	}
}
