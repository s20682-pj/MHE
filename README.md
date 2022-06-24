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

?-quantity - ile przedmiotów ma zostać sprawdzonych (int)? - /do sprawdzenia/

-backpackSize - rozmiar naszego plecaka (int) [1-5]

-uniformRealDistributionIsSet - wartość dla symulowanego wyżarzania, która definiuje rodzaj rozkładu (true/false) [4]

?-showAllOrBest - pokaż wszystkie wyniki lub najlepszą kombinację (best/all)? - /do sprawdzenia/

-crossing - metoda crossowania rodziców w algorytmie genetycznym (half dla dzielenia po połowie, ) [5]

-mutation - rodzaj mutowania utworzonych dzieci (random - losowy chromosom mutuje, ) [5]

-ending - warunek do zakończenia algorytmu genetycznego (best - czy poprzednie pokolenie miało lepszy wynik niż nowe, ) [5]

Dołączony zostaje również skrypt, który ukazuje, jak szybko dany algorytm odnajduje najlepsze rozwiązanie, dzięki czemu możemy określić, która metoda jest najlepsza dla danego problemu.

W folderze znajduje się również plik z przykładowymi danymi. Paramatry mają jako default ustawione najbardziej sprzyjające wartości.
