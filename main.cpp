#include <graphics.h>
#include <stdlib.h>
#include <ctime>
#include <winbgim.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#define NEGATIVE_INT -100000
using namespace std;

/////////////////////// Se decid de catre jucatori

int nrMutMax=70;// maximul de mutari dintr o partida
int scoaterepiese=6;// numarul minim de mutari dupa care putem elimina piese

//////////////////////


int z=0,nrcastNG=0,nrcastAL=0,apasat=0;
int numarPatrate = 8;
int tabla[8][8];
int culoriTabla[8][8];
int mutat[8][8];
int laturaPatrat = 80;
int piesaApasata=0,piesaX,piesaY;
int okeystergere=1;
int undo=0;
int cx,ccx,ccy,cy,piesastearsa,piesamutata;
int tipPiesa;
int playerCurent = 1;
char result=1;
int nrMutAlb=0, nrMutNegru=0;
char nma[]="Mutari alb : ";
char nmn[]="Mutari negru : ";
bool intoarce;
int mda;
int deplasareLinie[] = {1, 1, -1, -1};
int deplasareColoana[] = {-1, 1, 1, -1};


bool mutarePiesa1(int tipPiesa);
void startjoc();
void mutarePiesaCalculator (int tipPiesa);
void scoatePiesaCapturata(int tipPiesa, int linie, int coloana);
bool esteVreoPiesaCapturata(int tipPiesa, int linie, int coloana);
bool inInterior(int linie, int coloana);
void startjoc1();
bool mutarePiesa(int tipPiesa);
void cedeaza(int x,int y);
void reloade1(int x,int y,int lu1,int cu1,int lu2,int cu2,int lc,int cc,int tippiesa);
void reloade(int x,int y,int lu1,int cu1,int lu2,int cu2,int lc,int cc,int tippiesa);
void verificacapturare(int x, int y);
void desenezTabla();
void crearepozitiejucatori();
void verificarecastigator();
void verificarecastigator1();
void desenezJucator2(int x,int y,int razaCerc);
void desenezJucator1(int x,int y,int razaCerc);
void desenezPatratGri(int x,int y,int lungime);
void desenezPatratAlb(int x,int y,int lungime);
void creareTablaculori();
void bordareTabla();
int checkWinner();

int main()
{
    PlaySound("joc.wav", NULL, SND_LOOP | SND_ASYNC);
    int x,y;
    if(z==0)
        initwindow(800,640);

dinNou:
    readimagefile("main.jpg", 0, 0, 800, 640);

    while(1)
    {
iesi:
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(x>=307 && x<=420)
                if(y>=230 && y<=280)
                {
                    startjoc();
                    if (intoarce)
                    {
                        intoarce = false;
                        goto dinNou;
                    }
                }
            if(x>=310 && x<=410)
                if(y>=370 && y<=420)
                {
                    readimagefile("help2.jpg", 0, 0, 800, 640);
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            x=mousex();
                            y=mousey();
                            clearmouseclick(WM_LBUTTONDOWN);
                            if(x>=13 && x<=90)
                                if(y>=20 && y<=70)
                                {
                                    readimagefile("main.jpg", 0, 0, 800, 640);
                                    break;
                                }
                        }
                    }
                }
        }
    }
    getch();
    return 0;
}


void bordareTabla()
{
    for(int i=0; i<=8; i++)
        tabla[0][i]=tabla[i][0]=NEGATIVE_INT;
}

void creareTablaculori()
{
    int i,j;
    for(i=0; i<numarPatrate; i++)
    {
        j=!(i%2);
        for(; j<=7; j+=2)
            culoriTabla[i][j]=1;
        j=i%2;
        for(; j<=7; j+=2)
            culoriTabla[i][j]=2;
    }
}

void desenezPatratAlb(int x,int y,int lungime)
{
    setfillstyle(1, 15);
    bar(x-lungime/2,y-lungime/2,x+lungime/2,y+lungime/2);
}

void desenezPatratGri(int x,int y,int lungime)
{
    setfillstyle(1,8);
    bar(x-lungime/2,y-lungime/2,x+lungime/2,y+lungime/2);
}

