gcc -o game main.c -lglfw -lGL

./game

gcc -o game src/Math/*.c src/Utilities/*.c main.c -lglfw -lGL -lm -Wall 