/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:21:44 by ktiong            #+#    #+#             */
/*   Updated: 2021/06/06 18:12:46 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	static int	ascii; // static because the function is called several times and you need to remember the previous value
	static int	power;

	(void)ptr;
	if (!info->si_pid) 
		return ;
	if (kill(info->si_pid, signum) != 0) // info - finds out what is the pid on the client, where the signal came from. We send 2signal to the client
		return ;
	if (signum == SIGUSR1)
		ascii |= (1 << power);
	if (++power == 8) // if all 8 characters arrived (in 2 code), then print the character
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
	char	*c;

	c = (char *)p;
	while (n--)
		*c++ = 0;
}

/*  The sigaction() system call is used to change the action taken by
	**							a process on receipt of a specific signal.
	** sigaction (SIGNUM, action, old_action)
	**	The sigaction structure is defined as something like:
    **     struct sigaction {
	**		void     (*sa_sigaction)(int, siginfo_t *, void *);
    **		sigset_t   sa_mask;
    **		int        sa_flags;
    **      };
	** Printing the active bits will lead us to the null bit at the end,
	** signaling that we've iterated through all the characters
	** pause() causes the calling process (or thread) to sleep until a
    ** signal is delivered that either terminates the process or causes
	** the invocation of a signal-catching function.
*/

int	main(void)
{
	pid_t				serv_pid;
	struct sigaction	act; // structure for receiving signals
	sigset_t			hold;

	serv_pid = getpid(); // get the pid of the current process
	mt_putstr("\033[1;35mWelcome to Minitalk\nserver pid: ");
	mt_putnbr_fd((int)serv_pid);
	mt_putstr("\n");
	sigemptyset(&hold); //ini signal mask to ex all sig
	mt_bzero(&act, sizeof(sigaction));
	act.sa_sigaction = &recept;
	act.sa_flags = SA_SIGINFO;  // this is a (flag) signal to accept from the client
	sigaddset(&hold, SIGUSR1); // to receive 1 signal
	sigaddset(&hold, SIGUSR2); // to receive signal 2
	act.sa_mask = hold;
	if (sigaction(SIGUSR1, &act, NULL) || sigaction(SIGUSR2, &act, NULL))
	{
		mt_putstr("\033[0;31mPlease retry\n");
	}
	while (42) // the server waits until a new signal arrives, if it arrives, it enters sig_take
		pause();
	return (0);
}
