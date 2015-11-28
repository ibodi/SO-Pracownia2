#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

int NUMBER_OF_ITERATIONS = 30;
int COLORS = 1;

// Funkcje pomocnicze
void delayRandom(void);

// Filozofowie i sztućce
const char * philosophersNames[5] = { "Aristotle", "Socrates", "Zeno of Elea", "Plato", "Xenophanes" };
const char * philosophersColors[5] = { "\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m" };

pthread_t Philosophers[5];
sem_t Forks[5];
int forksInUse = 0;

void putState(int id, const char * state)
{
  if (COLORS)
    printf("%s%s %s\033[0m\n", philosophersColors[id], philosophersNames[id], state);
  else
    printf("%s %s\n", philosophersNames[id], state);
}

void * lifeOfThePhilosopher(void * args)
{
  int id = *((int *)args);
  free(args);
  for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
  {
    putState(id, "is thinking...");
    delayRandom();
    putState(id, "is hungry...");
    int left = id;
    int right = (id + 1) % 5;
    sem_wait(&Forks[left]);
    sem_wait(&Forks[right]);
    putState(id, "is eating...");
    delayRandom();
    sem_post(&Forks[left]);
    sem_post(&Forks[right]);
  }
  putState(id, "finished.");
}

int main(int argc, char *argv[])
{
  if (argc >= 2)
  {
    NUMBER_OF_ITERATIONS = atoi(argv[1]);
    if (argc == 3)
      COLORS = atoi(argv[2]);
  }

  int tret; // wartość zwracana przez różne pthread_funkcja()
  srand(time(NULL));

  // inicjowanie semaforów
  for (int i = 0; i < 5; i++)
    sem_init(&Forks[i], 0, 1);

  // startowanie wątków
  int * id;
  for (int i = 0; i < 5; i++)
  {
    id = malloc(sizeof(int));
    *id = i;
    if (tret = pthread_create(&Philosophers[i], NULL, lifeOfThePhilosopher, (void *)id))
    {
      fprintf(stderr,"Error from pthread_create(). Returned %i instead of 0.", tret); // error code display
      exit(EXIT_FAILURE);
    }
  }

  // kończenie wątków
  for (int i = 0; i < 5; i++)
    if (tret = pthread_join(Philosophers[i], NULL)) // joins back the pthread
    {
      fprintf(stderr, "Error from pthread_join(). Returned %i instead of 0.", tret); // error code display
      exit(EXIT_FAILURE);
    }

  // destrukcja semaforów
  for (int i = 0; i < 5; i++)
    sem_destroy(&Forks[i]);
  return 0;
}

// Funkcje pomocnicze
void delayRandom()
{
  int random = rand();
  while (random-- >= 1);
}
