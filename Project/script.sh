#!/usr/bin/env bash
./../build/BinPackingProblem -fname ../data/data.csv -method hillClimbing > resultHillClimbing.txt
./../build/BinPackingProblem -fname ../data/data.csv -method hillClimbingRandom > resultHillClimbingRandom.txt
./../build/BinPackingProblem -fname ../data/data.csv -method tabuSearch > resultTabu.txt
./../build/BinPackingProblem -fname ../data/data.csv -method simulatedAnnealing > resultSimulatedAnnealing.txt

gnuplot -e "plot
 'resultHillClimbing.txt' u 1:3 w lines,
 'resultHillClimbingRandom.txt' u 1:3 w lines,
 'resultTabu.txt' u 1:3 w lines,
 'resultSimulatedAnnealing.txt' u 1:3 w lines" -p

rm resultHillClimbing.txt resultHillClimbingRandom.txt resultTabu.txt resultSimulatedAnnealing.txt