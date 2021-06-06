/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 18:15:44 by ktiong            #+#    #+#             */
/*   Updated: 2021/06/06 18:15:44 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H 
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

int		g_nbr;
char	ft_con_c(char c, int c1, int c2);
void	recept(int signum, siginfo_t *info, void *ptr);

#endif
