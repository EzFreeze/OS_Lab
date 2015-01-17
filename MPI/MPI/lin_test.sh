mpic++ EntryPoint.cpp -o EntryPoint
mkdir Logs
mpirun -np $1 ./EntryPoint $2 >Logs/log_thread_$1_matrix_size_$2.log