#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h> 
#include <string.h>
#include "console game1.h"

struct position
{
	unsigned char x;
	unsigned char y;
}pos = {3,3};

//unsigned int** puzzle;

int arr[4][4] = {1,4,15,7,
				 8,10,2,11,
		 		 14,3,6,13,
		 		 12,9,5,16},
	ans[4][4] = {1,2,3,4,
		     	 5,6,7,8,
		 		 9,10,11,12,
		 		 13,14,15,16};

int main()
{
	struct buffer b1;
	unsigned int **puzzle, **answer;
	int i,j,value,count = 0, key;
	char code[10],string[10], order;
	initscr();
	noecho();
	keypad ( stdscr, TRUE );
	//display_arr();
	order = 5;
	b1 = init_arr(order);
	puzzle = b1.puz;
	answer = b1.ans;
	while(key != 27)
	{
		//system("clear");
		clear();
		move(0,0);
		printw("Welcome to puzzle game");
		display_arr(order, puzzle);
		check_arr(order, puzzle, answer);
		refresh();
		key = getch();
		move_num(key, order, puzzle);
		//check_arr();
	    //refresh();
	}
	endwin();
	return 0;
}
struct buffer init_arr(unsigned char dimension)
{
	struct buffer b2;
	unsigned char i, j, k;
	unsigned int **solved, **scrambled, num_element;
	num_element = dimension*dimension;
	solved = (unsigned int **)malloc(sizeof(unsigned int *)*dimension);
	scrambled = (unsigned int **)malloc(sizeof(unsigned int *)*dimension);
	srand(time(0)); 
	for(i = 0; i < dimension; i++)
	{
		solved[i] = (unsigned int *)malloc(sizeof(unsigned int)*dimension);
		scrambled[i] = (unsigned int *)malloc(sizeof(unsigned int)*dimension);
		for(j = 0; j < dimension; j++)
		{
			solved[i][j] = i*dimension + j + 1;
			scrambled[i][j] = solved[i][j]; // initially both solved and scrambled are equal
		}
	}
	for(k = 0; k < num_element; k++)
	{
		unsigned int index;
		index = rand() % num_element;
		swap((num_element - k - 1), index, dimension, scrambled);
	}
	b2.puz = scrambled;
	b2.ans = solved;
	return b2; 
}

void swap(unsigned int first, unsigned int second, unsigned char dimension, unsigned int** array)
{
	unsigned int first_x, first_y, second_x, second_y;
	unsigned int temp;
	first_x = first % dimension;
	first_y = first / dimension;
	second_x = second % dimension;
	second_y = second / dimension;
	temp = array[first_y][first_x];
	array[first_y][first_x] = array[second_y][second_x];
	array[second_y][second_x] = temp;
}

void display_arr(unsigned char dimension, unsigned int **array)
{
	int i,j;
	//printf("\r\n");
	printw("\n");
	for(i = 0; i < dimension; i++)
	{
		for(j = 0; j < dimension; j++)
		{
			if(array[i][j] == (dimension*dimension))
			{
				//printf("\t");
				printw("\t");
				pos = (struct position){j, i};
			}
			else
			{
				//printf("\t%2d",arr[i][j]);
				printw("\t%2d",array[i][j]);
			}
		}
		//printf("\r\n\n");
		printw("\n\n");
	}
}

void move_num(int key, unsigned char dimension, unsigned int **array)
{
	int temp;
	switch(key)
	{
		case KEY_UP:if(pos.y != 0)
					{
						temp = array[pos.y][pos.x];
						array[pos.y][pos.x] = array[pos.y - 1][pos.x];
						array[pos.y - 1][pos.x] = temp;
						pos.y = pos.y - 1;
					}
      				break;
		case KEY_DOWN:if(pos.y != (dimension - 1))
					{
						temp = array[pos.y][pos.x];
						array[pos.y][pos.x] = array[pos.y + 1][pos.x];
						array[pos.y + 1][pos.x] = temp;
						pos.y = pos.y + 1;
					}
      				break;
		case KEY_LEFT:if(pos.x != 0)
					{
						temp = array[pos.y][pos.x];
						array[pos.y][pos.x] = array[pos.y][pos.x - 1];
						array[pos.y][pos.x - 1] = temp;
						pos.x = pos.x - 1;
					}
      				break;
		case KEY_RIGHT:if(pos.x != (dimension - 1))
					{
						temp = array[pos.y][pos.x];
						array[pos.y][pos.x] = array[pos.y][pos.x + 1];
						array[pos.y][pos.x + 1] = temp;
						pos.x = pos.x + 1;
					}
      				break;
	}
}

void check_arr(unsigned char dimension, unsigned int **array1, unsigned int **array2)
{
	int i,j;
	unsigned int count = 0;
	for(i = 0;i<dimension;i++)
	{
		for(j = 0;j<dimension;j++)
		{
			if(array1[i][j] == array2[i][j])
			{
				count++;
			}
		}
	}
	//printf("\r\n count value %d", count);
	printw("\n count value %d", count);
	if(count == (dimension*dimension))
	{
		//printf("\r\n you have solved the puzzle");
		printw("\n you have solved the puzzle");
	}
}
