show: run
	feh im.ppm
run: raytracer
	./raytracer.out > im.ppm;
raytracer:
	gcc main.c ray.c vec3.c color.c sphere.c hittable.c hittable_list.c -lm -o raytracer.out
