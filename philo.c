#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// Filozof
enum { THINKING, HUNGRY, EATING };

void think(int philosopherId)
{
  printf("Philosopher %d is thinking...\n", philosopherId);
  clock_t now = clock();
  clock_t duration = (rand() % 5) * CLOCKS_PER_SEC; // losowa długość czynności
  while (clock() < now + duration);
}

void eat(int philosopherId)
{
  printf("Philosopher %d is eating...\n", philosopherId);
  clock_t now = clock();
  clock_t duration = (rand() % 5) * CLOCKS_PER_SEC; // losowa długość czynności
  while (clock() < now + duration);
}

void * lifeOfThePhilosopher(void * args)
{
  int philosopherId = *((int *)args);
  free(args);
  while (1)
  {
    think(philosopherId);
    // takeForks(philosopherId);
    eat(philosopherId);
    // dropForks(philosopherId);
  }
}

int main()
{
  srand(time(NULL));
  pthread_t Philosophers[5];
  int * id;
  int tret; // sprawdzenie, czy wątek utworzył się poprawnie
  for (int i = 0; i < 5; i++)
  {
    id = malloc(sizeof(int));
    *id = i + 1;
    if (tret = pthread_create(&Philosophers[i], NULL, lifeOfThePhilosopher, (void *)id))
    {
      fprintf(stderr,"Error from pthread_create(). Returned %i instead of 0.", tret); // error code display
      exit(EXIT_FAILURE);
    }
  }
  for (int i = 0; i < 5; i++)
  {
    if (tret = pthread_join(Philosophers[i], NULL)) // joins back the pthread
    {
      fprintf(stderr, "Error from pthread_join(). Returned %i instead of 0.", tret); // error code display
      exit(EXIT_FAILURE);
    }
  }
  
  return 0;
}
