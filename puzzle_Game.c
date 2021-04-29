#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>
void loadData();
int checkValue(int value);
void Display();
void SuccessMessage();
int Check(int row,int column,int key);
int shuffleCounter();
int checkTotal();
int boundary(int row,int column);
void Levels();
void Undo();
void GameTitle();
void swapValue(int row1,int column1,int row2,int column2);
int puzzle[10][10],index_i,index_j,show[100],row,column,moves,size,stack[100],top=-1;
int main()
{
	char GameEnd,Value;
	int number,input;
	GameTitle();
	Levels();
	if(Value=getch())
	{
		GameEnd='S';
		size=Value-'0';
	}
	while(GameEnd=='S')
	{
		moves=0;row=-1;column=-1,top=-1;
		system("CLS");
		memset(show,0,sizeof(show));
		loadData();
		Display();
		while((input=getch())!='Q')
		{
			if(input==72 || input==80 || input==75 || input==77)  //72-Top,80-Down 75-Left,77-Right
			{
				switch(input)
				{
					case 72:	row=Check(row-1,column,72);break;
					case 80:	row=Check(row+1,column,80);break;
					case 75:	column=Check(row,column-1,75);break;
					case 77:	column=Check(row,column+1,77);break;    
				}
				if(checkTotal())
				{
					SuccessMessage();
					GameEnd='E';
					break;
				}
			}
			else if(input==85)
			{
				if(top!=-1)
				{
					moves--;
					Undo();
				}
				else
				{
					Beep(750,800);
				}
			}
			else if(input==69)
			{
				GameEnd='E';
				break;
			}
			else if(input==82)
			{
				break;
			}
			system("CLS");
			Display();
		
		}
   }
return 0;
}
void GameTitle()
{
	for(index_i=0;index_i<10;index_i++)	printf("\n");
	printf("%*s",43,"");
	
	char Title[100]="PUZZLE GAME";
	for(index_i=0;index_i<strlen(Title);index_i++)
	{
		printf("%c",Title[index_i]);
		usleep(500000);
	}
}
int boundary(int rowindex,int columnindex)
{
	if(rowindex>=1 && rowindex<=4 && columnindex>=1 && columnindex<=4)	return true;
	return false;
}
void Undo()
{
	
	int pop=stack[top];
	top--;
	if(boundary(row+1,column) && puzzle[row+1][column]==pop)
	{
		swapValue(row,column,row+1,column);
		row=row+1;
	}
	else if(boundary(row-1,column) && puzzle[row-1][column]==pop)
	{
		swapValue(row,column,row-1,column);
		row=row-1;
	}
	else if(boundary(row,column+1) && puzzle[row][column+1]==pop)
	{
		swapValue(row,column,row,column+1);
		column=column+1;
	}
	else if(boundary(row,column-1) && puzzle[row][column-1]==pop)
	{
		swapValue(row,column,row,column-1);
		column=column-1;
	}	
}
void Levels()
{
	for(index_i=0;index_i<5;index_i++)	printf("\n");
	printf("%*s",40,"");
	printf("    Levels\n");
	printf("%*s",40,"");
	printf("Easy      2-3\n");
	printf("%*s",40,"");
	printf("Medium    4-6\n");
	printf("%*s",40,"");
	printf("Hard      7-9\n");
}
void SuccessMessage()
{
	system("CLS");
	for(index_i=0;index_i<10;index_i++)	printf("\n");
	printf("%*s",40,"");
	char Success[100]="Successsssss!";
	for(index_i=0;index_i<=strlen(Success);index_i++)
	{
		printf("%c ",Success[index_i]);
		usleep(500000);
	}
	printf("\n");
	printf("%*s",40,"");
	printf("%d moves used",moves);
}
int checkTotal()
{
	int check=1;
	for(index_i=1;index_i<=4;index_i++)
	{
		for(index_j=1;index_j<=4;index_j++)
		{
			if(puzzle[index_i][index_j]!=check)	return false;
			check++;
		}
	}
	return true;
}
void swapValue(int row1,int column1,int row2,int column2)
{
	int t=puzzle[row1][column1];
	puzzle[row1][column1]=puzzle[row2][column2];
	puzzle[row2][column2]=t;
}

int Check(int rowindex,int columnindex,int key)
{

	int value;
	if(key==72)
	{
		if(rowindex>=1)
		{
			stack[++top]=puzzle[rowindex][columnindex];
			moves++;
			value=rowindex;
			swapValue(rowindex,columnindex,rowindex+1,columnindex);
		}
		else
		{
			value=rowindex+1;
			Beep(750,800);
		}
	}
	else if(key==80)
	{
		if(rowindex<=4)
		{
			stack[++top]=puzzle[rowindex][columnindex];
			moves++;
			value=rowindex;
			swapValue(rowindex,columnindex,rowindex-1,columnindex);
		}
		else
		{		
			value=rowindex-1;
			Beep(750,800);
		}
	}
	else if(key==75)
	{
		
		if(columnindex>=1)
		{
			stack[++top]=puzzle[rowindex][columnindex];
			moves++;
			value=columnindex;
			swapValue(rowindex,columnindex,rowindex,columnindex+1);
		}
		else
		{
			value=columnindex+1;
			Beep(750,800);
		}
	}
	else if(key==77)
	{
		
		if(columnindex<=4)
		{
			stack[++top]=puzzle[rowindex][columnindex];
			moves++;
			value=columnindex;
			swapValue(rowindex,columnindex,rowindex,columnindex-1);
		}
		else
		{
			value=columnindex-1;
			Beep(750,800);
		}
	}
	return value;
}
int shuffleCounter()
{
	if(size>=1 && size<=3)	return 3;
	if(size>=4 && size<=6)	return 5;
	if(size>=7 && size<=9)	return 7;
	return 0;
}
void loadData()
{
	int value=1,counter;
	counter=shuffleCounter();
	for(index_i=1;index_i<=4;index_i++)
	{
		for(index_j=1;index_j<=4;index_j++)
		{
			puzzle[index_i][index_j]=value;
			value++;
		}
	}
	row=4;column=4;
	while(counter>0)
	{
		int rowValue=rand()%(4+1);
		int columnValue=rand()%(4+1);
		if(rowValue!=columnValue && rowValue<=4 && columnValue<=4)
		{	
			swapValue(rowValue,columnValue,columnValue,rowValue);
			counter--;	
		}
	}
}
void Display()
{
	for(index_i=1;index_i<=10;index_i++)	printf("\n");
	for(index_i=1;index_i<=4;index_i++)
	{
		printf("%*s",40,"");
		printf("%c",(char)186);
		for(index_j=1;index_j<=4;index_j++)
		{
			printf("%2d ",puzzle[index_i][index_j]);
		}
		printf("%c",(char)186);
		printf("\n");
	}
		printf("\n");
		printf("%*s",35,"");
		printf("E-End    R-Reset    U-Undo");
		printf("\n\n");
		printf("%*s",45,"");
		printf("%d Moves",moves);	
}