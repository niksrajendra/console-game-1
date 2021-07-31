#ifndef __CONSOLE_H
#define __CONSOLE_H

struct buffer
{
	unsigned int **ans;
	unsigned int **puz;
};

struct buffer init_arr(unsigned char dimension);
void swap(unsigned int first, unsigned int second, unsigned char dimension, unsigned int** array);
void display_arr(unsigned char dimension,  unsigned int **array);
void move_num(int key, unsigned char dimension, unsigned int **array);
void check_arr(unsigned char dimension, unsigned int **array1, unsigned int **array2);

#endif
