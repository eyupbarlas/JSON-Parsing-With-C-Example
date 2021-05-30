all: compile run
compile:
	gcc -I ./include/ -o ./lib/cJSON.o -c ./src/cJSON.c 
	gcc -I ./include/ -o ./lib/Hisse.o -c ./src/Hisse.c
	gcc -I ./include/ -o ./lib/Emir.o -c ./src/Emir.c
	gcc -I ./include/ -o ./lib/Portfoy.o -c ./src/Portfoy.c
	gcc -I ./include/ -o ./lib/Banka.o -c ./src/Banka.c
	gcc -I ./include/ -o ./bin/Test ./lib/cJSON.o ./lib/Hisse.o ./lib/Emir.o ./lib/Portfoy.o ./lib/Banka.o ./src/Test.c 

	@echo ==== Compile successful. ====
run:
	./bin/Test