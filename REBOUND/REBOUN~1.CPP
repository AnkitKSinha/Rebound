#include<fstream.h>
#include<string.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


union REGS in,out;
int points=0;


class score
{
        public:
        char *name;
        int points;

               score();
               void setdata(int,int,int);
               void display(int,int);

               int retscore(){return points;}
};

void score::score()
{
        name=(char*)malloc(20);
        for(int i=0;i<20;i++)name[i]='\0';
}

void score :: setdata(int maxx,int maxy,int p)
{
        cleardevice();
        setbkcolor(WHITE);
        setcolor(BLUE);
        char ch;
        rectangle(0,0,maxx,maxy);
        rectangle(10,10,maxx-10,maxy-10);
        setfillstyle(SOLID_FILL,RED);
        floodfill(1,1,BLUE);

        settextstyle(DEFAULT_FONT,0,3);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(maxx/2,maxy/2-100,"ENTER NAME:");
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        int i=0;
        while(ch!=13)
        {

                ch=getch();
                setcolor(WHITE);
                outtextxy(maxx/2,maxy/2,name);
                if(ch!=13)
                {
                        if(ch!=8)
                        {
                                setcolor(BLUE);
                                name[i++]=ch;
                                outtextxy(maxx/2,maxy/2,name);
                        }
                        else
                        {
                                i--;
                                name[i]='\0';
                                setcolor(BLUE);
                                outtextxy(maxx/2,maxy/2,name);
                        }

                }
        }
        name[i]='\0';
        cleardevice();
        setbkcolor(BLUE);
        cout<<"\n"<<name;
        points=p;
        cout<<points;
        getch();


}

void score :: display(int x,int y)
{
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        gotoxy(20,25);
        cout<<name<<"hjhj";
        char string[10],temp[30];
        itoa(points,string,10);
        strcpy(temp,name);
        strcat(temp,string);
        settextstyle(DEFAULT_FONT,0,3);
        setcolor(GREEN);
        outtextxy(x,y,temp);
}

void ball(int,int,int);
void callmouse();
void hidemouse();
void positionmouse(int,int);
void gameover(int,int,int,char *);
void initmouse();
void altermouse(int&,int&,int&);
void setlimits(int,int,int,int);
void tab(int,int,int,int);
void bricks(int,int);
void level1(int,int);
void level2(int,int);
void bonus(int,int,int,int);
void mainmenu(int,int);
void highscore(int,int,int);
void displayscore(int,int);





void main()
{

	int gdriver=DETECT,gmode;
        initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");
        initmouse();
	int maxx=getmaxx(),maxy=getmaxy();
        //score s;
        //s.setdata(maxx,maxy);
        //getch();
        //positionmouse(maxx/2,maxy-5);
        //mainmenu(maxx,maxy);
        level1(maxx,maxy);
        hidemouse();
	closegraph();
}

void mainmenu(int maxx,int maxy)
{
        cleardevice();
        callmouse();
        setbkcolor(BLACK);
        setcolor(RED);
        rectangle(0,0,maxx,maxy);
        rectangle(10,10,maxx-10,maxy-10);
        setfillstyle(CLOSE_DOT_FILL,GREEN);
        floodfill(1,1,RED);
        settextstyle(DEFAULT_FONT,0,3);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(maxx/2,50,"MENU");
        outtextxy(maxx/2,150,"1.PLAY");
        outtextxy(maxx/2,250,"2.HIGH SCORES");
        outtextxy(maxx/2,350,"3.EXIT");

        int x,y,cl;
        while(1)
        {
                altermouse(x,y,cl);
                if(cl==1)
                {
                        if(x>maxx/2-50&&x<maxx/2+50&&y>130&&y<170)
                        {
                                hidemouse();
                                level1(maxx,maxy);
                        }
                        else if(x>maxx/2-100&&x<maxx/2+100&&y>230&&y<270)
                        {
                                displayscore(maxx,maxy);

                        }
                        else if(x>maxx/2-50&&x<maxx/2+50&&y>320&&y<370)
                        {
                                break;
                        }
                }
        }



}

void displayscore(int maxx,int maxy)
{
        cleardevice();
        setcolor(GREEN);
        rectangle(0,0,maxx,maxy);
        rectangle(10,10,maxx-10,maxy-10);
        setfillstyle(SOLID_FILL,LIGHTGREEN);
        floodfill(1,1,GREEN);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        settextstyle(DEFAULT_FONT,0,3);


        ifstream scorefile("scores.dat");
        if(!scorefile)
        {
                outtextxy(maxx/2,maxy/2,"NO HIGHSCORE SET!");
        }
        else
        {
                score s;
                scorefile.read((char *)&s,sizeof(s));
                gotoxy(20,28);
                cout<<s.name<<s.points;
                getch();
                s.display(maxx/2,maxy/2);
        }
        getch();
        mainmenu(maxx,maxy);
}




