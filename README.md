# Pracownia P2 
#### Problem Pięciu Filozofów
Poniższy program stanowi ilustrację rozwiązania klasycznego problemu synchronizacji zwanego *Problemem Pięciu Filozofów*, który został wymyślony przez E. Dijkstrę w 1965 roku, jako zadanie egzaminacyjne. Problem polega na skoordynowaniu działań pięciu ucztujących filozofów. Filozofowie siedzą przy okrągłym stole nad wielką misą spaghetti. Pomiędzy nimi znajduje się pięć widelców.
Jak wiadomo życie filozofa polega albo na jedzeniu spaghetti, albo na myśleniu. Każdy filozof albo myśli, albo je, przy czym do jedzenia potrzebuje obu najbliższych mu widelców. Widelce nie mogą być dzielone. W rozwiązaniu trzeba poradzić sobie z następującymi problemami.

* *deadlock* - gdy każdy filozof weźmie odpowiednio lewy/prawy widelec. Każdy z nich oczekuje na kolejny widelec, ale nigdy go nie dostanie. Układ jest zablokowany.
* *livelock* - filozofowie nieustannie biorą jeden widelec, czekają pewien czas i go odkładają nigdy nie wykonując czynności jedzenia.
* *starvation* - gdy jeden z filozofów nigdy nie jest dopuszczany do misy przez pozostałych.

#### Rozwiązanie
Moje rozwiązanie stanowi implementację oryginalnego rozwiązania E. Dijkstry polegającego na wprowadzeniu hierarchii zasobów. Widelce numeruje się od 1 do 5. Wprowadza się zasadę, że filozof zawsze najpierw bierze widelec o niższym numerze, a potem o wyższym. Filozof oddaje widelce w odwrotnej kolejności. W ten sposób wykluczony jest *deadlock*, gdyż sytuacja w której każdy filozof ma tylko lewy/prawy widelec jest niemożliwa. Problemy *livelock* i *starvation* zostały usunięte dzięki wprowadzeniu losowości. Rozwiązanie korzysta z semaforów.

#### Instalacja
Aby skompilować program wystarczy uruchomić:
```
make compile
```
lub:
```
make
```

#### Uruchomienie
Program przyjmuje kilka parametrów:
```
[-i] - określa liczbę iteracji filozofów (domyślnie 30).
[-s] - SPEED (od 0 do 9): określa maksymalny zakres [0, 10^SPEED], z którego będą losowane 
       czasy wykonywania czynności przez filozofów (domyślnie 9)
[-c] - 0 lub 1. Określa czy wyjście będzie kolorowane (domyślnie 1).
```
Przykładowe uruchomienia:

A) uruchomienie 20 iteracji z prędkością 5 i kolorami
```
./Philo -i 20 -s 5 -c 1
```
lub:
```
make run ARGS="-i 20 -s 5 -c 1"
```
B) uruchomienie 5 iteracji z domyślną prędkością 9 i domyślnie włączonymi kolorami
```
./Philo -s 5
```
lub:
```
make run ARGS="-s 5"
```

#### Test
Program jest łatwo testowalny. Dla prędkości 0 (tzn. czynności filozofów trwają albo zero, albo jedną jednostkę czasu) i dużej liczby operacji z dużym prawdopodobieństwem może wystąpić zjawisko potencjalnego *deadlocka*. Jednak dzięki hierarchii zasobów problem nie wystąpi.
Aby przetestować program wystarczy uruchomić:
```
make test
```
co skutkuje uruchomieniem programu z parametrami:
```
-s 0 -i 1000 -c 1
```

### Usuwanie
Aby usunąć program wystarczy uruchomić:
```
make clean
```



*30.11.2015, Oskar Wieczorek*
