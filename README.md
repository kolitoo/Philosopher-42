# Philosopher

Learning the basics of threading a process.
How to create threads and discover mutexes.
I only did the mandatory subject.

## Description

I did this project in 4 steps:
* Understand the subject
* Parsing & check arguments.
* Create & Use mutex/threads.
* Check the death and the number of meals each philosopher ate.

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

## Step 3: Mutex & treads

## Step 4: Death & meals

# Tester
To test my program, i used this one :
https://github.com/MichelleJiam/LazyPhilosophersTester