void highscore(int maxx,int maxy,int points)
{
        score s;
        ifstream scorefile("scores.dat");
        if(!scorefile)
        {
                scorefile.close();
                ofstream file("scores.dat");

                gotoxy(20,24);
                cout<<"\nNO SCORE FILE";
                getch();

                s.setdata(maxx,maxy,points);
                gotoxy(20,24);
                cout<<s.name<<s.points;
                getch();
                file.write((char *)&s,sizeof(s));
                file.close();
        }
        else
        {
                scorefile.read((char *)&s,sizeof(s));
                scorefile.close();
                if(points>s.retscore())
                {
                        ofstream file("scores.dat");

                        s.setdata(maxx,maxy,points);
                        file.write((char *)&s,sizeof(s));
                        file.close();
                }
        }
        scorefile.close();
}



void callmouse()
{
        in.x.ax=1;
        int86(51,&in,&out);
}


void ball(int x,int y,int color)
{
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	circle(x,y,5);
	floodfill(x,y,color);
}
void initmouse()
{
	in.x.ax=0;
	int86(51,&in,&out);
}
void hidemouse()
{
	in.x.ax=2;
	int86(51,&in,&out);
}
void setlimits(int minx,int maxx,int miny,int maxy)
{
	in.x.ax=7;
	in.x.cx=minx;
	in.x.dx=maxx;
	int86(51,&in,&out);
	in.x.ax=8;
	in.x.cx=miny;
	in.x.dx=maxy;
	int86(51,&in,&out);
}
void altermouse(int &x,int &y,int &click)
{
	in.x.ax=3;
	int86(51,&in,&out);
	x=out.x.cx;
	y=out.x.dx;
	click=out.x.bx;
}

void tab(int x,int extrax,int y,int color)
{
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	rectangle(x-50-extrax,y-5,x+50+extrax,y+5);
	floodfill(x,y,color);
}
void positionmouse(int x,int y)
{
        in.x.ax=4;
        in.x.cx=x;
        in.x.dx=y;
        int86(51,&in,&out);
}
void gameover(int points,int maxx,int maxy,char *state)
{
        cleardevice();
	setbkcolor(BLACK);
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT,0,3);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(maxx/2,maxy/2-50,state);
	char p[20];
	itoa(points,p,10);
	setcolor(BLUE);
	outtextxy(maxx/2,maxy/2,p);
        getch();
        if(!strcmp(state,"GAME OVER"))
        {
                highscore(maxx,maxy,points);
        }
}
void level1(int maxx,int maxy)
{
        cleardevice();
	setbkcolor(GREEN);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
	setcolor(RED);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(maxx/2,maxy/2,"LEVEL 1");
        delay(5000);
	cleardevice();
	setbkcolor(BLACK);
        clock_t startclock,endclock;
        int x,y,signx=1,signy=-1,rx=452,ry=565,ctr=0,extrax=50;
        int arr[10][10];
        double degrees=45.0;
	int delvar=30;
	int mousex,mousey,click,ctry=0,ctrdel=0;
	setlimits(10,maxx,maxy-10,maxy-10);

        double angle=(3.14*degrees/180);

	int blockx[10],blocky[10],i,j;
	for(i=1;i<=10;i++)
	{
		blockx[i-1]=(i*maxx/10)-(maxx/20);
		blocky[i-1]=(i*maxy/20);


	}
	setcolor(RED);
	setfillstyle(SOLID_FILL,BLUE);

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			rectangle(blockx[i]-32,blocky[j]-12,blockx[i]+32,blocky[j]+12);
			floodfill(blockx[i],blocky[j],RED);
			arr[i][j]=1;

		}
	}

	delay(500);
        startclock=clock();



	while(!kbhit())
	{


		altermouse(mousex,mousey,click);
		tab(mousex,extrax,mousey,RED);
                //angle=(3.14*degrees/180);
		x=rx*cos(angle);
		y=ry*sin(angle);

		ball(x,y,WHITE);
		if(x>=maxx||x<0)signx*=-1;
		if(y<0)signy*=-1;
		else if(y>maxy)
		{
			gameover(points,maxx,maxy,"GAME OVER");
                        getch();
                        cleardevice();
                        closegraph();
                        exit(0);

		}
		if(x>=mousex-50-extrax && x<=mousex+50+extrax &&y>=mousey-10)
		{
			signy*=-1;
                        if(x<mousex-30-extrax)
                        {
                                //degrees-=(0.1*(mousex-x));
                                signx=-1;
                        }
                        else if(x>mousex+30+extrax)
                        {
                                //degrees+=(0.1*(x-mousex));
                                signx=1;
                        }

		}


		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)
			{

				 if(x<=(blockx[i]+32)&&x>=(blockx[i]-32)&&y<(blocky[j]+20)&&y>(blocky[j]-10)&&arr[i][j]==1)
				 {
					 setcolor(BLACK);   ctr++;

					 rectangle(blockx[i]-32,blocky[j]-12,blockx[i]+32,blocky[j]+12);
					 setfillstyle(SOLID_FILL,BLACK);
					 floodfill(blockx[i],blocky[j],BLACK);
					 points+=10;
					  if(x>blockx[i]+20||x<blockx[i]-20)
					  {
						signx*=-1;
						ctry=1;

					  }
					  else
					  {
						ctry=0;
					  }
					  if((y>blocky[j]-10||y<blocky[j]+10)&&ctry!=1)
					  {
						signy*=-1;

					  }


					 arr[i][j]=0;
					 if(ctr==100)
					 {
                                                gameover(points,maxx,maxy,"LEVEL COMPLETE");
                                                getch();

                                                cleardevice();
                                                level2(maxx,maxy);
                                                //closegraph();
                                                //exit(0);
                                         }
                                         break;

				 }

			}
		}
		rx+=(signx*10);
		ry+=(signy*10);
		delay(delvar);
		ball(x,y,BLACK);
                tab(mousex,extrax,mousey,BLACK);

                endclock=clock();
                if( (ceill(endclock-startclock)/CLK_TCK)>=5&&ctrdel!=1)
                {
                        delvar-=10;
                        if(delvar<20)
                        {
                                ctrdel=1;
                        }
                        startclock=clock();
                }



	}
        closegraph();
        exit(0);


}

