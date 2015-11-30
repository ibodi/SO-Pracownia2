compile: philo.c
	gcc -std=c99 -pthread philo.c -o Philo -lm
run: ./Philo 
	./Philo ${ARGS}
test: ./Philo
	./Philo -s 0 -i 1000 -c 1
clean: ./Philo
	rm ./Philo
