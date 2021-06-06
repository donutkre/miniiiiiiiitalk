/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:21:44 by ktiong            #+#    #+#             */
/*   Updated: 2021/06/06 18:12:46 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	mt_putstr(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}

static void	mt_putnbr_fd(int n)
{
	char	a;

	a = n % 10 + '0';
	if (n >= 10)
		mt_putnbr_fd(n / 10);
	write(1, &a, 1);
}

void	recept(int signum, siginfo_t *info, void *ptr)
{
	static int	ascii;
	static int	power;

	(void)ptr;
	if (!info->si_pid)
		return ;
	if (kill(info->si_pid, signum) != 0)
		return ;
	if (signum == SIGUSR1)
		ascii |= (1 << power);
	if (++power == 8)
	{
		power = 0;
		if (ascii)
			write(1, &ascii, 1);
		else
			mt_putstr("\n");
		ascii = 0;
	}
}

void	mt_bzero(void *p, int n)
{
	char		*c;

	c = (char *)p;
	while (n--)
		*c++ = 0;
}

int	main(void)
{
	pid_t				serv_pid;
	struct sigaction	act;
	sigset_t			hold;

	serv_pid = getpid();
	mt_putstr("\033[1;35mWelcome to Minitalk\nserver pid: ");
	mt_putnbr_fd((int)serv_pid);
	mt_putstr("\n");
	sigemptyset(&hold);
	mt_bzero(&act, sizeof(sigaction));
	act.sa_sigaction = &recept;
	act.sa_flags = SA_SIGINFO;
	sigaddset(&hold, SIGUSR1);
	sigaddset(&hold, SIGUSR2);
	act.sa_mask = hold;
	if (sigaction(SIGUSR1, &act, NULL) || sigaction(SIGUSR2, &act, NULL))
	{
		mt_putstr("\033[0;31mPlease retry\n");
	}
	while (42)
		pause();
	return (0);
}
