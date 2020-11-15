#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<math.h>
#include<mmsystem.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include"assets.h"

#define MAX_OBJ_NO 5
#define MAX_SHIP_X 80
#define MIN_SHIP_X 5
#define MAX_SHIP_Y 25
#define MIN_SHIP_Y 20
#define BULLET_SPEED 7
#define BULLET_TYPE 237
#define BUL_Y 0
#define BULLET_TIME 300
#define EXPLOSION_TIME 200
#define BORDER 89
#define MENU_X 50
#define MENU_Y 14
#define SCORE_X 10
#define SCORE_Y 5
#define LOAD_TIME 100


int obj_no=MAX_OBJ_NO;
int posx=41,posy=25;
int max_obj_x=MAX_SHIP_X-5 , max_obj_y=MIN_SHIP_Y-4;
int obj_flag=0;
static int score=0;
int enemy_no;
static int countdown;


void draw_ship(int xpos,int ypos);
void destroy_ship(int xpos,int ypos);
int controlchkx(char input,int xpos);
int controlchky(char input,int ypos);
int collisiondetect(int xpos1,int ypos1,int xpos2,int ypos2);
void bullets(int xpos,int ypos,int objx[],int objy[],int objno);
void destroy_bullet(int xpos,int ypos);
void draw_object(int objx[],int objy[],int objno);
void background();
void game();
void destroy_object(int xpos,int ypos);
void game_menu();
void instructions();
void loading(char name[]);
void countdown_sleep(int );
void leaderboard();
void blast(int xpos,int ypos);

void main()
{
    game_menu();
}

                                                                //main game function
void game()
{
    PlaySound(("Game.wav"),0,1);
        char name[10];
        gotoxy(MENU_X,MENU_Y);
        printf("Enter your name: ");
        gets(name);
        name[0]=toupper(name[0]);
        system("cls");

    loading(name);
    background();
    PlaySound(("Khali.wav"),0,1);
    gotoxy(95,13);
    printf("Hello! %s",name);
    draw_ship(posx,posy);
    gotoxy(MENU_X-10,MENU_Y);
    while(kbhit())
    {
        getch();
    }
    printf("Press any key to start");
    getch();
    gotoxy(MENU_X-10,MENU_Y);
    printf("                       ");

char a=0;
int wave=1;
int obj_count=0;
int obj_x[obj_no];
int obj_y[obj_no];
countdown=5*1000;
while(a!='e' && countdown>0)
{
 while(!kbhit())
 {
     textcolor(15);
     Sleep(1);
     gotoxy(BORDER+11,3);
     printf("%d ",countdown);
     countdown--;
     if(countdown<0)
     {
         goto exit;
     }

     while(obj_flag==0)
     {
     gotoxy(94,7);
     printf("%d",wave);
      srand(time(0));
      obj_no=rand()%MAX_OBJ_NO;
      enemy_no=obj_no;

     for(int i=0;i<obj_no;i++)
    {
     obj_x[i]=(rand()%max_obj_x)+5;
     obj_y[i]=rand()%max_obj_y+2;
    }

  for(int i=0;i<obj_no;i++)
    {
        for(int b=i+1;b<obj_no;b++)
        {
          if((abs(obj_x[i]-obj_x[b])<5) || (abs(obj_y[i]-obj_y[b])<5))
          {
              if((obj_y[i]!=0) && (obj_x[i]!=0))
              {
           obj_x[i]=0;
           obj_y[i]=0;
           enemy_no--;
              }
          }
        }
    }


   draw_object(obj_x,obj_y,obj_no);
    obj_flag=1;
    wave++;
     }
 }


 a=getch();
 posx=controlchkx(a,posx);
 posy=controlchky(a,posy);
 draw_ship(posx,posy);


 if(a==' ')
 {
   PlaySound(("lasernice.wav"),0,1);
   bullets(posx,posy,obj_x,obj_y,obj_no);
 }

  for(int i=0;i<obj_no;i++)
    {
     if(obj_x[i]==0 && obj_y[i]==0)
        obj_count++;
    }
    if(obj_count==(obj_no))
    {
        obj_flag=0;
    }
    obj_count=0;

    textcolor(15);
    gotoxy(BORDER+7,5);
    printf("%d",score);
    gotoxy(BORDER+9,9);
    printf("%d ",enemy_no);

  }
 exit:
 system("color C");
 gotoxy(MAX_SHIP_X/2,MAX_SHIP_Y/2);
 printf("GAME OVER");
 PlaySound(("gameover.wav"),0,0);

 FILE *fp;                                                            //leader-board update
  fp=fopen("leaderboard","a");
  fprintf(fp,"%s %d\n",name,score);
  fflush(fp);
  fclose(fp);

 printf("\n\n\t\t\t\tPress any key to exit");
 while(kbhit())
 {
 getch();
 }
 getch();
 game_menu();

   }                                                         //end of game

                                                              //check control for side movement
 int controlchkx(char a,int conx)
 {
  if((a=='a' || a==75) && conx > MIN_SHIP_X)
  conx--;
  else if((a=='d' || a==77) && conx < MAX_SHIP_X)
  conx++;
  return conx;
  }

                                                              //check control for up-down movement
  int controlchky(char a,int cony)
  {
  if((a=='w' || a==72) && (cony > MIN_SHIP_Y))
  cony--;
  else if((a=='s' || a==80) && cony<MAX_SHIP_Y)
  cony++;
  return cony;
    }

                                                              //draw ship at given positions
 void draw_ship(int x,int y)
 {
   static int flag=0;
   if(flag!=0)
   {destroy_ship(x,y);}

textcolor(7);
gotoxy(x-3,y+1);
printf("%c%c%c%c%c%c%c",223,223,219,223,219,223,223);
gotoxy(x-2,y);
textcolor(12);
printf("%c%c%c%c%c",220,219,237,219,220);
textcolor(24);
gotoxy(x-1,y-1);
printf("%c %c",222,221);
textcolor(14);
gotoxy(x-1,y+2);
printf("%c %c",237,237);
gotoxy(x-1,y+3);
printf("%c %c",248,248);
textcolor(15);
gotoxy(x-2,y);
printf("%c",220);
gotoxy(x+2,y);
printf("%c",220);
textcolor(8);
gotoxy(x-1,y+1);
printf("%c%c%c",219,223,219);
textbackground(15,12);
gotoxy(x,y);
printf("%c",127);
textbackground(7,0);

flag++;
  }
                                                                  //remove previous ship