void desenezJucator1(int x,int y,int razaCerc)
{
    setfillstyle(1,15);
    fillellipse(x, y, razaCerc, razaCerc);


}

void desenezJucator2(int x,int y,int razaCerc)
{
    setfillstyle(1,0);
    fillellipse(x, y, razaCerc, razaCerc);
}

void crearepozitiejucatori()
{
    int i,j;
    //initializez piesele negre

    i=0;
    for(j=1; j<=7; j+=2)
    {
        tabla[i][j] = 2;
        mutat[i][j] = 1;
    }
    i=1;
    for(j=0; j<=7; j+=2)
    {
        tabla[i][j] = 2;
        mutat[i][j] = 1;
    }
    //initializez piesele albe
    i=6;
    for(j=1; j<=7; j+=2)
    {
        tabla[i][j] = 1;
        mutat[i][j] = 1;
    }
    i=7;
    for(j=0; j<=7; j+=2)
    {
        tabla[i][j] = 1;
        mutat[i][j] = 1;
    }
    for (i=2; i<=5; i++)
        for(j=0; j<=7; j++)
            tabla[i][j]=0;
}

void desenezTabla()
{
    int laturaJ = laturaPatrat/2;
    int i,j,x,y;
    for(i=0; i<numarPatrate; i++)
    {
        for(j=0; j<numarPatrate; j++)
        {
            x = j*laturaPatrat+laturaJ;
            y = i*laturaPatrat+laturaJ;
            if (culoriTabla[i][j]==2)
                desenezPatratAlb(x, y, laturaPatrat-1);
            else
                desenezPatratGri(x, y, laturaPatrat-1);
            if (tabla[i][j]==1)
                desenezJucator1(x, y, laturaPatrat/3);
            else
            {
                if (tabla[i][j]==2)
                    desenezJucator2(x, y, laturaPatrat/3);
            }
        }
    }

}

void verificacapturare(int x, int y)
{
    piesastearsa=tabla[x][y];
    if(y==0)
    {
        if(tabla[x+1][y+1]!=0)
        {
            if(tabla[x-1][y+1]!=0)
            {
                if(mutat[x][y]==0)
                {
                    tabla[x][y]=0;
                    desenezTabla();
                    okeystergere=0;
                }
            }
        }
    }
    if(y==7)
    {
        if(tabla[x-1][y-1]!=0)
        {
            if(tabla[x+1][y-1]!=0)
            {
                if(mutat[x][y]==0)
                {
                    tabla[x][y]=0;
                    desenezTabla();
                    okeystergere=0;
                }
            }
        }
    }
    if(x==0)
    {
        if(tabla[x+1][y+1]!=0)
        {
            if(tabla[x+1][y-1]!=0)
            {
                if(mutat[x][y]==0)
                {
                    tabla[x][y]=0;
                    desenezTabla();
                    okeystergere=0;
                }
            }
        }
    }
    if(x==0)
    {
        if(y==7)
        {
            if(tabla[x+1][y-1]!=0)
            {
                tabla[x][y]=0;
                desenezTabla();
                okeystergere=0;

            }

        }
    }
    if(x==7)
    {
        if(y==0)
        {
            if(tabla[x-1][y+1]!=0)
            {
                tabla[x][y]=0;
                desenezTabla();
                okeystergere=0;

            }

        }
    }
    if(x==7)
    {
        if(tabla[x-1][y+1]!=0)
        {
            if(tabla[x-1][y-1]!=0)
            {
                if(mutat[x][y]==0)
                {
                    tabla[x][y]=0;
                    desenezTabla();
                    okeystergere=0;
                }
            }
        }
    }
    if(tabla[x+1][y+1]!=0)
    {
        if(tabla[x-1][y-1]!=0)
        {
            if(tabla[x+1][y-1]!=0)
            {
                if(tabla[x-1][y+1]!=0)
                {
                    if(mutat[x][y]==0)
                    {
                        tabla[x][y]=0;
                        desenezTabla();
                        okeystergere=0;

                    }
                }
            }

        }
    }
    cx=x;
    cy=y;
}

