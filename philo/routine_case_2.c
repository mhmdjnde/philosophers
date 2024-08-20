/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_case_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:00:20 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/12 13:00:54 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	routine_case2_helper2(t_philo *philo, int left, int right)
{
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->print_lock);
	philo->last_meal = get_timestamp(philo->start_time);
	pthread_mutex_lock(philo->nte_lock);
	philo->nte--;
	pthread_mutex_unlock(philo->nte_lock);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->tte * 1000);
	pthread_mutex_unlock(&philo->forks[right]);
	pthread_mutex_unlock(&philo->forks[left]);
}

int	routine_case2_helper1(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(philo->is_alive_lock);
	if (!philo->is_alive || philo->one_dead == 1)
	{
		pthread_mutex_unlock(philo->is_alive_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->is_alive_lock);
	print_status(philo, "is thinking");
	usleep(100);
	if (left > right)
	{
		pthread_mutex_lock(&philo->forks[right]);
		pthread_mutex_lock(&philo->forks[left]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[left]);
		pthread_mutex_lock(&philo->forks[right]);
	}
	return (1);
}

int	routine_case2(t_philo *philo, int left, int right)
{
	if (routine_case2_helper1(philo, left, right) == 0)
		return (0);
	pthread_mutex_lock(philo->is_alive_lock);
	if (!philo->is_alive || philo->one_dead == 1)
	{
		pthread_mutex_unlock(philo->is_alive_lock);
		pthread_mutex_unlock(&philo->forks[right]);
		pthread_mutex_unlock(&philo->forks[left]);
		return (0);
	}
	pthread_mutex_unlock(philo->is_alive_lock);
	routine_case2_helper2(philo, left, right);
	pthread_mutex_lock(philo->is_alive_lock);
	if (!philo->is_alive || philo->one_dead == 1)
	{
		pthread_mutex_unlock(philo->is_alive_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->is_alive_lock);
	print_status(philo, "is sleeping");
	usleep(philo->tts * 1000);
	usleep(100);
	return (1);
}
