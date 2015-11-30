#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

unsigned int NUMBER_OF_ITERATIONS = 30;
unsigned int COLORS = 1;
unsigned int SPEED = 9;

// Funkcja pomocnicza
void delayRandom(void);

// Filozofowie i sztućce
const char * philosophersNames[5] = { "Aristotle", "Socrates", "Zeno of Elea", "Plato", "Xenophanes" };
const char * philosophersColors[5] = { "\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m" };

pthread_t Philosophers[5];
sem_t Forks[5];

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
    delayRandom(); // sumulacja wykonania czynności przez filozofa
    putState(id, "is hungry...");
    // ustalenie hierarchii zasobów ~Dijkstra
    int lowFork = (id == 4 ? 0 : id);
    int highFork = (id == 4 ? 4 : (id + 1));
    sem_wait(&Forks[lowFork]);
    sem_wait(&Forks[highFork]);
    putState(id, "is eating...");
    delayRandom(); // sumulacja wykonania czynności przez filozofa
    sem_post(&Forks[highFork]);
    sem_post(&Forks[lowFork]);
  }
  putState(id, "finished.");
}

int main(int argc, char *argv[])
{
  // wczytywanie parametrów programu
  for (int i = 1; i < argc; i += 2)
  {
    if (!strcmp(argv[i], "-i"))
      NUMBER_OF_ITERATIONS = atoi(argv[i+1]);
    if (!strcmp(argv[i], "-s"))
      SPEED = atoi(argv[i+1]);
    if (!strcmp(argv[i], "-c"))
      COLORS = atoi(argv[i+1]);
  }

  // normalizacja prędkości wykonania
  if (SPEED > 9)
    SPEED = 9;
  else if (SPEED < 0)
    SPEED = 0;

  // info
  printf("speed: %d, iterations %d, %s\n", SPEED, NUMBER_OF_ITERATIONS, COLORS ? "with colors" : "without colors");

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
      fprintf(stderr,"Error from pthread_create(). Returned %i instead of 0.", tret); // wyświetlanie kodu błędu
      exit(EXIT_FAILURE);
    }
  }

  // kończenie wątków
  for (int i = 0; i < 5; i++)
    if (tret = pthread_join(Philosophers[i], NULL))
    {
      fprintf(stderr, "Error from pthread_join(). Returned %i instead of 0.", tret); // wyświetlanie kodu błędu
      exit(EXIT_FAILURE);
    }

  // destrukcja semaforów
  for (int i = 0; i < 5; i++)
    sem_destroy(&Forks[i]);
  return 0;
}

// Funkcja pomocnicza
void delayRandom()
{
  int random = rand() % (int)pow(10, SPEED);
  while (random-- >= 1);
}
