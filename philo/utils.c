/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:56:34 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/12 12:59:04 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	get_timestamp(long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
}

void	print_status(t_philo *philo, char *status)
{
	long	t;

	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_lock(philo->is_alive_lock);
	if (philo->is_alive)
	{
		t = get_timestamp(philo->start_time);
		printf("%ld %d %s\n", t, philo->id + 1, status);
	}
	pthread_mutex_unlock(philo->is_alive_lock);
	pthread_mutex_unlock(philo->print_lock);
}

void	set_one_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nop)
	{
		philos[i].one_dead = 1;
		i++;
	}
}