void reloade(int x,int y,int lu1,int cu1,int lu2,int cu2,int lc,int cc,int tippiesa)
{
    tabla[lu2][cu2]=0;
    tabla[lu1][cu1]=piesamutata;
    mutat[lc][cc]=1;
    desenezTabla();
    undo = 0;
    if (piesamutata==1)
    {
        readimagefile("j2.jpg", 640, 0, 900, 640);
    }
    else
    {
        readimagefile("j1.jpg", 640, 0, 900, 640);
    }

    if (piesamutata==2)
    {
        nrMutNegru=nrMutNegru-1;
        settextstyle(0, HORIZ_DIR,4);
        bgiout<<nrMutNegru<<endl;
        outstreamxy(838,99);

        settextstyle(0, HORIZ_DIR,4);
        bgiout<<nrMutAlb<<endl;
        outstreamxy(838,489);

    }
    else
    {
        nrMutAlb=nrMutAlb-1;
        settextstyle(0, HORIZ_DIR,4);
        bgiout<<nrMutAlb<<endl;
        outstreamxy(838,99);

        settextstyle(0, HORIZ_DIR,4);
        bgiout<<nrMutNegru<<endl;
        outstreamxy(838,489);

    }

}

void reloade1(int x,int y,int lu1,int cu1,int lu2,int cu2,int lc,int cc,int tippiesa)
{
    tabla[lu1][cu1]=piesastearsa;
    mutat[lc][cc]=1;
    undo = 0;
    if (piesastearsa==1)
        readimagefile("j1.jpg", 640, 0, 900, 640);
    else
        readimagefile("j2.jpg", 640, 0, 900, 640);
    if (piesastearsa==2)
    {

        settextstyle(0, HORIZ_DIR,4);
        bgiout<<nrMutNegru<<endl;
        outstreamxy(838,99);

        settextstyle(0, HORIZ_DIR,4);
        bgiout<<nrMutAlb<<endl;
        outstreamxy(838,489);

    }
    else
    {
        settextstyle(0, HORIZ_DIR,4);
        bgiout<<nrMutAlb<<endl;
        outstreamxy(838,99);

        settextstyle(0, HORIZ_DIR,4);
        bgiout<<nrMutNegru<<endl;
        outstreamxy(838,489);

    }

    desenezTabla();
}

void cedeaza(int x,int y)
{
    if(x>=658&& x<=810)
    {
        if(y>=220 && y<=250)
        {
            if(playerCurent==2)
            {
                closegraph();
                initwindow(800,640);
                readimagefile("v2.jpg", 0, 0, 800, 640);
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        x=mousex();
                        y=mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(x>=730 && x<=800)
                            if(y>=580 && y<=640)
                            {
                                z=1;
                                main();
                            }

                    }
                }
            }
        }
    }
    if(x>=658&& x<=810)
    {
        if(y>=580 && y<=610)
        {
            if(playerCurent==1)
            {
                closegraph();
                initwindow(800,640);
                readimagefile("v1.jpg", 0, 0, 800, 640);
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        x=mousex();
                        y=mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(x>=730 && x<=800)
                            if(y>=580 && y<=640)
                            {
                                z=1;
                                main();
                            }

                    }
                }
            }
        }
    }



}

