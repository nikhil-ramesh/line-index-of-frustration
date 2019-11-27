objects = load_data.o store_data.o utility.o lof_driver.o

frustration : $(objects)
	gcc -o $@ $(objects) -lm

load_data.o : load_data.c
	gcc -c load_data.c

store_data.o : store_data.c
	gcc -c store_data.c

utility.o : utility.c
	gcc -c utility.c

lof_driver.o : load_data.c store_data.c utility.c lof_driver.c
	gcc -c lof_driver.c
