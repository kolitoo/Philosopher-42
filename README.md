# Philosopher

Learning the basics of threading a process.
How to create threads and discover mutexes.
I only did the mandatory subject.

## To launch my program

 ```
git clone https://github.com/kolitoo/Philosopher-42.git && cd Philosopher-42 && cd philo && make
 ```
 
## Description

I did this project in 4 steps:
- Understand the subject
- Parsing & check arguments.
- Create & Use mutex/threads.
- Control time.
- Check the death and the number of meals each philosopher ate.

## Step 1: Understand the subject

The purpose of this simulation is that it is infinite, unless a philosopher dies or else they ate the number of meals indicated if there are 5 arguments.
 ```
 ./philo [nb of philosophers][time to die][time to eat][time to sleep][nb of meals]
 ```
A philosopher is represented by a thread and there is a number of forks (mutex) equal to the number of philosophers. 
Philosophers can in order: take the forks => eat => sleep => think. (In reality, they think while waiting to take the forks).
To eat, a philosopher needs two forks (in my program, each philosopher takes his fork and that of his right neighbor).

## Step 2: Parsing & Check

- We need to check the numbers of arguments.
- We need check if each argument is a number and equal or greater than 0. Else, return an error.
- I choose to do a structure table to store philosopher information, a cell of the table corresponds to a philosopher.

## Step 3: Mutex & threads

What is a mutex & a thread ?

A mutex is a synchronization mechanism that allows multiple threads to safely access shared resources by enforcing exclusive access to those resources.

A thread is a unit of execution within a process that enables concurrent and independent execution of tasks.

To use a mutex or a thread, you need to init it:
 ```
 pthread_mutex_init(&mutex[i], NULL);
 pthread_create(&threads[i], NULL, thread_routine, (void *)&arg->philo_tabstruct[i]);
 ```
thread_routine is my function where I declenche the different actions of philosophers.

## Step 4: Control time

You need to make your own fonction to get the time like that
 ```
long	ft_get_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}
```
 You can use usleep(), but this function is not precise, so you will need to do your own function with a loop to be precis.
```  
void	ft_usleep(long int usec, t_philo *philo)
{
	long	time_action_start;

	time_action_start = ft_get_time();
	usleep(usec * (800 + philo->arg->nbr_philo));
	while (ft_get_time() - time_action_start < usec)
		usleep(usec / 10);
}
```
(i use a usleep(800) before the loop to optimize my program).

The strategy adopted in the program is to launch philosophers by pair or odd.
```
if (philo->philo_id % 2 != 0)
 ft_usleep(philo->arg->time_to_eat / 2, philo);
```

## Step 5: Death & meals

#1 Death:
To check death, I use an infinite loop or I check each philosopher continuously. If one dies, the program stops. I run this loop in the main process. I don’t use additional threads unnecessarily (and this optimizes my program).

#2 Meals: 
To check meals, I simply increment a variable that is then compared if my variable if there is a number of meals to eat. If so, my program stops.

⚠️Warning: Every check are protect with the mutex (Otherwise this create data race).

## Leaks & tests
 To test the leaks, u can use 2 tools:
 - compile with -g -fsanitize=thread to see every mutex & threads problems (unlock mutex, data race, ...).
 
 OR
 
 - Use valgrind --tool=helgrind to see every mutex & threads problems (unlock mutex, data race, ...).
 
 (I used fsanitize because for me it slows down the performance of the program)
 
⚠️Warning: NEVER USE FSANITISE WITH VALGRIND (Or your PC will hate u).

To test my program, i used this one :
https://github.com/MichelleJiam/LazyPhilosophersTester

## Links
https://stackoverflow.com/questions/61255354/solve-dining-philosophers-problem-using-pthreads-mutex-locks-and-condition-var

https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/

https://franckh.developpez.com/tutoriels/posix/pthreads/
