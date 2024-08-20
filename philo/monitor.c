/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:04:07 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/12 15:11:50 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check_if_any_death(t_philo *philo, int *i, long *t)
{
	*i = 0;
	while (*i < philo->nop)
	{
		pthread_mutex_lock(philo[*i].print_lock);
		*t = get_timestamp(philo[*i].start_time) - philo[*i].last_meal;
		if (*t > philo->ttd)
		{
			if (philo->nte == -2)
			{
				pthread_mutex_unlock(philo[*i].print_lock);
				return (0);
			}
			pthread_mutex_lock(philo->is_alive_lock);
			philo->is_alive = 0;
			set_one_dead(philo);
			pthread_mutex_unlock(philo->is_alive_lock);
			*t = get_timestamp(philo->start_time);
			printf("%ld %d died\n", *t, philo[*i].id + 1);
			pthread_mutex_unlock(philo[*i].print_lock);
			return (0);
		}
		pthread_mutex_unlock(philo[*i].print_lock);
		(*i)++;
	}
	return (1);
}

int	check_alive_and_nte(t_philo *philo)
{
	pthread_mutex_lock(philo->is_alive_lock);
	pthread_mutex_lock(philo->nte_lock);
	if (philo->nte == 0)
	{
		philo->nte = -2;
		pthread_mutex_unlock(philo->is_alive_lock);
		pthread_mutex_unlock(philo->nte_lock);
		return (-1);
	}
	pthread_mutex_unlock(philo->nte_lock);
	if (!philo->is_alive)
	{
		pthread_mutex_unlock(philo->is_alive_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->is_alive_lock);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	int		i;
	long	t;

	philo = (t_philo *)arg;
	if (philo->nop == 1)
	{
		usleep(philo->ttd * 1000);
		print_status(philo, "died");
		return (NULL);
	}
	while (1)
	{
		if (check_alive_and_nte(philo) == -1)
			continue ;
		if (check_alive_and_nte(philo) == 0)
			return (NULL);
		if (check_if_any_death(philo, &i, &t) == 0)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
