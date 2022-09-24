default: build run

source_name = main.c
executable_name = lab_1

build:
	@gcc $(source_name) -o $(executable_name)

run:
	@./$(executable_name)

