#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <time.h>
#include <pthread.h>
#include <graphics.h>


using namespace std;

struct node
{
	int i;
	int j;
	char body;
	node *next;
};

void renderSnake(void);

char boundary[100][100], headChar, bodyElement;
int foodPosX[4];
int foodPosY[4];
node *head;
int posX, posY, xInc, yInc, count;
int userScore;

void addBody(int i, int j)
{
	node *tempBody, *cur;
	int flag = 0;
	cur = head->next;
	tempBody = new node();
	while(cur)
	{
		if(cur->i == i &&cur->j == j)
			break;
		cur = cur->next;
	}
	if(!cur)
	{
		tempBody->i = i;
		tempBody->j = j;
		tempBody->body = bodyElement;
		tempBody->next = head;
		head = NULL;
		head = tempBody;
		tempBody = NULL;
	}
	else
	{
		tempBody = cur;
		while(tempBody)
		{
			boundary[tempBody->i][tempBody->j] = '.';
			tempBody = tempBody->next;
		}
		cur->next = NULL;
		tempBody = NULL;
		delete tempBody;
	}	
}

void setup()
{
	for(int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			boundary[i][j] = '.';

	head = new node();
	head->body = '*';
	head->i = 0;
	head->j = 0;
	head->next = NULL;
	addBody(0, 1);

	xInc = 0;
	yInc = 1;
	count = 0;

	bodyElement = '-';
	headChar = '>';

	for(int i = 0; i < 4; i++)
	{
		foodPosX[i] = 0;
		foodPosY[i] = 0;
	}

	userScore = 0;	
}

void renderFood()
{
	boundary[foodPosX[0]][foodPosY[0]] = '.';
	boundary[foodPosX[1]][foodPosY[1]] = '.';
	boundary[foodPosX[2]][foodPosY[2]] = '.';
	boundary[foodPosX[3]][foodPosY[3]] = '.';

	int tempX, tempY;
	for(int i = 0; i < 4; i++)
	{
		tempX = rand()%20;
		tempY = rand()%20;
		boundary[tempX][tempY] = '*';
		foodPosX[i] = tempX;
		foodPosY[i] = tempY;
	}

}

void deleteBody()
{
	node *temp = head;
	while(temp->next->next)
		temp = temp->next;
	boundary[temp->next->i][temp->next->j] = '.';
	temp->next = NULL;
	temp = NULL;
}

void renderSnake()
{
	cout << "\n";
	node *temp = head->next;
	while(temp)
	{
		boundary[temp->i][temp->j] = temp->body;
		temp = temp->next;
	}
	boundary[head->i][head->j] = headChar;
	for(int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
			cout << boundary[i][j];
		cout << "\n";
	}

	usleep(1000000);
	int ret = system("clear");	
}

void *get_input(void *unused)
{	
	char g = getch();
	xInc = 0; yInc = 0;
	if(g == 'w')
	{
		xInc = -1;
		headChar = '^';
		bodyElement = '|';
	}
	else if (g == 's')
	{
		xInc = 1;
		headChar = 'v';
		bodyElement = '|';
	}
	else if (g == 'a')
	{
		yInc = -1;
		headChar = '<';
		bodyElement = '-';
	}
	else if(g == 'd')
	{
		yInc = 1;
		headChar = '>';
		bodyElement = '-';
	}
	pthread_exit(NULL);			
}

int main()
{
	setup();
	posX = 0;
	posY = 2;
	int flag = 0;
	int headX = 0, headY = 0;
	pthread_t motion_thread_id, food_id;
	while(headX >= 0 && headY >= 0 && headX < 20 && headY < 20)
	{
		int ret = pthread_create(&motion_thread_id, NULL, get_input, NULL); 
		if(!count)
		{
			renderFood();
			count = 10;
		}
		else
			count--;
		addBody(posX, posY);
		headX = head->i;
		headY = head->j;
		if(!(headX==foodPosX[0]&&headY==foodPosY[0]||headX==foodPosX[1]&&headY==foodPosY[1]||headX==foodPosX[2]&&headY==foodPosY[2]||headX==foodPosX[3]&&headY==foodPosY[3]))	
			deleteBody();	
		else
			userScore++;
		renderSnake();
		pthread_detach(motion_thread_id);
		posX += xInc;
		posY += yInc;
	}
	int ret = system("clear");
	cout << "Game Over \n" << "User Score is : " << userScore << endl;
	return 0;
}