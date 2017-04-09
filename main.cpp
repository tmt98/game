#include<iostream>
#include<windows.h>
#include<ctime>
#include<cmath>
#include<conio.h>
using namespace std;

    DWORD EventCount;
    DWORD readnum;
    INPUT_RECORD record;
    int numberE=4;
    int point=0;
    int speed=100;
    bool conti=1;
    int countLoop=0;

    void gotoxy(int x, int y)
    {
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
    }



	void Objectcolor(WORD color)
	{
		color--;
	 CONSOLE_SCREEN_BUFFER_INFO thongtinbuffermanhinh;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &thongtinbuffermanhinh);

    WORD k = thongtinbuffermanhinh.wAttributes;
    color &= 0x000f;
    k &= 0xfff0;
    k |= color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

	class player{
			public:
				int x;
				int y;
				int color;
				int life;
				int c;
				player(){
					c=2;
					x=41;
					y=20;
					color=114;
					life = 4;
				}
				bool move(int a){
				switch(a){
					case 1: x+=3;break;
					case 2: x-=3;break;
				}

				}
				void print(){
					Objectcolor(color);
					gotoxy(x,y);
					cout<<char(24);
					gotoxy(x-1,y);
					cout<<char(24);
					gotoxy(x+1,y);
					cout<<char(24);
					gotoxy(x,y-1);
					cout<<char(24);
				}
				void delet(){
					gotoxy(x,y);
					cout<<" ";
					gotoxy(x-1,y);
					cout<<" ";
					gotoxy(x+1,y);
					cout<<" ";
					gotoxy(x,y-1);
					cout<<" ";
				}
				void showPoints(){
					gotoxy(47,2);
					Objectcolor(238);
					cout<<"BARRIER: "<<point;
				}
				void showLife(){
				if(life<=4){

					gotoxy(23,3);
					Objectcolor(237);
					cout<<"LIFE: ";
					if(life==4)cout<<"oooo";
					if(life==3)cout<<"ooo";
					if(life==2)cout<<"oo";
				}
				else if(life>4){
				Objectcolor(237);
				gotoxy(29,3);
				cout<<"    ";
				gotoxy(29,3);
				cout<<life<<"o";
			}
			}
				void kill(){
					showLife();
					gotoxy(33+(life-4),3);
					if(life==3)cout<<" ";
					if(life==2)cout<<"  ";
					if(life==1)cout<<"   ";
					if(life==0)cout<<"    ";

				}


		};

class Enemy{

	public:
	int x;
	int y;
	Enemy(){
		y=2;
		randomx();
		randomy();
	}
	void move(){
		y++;
		if(y==24) { y=2;
		randomx();
		}
	}
	void print(){
		Objectcolor(249);
		if(y>=2){
		gotoxy(x-1,y);
		cout<<"   ";
		}
		move();

		if(y>=2){
		gotoxy(x,y);
		cout<<char(22);
		gotoxy(x-1,y);
		cout<<char(22);
		gotoxy(x+1,y);
		cout<<char(22);
		}
	}
	private:
		void randomx(){
			int i= rand()%4+1;
			switch(i){
				case 1: x=35;break;
				case 2: x=38;break;
				case 3: x=41; break;
				case 4: x=44;break;
			}
		}
		void randomy(){
			y=(rand()%20+1)-18;
		}
};
class Heart{

		public:
	int x;
	int y;
	char iconHeart;
	bool isHeart;
	Heart(){
		y=2;
		randomx();
		iconHeart=char(169);
//		randomy();
		isHeart=false;
	}

	void move(){
		y++;
		if(y==23) { y=1;
		randomx();
		isHeart=false;
		iconHeart=char(169);
		}
	}
	void print(){
		Objectcolor(237);
		if(y>=2){
		gotoxy(x,y);
		cout<<" ";
		}

		move();

		if(y>=2){
		gotoxy(x,y);
		cout<<iconHeart;
		}
	}
	void activeHeart(){
		if(fmod(countLoop,150)==0){
			isHeart=true;
		}
		if(isHeart==true){
			print();
		}
	}
		void dieukieny(Enemy E1){
			if(fabs(x-E1.x)<=1&&y!=E1.y){
				y--;
			}
		}
		void delet(){

			gotoxy(x,y);
			iconHeart=' ';
		}
	private:
		void randomx(){
			int i = rand()%12+1;
			x=i+33;
			}

			};