void destroy_ship(int ix,int iy)
{
    for(int i=0;i<7;i++)
    {
        gotoxy(ix-4,iy-2);
        printf("         ");
        iy++;
    }
}

                                                               //detect collision of two objects
int collisiondetect(int x1,int y1,int x2,int y2)
{
if(x1==x2 && y1==y2)
return 1;
else
return 0;
}

                                                                //fire projectile
void bullets(int x,int y,int obj_x[],int obj_y[],int obj_no)
{
    int i;
    textcolor(19);
    gotoxy(x,y-1);
    printf("%c",216);
    Sleep(BULLET_TIME);
    for(i=y-2;i>BUL_Y;i--)
    {
    countdown_sleep(BULLET_SPEED);
    textcolor(14);
    gotoxy(x,i);
    printf("%c",BULLET_TYPE);
    gotoxy(x,i+1);
    printf(" ");
    for(int j=0;j<obj_no;j++)
     {
    if (collisiondetect(x,i,obj_x[j],obj_y[j])==1)
    {
        obj_x[j]=0;
        obj_y[j]=0;
        enemy_no--;
        score+=100;
        gotoxy(x,i);
        blast(x,i);
        PlaySound(("Explosion.wav"),0,1);
        Sleep(EXPLOSION_TIME);
        destroy_object(x,i);
        j=obj_no;
        i=BUL_Y;
    }
     }
    }
    destroy_bullet(x,i);
}
                                                           //remove the final projectile
void destroy_bullet(int x,int y)
{
    gotoxy(x,y+1);
    printf(" ");

}
                                                            //draw emeny ships at different positions
#include"objects.h"
  void draw_object(int x[],int y[],int obj_no)
  {
      for(int i=0;i<obj_no;i++)
      {
          if((x[i]!=0) && (y[i]!=0))
        {
          objects(x[i],y[i]);
        }

       }
  }
                                                        //remove enemy ship from screen
void destroy_object(int x,int y)
{
        for(int j=y-2;j<y+3;j++)
        {
        gotoxy(x-4,j);
        printf("         ");
        }
        gotoxy(x,y);

}

                                                            //blast animation
void blast(int x,int i)
{
    gotoxy(x-2,i);
    printf("*  %c  *",236);
    gotoxy(x-1,i-1);
    Sleep(200);
    printf("*   *");
    gotoxy(x-1,i+1);
    printf("*   *");
    Sleep(100);
}
                                                          //backgrounds
void background()
{
    textcolor(23);
    for(int z=0;z<MAX_SHIP_Y+5;z++)
    {
        gotoxy(BORDER-2,z);
        printf("%c",186);

    }
 textcolor(10);
 gotoxy(BORDER,5);
 printf("SCORE:");
 gotoxy(BORDER,9);
 textcolor(14);
 printf("ENEMY NO:");
 gotoxy(BORDER,7);
 printf("WAVE:");
 gotoxy(BORDER,3);
 textcolor(12);
 printf("COUNTDOWN:");
 gotoxy(BORDER+6,15);
 textcolor(11);
 printf("Gala-C-tic Shooter");
 gotoxy(BORDER+6,16);
 printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",247,247,247,247,247,247,247,247,247,247,247,247,247,247,247,247,247,247);
}
                                                         //loading screen
