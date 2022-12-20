#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{
    char id;
    int valeur[3];
}player;

player T[2];
#define p 46
#define q 6
#define p1 5
#define p2 75

int n1, n2, w;
int cs[9];
char name1[30], name2[30];

void initial()
{
    w = 0;
    T[0].id = 'a';
    T[1].id = 'b';
    n1 = 0;
    n2 = 0;
    for (int i = 0; i < 9; i++)
        cs[i] = 0;
}

void run()
{
    int win;
    initial();
    table(p,q);
    do
    {
        play('a');
        if (checkwin() == 1)
            break;
        else
            play('b');
    } while (n1!=3);

    check();

    if (w <= 0){
        do
        {
            relay('a');
            w = checkwin();
            if (w == 1)
                break;
            else
                relay('b');
            w = checkwin();
        } while (w != 1 && w != 2);

        check();
    }
}

void check()
{
    w = checkwin();
    if (w > 0)
    {
        if (w == 1)
        {
            gotoxy(43,24);
            printf("The winner is \"%s\"", name1);
        }
        else
        {
            gotoxy(43,24);
            printf("The winner is \"%s\"", name2);
        }
    }
}

void play(char id)
{
    int nb, cpt;
    do
    {
        cpt = 0;
        if (id == 'a')
        {
            gotoxy(p1,15);printf("                       ");
            gotoxy(p1,15);printf("%s: ", name1);scanf("%d",&nb);
        }
        else
        {
            gotoxy(p2,15);printf("                       ");
            gotoxy(p2,15);printf("%s: ",name2);scanf("%d",&nb);
        }
        
        for (int i = 0; i < 9; i++)
        {
            if (nb == (i+1) && cs[i] == 0)
            {
                if (id == 'a')
                {    
                    draw(id, nb);
                    T[0].valeur[n1] = nb;
                    n1++;
                    cs[i] = 1;
                    gotoxy(p1,15);printf("                       ");
                }
                else if (id == 'b')
                {    
                    draw(id, nb);
                    T[1].valeur[n2] = nb;
                    n2++;
                    cs[i] = 2;
                    gotoxy(p2,15);printf("                       ");
                }
                cpt++;
                i=9;
            }
        }
        if (cpt == 0)
        {
            gotoxy(45,24);printf("Invalid Position!!", 130);
            Sleep(1800);
            gotoxy(45,24);printf("                      ");
        }
    } while (cpt == 0);
}

void relay(char id)
{
    int nb, np, v, ch;
    
    if (id == 'a')
    {
        gotoxy(p1,15);printf("%s", name1);
        do
        {
            v=0;
            gotoxy(p1,16);printf("                                  ");
            gotoxy(p1,16);printf("Symbol which place will change: ");scanf("%d",&nb);
            
            for (int i = 0; i < 3; i++){
                if (T[0].valeur[i] == nb && cs[nb-1] == 1 && check_nb(nb) == 1){
                    ch=i;
                    v++;
                    i=3;
                }
            }
            if (v==0){
                gotoxy(45,26);printf("Invalid Position!!");
                Sleep(1500);
                gotoxy(45,26);printf("                  ");
            }
        } while (v == 0);
        do
        {
            gotoxy(p1,17);printf("                ");
            gotoxy(p1,17);printf("New position: ");scanf("%d",&np);
            if (cs[np-1] == 0 && check_np(nb,np) == 1){
                T[0].valeur[ch] == np;
                v = -1;
            }
            else{
                gotoxy(45,26);printf("Invalid Position!!");
                Sleep(1500);
                gotoxy(45,26);printf("                  ");
            }
        } while (v != -1);

        //Mise a jour de la case
        cs[np-1]=1;
        //Mise a jour de la case où le symbole a été enlevé
        cs[nb-1]=0;

        clean(nb);
        draw('a',np);
        T[0].valeur[ch] = np;

        gotoxy(p1,15);printf("                       ");
        gotoxy(p1,16);printf("                                  ");
        gotoxy(p1,17);printf("                ");
    }
    else
    {
        gotoxy(p2,15);printf("%s", name2);
        do
        {
            v=0;
            gotoxy(p2,16);printf("                                  ");
            gotoxy(p2,16);printf("Symbol which place will change: ");scanf("%d",&nb);
            
            for (int i = 0; i < 3; i++){
                if (T[1].valeur[i] == nb && cs[nb-1] == 2 && check_nb(nb) == 1){
                    ch=i;
                    v++;
                    i=3;
                }
            }
            if (v==0){
                gotoxy(45,26);printf("Invalid Position!!");
                Sleep(1500);
                gotoxy(45,26);printf("                  ");
            }
        } while (v == 0);
        do
        {
            gotoxy(p2,17);printf("                     ");
            gotoxy(p2,17);printf("New position: ");scanf("%d",&np);
            if (cs[np-1] == 0 && check_np(nb,np) == 1){
                T[1].valeur[ch] == np;
                v = -1;
            }
            else{
                gotoxy(45,26);printf("Invalid Position!!");
                Sleep(1500);
                gotoxy(45,26);printf("                  ");
            }
        } while (v != -1);

        //Mise a jour de la case
        cs[np-1]=2;
        //Mise a jour de la case où le symbole a été enlevé
        cs[nb-1]=0;

        clean(nb);
        draw('b',np);
        T[1].valeur[ch] = np;

        gotoxy(p2,15);printf("                       ");
        gotoxy(p2,16);printf("                                  ");
        gotoxy(p2,17);printf("                ");
    }
}

