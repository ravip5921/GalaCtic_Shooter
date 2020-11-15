
void objects(int ox,int oy)
{
 int n=rand()%4,c;
 c=(rand()%14)+1;

 switch(n)
  {
    case 1:
    textcolor(c);
    gotoxy(ox-1,oy-1);
    printf("%c",210);
    gotoxy(ox-4,oy);
    printf("%c%c%c%c%c%c%c",174,198,206,153,206,181,175);
    gotoxy(ox-2,oy+1);
    printf("%c%c%c",216,234,216);
    break;

    case 2:
     textcolor(c);
     gotoxy(ox-1,oy-1);
     printf("%c%c%c%c%c",170,220,220,220,169);
     gotoxy(ox-1,oy);
     printf("%c%c%c%c%c",219,219,233,219,219);
     gotoxy(ox-1,oy+1);
     printf("%c%c%c%c%c",223,223,223,223,223);
     break;

    case 3:
    textcolor(c);
    gotoxy(ox-3,oy-1);
    printf("%c%c %c %c%c",243,220,209,220,242);
    gotoxy(ox-2,oy);
    printf("%c%c%c%c%c",223,219,219,219,223);
    gotoxy(ox,oy+1);
    printf("%c",223);
    break;

    default:
     textcolor(c);
     gotoxy(ox,oy);
     printf("%c%c",223,223);
     gotoxy(ox,oy-1);
     printf("%c%c",220,220);
     break;

  }

}
