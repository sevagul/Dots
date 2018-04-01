#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

class Menu
{
	COORD field;
	int w, h;
	char* player1, *player2; 
	public:
		Menu()
		{
			player1 = new char[15];
			player2 = new char[15];
			strcpy(player1, "Player 1");
			strcpy(player2, "Player 2");
			w=119;
			h=28;
		}
		Menu(int hh, int ww)
		{
			player1 = new char[15];
			player2 = new char[15];
			strcpy(player1, "Player 1");
			strcpy(player2, "Player 2");
			h=hh;
			w=ww;
		}
		void main()
		{
			COORD co={w/4, 0};
			HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
			CONSOLE_SCREEN_BUFFER_INFO bi;
			SetConsoleCursorPosition(h, co);
			cout<<"Welcome to the DOTS";
			co.Y++;
			SetConsoleCursorPosition(h, co);
			cout<<"Please enter the name of the ";	
			SetConsoleTextAttribute(h, 31);
			cout<<"First";
			SetConsoleTextAttribute(h, 7);
			cout<<" Player: ";
			co.Y++;
			SetConsoleCursorPosition(h, co);
			gets(player1);
			co.Y++;
			SetConsoleCursorPosition(h, co);
			cout<<"Please enter the name of the ";	
			SetConsoleTextAttribute(h, 32);
			cout<<"Second";
			SetConsoleTextAttribute(h, 7);
			cout<<" Player: ";
			
			co.Y++;
			SetConsoleCursorPosition(h, co);
			gets(player2);
			co.Y++;
			SetConsoleCursorPosition(h, co);
			CleanConsole();
			co={w/4, 0};
			SetConsoleCursorPosition(h, co);
			cout<<player1<<" vs "<<player2<<endl;
			co={0, 1};
			SetConsoleCursorPosition(h, co);
				
		}
		void CleanConsole()
		{
			COORD co={0, 0};
			HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
			CONSOLE_SCREEN_BUFFER_INFO bi;
			GetConsoleScreenBufferInfo( h, &bi );
			long q =bi.dwSize.X *bi.dwSize.Y;
			DWORD count;
			const int NotUsed = system( "color 07" );
			FillConsoleOutputCharacter(h, /*(TCHAR)*/ ' ', q , co , &count);
			SetConsoleCursorPosition(h, co);
		}
			
};


class Dot
{
	private:
		int player;
		int x;
		int y;
		static int count;
	public:
		Dot ()
		{
			player=0;
			x=5000;
			y=5000;
			count++;
		}
		~Dot ()
		{
		}
		
};

class Field
{
	private:
		int Mass[30][100];
	public:
		Field ()
		{
			for(int i=0; i<30; i++)
			{
				for(int j=0; j<100; j++)
				{
					Mass[i][j]=0;	
				}	
			}
		}
		void setdot(int i, int j, int v)
		{
			Mass[i][j]=v;
		}
		int getdot (int i, int j)
		{
			return Mass[i][j];
		}
		void display()
		{
			for(int i=0; i<30; i++)
			{
				for(int j=0; j<100; j++)
				{
					cout<<Mass[i][j];	
				}	
				cout<<endl;
			}	
		}
};

void display(COORD c)
{
	cout<<c.X<<" "<<c.Y<<endl;
}

void dmas(int** m, int x, int y)
{
	for(int j=0; j<y; j++)
	{
		cout<<' ';
		for(int i=0; i<x; i++)
		{
			if(!m[i][j])
			cout<<(char)176;
			else
			cout<<m[i][j];
		}
		cout<<endl;
	}
}

void deletemas(int***mas, int x, int y)
{
	for(int i=0; i<x; i++)
	{
		delete[] (*mas)[i]; 
	}
	delete[]*mas;
}

