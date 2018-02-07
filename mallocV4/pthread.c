/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include <pthread.h>
#include <signal.h>
#include <zconf.h>

static pthread_mutex_t g_mutex_m = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t g_mutex_r = PTHREAD_MUTEX_INITIALIZER;

void lock_thread(int flag)
{
	if (!flag) {
		if (pthread_mutex_lock(&g_mutex_m))
			raise(SIGABRT);
	} else if (flag == 1) {
		if (pthread_mutex_lock(&g_mutex_r))
			raise(SIGABRT);
	}
}

void unlock_thread(int flag)
{
	if (!flag) {
		if (pthread_mutex_unlock(&g_mutex_m))
			raise(SIGABRT);
	} else if (flag == 1) {
		if (pthread_mutex_unlock(&g_mutex_r))
			raise(SIGABRT);
	}
}
