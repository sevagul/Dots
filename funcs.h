#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <wincon.h>

using namespace std;


struct Dot
{
	int player;
	int status;
	int isoccupated;
};

class Menu;

void draw( HANDLE h, CONSOLE_SCREEN_BUFFER_INFO bi, Dot** m, int x, int y, Menu& menu );//main game function
void search1(Dot** m, int x, int y, int c1, int c2, Menu& menu);//head of circle-searching function
void search(Dot** m, int** info, int x, int y, int c1, int c2, int start, int player, Menu& menu, int* result);//main part of it
void printo(COORD c, string s);//some tools...
void printo(COORD c, string s, int col);
void printo(COORD c, int s);
void scoring1(Dot** m, int** info, int x, int y, Menu& menu);//head of occupated dots - searching function
void scoring(Dot** m, int** info, int x, int y, int c1, int c2,  Menu& menu);//main part of it
void dmas( Dot** m, int x, int y );//some tools...
void dimas( int** m, int x, int y, COORD c );
void deletemas( Dot*** mas, int x, int y );
void initimas( int*** m, int x, int y );
void dmas( Dot** m, int x, int y );


class Menu
{
	private:
		COORD field;
		int w, h;
		int score1, score2;
		char* player1, *player2; 
	public:
		
		Menu()
		{
			score1 = 0;
			score2 = 0;
			player1 = new char[15];
			player2 = new char[15];
			strcpy(player1, "Player 1");
			strcpy(player2, "Player 2");
			w=119;
			h=28;
		}
		
		Menu(int ww, int hh)
		{
			score1 = 0;
			score2 = 0;
			player1 = new char[10];
			player2 = new char[10];
			strcpy(player1, "Player 1");
			strcpy(player2, "Player 2");
			h=hh;
			w=ww;
		}
		
		~Menu()
		{
			delete[] player1;
			delete[] player2;
		}
		
		char* getp1()
		{
			return player1;
		}
		
		char* getp2()
		{
			return player2;
		}
		
		int gs1(){ return score1; }
		int gs2(){ return score2; }
		void ss1(int a){ score1 = a; }
		void ss2(int a){ score2 = a; }
		void ss1(){ score1++; }
		void ss2(){ score2++; }
		