int check_nb(int nb)
{
    if (nb == 1 && (cs[1] == 0 || cs[3] == 0 || cs[4] == 0))
        return 1;
    else if (nb == 2 && (cs[0] == 0 || cs[2] == 0 || cs[4] == 0))
        return 1;
    else if (nb == 3 && (cs[2] == 0 || cs[4] == 0 || cs[5] == 0))
        return 1;
    else if (nb == 4 && (cs[0] == 0 || cs[4] == 0 || cs[6] == 0))
        return 1;
    else if (nb == 5)
        return 1;
    else if (nb == 6 && (cs[2] == 0 || cs[4] == 0 || cs[8] == 0))
        return 1;
    else if (nb == 7 && (cs[3] == 0 || cs[4] == 0 || cs[7] == 0))
        return 1;
    else if (nb == 8 && (cs[6] == 0 || cs[4] == 0 || cs[8] == 0))
        return 1;
    else if (nb == 9 && (cs[5] == 0 || cs[4] == 0 || cs[7] == 0))
        return 1;
    else
        return 0;
}

int check_np(int nb, int np)
{
    if (nb == 1 && (np == 2 || np == 4 || np ==5))
        return 1;
    else if (nb == 2 && (np == 1 || np == 3 || np ==5))
        return 1;
    else if (nb == 3 && (np == 2 || np == 5 || np ==6))
        return 1;
    else if (nb == 4 && (np ==  1 || np == 5 || np ==7))
        return 1;
    else if (nb == 5)
        return 1;
    else if (nb == 6 && (np == 3 || np == 5 || np ==9))
        return 1;
    else if (nb == 7 && (np == 4 || np == 5 || np ==8))
        return 1;
    else if (nb == 8 && (np == 7 || np == 5 || np ==9))
        return 1;
    else if (nb == 9 && (np == 6 || np == 5 || np ==8))
        return 1;
    else
        return 0;
}

int checkwin()
{
    if (cs[0] == cs[1] && cs[1] == cs[2])
        return cs[0];
        
    else if (cs[3] == cs[4] && cs[4] == cs[5])
        return cs[3];
        
    else if (cs[6] == cs[7] && cs[7] == cs[8])
        return cs[6];
        
    else if (cs[0] == cs[3] && cs[3] == cs[6])
        return cs[0];
        
    else if (cs[1] == cs[4] && cs[4] == cs[7])
        return cs[1];
        
    else if (cs[2] == cs[5] && cs[5] == cs[8])
        return cs[2];
        
    else if (cs[0] == cs[4] && cs[4] == cs[8])
        return cs[0];
        
    else if (cs[2] == cs[4] && cs[4] == cs[6])
        return cs[2];
        
    else if (cs[0] == 0 && cs[1] == 0 && cs[2] == 0 && cs[3] == 0 && cs[4] == 0 && cs[5] == 0 && cs[6] == 0 && cs[7] == 0 && cs[8] == 0)
        return 0;
    else
        return  -1;
}

