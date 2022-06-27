./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method hc -howLong 1 > resultHillClimbing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method random -howLong 1 > resultRandomHillClimbing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method tabu -howLong 1 > resultTabu.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method sa -howLong 1 > resultSimulatedAnnealing.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -generations 1000 -howLong 1 > resultGeneticGenerations.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -ending best -howLong 1 > resultGeneticBest.txt

gnuplot -e "plot
 'resultHillClimbing.txt' u 1 w lines,
 'resultRandomHillClimbing.txt' u 1 w lines,
 'resultTabu.txt' u 1 w lines,
 'resultSimulatedAnnealing.txt' u 1 w lines,
 'resultGeneticGenerations.txt' u 1 w lines,
 'resultGeneticBest.txt' u 1 w lines" -p

rm resultHillClimbing.txt resultRandomHillClimbing.txt resultTabu.txt resultSimulatedAnnealing.txt resultGeneticGenerations.txt resultGeneticBest.txt