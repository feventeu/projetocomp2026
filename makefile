ProjetoAlbum/

main.c
figurinha.c
figurinha.h

arquivo.c
arquivo.h

makefile

all:
	gcc main.c figurinha.c arquivo.c -o album

run:
	./album