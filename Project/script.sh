./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method hc -script 1 > resultHillClimbing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method random -script 1 > resultRandomHillClimbing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method tabu -script 1 > resultTabu.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method sa -script 1 > resultSimulatedAnnealing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -generations 1000 -script 1 > resultGenetic.txt

gnuplot -e "plot 'resultHillClimbing.txt' using 1:2 title 'score' with lines" -p
#https://gnuplot.respawned.com/
#9 39
#12 43
#31 46
#32 47

gnuplot -e "plot
 'resultRandomHillClimbing.txt' u 1:2 title 'random' with lines,
 'resultTabu.txt' u 1:2 title 'tabu' with lines,
 'resultSimulatedAnnealing.txt' u 1:2 title 'sa' with lines" -p

gnuplot -e "plot 'resultGenetic.txt' using 1:2 title 'score' with lines" -p

rm resultHillClimbing.txt resultRandomHillClimbing.txt resultTabu.txt resultSimulatedAnnealing.txt resultGenetic.txt