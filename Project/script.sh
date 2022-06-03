#!/usr/bin/env bash
./../build/BinPackingProblem -fname data.csv -method hillClimbing -showBestOrAll all > resultHillClimbing.txt
./../build/BinPackingProblem -fname data.csv -method hillClimbingRandom -showBestOrAll all > resultHillClimbingRandom.txt
./../build/BinPackingProblem -fname data.csv -method tabuSearch -showBestOrAll all > resultTabu.txt
./../build/BinPackingProblem -fname data.csv -method simulatedAnnealing -showBestOrAll all > resultSimulatedAnnealing.txt

gnuplot -e "plot
 'resultHillClimbing.txt' u 1:3 w lines,
 'resultHillClimbingRandom.txt' u 1:3 w lines,
 'resultTabu.txt' u 1:3 w lines,
 'resultSimulatedAnnealing.txt' u 1:3 w lines" -p

rm resultHillClimbing.txt resultHillClimbingRandom.txt resultTabu.txt resultSimulatedAnnealing.txt