void loading(char name[])
 {
        gotoxy(45,15);
        textbackground(41,15);
        printf("Let's get shooting! %s",name);
        gotoxy(51,16);
        printf("LOADING...");
        textbackground(42,31);
        for(int l=0;l<33;l++)
        {
        Sleep(LOAD_TIME);
        gotoxy(40+l,17);
        printf("%c",178);
        }
        Sleep(1000);
        textbackground(15,0);
        system("cls");
 }
                                                                //main menu of game
void game_menu()
{
    system("cls");
    PlaySound(("select1.wav"),0,1);
    textcolor(11);
    char m='a';
    hidecursor();
    printf("\n\n\n\n\tUse up & down arrows to navigate through items and enter key to select it");
    printf("\n\n\tDon't forget to read instructions before playing");
    int mx=MENU_X-3,my=MENU_Y;
    textcolor(14);
    gotoxy(MENU_X,MENU_Y+4);
    printf("NEW GAME");
    gotoxy(MENU_X,MENU_Y+2);
    printf("LEADERBOARD");
    gotoxy(MENU_X,MENU_Y);
    printf("INSTRUCTIONS");
    gotoxy(MENU_X,MENU_Y+6);
    printf("EXIT");
    gotoxy(mx,my);
    printf("%c",175);

    while(m!=13)
    {
    m=getch();
    PlaySound(("menu.wav"),0,1);
    if(m==80 &&  my<=MENU_Y+4 )
    {
        gotoxy(mx,my);
        printf("  ");
        my+=2;
        gotoxy(mx,my);
        printf("%c",175);
    }
    if(m==72 && my>=MENU_Y+2)
    {
        gotoxy(mx,my);
        printf("  ");
        my-=2;
        gotoxy(mx,my);
        printf("%c",175);
    }
    }

    PlaySound(("select1.wav"),0,1);
    if(my==MENU_Y)
    {
        instructions();
    }
    else if(my==MENU_Y+4)
    {
        system("cls");
        game();
    }
    else if(my==MENU_Y+2)
    {
        leaderboard();
    }
    else
    {
        exit(0);
    }
    gotoxy(0,0);
}

                                                          //instructions of game
void instructions()
{
system("cls");
printf("\n\tMOVEMENTS & GENERALS:");
printf("\n\t%c 'W or Up arrow' to move up\n\t%c 'A or Left-side arrow' to move left",30,17);
printf("\n\t%c 'S or Down arrow' to move down\n\t%c 'D or Right-side arrow' to move right",31,16);
printf("\n\t  Press 'Space-bar' to shoot");
printf("\n\n\t# You can view the current status at the right side of screen while playing");
printf("\n\t# Try to get maximum score by destroying enemy ships within set limit of countdown");
printf("\n\t# Press 'ESC' to exit to menu while playing.However exiting will save the score to leader-boards");
printf("\n\t# Press 'P' to pause the game");
printf("\n\n\n\tTips:");
printf("\n\t# You can shoot only once before the fired projectile disappears");
printf("\n\t# Every enemy ship has its own weak point so destroying some part may not be enough.\n\t  So be sure to hit them at correct spot");
printf("\n\t# Countdown time is not affected while reloading your weapon and destroying enemy ships");
textcolor(10);
printf("\n\n\n\t\t\tGOOD LUCK!!");
printf("\n\n\t\tPress any key to go back");
getch();
game_menu();
}


                                                              //countdown sleep
void countdown_sleep(int m)
{
    for(int z=0;z<m;z++)
    {
    Sleep(1);
    countdown--;
    gotoxy(BORDER+11,3);
    textcolor(15);
    printf("%d ",countdown);
    }
}


                                                                //leader-board display
void leaderboard()
{
system("cls");
printf("score is displayed based on time from descending order");
textcolor(11);
gotoxy(SCORE_X,SCORE_Y-2);
printf("NAME:          SCORE:");
textcolor(10);
int count=0;
int scor,i=0;
char name[10];
FILE *fp;
 if((fp=fopen("leaderboard","r"))==NULL)
 {
  fp=fopen("leaderboard","w+");
  printf("\n\n\tLeaderboard not created yet!!");
  }
  fp=fopen("leaderboard","r");
  while(!feof(fp))
  {
   count++;
  fscanf(fp,"%s %d",name,&scor);
  gotoxy(SCORE_X-3,SCORE_Y+i);
  printf("%d. %-15s%d",count,name,score);
  i+=2;
  }
  if(count==1)
  {
    printf("\n\tLeaderboard not created yet!!");
  }
  gotoxy(SCORE_X-3,SCORE_Y+i-2);
  printf("                                          ");
  fflush(fp);
  fclose(fp);
  textcolor(14);
  printf("\n\n\n\t\tpress any key to go back");
  getch();
  game_menu();
}




