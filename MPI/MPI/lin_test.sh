mpic++ EntryPoint.cpp -o EntryPoint
mpirun -np $1 ./EntryPoint $2 >log_thread_count_$1_matrix_size_$2.log