bool mutarePiesa(int tipPiesa)
{
    int x,y,l,c,lc,cc,lu1,cu1,lu2,cu2;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            bool ok=false;
            clearmouseclick(WM_LBUTTONDOWN);
            cedeaza(x,y);
            if(x>=730 && x<=785)
            {
                if(y>=280 && y<=340)
                {
                    if( undo==1 || (undo == 0 && okeystergere == 0))
                    {
                        cout<<"UNDO\n";
                        if(okeystergere==1)
                        {
                            reloade(x,y,lu1,cu1,lu2,cu2,lc,cc,tipPiesa);
                        }
                        if(okeystergere==0)
                        {
                            reloade1(x,y,cx,cy,cx,cy,lc,cc,tipPiesa);
                            okeystergere=1;

                        }

                        desenezTabla();
                        Beep(600,300);
                        return true;
                    }

                }
            }

            okeystergere=1;
            l=y/laturaPatrat;
            c=x/laturaPatrat;

            cout<<"("<<l<<','<<c<<')';
            verificacapturare(l,c);
            if(mda==1)
            {
                verificarecastigator1();
            }
            if (piesaApasata)
            {


                piesaApasata=false;
                if(tabla[l][c]==0)
                {
                    if(tipPiesa==1)
                    {
                        cout<<" a mutat albul\n";
                        if(l==piesaY-1 && c==piesaX -1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                            nrMutAlb=nrMutAlb+1;
                        }
                        if(l==piesaY+1 && c==piesaX+1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                            nrMutAlb=nrMutAlb+1;
                        }
                        if(l==piesaY-1 && c==piesaX +1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                            nrMutAlb=nrMutAlb+1;
                        }
                        if(l==piesaY+1 && c==piesaX -1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                            nrMutAlb=nrMutAlb+1;

                        }
                        readimagefile("j1.jpg", 640, 0, 900, 640);
                    }
                    else if (tipPiesa==2)
                    {
                        cout<<" a mutat negrul\n";
                        if(l==piesaY-1 && c==piesaX -1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;
                            nrMutNegru=nrMutNegru+1;
                        }
                        if(l==piesaY+1 && c==piesaX+1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                            nrMutNegru=nrMutNegru+1;
                        }
                        if(l==piesaY-1 && c==piesaX +1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                            nrMutNegru=nrMutNegru+1;
                        }
                        if(l==piesaY+1 && c==piesaX -1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                            nrMutNegru=nrMutNegru+1;
                        }
                    }


                    piesamutata=tabla[l][c];
                    lu2=l;
                    cu2=c;
                    mutat[lc][cc]=0;
                    undo=1;
                    okeystergere=1;

                }
                if (tipPiesa==2)

                {
                    readimagefile("j2.jpg", 640, 0, 900, 640);

                    settextstyle(0, HORIZ_DIR,4);
                    bgiout<<nrMutNegru<<endl;
                    outstreamxy(838,489);


                    settextstyle(0, HORIZ_DIR,4);
                    bgiout<<nrMutAlb<<endl;
                    outstreamxy(838,99);
                    apasat=0;
                }
                else
                {
                    readimagefile("j1.jpg", 640, 0, 900, 640);

                    settextstyle(0, HORIZ_DIR,4);
                    bgiout<<nrMutAlb<<endl;
                    outstreamxy(838,489);

                    settextstyle(0, HORIZ_DIR,4);
                    bgiout<<nrMutNegru<<endl;
                    outstreamxy(838,99);
                    apasat=0;
                }
            }
            else
            {

                if(tabla[l][c]==tipPiesa)
                {
                    piesaApasata=true;
                    piesaX=c;
                    piesaY=l;
                    if(mutat[l][c]==1)
                    {
                        lc=l;
                        cc=c;
                    }
                    lu1=l;
                    cu1=c;
                }
            }
            if (ok)
            {
                break;
            }
        }
    }

    /* for(int i=0 ; i<8; i++)
     {
         for(int j=0 ; j<8 ; j++)
             cout<<tabla[i][j]<<' ';
         cout<<'\n';
     }
     cout<<'\n';
     cout<<'\n';
     cout<<'\n';*/

    /*for(int i=0 ; i<8; i++)
    {
        for(int j=0 ; j<8 ; j++)
            cout<<mutat[i][j]<<' ';
        cout<<'\n';
    }*/
    desenezTabla();
    Beep(600,300);


    return false;
}
int checkWinner()
{   int nrpa=0;
    int nrpn=0;
    int i,j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
            if(tabla[i][j]==1)
                nrpa++;
            else if(tabla[i][j]==2)
                nrpn++;
    if(nrpa>nrpn)
        return 1;
       else if(nrpa<nrpn)
               return 2;
               else return 0;

}
void albulCastiga()
{ int x,y;
    closegraph();
                initwindow(800,640);
                readimagefile("v2.jpg", 0, 0, 800, 640);
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        x=mousex();
                        y=mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(x>=730 && x<=800)
                            if(y>=580 && y<=640)
                            {
                                z=1;
                                main();
                            }

                    }
                }
}
void negrulCastiga()
{    int x,y;
        closegraph();
                initwindow(800,640);
                readimagefile("v1.jpg", 0, 0, 800, 640);
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        x=mousex();
                        y=mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(x>=730 && x<=800)
                            if(y>=580 && y<=640)
                            {
                                z=1;
                                main();
                            }

                    }
                }
}
void startjoc1()
{
    nrMutNegru=0;
    nrMutAlb=0;
    closegraph();
    initwindow(900,640);
    readimagefile("j2.jpg", 640, 0, 900, 640);
    creareTablaculori();
    crearepozitiejucatori();
    desenezTabla();
    settextstyle(0, HORIZ_DIR,4);
    bgiout<<nrMutAlb<<endl;
    outstreamxy(838,99);


    settextstyle(0, HORIZ_DIR,4);
    bgiout<<nrMutNegru<<endl;
    outstreamxy(838,489);

    do
    {

        if(scoaterepiese==nrMutNegru)
        {
            for(int i=0; i<=8; i++)
            {
                for(int j=0; j<=8; j++)
                    mutat[i][j]=0;
            }
        }

        if (mutarePiesa(playerCurent))
        {
            playerCurent = 3 - playerCurent;
            mda=1;
            continue;
        }
        playerCurent = 3 - playerCurent;
        mda=1;
    }
    while (nrMutNegru<nrMutMax);
    if(mda==1)
    {
        verificarecastigator1();
    }
    if(nrMutNegru==nrMutMax)
       {if(checkWinner()==1)
           albulCastiga();
       else if(checkWinner()==2)
                 negrulCastiga();
       else {
            setbkcolor(BLACK);
            setfillstyle(1, BLACK);
            setcolor(RED);
            settextstyle(3, HORIZ_DIR, 0.5);
            outtextxy(740, 410, "Remiza");
       }
       }
    getch();
}



