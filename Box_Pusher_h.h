//----------------------------------------------------------------------------------------
//		������(����̨��)		����:EyreFree		���뻷��:VS2008		2012/11/30
//----------------------------------------------------------------------------------------


//����ͷ�ļ�------------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "Box_Map.h"


//����------------------------------------------------------------------------------------

POINT me,old,trend;				//��ǰλ�ã��ɵ�λ�ã�̽��λ��
int size=0;						//��ͼ�ߴ�


//���ع��--------------------------------------------------------------------------------

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


//��λ���--------------------------------------------------------------------------------

void Gotoxy(int x,int y)
{ 
	COORD pos; 
	pos.X = x - 1; 
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos); 
}


//���ݳ�ʼ��------------------------------------------------------------------------------

void Init()
{
	int i=0,j=0;
	me.x =0;
	me.y =0;
	trend.x =0;
	trend.y =0;
	old.x =0;
	old.y =0;
	size=sqrt(sizeof(map)/sizeof(int));		//��ȡ��ͼ�߳�
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(map[i][j]==4)				//��ȡ�����ʼλ��
			{
				me.x =i;
				me.y =j;
			}
		}
	}
	if(me.x==0||me.y==0)					//����λ�÷Ƿ��򷵻ش�����Ϣ
	{
		MessageBox(NULL,"��ͼ���ݴ���\n\nInit","����ʧ�ܣ�",MB_ICONEXCLAMATION);
		system("pause");
		exit(0);
	}
}


//��۵���--------------------------------------------------------------------------------

void Appearance()
{
	char screen_size[26]="mode con cols=17 lines=09";
	screen_size[14]=((size-7)*2+23)/10+48;
	screen_size[15]=((size-7)*2+23)%10+48;
	screen_size[23]=(size-7+12)/10+48;
	screen_size[24]=(size-7+12)%10+48;
	system(screen_size);					//������С
	system("color f0");						//������ɫ
	system("title ������");					//���ñ���
	HideCursor();							//���ع��
}


//���ͼ��--------------------------------------------------------------------------------

void Showscreen()
{
	int i=0,j=0,temp=0;
	Gotoxy(1,1);				//����������Ͻ�
	for(i=0;i<size;i++)
	{
		printf("\n  ");
		for(j=0;j<size;j++)
		{
			switch(map[i][j])
			{
			case 0:
				temp=0;
				break;
			case 1:
				temp=35;
				break;
			case 2:
				temp=43;
				break;
			case 3:
				temp=15;
				break;
			case 4:
				temp=1;
				break;
			default:			//��ͼ��Ϣ�Ƿ��򷵻ش�����Ϣ
				MessageBox(NULL,"��ͼ���ݴ���\n\nShowscreen","����ʧ�ܣ�",MB_ICONEXCLAMATION);
				system("pause");
				exit(0);
				break;
			}
			printf("%c ",temp);
		}
	}
}


//��ʤ�ж�--------------------------------------------------------------------------------

int Is_not_win()
{
	int i=0,j=0;
	for(i=0;i<size;++i)
	{
		for(j=0;j<size;++j)
		{
			if(map_goal[i][j]==2&&map[i][j]!=3)
				return 1;
		}
	}
	return 0;
}


//�ָ�Ŀ��--------------------------------------------------------------------------------

void Rollback()
{
	int i=0,j=0;
	for(i=0;i<size;++i)
	{
		for(j=0;j<size;++j)
		{
			if(map_goal[i][j]==2&&map[i][j]==0)
				map[i][j]=2;
		}
	}
}


//�ƶ�����--------------------------------------------------------------------------------

void Move(int direct)
{
	POINT temp;
	trend=me;
	switch(direct)
	{
	case 'w':
		--trend.x;
		break;
	case 's':
		++trend.x;
		break;
	case 'a':
		--trend.y;
		break;
	case 'd':
		++trend.y;
		break;
	default:
		break;
	}
	temp=trend;
	if(map[trend.x][trend.y]==0||map[trend.x][trend.y]==2)
	{
		old=me;	
		me=trend;
	}
	else if(map[trend.x][trend.y]==3)
	{
		switch(direct)
		{
		case 'w':
			--temp.x;
			break;
		case 's':
			++temp.x;
			break;
		case 'a':
			--temp.y;
			break;
		case 'd':
			++temp.y;
			break;
		default:
			break;
		}
		if(map[temp.x][temp.y]==0||map[temp.x][temp.y]==2)
		{
			map[temp.x][temp.y]=3;
			map[trend.x][trend.y]=0;
			old=me;
			me=trend;
		}
	}
	if(map[me.x][me.y]!=4)
	{
		map[old.x][old.y]=0;
		map[me.x][me.y]=4;
		old=me;
	}
	Rollback();					//�ָ������ǵ�Ŀ��ͼ��
}


//ѭ��------------------------------------------------------------------------------------

void Run()
{
	Showscreen();				//���ͼ��
	while(Is_not_win())			//�ǻ�ʤ�ж��ɹ������
	{
		Move(getch());			//���������ƶ�
		Showscreen();			//���ͼ��
	}
	system("title ��Ӯ�ˣ�");
	printf("\n\n  ��Ӯ�ˣ�\n\n  ");
	system("pause");
}