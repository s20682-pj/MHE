./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method hc -howLong 1 > result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method random -howLong 1 > result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method tabu -howLong 1 > result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method sa -howLong 1 > result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -generations 1000 -howLong 1 > result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -ending best -howLong 1 > result.txt

gnuplot -e "
  set size 1, 1
  set boxwidth 0.75
  set style fill solid
  plot 'result.txt' using 2:xtic(1) with boxes" -p

rm result.txt