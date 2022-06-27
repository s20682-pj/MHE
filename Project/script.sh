./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method hc -script 1 > resultHillClimbing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method random -script 1 > resultRandomHillClimbing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method tabu -script 1 > resultTabu.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method sa -script 1 > resultSimulatedAnnealing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -generations 1000 -script 1 > resultGenetic.txt

gnuplot -e "plot
 'resultHillClimbing.txt' u 1:2 w lines,
 'resultRandomHillClimbing.txt' u 1:2 w lines,
 'resultTabu.txt' u 1:2 w lines,
 'resultSimulatedAnnealing.txt' u 1:2 w lines" -p

gnuplot -e "plot 'resultGenetic.txt' u 1:2 w lines" -p

rm resultHillClimbing.txt resultRandomHillClimbing.txt resultTabu.txt resultSimulatedAnnealing.txt resultGenetic.txt