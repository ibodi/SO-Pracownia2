# Pracownia P2 
#### Problem Pięciu Filozofów
Poniższy program stanowi ilustrację rozwiązania klasycznego problemu synchronizacji zwanego *Problemem Pięciu Filozofów*, który został wymyślony przez E. Dijkstrę w 1965 roku, jako zadanie egzaminacyjne. Problem polega na skordynowaniu działań pięciu ucztujących filozofów. Filozofowie siedzą przy okrągłym stole nad wielką misą spaghetti. Pomiędzy nimi znajduje się pięć widelców.
Jak wiadomo życie filozofa polega albo na jedzeniu spaghetti, albo na myśleniu. Każdy filozof albo myśli, albo je, przy czym do jedzenia potrzebuje obu najbliższych mu widelców. Widelce nie mogą być dzielone. W rozwiązaniu trzeba poradzić sobie z następującymi problemami.

* *deadlock* - gdy każdy filozof weźmie odpowiednio lewy/prawy widelec. Każdy z nich oczekuje na kolejny widelec, ale nigdy go nie dostanie. Układ jest zablokowany.
* *livelock* - filozofowie nieustannie biorą jeden widelec, czekają pewien czas i go odkładają nigdy nie wykonując czynności jedzenia.
* *głodzenie* - gdy jeden z filozofów nigdy nie jest dopuszczany do misy przez pozostałych.

#### Moje rozwiązanie
Moje rozwiązanie stanowi implementację oryginalnego rozwiązania E. Dijkstry polegającego na wprowadzeniu hierarchii zasobów. Widelce numeruje się od 1 do 5. W ten sposób nie 

