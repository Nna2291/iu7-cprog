#!/bin/bash

sizes=(500 1000 1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500 8000 8500 9000 9500 10000)
optimize=("O0" "O1" "O2" "O3" "Ofast")

sort=(0 1)

for item in "${sizes[*]}"; do
    echo "$item"
done

for opt_levels in ${optimize[*]}; do

    echo "N,ans_q,counter_q,rse_q,ans_m,counter_m,rse_m" >> sort_asc"$opt_levels"_avg.txt
    echo "N,ans_q,counter_q,rse_q,ans_m,counter_m,rse_m" >> sort_rand"$opt_levels"_avg.txt
    
    for item in ${sizes[*]}; do
        gcc -"$opt_levels" -std=gnu99 -DN="$item" -DF=1 -I../inc/ -o sort_size_"$item".exe main.c ../src/sorting.c ../src/array_io.c ../src/array_loc.c ../src/calculate_time.c -lm
        # ./sort_size_"$item".exe
        ./sort_size_"$item".exe >> sort_asc"$opt_levels"_avg.txt
        echo "$item" done
        rm tempq.txt
        rm tempm.txt
        rm sort_size_"$item".exe 
        # break

        gcc -"$opt_levels" -std=gnu99 -DN="$item" -DF=0 -I../inc/ -o sort_size_"$item".exe main.c ../src/sorting.c ../src/array_io.c ../src/array_loc.c ../src/calculate_time.c -lm
        # ./sort_size_"$item".exe
        ./sort_size_"$item".exe >> sort_rand"$opt_levels"_avg.txt
        echo "$item" done
        rm tempq.txt
        rm tempm.txt
        rm sort_size_"$item".exe 
        # break
    done
done
