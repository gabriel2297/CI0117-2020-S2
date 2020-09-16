all: array_thrsafe_mutex array_thrsafe_rwlock

array_thrsafe_mutex: array_thrsafe_mutex.c
	rm -rf array_thrsafe_mutex
	gcc array_thrsafe_mutex.c -o array_thrsafe_mutex -pthread
array_thrsafe_rwlock: array_thrsafe_rwlock.c
	rm -rf array_thrsafe_rwlock
	gcc array_thrsafe_rwlock.c -o array_thrsafe_rwlock -pthread