void initmas(int***m, int x, int y)
{
	*m=new int*[x];
	for(int i=0; i<x; i++)
	{
		(*m)[i]=new int[y];
		for(int j=0; j<y; j++)
		{
			(*m)[i][j]=0;
		}
	}
}
void draw(HANDLE h, CONSOLE_SCREEN_BUFFER_INFO bi, int*** m, int x, int y)
{
	COORD co={0, 1};
	char c=13;
	int bo=0;
	while(c=='w'||c=='a'||c=='s'||c=='d'||c==13)
	{
		c= _getch();
		switch(c)
		{
			case 119: 
			{	
				GetConsoleScreenBufferInfo(h, &bi);
				if(bi.dwCursorPosition.Y>1)
				bi.dwCursorPosition.Y-=1;
				else
				{
					bi.dwCursorPosition.Y-=1;
					SetConsoleCursorPosition(h, bi.dwCursorPosition);
					bi.dwCursorPosition.Y+=1;
					SetConsoleCursorPosition(h, bi.dwCursorPosition);
				}
				SetConsoleCursorPosition(h, bi.dwCursorPosition);
				break;
			}
			case 97: 
			{
				GetConsoleScreenBufferInfo(h, &bi);
				if(bi.dwCursorPosition.X>1)
				bi.dwCursorPosition.X-=1;
				SetConsoleCursorPosition(h, bi.dwCursorPosition);
				break;
			}
			case 115: 
			{
				GetConsoleScreenBufferInfo(h, &bi);
				if(bi.dwCursorPosition.Y<y)
				{
					bi.dwCursorPosition.Y+=1;
					SetConsoleCursorPosition(h, bi.dwCursorPosition);
				}
				break;
			}
			case 100: 
			{	
				GetConsoleScreenBufferInfo(h, &bi);
				if(bi.dwCursorPosition.X<x)
				{
					bi.dwCursorPosition.X+=1;
					SetConsoleCursorPosition(h, bi.dwCursorPosition);
				}
				break;
			}
			case 13: 
			{
				bo=!bo;
				GetConsoleScreenBufferInfo(h, &bi);
				if(bo)
				{
					SetConsoleTextAttribute(h, 32);
					(*m)[bi.dwCursorPosition.X-1][bi.dwCursorPosition.Y-1]=1;
					cout<<(*m)[bi.dwCursorPosition.X-1][bi.dwCursorPosition.Y-1];
					SetConsoleCursorPosition(h, bi.dwCursorPosition);
					SetConsoleTextAttribute(h, 7);
				}
				else
				{
					SetConsoleTextAttribute(h, 31);
					(*m)[bi.dwCursorPosition.X-1][bi.dwCursorPosition.Y-1]=2;
					cout<<(*m)[bi.dwCursorPosition.X-1][bi.dwCursorPosition.Y-1];
					SetConsoleCursorPosition(h, bi.dwCursorPosition);
					SetConsoleTextAttribute(h, 7);
				}
			break;
			}
			default:
			{
				if( !(c==27||c=='j') ) 
					c = 13;
				else
				{ 
					if(c=='j')
					{					
						GetConsoleScreenBufferInfo(h, &bi);
						SetConsoleCursorPosition(h, co);
						dmas(*m, x, y);						
						SetConsoleCursorPosition(h, bi.dwCursorPosition);
						c=13;
					}
					else
					SetConsoleCursorPosition(h, co);
					break;
				}
			}
		}	
	}
}

int main()
{
	SetConsoleTitle( "___________Dots____________" );
	COORD co={ 1, 1 };
	Sleep( 3000 );
	HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo( h, &bi );
	int a = bi.dwMaximumWindowSize.X, b = bi.dwMaximumWindowSize.Y, sa = a - 2, sb = b/2 + 5 ;
	int** mass;
	initmas( &mass, sa, sb );
	Menu m( sa, sb );
	m.main();
	dmas ( mass, sa, sb );
	SetConsoleCursorPosition( h, co );
	draw( h, bi, &mass, sa, sb );
	m.CleanConsole();
	deletemas( &mass, sa, sb );
	Sleep( 3000 );
	return 0;
}
