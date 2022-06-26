#!/usr/bin/env bash
./../build/KnapsackProblem -fname data_test.csv -method hc > resultHillClimbing.txt
./../build/KnapsackProblem -fname data_test.csv -method random > resultHillClimbingRandom.txt
./../build/KnapsackProblem -fname data_test.csv -method tabu > resultTabu.txt
./../build/KnapsackProblem -fname data_test.csv -method sa > resultSimulatedAnnealing.txt
./../build/KnapsackProblem -fname data_test.csv -method genetic > resultGenetic.txt

gnuplot -e "plot
 'resultHillClimbing.txt' u 1:3 w lines,
 'resultHillClimbingRandom.txt' u 1:3 w lines,
 'resultTabu.txt' u 1:3 w lines,
 'resultSimulatedAnnealing.txt' u 1:3 w lines,
 'resultGenetic.txt' u 1:3 w lines" -p

rm resultHillClimbing.txt resultHillClimbingRandom.txt resultTabu.txt resultSimulatedAnnealing.txt resultGenetic.txt