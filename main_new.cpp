#include "funcs.h"

int main()
{
	SetConsoleTitle( "Dots" );// Name of the game
		COORD co={ 0, 0 };//helps to define the coordinates
		Sleep( 2000 );
		HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
		CONSOLE_SCREEN_BUFFER_INFO bi;
		GetConsoleScreenBufferInfo( h, &bi );
		int a = bi.dwMaximumWindowSize.X;//defining of playground size
		int b = bi.dwMaximumWindowSize.Y;
		int sa = a - 2;
		int sb = b/2 + 5 ;
		if(sa>100) 
		{
			sa=100;
			sb-=5;
		}
		Dot** mass;
		initdmas ( &mass, sa, sb );
		Menu m ( sa, sb );
		m.mainmenu ( );
		co.X=0;
		co.Y=1;
		SetConsoleCursorPosition(h, co);
		dmas ( mass, sa, sb );//preparation for the game
		co.X=0;
		co.Y=0;
		SetConsoleCursorPosition(h, co);
		co.X=2;
		co.Y=2;
		SetConsoleCursorPosition( h, co );
		draw( h, bi, mass, sa, sb, m );//game&ending
		getch();
		//m.CleanConsole( );
		deletemas( &mass, sa, sb );
	system("pause");
	return 0;
}
