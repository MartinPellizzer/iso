build:
	gcc -Wall \
	./src/*.c \
	-o game \
	-lm \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf;

clean:
	rm ./game

run:
	./game

