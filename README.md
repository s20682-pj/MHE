Algorytmy w języku C++ na zajęcia z Metaheurystyk PJATK 2021/2022
Wybrany problem: https://en.wikipedia.org/wiki/Knapsack_problem

Problem polega na tym, by do plecaka o danej pojemności zmieścić jak najbardziej wartościowe przedmioty.

Dany problem można rozwiązać następującymi algorytmami, które zostały zaimplemetowane:

Algorytm 1 - Algorytm wspinaczkowy w wersji deterministycznej

Algorytm 2 - Algorytm wspinaczkowy w wersji stochastycznej

Algorytm 3 - Algorytm tabu

Algorytm 4 - Algorytm symulowanego wyżarzania

Algorytm 5 - Algorytm genetyczny


Podczas uruchamiania możnna wywołać następujące argumenty [do których algorytmów można użyć]:

-fname - nazwa pliku z danymi, jeżeli pozostanie puste, to nastąpi przejście do samodzielnego wpisania danych (string) [1-5]

-iterations - ilość iteracji algorytmów (int) [1-4]

-method - który algorytm ma zostać uruchomiony (hc dla algorytmu wspinaczkowy w wersji deterministycznej, random dla algorytmu wspinaczkowy w wersji stochastycznej, tabu - dla algorytmu tabu, sa - dla algorytmu symulowanego wyżarzania, genetic - dla algorytmu genetycznego) [domyślnie jest ustawiona wartość hc] [1-5]

-tabu_size - rozmiar naszego tabu (int) [3]

-backpackSize - rozmiar naszego plecaka (int) [1-5]

-uniformRealDistributionIsSet - wartość dla symulowanego wyżarzania, która definiuje rodzaj rozkładu (true/false) [4]

-crossing - metoda crossowania rodziców w algorytmie genetycznym (half dla dzielenia w losowo wybranym miejscu, w przeciwnym wypadku zostanie wykonane crossowanie biorąc na zmianę po jednym chromsomie od każdego rodzica) [5]

-populationSize - ile osobników ma być w populacji [5]

-mutation - rodzaj mutowania utworzonych dzieci (random - losowy chromosom mutuje, w innym wypadku losowemu dziecku zostanie zmieniony pierwszy bit) [5]

-ending - warunek do zakończenia algorytmu genetycznego (best - algorytm zakończy się, jeżeli następne pokolenie nie osiągnie lepszego wyniku, generations - algorytm stworzy x pokoleń i wybierze najlepszy wynik z ostatniego) [5]

-generations - po ilu generacjach ma zostać zakończony algorytm, jeśli wybrano warunek zakończenia generations (int) [5]

Dołączony zostaje również skrypt, który ukazuje, jak szybko dany algorytm odnajduje najlepsze rozwiązanie, dzięki czemu możemy określić, która metoda jest najlepsza dla danego problemu.

W folderze znajduje się również plik z przykładowymi danymi. Paramatry mają jako default ustawione najbardziej sprzyjające wartości.
