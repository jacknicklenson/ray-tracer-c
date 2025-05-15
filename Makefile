all:
	gcc main.c -o raytracer && ./raytracer > image.ppm

clean:
	rm -f raytracer