void draw(char id, int nb)
{
    int x=p, y=q;
    if (id == 'a')
    {
        if(nb == 1)
            X(x+1,y+2);
        if(nb == 2)
            X(x+7,y+2);
        if(nb == 3)
            X(x+12,y+2);
        if(nb == 4)
            X(x+1,y+7);
        if(nb == 5)
            X(x+7,y+7);
        if(nb == 6)
            X(x+12,y+7);
        if(nb == 7)
            X(x+1,y+12);
        if(nb == 8)
            X(x+7,y+12);
        if(nb == 9)
            X(x+12,y+12);
    }
    if (id == 'b')
    {    
        if(nb == 1)
            O(x+1,y+2);
        if(nb == 2)
            O(x+7,y+2);
        if(nb == 3)
            O(x+12,y+2);
        if(nb == 4)
            O(x+1,y+7);
        if(nb == 5)
            O(x+7,y+7);
        if(nb == 6)
            O(x+12,y+7);
        if(nb == 7)
            O(x+1,y+12);
        if(nb == 8)
            O(x+7,y+12);
        if(nb == 9)
            O(x+12,y+12);
    }
}

void clean(int nb)
{
    int x=p, y=q;
    if(nb == 1)
        Cl(x+1,y+2);
    if(nb == 2)
        Cl(x+7,y+2);
    if(nb == 3)
        Cl(x+12,y+2);
    if(nb == 4)
        Cl(x+1,y+7);
    if(nb == 5)
        Cl(x+7,y+7);
    if(nb == 6)
        Cl(x+12,y+7);
    if(nb == 7)
        Cl(x+1,y+12);
    if(nb == 8)
        Cl(x+7,y+12);
    if(nb == 9)
        Cl(x+12,y+12);
}

void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    // cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void text(int x, int y, int c)
{
    if (c == 1){
        gotoxy(x,y);  printf("######## ##  #####   ########    ##      #####   ######## ########  ####### ");
        gotoxy(x,y+1);printf("   ##    ## ##          ##      ####    ##          ##    ##    ##  ##       ");
        gotoxy(x,y+2);printf("   ##    ## ##          ##     ##  ##   ##          ##    ##    ##  ####### ");
        gotoxy(x,y+3);printf("   ##    ## ##          ##    ########  ##          ##    ##    ##  ##       ");
        gotoxy(x,y+4);printf("   ##    ##  #####      ##   ##      ##  #####      ##    ########  ####### ");
        gotoxy(x+77,y+4);printf("by_bslik01");
    }
    else if (c == 0)
    {
        gotoxy(x,y);  printf("#######  ##    ## ####### ");
        gotoxy(x,y+1);printf("##    ##  ##  ##  ##      ");
        gotoxy(x,y+2);printf("#######    ####   ####### ");
        gotoxy(x,y+3);printf("##    ##    ##    ##      ");
        gotoxy(x,y+4);printf("#######     ##    ####### ");
        Sleep(1000);
    }
}

void X(int x, int y) 
{
    gotoxy(x,y);printf("%c", 92);
    gotoxy(x+1,y+1);printf("%c", 92);
    gotoxy(x+3,y);printf("%c", 47);
    gotoxy(x+2,y+1);printf("%c", 47);
    gotoxy(x+1,y+1);printf("%c", 88);
    gotoxy(x+1,y+2);printf("%c", 47);
    gotoxy(x+2,y);printf("%c", 47);
    gotoxy(x+2,y+2);printf("%c", 92);
    gotoxy(x+3,y+3);printf("%c", 92);
    gotoxy(5,30);
}

