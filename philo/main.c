/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:48:12 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/12 15:06:32 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	main_helper(char **av, pthread_t *p, t_philo *philos)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&p[i], NULL, philosopher_routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_routine, philos);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(p[i], NULL);
		i++;
	}
}

void	clear(t_mutexes *m, t_philo *ps, pthread_mutex_t *forks, pthread_t *p)
{
	free(ps);
	free(forks);
	free(p);
	destroy_mutexes(m);
}

int	main(int ac, char **av)
{
	t_mutexes		mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*p;

	if (ac != 5 && ac != 6)
	{
		printf("usage ./philo nop ttd tte tts");
		return (0);
	}
	if (!val(av))
	{
		printf("invalid input");
		return (0);
	}
	philos = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	p = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	init_mutexes(&mutex);
	philo_ini(philos, av, forks, &mutex);
	main_helper(av, p, philos);
	clear(&mutex, philos, forks, p);
	return (0);
}
