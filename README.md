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

#1 Death:
To check death, I use an infinite loop or I check each philosopher continuously. If one dies, the program stops. I run this loop in the main process. I don’t use additional threads unnecessarily (and this optimizes my program).

#2 Meals: 
To check meals, I simply increment a variable that is then compared if my variable if there is a number of meals to eat. If so, my program stops.

⚠️Warning⚠️: Every check are protect with the mutex (Otherwise this create data race).

# Tester
To test my program, i used this one :
https://github.com/MichelleJiam/LazyPhilosophersTester