void level2(int maxx,int maxy)
{
        randomize();
        setbkcolor(GREEN);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
	setcolor(RED);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(maxx/2,maxy/2,"LEVEL 2");
        delay(5000);
	cleardevice();
	setbkcolor(BLACK);
        int x,y,signx=1,signy=-1,rx=452,ry=565,ctr=0;
        int arr[10][10],ctrbonus=0,bonusx[10],bonusy[10],actbonus[10],extrax=0;
        int bonusi=0,bonusj=0;
	int delvar=30,ctrfast=0;
        clock_t startfast,endfast;
	int mousex,mousey,click,ctry=0;
	setlimits(10,maxx-10,maxy-10,maxy-10);
        double angle=(3.14*45/180);

	int blockx[10],blocky[10],i,j;
	for(i=1;i<=10;i++)
	{
		blockx[i-1]=(i*maxx/10)-(maxx/20);
		blocky[i-1]=(i*maxy/20);


	}
	setcolor(WHITE);


	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			rectangle(blockx[i]-32,blocky[j]-12,blockx[i]+32,blocky[j]+12);

                        if(j==4||j==5)
                        {
                                      setfillstyle(SOLID_FILL,MAGENTA);
                                      arr[i][j]=2;
                        }
                        else
                        {
                                      setfillstyle(SOLID_FILL,RED);
                                      arr[i][j]=1;
                        }

			floodfill(blockx[i],blocky[j],WHITE);


		}
	}

        for(int a=0;a<5;)
        {
                i=random(10);
                j=random(10);
                if(j!=4 || j!=5)
                {
                        arr[i][j]=3;
                        a++;
                }

        }

	delay(500);



	while(!kbhit())
	{
		tab(mousex,extrax,mousey,BLACK);
		altermouse(mousex,mousey,click);
		tab(mousex,extrax,mousey,BLUE);
                if(ctrfast!=0)
                {
                        endfast=clock();
                        if(ceill((endfast-startfast)/CLK_TCK) == 5)
                        {
                                ctrfast--;
                                delvar+=10;
                        }
                }



                if(ctrbonus!=0)
                {
                        int tempbonus=ctrbonus;

                        //gotoxy(20,25);
                        //cout<<"ACTIVATED";


                        for(i=0;i<ctrbonus;i++)
                        {
                                bonus(bonusx[i],bonusy[i],actbonus[i],5);


                                if(bonusx[i]<mousex+50+extrax && bonusx[i]>mousex-50-extrax &&bonusy[i]>mousey-10&&bonusy[i]<mousey+10)
                                {
                                        gotoxy(20,25);
                                        cout<<"caught";
                                        tempbonus--;
                                        switch(actbonus[i])
                                        {
                                                case 1:
                                                     extrax+=50;
                                                     break;
                                                case 2:
                                                     extrax-=25;
                                                case 3:
                                                     delvar-=10;
                                                     startfast=clock();
                                                     ctrfast++;
                                                     break;
                                        }
                                        bonus(bonusx[i],bonusy[i],5,BLACK);

                                }
                                else if(bonusy[i]>maxy)
                                {
                                        tempbonus--;
                                        bonus(bonusx[i],bonusy[i],5,BLACK);
                                }

                        }
                        ctrbonus=tempbonus;
                }

		x=rx*cos(angle);
		y=ry*sin(angle);

		ball(x,y,YELLOW);
		if(x>=maxx||x<0)signx*=-1;
		if(y<0)signy*=-1;
		else if(y>maxy)
		{
			gameover(points,maxx,maxy,"GAME OVER!");
                        getch();
                        cleardevice();
                        closegraph();
                        exit(0);

		}
		if(x>=mousex-50-extrax &&x<=mousex+50+extrax &&y>=mousey-10)
		{
			signy*=-1;
			if(x<mousex)signx=-1;
			else if(x>mousex)signx=1;
		}


		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)
			{

				 if(x<=(blockx[i]+32)&&x>=(blockx[i]-32)&&y<(blocky[j]+20)&&y>(blocky[j]-10)&&arr[i][j]!=0)
				 {
				         ctr++;
                                         int fillclr,drawclr;
                                         if(arr[i][j]==2)
                                         {
                                                fillclr=RED;
                                                drawclr=WHITE;

                                         }
                                         else if(arr[i][j]==3)
                                         {
                                                fillclr=BLACK;
                                                drawclr=BLACK;
                                                actbonus[ctrbonus]=random(3)+1;
                                                bonusx[ctrbonus]=blockx[i];
                                                bonusj=j;
                                                bonusi=i;
                                                bonusy[ctrbonus++]=blocky[j];
                                                arr[i][j]-=2;

                                         }
                                         else
                                         {
                                                fillclr=BLACK;
                                                drawclr=BLACK;


                                         }


                                         setcolor(drawclr);
					 rectangle(blockx[i]-32,blocky[j]-12,blockx[i]+32,blocky[j]+12);

					 setfillstyle(SOLID_FILL,fillclr);
					 floodfill(blockx[i],blocky[j],drawclr);
					 points+=10;
					  if(x>blockx[i]+20||x<blockx[i]-20)
					  {
						signx*=-1;
						ctry=1;

					  }
					  else
					  {
						ctry=0;
					  }
					  if((y>blocky[j]-10||y<blocky[j]+10)&&ctry!=1)
					  {
						signy*=-1;

					  }


					 arr[i][j]--;
					 if(ctr==120)
					 {
                                                gameover(points,maxx,maxy,"LEVEL COMPLETE");
                                                getch();
                                                cleardevice();
                                                closegraph();
                                                exit(0);
                                         }

				 }

			}
		}
		rx+=(signx*10);
		ry+=(signy*10);
		delay(delvar);
		ball(x,y,BLACK);
                if(ctrbonus!=0)
                {
                        for(i=0;i<ctrbonus;i++)
                        {
                                //if(arr[i][j]==1)
                                int bonuscolor=0;
                                if(bonusi<10)
                                {
                                        if(arr[bonusi][bonusj]==1)
                                        {
                                                bonuscolor=RED;
                                        }
                                        else if(arr[bonusi][bonusj]==2)
                                        {
                                                bonuscolor=MAGENTA;
                                        }
                                        else
                                        {
                                                bonuscolor=BLACK;
                                        }
                                }
                                else
                                {
                                        bonuscolor=BLACK;
                                }

                                bonus(bonusx[i],bonusy[i],4,bonuscolor);
                                bonusy[i]+=5;
                                bonusi++;
                        }
                }




        }
}


void bonus(int x,int y,int number,int color)
{
        int col;
        switch(number)
        {
                case 1:
                     col=RED;
                     break;
                case 2:
                     col=GREEN;
                     break;
                case 3:
                     col=WHITE;
                     break;
                default:
                     col=color;


        }

        setcolor(col);
        circle(x,y,10);
        setfillstyle(SOLID_FILL,col);
        floodfill(x,y,col);
}