#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

int NUMBER_OF_ITERATIONS = 30;

// Funkcje pomocnicze
void delayRandom(void);

// Filozofowie i sztućce
enum { THINKING, HUNGRY, EATING };
const char * philosophersNames[5] = { "Aristotle", "Socrates", "Zeno of Elea", "Plato", "Xenophanes" };

pthread_t Philosophers[5];
sem_t Forks[5];

void putState(int id, const char * state)
{
  printf("%s is %s...\n", philosophersNames[id], state);
}

void * lifeOfThePhilosopher(void * args)
{
  int id = *((int *)args);
  free(args);
  int i = 0;
  while (i++ < NUMBER_OF_ITERATIONS)
  {
    putState(id, "thinking");
    delayRandom();
    putState(id, "hungry");
    int left = id;
    int right = (id + 1) % 5;
    sem_wait(&Forks[id]);
    sem_wait(&Forks[(id + 1) % 5]);
    putState(id, "eating");
    delayRandom();
    sem_post(&Forks[id]);
    sem_post(&Forks[id]);
  }
}


int main()
{
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
