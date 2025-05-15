all:
	gcc -ggdb main.c -o raytracer && ./raytracer > image.ppm

clean:
	rm -f raytracer