void BGcolor(WORD color){
	 CONSOLE_SCREEN_BUFFER_INFO thongtinbuffermanhinh;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &thongtinbuffermanhinh);
    WORD k = thongtinbuffermanhinh.wAttributes;
    color &= 0x000f;
    color <<= 4;
    k &= 0xff0f;
    k |= color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

void Menu(){
    Objectcolor(109);
    gotoxy(38,10);
    cout<<"PLAY";
    gotoxy(26,13);
    Objectcolor(110);
    cout<<"PLEASE PRESS ENTER TO PLAY GAME";
    gotoxy(29,19);
    cout<<"GAME BY TMT SOCIU STUDIO ^_^";
    int k;

    do
        {
        k=getch();
    }
    while(k!=13);
    Objectcolor(111);
    gotoxy(38,10);
    cout<<"PLAY";
    Beep(1444,200);
    }


class Background{
	public:
//		int color[4];
		void printBG(){
				BGcolor(116);
			for(int i= 0; i<=25;i++){

				gotoxy(0,i);
				cout<<"                                                                                ";
			}
			gotoxy(1,1);
		}

		void printBG2(){
			BGcolor(111);
			for(int i = 0; i<=23;i++){
			gotoxy(33,1+i);
			cout<<"|            |";
		}
		}
};
int HoldkeyLoop(player player1){
 		int HoldKey;
       	GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE),&EventCount);
        while (EventCount > 0)
        {
            ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),&record,1,&readnum);
            if (record.EventType == KEY_EVENT )
			{
				HoldKey = record.Event.KeyEvent.uChar.AsciiChar;
			}
			 GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE),&EventCount);
        }
        if((player1.x==44&&HoldKey==100)||(player1.x==35&&HoldKey==97)) HoldKey=0;
        return HoldKey;
}

void turnUptheSpeed(){
	float k;
	if(speed<50)
	k+=0.1;
	else{
		k+=0.01;
	}

	speed=int(k);
	gotoxy(22,2);
	Objectcolor(241);
	cout<<"SPEED: +"<<speed+100;
}

void moveWord(){
	Objectcolor(240);
	for(int i= 10; i<=28; i++){
		gotoxy(9+i,12);
		cout<<"GAME";
		gotoxy(70-i,12);
		cout<<"OVER";

		Beep((41-i)*100,100);
		gotoxy(70-i-1,12);
		if(i<28)cout<<"      ";
		gotoxy(9+i,12);
		if (i<28)
		cout<<"    ";
	}
}
void GameOver(Background BG2){
	BG2.printBG();
	moveWord();
	Sleep(500);
	conti=false;
	}




int main(){

    Menu();
	player player1;
	Enemy enemy[numberE+1];
	Heart heart;

	srand(time(0));
    Background BG1;
	BG1.printBG();
	BG1.printBG2();
	player1.showPoints();
	player1.showLife();
	player1.print();
	while (conti){
		countLoop++;
		Sleep(100-speed);
		for(int i= 1; i<=numberE;i++) {
		enemy[i].print();
		if ((enemy[i].x==player1.x||enemy[i].x==player1.x+1||enemy[i].x==player1.x-1)&&(enemy[i].y==player1.y)){
			player1.life--;
			player1.kill();
			Beep(700,250);
			player1.print();
			if (player1.life==0) GameOver(BG1);
		}




		if(enemy[i].y==22){
			point++;
			player1.showPoints();
		}
		}


		heart.activeHeart();

		if ((heart.x==player1.x||heart.x==player1.x+1||heart.x==player1.x-1)&&(heart.y==player1.y)){
			player1.life++;
			player1.showLife();
			heart.delet();
			player1.print();
		}
		else player1.print();

		turnUptheSpeed();
		if(point>1&&(fmod(point,100)==0)){
			int r=rand()%8+1;
			player1.color=r+71;
			Beep(800,200);
		}
		if(GetAsyncKeyState(VK_LEFT)!=0&&player1.x>36)
		{
			player1.delet();
				player1.move(2);
				player1.print();

		}
		if (GetAsyncKeyState(VK_RIGHT)!=0&&player1.x<44){
			player1.delet();
				player1.move(1);
				player1.print();

		}
	}



}
