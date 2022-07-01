./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method hc -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method random -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method tabu -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method sa -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -generations 1000 -howLong 1 >> result.txt
./cmake-build-debug/KnapsackProblem -fname ./cmake-build-debug/data_test.csv -method genetic -ending best -howLong 1 >> result.txt

gnuplot -e "set style fill solid;
  set boxwidth 0.75;
  plot 'result.txt' using 2:xtic(1) with boxes title 'time'" -p

#HC 0.001
#HCR 0.06
#Tabu 0.132
#SA 0.003
#GG 1.365
#GB 0.006

rm result.txt

