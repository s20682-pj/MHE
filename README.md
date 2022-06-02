Algorytmy w języku C++ na zajęcia z Metaheurystyk PJATK 2021/2022
Wybrany problem: https://en.wikipedia.org/wiki/Bin_packing_problem

Problem polega na tym, by przedmioty o różnej pojemności zmieścić do jak najmniejszej ilości pojemników.

Dany problem można rozwiązać następującymi algorytmami, które zostały zaimplemetowane:

Algorytm 1 - Algorytm wspinaczkowy w wersji deterministycznej

Algorytm 2 - Algorytm wspinaczkowy w wersji stochastycznej

Algorytm 3 - Algorytm tabu

Algorytm 4 - Algorytm symulowanego wyżarzania


Podczas uruchamiania możnna wywołać następujące argumenty:

-fname - nazwa pliku z danymi, jeżeli pozostanie puste, to nastąpi przejście do samodzielnego wpisania danych

-iterations - ilość iteracji algorytmów

-method - który algorytm ma zostać uruchomiony (all - dla wszystkich, hc dla algorytmu wspinaczkowy w wersji deterministycznej, random dla algorytmu wspinaczkowy w wersji stochastycznej, tabu - dla algorytmu tabu, sa - dla algorytmu symulowanego wyżarzania) [domyślnie jest ustawiona wartość all]

-tabu_size - rozmiar naszego tabu

-quantity - ile przedmiotów ma zostać sprawdzonych

-binSize - rozmiar naszego "śmietnika"

Dołączony zostaje również skrypt, który ukazuje, jak szybko dany algorytm odnajduje najlepsze rozwiązanie, dzięki czemu możemy określić, która metoda jest najlepsza dla danego problemu.

W folderze znajdują się również 2 pliki z przykładowymi danymi. Paramatry mają jako default ustawione najbardziej sprzyjające wartości.
