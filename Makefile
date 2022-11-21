all:
	gcc -o backend backend.c users_lib.o
	gcc -o frontend frontend.c

backend:
	gcc -o backend backend.c users_lib.o

frontend:
	gcc -o frontend frontend.c