		void mainmenu()
		{
			COORD co={w/3, 0};
			HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
			CONSOLE_SCREEN_BUFFER_INFO bi;
			SetConsoleCursorPosition(h, co);
			cout<<"Welcome to the DOTS";
			co.Y++;
			SetConsoleCursorPosition(h, co);
			cout<<"Please enter the name of the ";	
			SetConsoleTextAttribute(h, 31);
			cout<< "First"; 
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
			gets( player2 );
			co.Y++;
			SetConsoleCursorPosition(h, co);
			CleanConsole();
			co.X=1;
			co.Y=0;
			SetConsoleCursorPosition(h, co);
			printo(co, player1);
			co.X=11;
			co.Y=0;
			printo(co, 0);
			co.X=w-20;
			co.Y=0;
			printo(co, player2);
			co.X=w-10;
			co.Y=0;
			printo(co, 0);
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


void display( COORD c )
{
	cout<< c.X << " " << c.Y << endl;
}

void dmas( Dot** m, int x, int y )
{
	for( int j = 0; j < y; j++ )
	{
		cout<< ' ';
		for( int i = 0; i < x; i++ )
		{
			if( (i!=0) & (j!=0) & j!=(y-1) & i!=(x-1))
			{
				if( !m[i][j].player )
				cout<< (char)197;
				else
				cout<< m[i][j].player;
			}
			else
			{
				if( i!=0 & j==0 & i!=x-1 )
					cout<< (char)209;
				if( j!=0 & i==0 & j!=y-1)
					cout<< (char)199;
				if( i==0 & j==0 )
					cout<< (char)201;
				if( i!=x-1 & j==y-1 & i!=0 )
					cout<< (char)207;
				if( j!=y-1 & i==x-1 & j!=0 )
					cout<< (char)182;
				if( i==x-1 & j==y-1 )
					cout<< (char)188;
				if( i==x-1 & j==0 )
					cout<< (char)187;
				if( i==0 & j==y-1 )
					cout<< (char)200;
			}
		}
		cout<< endl;
	}
}

void dimas( int** m, int x, int y, COORD c )
{
	HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo( h, &bi );
	SetConsoleCursorPosition( h, c);
	for( int j = 0; j < y; j++ )
	{
		cout<< ' ';
		for( int i = 0; i < x; i++ )
		{
			cout<< m[i][j];
		}
		cout<< endl;
	}
	SetConsoleCursorPosition( h, bi.dwCursorPosition);
}

void deletemas( Dot*** mas, int x, int y )
{
	for( int i = 0; i < x; i++ )
	{
		delete[] (*mas)[i]; 
	}
	delete[] *mas;
}

void initdmas( Dot*** m, int x, int y )
{
	*m=new Dot* [x];
	for(int i = 0; i < x; i++)
	{
		(*m)[i] = new Dot[y];
		for(int j = 0; j < y; j++)
		{
			(*m)[i][j].player = 0;
			(*m)[i][j].status = 0;
			(*m)[i][j].isoccupated = 0;
		}
	}
}

void initimas( int*** m, int x, int y )
{
	*m = new int* [x];
	for(int i = 0; i < x; i++)
	{
		(*m)[i] = new int[y];
		for(int j = 0; j < y; j++)
		{
			(*m)[i][j] = 0;
		}
	}
}

void out(int o)
{
		COORD c0={10, 0};
		HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
		CONSOLE_SCREEN_BUFFER_INFO bi;
		GetConsoleScreenBufferInfo( h, &bi );
		SetConsoleCursorPosition( h, c0);
		cout<<o;
		SetConsoleCursorPosition( h, bi.dwCursorPosition);
}

void draw( HANDLE h, CONSOLE_SCREEN_BUFFER_INFO bi, Dot** m, int x, int y, Menu& menu )
{
	COORD co={ 0, 1 };
	char c = 13;
	int bo = 0;
	GetConsoleScreenBufferInfo( h, &bi );
	while( c=='w' || c=='a' || c=='s' || c=='d' || c==13 )
	{
		c= _getch();
		switch( c )
		{
			case 119: 
			{	
				GetConsoleScreenBufferInfo( h, &bi );
				if( bi.dwCursorPosition.Y > 2 )
				bi.dwCursorPosition.Y -= 1;
				else
				{
					bi.dwCursorPosition.Y -= 2;
					SetConsoleCursorPosition( h, bi.dwCursorPosition );
					bi.dwCursorPosition.Y += 2;
				}
				SetConsoleCursorPosition( h, bi.dwCursorPosition );
				break;
			}
			case 97: 
			{
				GetConsoleScreenBufferInfo( h, &bi );
				if(bi.dwCursorPosition.X > 2 )
				bi.dwCursorPosition.X -=1 ;
				SetConsoleCursorPosition( h, bi.dwCursorPosition );
				break;
			}
			case 115: 
			{
				GetConsoleScreenBufferInfo( h, &bi );
				if( bi.dwCursorPosition.Y < y-1 )
				{
					bi.dwCursorPosition.Y += 1;
				}
				else
				{
					bi.dwCursorPosition.Y += 2;
					SetConsoleCursorPosition( h, bi.dwCursorPosition );
					bi.dwCursorPosition.Y -= 2;
				}
				SetConsoleCursorPosition( h, bi.dwCursorPosition );
				break;
			}
			case 100: 
			{	
				GetConsoleScreenBufferInfo( h, &bi );
				if( bi.dwCursorPosition.X < x-1 )
				{
					bi.dwCursorPosition.X += 1;
					SetConsoleCursorPosition( h, bi.dwCursorPosition );
				}
				break;
			}
			case 13: 
			{
				if(m[bi.dwCursorPosition.X-1][bi.dwCursorPosition.Y-1].player || m[bi.dwCursorPosition.X-1][bi.dwCursorPosition.Y-1].isoccupated) break;
				bo=!bo;
				GetConsoleScreenBufferInfo( h, &bi );
				if(bo)
				{
					SetConsoleTextAttribute( h, 32 );
					m[ bi.dwCursorPosition.X-1 ][ bi.dwCursorPosition.Y-1 ].player = 1;
					cout<< m[ bi.dwCursorPosition.X-1 ][ bi.dwCursorPosition.Y-1 ].player;
					SetConsoleCursorPosition(h, bi.dwCursorPosition);
					SetConsoleTextAttribute(h, 7);
					search1(m, x, y, bi.dwCursorPosition.X-1, bi.dwCursorPosition.Y-1, menu);
				}
				else
				{
					SetConsoleTextAttribute( h, 31 );
					m[ bi.dwCursorPosition.X-1 ][ bi.dwCursorPosition.Y-1 ].player = 2;
					cout<< m[ bi.dwCursorPosition.X-1 ][ bi.dwCursorPosition.Y-1 ].player;
					SetConsoleCursorPosition( h, bi.dwCursorPosition );
					SetConsoleTextAttribute( h, 7 );
					search1(m, x, y, bi.dwCursorPosition.X-1, bi.dwCursorPosition.Y-1, menu);
				}
			break;
			}
			default:
			{
				if( c!=27 & c!='j' ) 
					c = 13;
				else
				{ 
					if( c=='j' )
					{					
						GetConsoleScreenBufferInfo(h, &bi);
						SetConsoleCursorPosition(h, co);
						dmas(m, x, y);						
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
	if ( menu.gs1() > menu.gs2() )
	{
		co={1, y+2};
		printo(co, "Winner: ");
		co={9, y+2};
		printo(co, menu.getp1() );
	}
	if ( menu.gs2() > menu.gs1() )
	{
		co={1, y+2};
		printo(co, "Winner: ");
		co={9, y+2};
		printo(co, menu.getp2() );
	}
	if ( menu.gs2()==menu.gs1() )
	{
		co={1, y+2};
		printo(co, "Winner: Friendship");
	}
	co={1, y+3};
	SetConsoleCursorPosition(h, co);
}

void printo(COORD c, string s)
{
	HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo( h, &bi );
	SetConsoleCursorPosition( h, c);
	cout<<s;
	SetConsoleCursorPosition( h, bi.dwCursorPosition);
}

void printo(COORD c, string s, int col)
{
	HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( h, col );
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo( h, &bi );
	SetConsoleCursorPosition( h, c);
	cout<<s;
	SetConsoleTextAttribute( h, 7 );
	SetConsoleCursorPosition( h, bi.dwCursorPosition);
}

void printo(COORD c, int s)
{
	HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo( h, &bi );
	SetConsoleCursorPosition( h, c);
	cout<<s;
	SetConsoleCursorPosition( h, bi.dwCursorPosition);
}

void search1( Dot** m, int x, int y, int c1, int c2, Menu& menu)
{
	int* result = new int;
	*result=0;
	COORD c={0, y+2};
	int** info;
	initimas(&info, x, y);
	info[c1][c2]=2;
	for(int dx=-1; dx<2; dx++)
	{
		for(int dy=-1; dy<2; dy++)
		{
			if(c1+dx>=0 & c1+dx< x & c2+dy>=0 & c2+dy<y)
				{
				if( (dx||dy) & (m[c1+dx][c2+dy].player==m[c1][c2].player) & !info[c1+dx][c2+dy] & m[c1+dx][c2+dy].isoccupated!=1 )
				{
					info[c1+dx][c2+dy]=1;
					search(m, info, x, y , c1+dx, c2+dy, 1, m[c1][c2].player, menu, result);
				}
			}
		}
	}
	if(*result) scoring1(m, info, x, y, menu);
	
}

void search(Dot** m, int** info, int x, int y, int c1, int c2, int start, int player, Menu& menu, int* result)
{
	COORD c={0, y+2};
	for(int dx=-1; dx<2; dx++)
	{
		for(int dy=-1; dy<2; dy++)
		{
			if(c1+dx>=0 & c1+dx< x & c2+dy>=0 & c2+dy<y)
			{
				if( (dx||dy) & m[c1+dx][c2+dy].player==player & info[c1+dx][c2+dy]!=1 & m[c1+dx][c2+dy].isoccupated!=1)
				{
				
					if(!(info[c1+dx][c2+dy]==2 & start))
					{
						if (info[c1+dx][c2+dy]==2)
						{
							c.Y--;
							*result=1;
							c.Y++;
						}
						else
						{
							info[c1+dx][c2+dy]=1;
							search(m, info, x, y , c1+dx, c2+dy, 0, player, menu, result);
						}
					}
				}
			}
		}
	}
}


void scoring1(Dot** m, int** info, int x, int y, Menu& menu)
{
	int player=1;
	COORD c={0, y+2};
	int c1=0;
	int c2=0;
	info[0][0]=3;
	for(int dx=1; dx>-2; dx--)
	{
		for(int dy=-1; dy<2; dy++)
		{
			if(c1+dx>=0 & c1+dx< x & c2+dy>=0 & c2+dy<y)
			{	
				if( (( dx!=0 & dy==0 )||( dy!=0 & dx==0 )) & (info[c1+dx][c2+dy]==0))
				{			
					info[c1+dx][c2+dy]=3;
					//dimas(info, x, y, c);
					scoring(m, info, x, y , c1+dx, c2+dy, menu);
				}
			}
		}
	}
	for( int j = 0; j < y; j++ )
	{
		for( int i = 0; i < x; i++ )
		{
			if( info[i][j]==1 ||  info[i][j]==2) 
			{
				player=m[i][j].player;
				player=(!(player-1))+1;
				m[i][j].isoccupated=2;
			}
			if( info[i][j]==0 & m[i][j].isoccupated!=1 & m[i][j].player==player )
			{
				COORD cu = {i+1, j+1};
				m[i][j].isoccupated=1;
				if (player==1)
				{
					menu.ss2();
					printo(cu, "1", 8);
				}
				if (player==2)
				{
					menu.ss1();
					printo(cu, "2", 8);
				}
			}
			if( info[i][j]==0 )
			{
				m[i][j].isoccupated=1;
			}
			
		}
	}
	c = {11, 0};
	printo(c, menu.gs1());
	c = {x-10, 0};
	printo(c, menu.gs2());
}

void scoring(Dot** m, int** info, int x, int y, int c1, int c2,  Menu& menu)
{
	
	COORD c={0, y+2};
	for(int dx=1; dx>-2; dx--)
	{
		for(int dy=-1; dy<2; dy++)
		{
			if(c1+dx>=0 & c1+dx< x & c2+dy>=0 & c2+dy<y)
			{	
				if( (( dx!=0 & dy==0 )||( dy!=0 & dx==0 )) & (info[c1+dx][c2+dy]==0) )
				{			
					info[c1+dx][c2+dy]=3;
					scoring(m, info, x, y , c1+dx, c2+dy, menu);
				}
			}
		}
	}	
}


