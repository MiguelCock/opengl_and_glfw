To compile the code you will nee to install the following librarie:

======> Linux:
------> sudo apt install libglfw3 libglfw3-dev

For compiling the projects from 1 to 3 where i did not create any library you can use the following command:

------> gcc -o game main.c -lglfw -lGL


Any other folder from the 4 and on will be compile using the following command:

------> gcc -o game src/*.c main.c -lglfw -lGL -lm -Wall
------> gcc -o createEnt src/*.c createEnt.c -lglfw -lGL -lm -Wall

And of course for running the app just write this:

------> ./game

si
