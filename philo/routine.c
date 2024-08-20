/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:02:49 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/12 14:17:48 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	routine_loop(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(philo->is_alive_lock);
	if (!philo->is_alive || philo->one_dead == 1)
	{
		pthread_mutex_unlock(philo->is_alive_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->is_alive_lock);
	if (philo->nte == -1)
	{
		if (routine_case1(philo, left, right) == 0)
			return (0);
	}
	else if (philo->nte > 0)
	{
		if (routine_case2(philo, left, right) == 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = (t_philo *)arg;
	left = philo->id % philo->nop;
	right = (philo->id - 1 + philo->nop) % philo->nop;
	if (philo->nop == 1)
	{
		print_status(philo, "is thinking");
		return (NULL);
	}
	while (1)
	{
		if (routine_loop(philo, left, right) == 0)
			break ;
	}
	return (NULL);
}