bool inInterior(int linie, int coloana)
{
    return linie >= 0 && coloana >=0 && linie < numarPatrate && coloana < numarPatrate;
}

bool esteVreoPiesaCapturata(int tipPiesa, int linie, int coloana)
{
    // am mutat o piesa pe tabla pe linia linie si coloana coloana
    for (int i=0; i<4; i++) // de acolo ma uit la vecini
    {
        if (inInterior(linie + deplasareLinie[i],coloana + deplasareColoana[i]))
        {
            // daca pozitiile sunt in interiorul tablei
            int lin = linie + deplasareLinie[i]; // vad pozitia
            int col = coloana + deplasareColoana[i];
            if (tabla[lin][col] == tipPiesa) // daca gasesc langa piesa mutata o piesa de a adversarului
            {
                int totalMutari = 0; // cate mutari posibile are piesa
                int mutariBlocate = 0; // cate mutari nu le poate face pentru ca nu e liber pe tabla
                for (int k=0; k<4; k++)
                {
                    if (inInterior(lin + deplasareLinie[k], col + deplasareColoana[k]))
                    {
                        totalMutari++; // poate face o mutare pe tabla
                        if (tabla[lin + deplasareLinie[k]][col + deplasareColoana[k]] != 0)
                        {
                            mutariBlocate++; // mutarea e blocata
                        }
                    }
                }
                if (totalMutari == mutariBlocate) // daca toate mutarile sunt blocate, piesa e capturata
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void scoatePiesaCapturata(int tipPiesa, int linie, int coloana)
{
    // la fel ca mai sus, doar ca daca gasesc o piesa capturata o scot si nu returnez nimic
    for (int i=0; i<4; i++)
    {
        if (inInterior(linie + deplasareLinie[i],coloana + deplasareColoana[i]))
        {
            int lin = linie + deplasareLinie[i];
            int col = coloana + deplasareColoana[i];
            if (tabla[lin][col] == tipPiesa)
            {
                int totalMutari = 0;
                int mutariBlocate = 0;
                for (int k=0; k<4; k++)
                {
                    if (inInterior(lin + deplasareLinie[k], col + deplasareColoana[k]))
                    {
                        totalMutari++;
                        if (tabla[lin + deplasareLinie[k]][col + deplasareColoana[k]] != 0)
                        {
                            mutariBlocate++;
                        }
                    }
                }
                if (totalMutari == mutariBlocate)
                {
                    tabla[lin][col] = 0;
                }
            }
        }
    }
}

void mutarePiesaCalculator (int tipPiesa)
{

    bool mutat = false;
    int mutariPosibile = 0;
    for (int i=0; i<numarPatrate && mutat == false; i++)
    {
        for (int j=0; j<numarPatrate && mutat == false; j++)
        {
            if (tabla[i][j] == tipPiesa) // am gasit o piesa a calculatorului
            {
                bool amAdaugatMutarea = false;
                for (int k=0; k<4 && mutat == false; k++)// o misc in toate directiile
                {
                    if (inInterior(i + deplasareLinie[k], j + deplasareColoana[k]) && tabla[i + deplasareLinie[k]][j + deplasareColoana[k]] == 0) // daca mutarea asta ramane pe tabla
                    {
                        if (!amAdaugatMutarea) // vreau sa contorizez numarul de mutari posibile
                        {
                            amAdaugatMutarea = true;
                            mutariPosibile++;
                        }
                        int linie = i + deplasareLinie[k]; // calculez noua linie
                        int coloana = j + deplasareColoana[k]; // noua coloana
                        tabla[i][j] = 0; // mut piesa calculatorului acolo
                        tabla[linie][coloana] = tipPiesa;
                        if (esteVreoPiesaCapturata(3 - tipPiesa, linie, coloana)) // si vad daca piesa mutata a blocat vreo piesa de a adversarului
                        {
                            mutat = true; // daca a mutat, imi convine deci efectuez mutarea asta
                            scoatePiesaCapturata(3 - tipPiesa, linie, coloana); // si scot piesa adversarului
                        }
                        if (!mutat) // daca nu blocheaza nimic, pun inapoi piesele cum erau inainte sa le mut
                        {
                            tabla[i][j] = tipPiesa;
                            tabla[linie][coloana] = 0;
                        }
                    }
                }
            }
        }
    }
    // cout<<"Mutari posibile pentru calculator\n"<<mutariPosibile<<'\n';
    if (!mutat) // daca nu am gasit nicio piesa care sa scoata piese ale adversarului
    {if (!mutariPosibile)
        {
            return;
        }
        int mutareAleasa = rand()%mutariPosibile; // vreau sa mut random o piesa de a mea, le am contorizat deci iau una random
        int mutareCurenta = -1; // vreau sa ajung la mutarea aleasa, deci o sa le contorizez din nou
        mutat = false; // cat timp n am mutat
        for (int i=0; i<numarPatrate && mutat == false; i++)
        {
            for (int j=0; j<numarPatrate && mutat == false; j++)
            {
                if (tabla[i][j] == tipPiesa) // am gasit o piesa
                {
                    bool amAdaugatMutarea = false;
                    for (int k=0; k<4 && mutat == false; k++) // verific daca piesa asta poate fi mutata
                    {
                        if (inInterior(i + deplasareLinie[k], j + deplasareColoana[k]) && tabla[i + deplasareLinie[k]][j + deplasareColoana[k]] == 0)
                        {
                            if (!amAdaugatMutarea) // daca da, o contorizez o singura data
                            {
                                amAdaugatMutarea = true;
                                mutareCurenta++;
                            }
                        }
                    }
                    if (mutareAleasa == mutareCurenta) // daca asta e mutarea random pe care trebuie sa o fac
                    {
                        // mut piesa asta
                        for (int k=0; k<4 && mutat == false; k++) // vad unde pot s-o mut
                        {
                            if (inInterior(i + deplasareLinie[k], j + deplasareColoana[k]) && tabla[i + deplasareLinie[k]][j + deplasareColoana[k]] == 0)
                            {
                                // daca mutarea e valida, o efectuez
                                tabla[i][j] = 0; // efectuez mutarea asta
                                tabla[i + deplasareLinie[k]][j + deplasareColoana[k]] = tipPiesa;
                                mutat = true; // si retin c am mutat
                            }
                        }
                    }
                }
            }
        }
    }

    Beep(600,300);
    desenezTabla();
}

bool mutarePiesa1(int tipPiesa)
{
    int x,y,l,c;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            bool ok=false;
            clearmouseclick(WM_LBUTTONDOWN);

            l=y/laturaPatrat;
            c=x/laturaPatrat;

            cout<<"("<<l<<','<<c<<')';
            verificacapturare(l,c);

            if (piesaApasata)
            {
                piesaApasata=false;
                if(tabla[l][c]==0)
                {
                    if(tipPiesa==1)
                    {
                        cout<<" a mutat albul\n";
                        if(l==piesaY-1 && c==piesaX -1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;
                        }
                        if(l==piesaY+1 && c==piesaX+1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                        }
                        if(l==piesaY-1 && c==piesaX +1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                        }
                        if(l==piesaY+1 && c==piesaX -1)
                        {
                            ok =true;
                            tabla[l][c]=tipPiesa;
                            tabla[piesaY][piesaX] = 0;

                        }
                    }
                    piesamutata=tabla[l][c];
                }

            }
            else
            {
                if(tabla[l][c]==tipPiesa)
                {
                    piesaApasata=true;
                    piesaX=c;
                    piesaY=l;
                }
            }
            if (ok)
            {
                break;
            }
        }
    }
    desenezTabla();
    Beep(600,300);
    return false;
}

void verificarecastigator()
{
    nrcastAL=0;
    nrcastNG=0;
    int x,y;
    for(int i=0; i<=7; i++)
    {
        for(int j=0; j<=7; j++)
        {
            if(tabla[i][j]== 1)
                nrcastAL=nrcastAL+1;
            if(tabla[i][j]== 2)
                nrcastNG=nrcastNG+1;

        }
    }
    if(nrcastNG==0)
    {
        if(nrcastAL>0)
        {
            closegraph();
            initwindow(800,640);
            readimagefile("vcpu.jpg", 0, 0, 800, 640);
            while(1)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    x=mousex();
                    y=mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x>=730 && x<=800)
                        if(y>=580 && y<=640)
                        {
                            z=1;
                            main();
                        }

                }
            }
        }

    }
    if(nrcastAL==0)
    {
        if(nrcastNG>0)
        {
            closegraph();
            initwindow(800,640);
            readimagefile("vcpu.jpg", 0, 0, 800, 640);
            while(1)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    x=mousex();
                    y=mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x>=730 && x<=800)
                        if(y>=580 && y<=640)
                        {
                            z=1;
                            main();
                        }

                }
            }
        }

    }
    mda=0;
}
void verificarecastigator1()
{
    nrcastAL=0;
    nrcastNG=0;
    for(int i=0; i<=7; i++)
    {
        for(int j=0; j<=7; j++)
        {
            if(tabla[i][j]== 1)
                nrcastAL=nrcastAL+1;
            if(tabla[i][j]== 2)
                nrcastNG=nrcastNG+1;

        }
    }
    // cout<<'\n'<<nrcastAL<<" "<<nrcastNG;
    if(nrcastNG==0)
    {
        if(nrcastAL>0)
        {
            albulCastiga();
        }

    }
    if(nrcastAL==0)
    {
        if(nrcastNG>0)
        {
            negrulCastiga();
        }

    }
    mda=0;
}

