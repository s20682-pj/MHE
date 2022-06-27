./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method hc -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method random -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method tabu -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method sa -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -generations 1000 -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -ending best -howLong 1 >> result.txt

gnuplot -e "set style fill solid;
  set boxwidth 0.75;
  plot 'result.txt' using 2:xtic(1) with boxes" -p

rm result.txt