void O(int x, int y) 
{
    int t = 3; // Taille de la lettre "O"
    for (int i = x; i < x+t+1; i++)
    {
        gotoxy(i,y);printf("%c", 196);
        gotoxy(i,y+t);printf("%c", 196);
    }
    
    for (int i = y; i < y+t+1; i++)
    {
        gotoxy(x,i);printf("%c", 179);
        gotoxy(x+t,i);printf("%c", 179);
    }

    gotoxy(x,y);printf("%c", 218);
    gotoxy(x+t,y);printf("%c", 191);
    gotoxy(x,y+t);printf("%c", 192);
    gotoxy(x+t,y+t);printf("%c", 217);
    gotoxy(5,30);
}

void Cl(int x, int y)
{
    int t = 3; // Taille de la lettre "O"
    for (int i = x; i < x+t+1; i++)
    {
        for (int j = y; j < y+t+1; j++)
        {
            gotoxy(i,j);printf(" ");
        }
    }
    
    gotoxy(x,y);printf(" ");
    gotoxy(x+t,y);printf(" ");
    gotoxy(x,y+t);printf(" ");
    gotoxy(x+t,y+t);printf(" ");
    gotoxy(5,30);
}

void table(int x, int y) 
{
    for (int i = x; i < x+16; i++)
    {
    	gotoxy(i,y+1);printf("%c", 196);    	
        gotoxy(i,y+6);printf("%c", 196);
        gotoxy(i,y+11);printf("%c", 196);
        gotoxy(i,y+16);printf("%c", 196);        
    }
    
    for (int i = y+1; i < y+16; i++)
    {
    	gotoxy(x,i);printf("%c", 179);
        gotoxy(x+6,i);printf("%c", 179);
        gotoxy(x+11,i);printf("%c", 179);
        gotoxy(x+16,i);printf("%c", 179);
    }
	// Les "+" des centres
    gotoxy(x+6,y+6);printf("%c", 197);
    gotoxy(x+6,y+11);printf("%c", 197);
    gotoxy(x+11,y+6);printf("%c", 197);
    gotoxy(x+11,y+11);printf("%c", 197);
    // Les bords du tableau
    gotoxy(x,y+6);printf("%c", 195);
    gotoxy(x,y+11);printf("%c", 195);
    gotoxy(x+16,y+6);printf("%c", 180);
    gotoxy(x+16,y+11);printf("%c", 180);
    gotoxy(x+6,y+1);printf("%c", 194);
    gotoxy(x+11,y+1);printf("%c", 194);
    gotoxy(x+6,y+16);printf("%c", 193);
    gotoxy(x+11,y+16);printf("%c", 193);
    // Les sommets du tableau
	gotoxy(x, y+1);printf("%c", 218);
    gotoxy(x+16, y+1);printf("%c", 191);
    gotoxy(x, y+16);printf("%c", 192);
    gotoxy(x+16, y+16);printf("%c", 217);
}

int main() 
{
    char g;
    
    text(19,2,1);
    gotoxy(15,10);
    printf("Name of the First player: ");scanf("%s", &name1);
    gotoxy(15,12);
    printf("Name of the Second player: ");scanf("%s", &name2);
    gotoxy(97,6);Sleep(1000);

    do
    {
        system("cls");
        text(19,2,1);
        run();
        gotoxy(p1,15);printf("                       ");
        gotoxy(p1,16);printf("                                  ");
        gotoxy(p1,17);printf("                ");
        gotoxy(p2,15);printf("                       ");
        gotoxy(p2,16);printf("                                  ");
        gotoxy(p2,17);printf("                ");
        gotoxy(38,27);
        printf("Do you want to leave? Yes(Y) or No(N)");
        gotoxy(38,28);
        printf("      Just press \"Y\" or \"N\"");
        g = getch();
    } while (g != 'y' && g != 'Y');

    system("cls");
    text(46,10,0);
}