void startjoc2()
{
    nrMutNegru=0;
    nrMutAlb=0;
    closegraph();
    initwindow(900,640);
    readimagefile("reloaded.jpg", 640, 0, 900, 640);
    creareTablaculori();
    crearepozitiejucatori();
    desenezTabla();
    int playerCurent = 1;
    do
    {
        if(scoaterepiese==nrMutNegru)
        {
            for(int i=0; i<=8; i++)
            {
                for(int j=0; j<=8; j++)
                    mutat[i][j]=0;
            }
        }
        if(mda==1)
        {
            verificarecastigator();
        }
        if (playerCurent == 1)
        {
            mda=1;
            mutarePiesa1(playerCurent);

        }
        else if (playerCurent == 2)
        {
            mda=1;
            mutarePiesaCalculator(playerCurent);

        }
        playerCurent = 3 - playerCurent;

    }
    while (true);
    getch();
}

void startjoc()
{
    int x,y;
    readimagefile("joc.jpg", 0, 0, 800, 640);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(x>=280 && x<=470)
                if(y>=211 && y<=250)
                {
                    startjoc2();
                }
            if(x>=288 && x<=471)
                if(y>=340 && y<=381)
                {
                    startjoc1();
                }
            if(x>=30 && x<=140)
                if(y>=30 && y<=90)
                {
                    z=1;
                    main();
                }

        }
    }
}
