#include <allegro.h>
#include <alfont.h>
#include <string.h>
#include <stdio.h>


using namespace std;
void init();
void deinit();

ALFONT_FONT *fnt;
                                                                                                                 	
PALETTE pal;

DATAFILE *left;
DATAFILE *right;
DATAFILE *levelbgs;
DATAFILE *levelpnts;
DATAFILE *levelbricks;
DATAFILE *welcome;
DATAFILE *others;
DATAFILE *invent;
DATAFILE *choco;
DATAFILE *nut;
DATAFILE *applause;

BITMAP *buffer;
BITMAP *temp;
BITMAP *sel;

int totscr=0,score=0,bgnum,bricknum,pntnum,rr,gg,bb;

char scr[10],stgscr[10],totalscr[10];	


            ////////////////////////////////       CLASS PLAYER         /////////////////////
class player
{
    private:
        int x;
        int y;
        int dist;

    public:
	    
	    int r,g,b;
		
        player(int xcord,int ycord,int ,BITMAP*,BITMAP*,BITMAP* );	                                                                         
		~player();                                                                          
		
        void move();
		int checkup();
		int chkright();
		int chkleft();
		int stepright();
		int stepleft();
		int checkground();
		void gravity();
		void initialisation();
		int getx();
		int gety();
		void setx(int );
		void sety(int );
		void load();
		void putonscr();
		void getrgb(int col);
		int getpoint(int i);
}; 
////////////////////////////////////////////////////////////////////        player::CONSTRUCTOR        ////////////////////////////////////////////////////////////////////
player::player(int xcord,int ycord,int d,BITMAP* bg,BITMAP* bricks,BITMAP* pnts)
{
                x=xcord;
                y=ycord;
                dist=d;
                 buffer=load_bitmap("buffer.bmp",pal);
                 draw_sprite(screen,bg,0,0);
                 draw_sprite(screen,bricks,0,0);
                 draw_sprite(screen,pnts,0,0);               
}
///////////////////////////////////////////////////////////////////         player::DESTRUCTOR         ////////////////////////////////////////////////////////////////////
player::~player()
{
                 
}

////////////////////////////////////////////////////////////////////         player::setx()           ////////////////////////////////////////////////////////////////////
int player::getx()
{
     return x;
}
////////////////////////////////////////////////////////////////////          player::sety()          ///////////////////////////////////////////////////////////////////
int player::gety()
{
     return y;
} 
////////////////////////////////////////////////////////////////////         player::setx()           ////////////////////////////////////////////////////////////////////
void player::setx(int xcord)
{
     x=xcord;
}
////////////////////////////////////////////////////////////////////          player::sety()          ///////////////////////////////////////////////////////////////////
void player::sety(int ycord)
{
     y=ycord;
} 
///////////////////////////////////////////////////////////////////         player::load()      //////////////////////////////////////////////////////////////////
void player::load()
{
     buffer=load_bitmap("buff.bmp",pal);
     draw_sprite(screen,(BITMAP*)levelbgs[bgnum].dat,0,0);
     draw_sprite(screen,(BITMAP*)levelbricks[bricknum].dat,0,0);
      draw_sprite(screen,(BITMAP*)levelpnts[pntnum].dat,0,0);    
     draw_sprite(screen,buffer,0,0); 
     draw_sprite(buffer,(BITMAP*)right[7].dat,x,y); 
     putonscr();                     
}                 
///////////////////////////////////////////////////////////////////         player::putonscr()         //////////////////////////////////////////////////////////////////
void player::putonscr()
{
     int col;
      draw_sprite(screen,buffer,0,0);
      blit((BITMAP*)levelbgs[bgnum].dat,buffer,x,y,x,y,40,40);
     
} 
//////////////////////////////////////////////////////////////////          player::getrgb();          /////////////////////////////////////////////////////////////////
void player::getrgb(int col)
{
     r=getr(col);
     g=getg(col);
     b=getb(col);
}          
//////////////////////////////////////////////////////////////////          player::checkground() ////////////////////////////////////////////////////////////////
int player::checkground()
{
     int colgr;
     colgr=getpixel((BITMAP*)levelbricks[bricknum].dat,x+20,y+40);                                                                //putpixel(buffer,x+21,y+65,makecol(255,240,0));
     getrgb(colgr);
     if(r==255&&g==0&&b==255)
       return 1;                    
     else
      return 0;     
}
/////////////////////////////////////////////////////////////////          player::gravity        /////////////////////////////////////////////////////////////////
void player::gravity()
{
      int fall;
      fall=checkground();
      for(;fall!=0;)
       {
             draw_sprite(buffer,(BITMAP*)right[7].dat,x,y+=2);
             putonscr();                                                                       
             fall=checkground();
       }       
}
///////////////////////////////////////////////////////////////////         player::checkup()        ////////////////////////////////////////////////////////////////////
int  player::checkup()
{
     int coluprt,coluplt,R,G,B;
     coluprt=getpixel((BITMAP*)levelbricks[bricknum].dat,x+10,y-1);
     getrgb(coluprt);
     R=r;
     G=g;
     B=b;
     coluplt=getpixel((BITMAP*)levelbricks[bricknum].dat,x+20,y-1);
     getrgb(coluplt);
     if(r!=255||g!=0||b!=255||R!=255||G!=0||B!=255)
      return 0;
     else                                                           
      return 1;
}       
/////////////////////////////////////////////////////////////////        player::stepright()        ////////////////////////////////////////////////////////////////////
int player::stepright()
{
    int colrt,colrtup,R,G,B;
    colrtup=getpixel((BITMAP*)levelbricks[bricknum].dat,x+41,y+20);                                                     
    getrgb(colrtup);
    colrt=getpixel((BITMAP*)levelbricks[bricknum].dat,x+41,y+40);                                                     
    getrgb(colrt);
    if(r!=255||g!=0||b!=255&&(R==255&&G==0&&B==255))
    { 
     getpoint(1);
     draw_sprite(buffer,(BITMAP*)right[7].dat,x+=40,y);
     putonscr();                                                                    
     gravity();                                  
     return 1;
    }
    else 
     return 0;
}

///////////////////////////////////////////////////////////////////         player::stepleft()          /////////////////////////////////////////////////////////////////    
int player::stepleft()
{
    int colft,colftup,R,G,B;
    colftup=getpixel((BITMAP*)levelbricks[bricknum].dat,x-1,y+20);                                                                                                                                                          
    getrgb(colftup);
    R=r;
    G=g;
    B=b;
     colft=getpixel((BITMAP*)levelbricks[bricknum].dat,x-1,y+40);                                                                                                                                                          
    getrgb(colft);
    if((r!=255||g!=0||b!=255)&&(R==255&&G==0&&B==255))
    
    {
     getpoint(2);
     draw_sprite(buffer,(BITMAP*)left[7].dat,x-=40,y);
     putonscr(); 
     gravity();                                                                          
     return 1;
    }
    else 
    return 0; 
} 
//////////////////////////////////////////////////////////////////         player::chkright()       ///////////////////////////////////////////////////////////////
int player::chkright()
{
    int colrt;
    if(dist==1)
     colrt=getpixel((BITMAP*)levelbricks[bricknum].dat,x+41,y+20);
    else if(dist==2)
     colrt=getpixel((BITMAP*)levelbricks[bricknum].dat,x+42,y);
    getrgb(colrt);
     if(r==255&&g==0&&b==255)
       return 1;                    
     else
      return 0;     
}          
//////////////////////////////////////////////////////////////////         player::chkright()       ///////////////////////////////////////////////////////////////
int player::chkleft()
{
    int colft;
    if(dist==1)
     colft=getpixel((BITMAP*)levelbricks[bricknum].dat,x-1,y+20);
    else if(dist==2)
     colft=getpixel((BITMAP*)levelbricks[bricknum].dat,x-2,y);
    getrgb(colft);
     if(r==255&&g==0&&b==255)
       return 1;                    
     else
      return 0;     
} 
////////////////////////////////////////////////////////////////////        player::getpoint()          ///////////////////////////////////////////
int player::getpoint(int i)         
{
    BITMAP *bp=create_bitmap(40,40),*tem=load_bitmap("pm.bmp",pal); 
      clear_to_color(bp,makecol(0,0,0)); 
     int col,a,b;
     char rr[10],gg[10],bb[10];
     switch(i)
     {
       case 1: col=getpixel(tem,x+60,y+20);a=x+40;b=y;break;
       case 2: col=getpixel(tem,x-20,y+20);a=x-40,b=y;break;
       case 3: col=getpixel(tem,x+20,y-20);a=x;b=y-40;break;
     }
     getrgb(col);
        rest(1);
     if((r!=255&&g!=0&&b!=255)&&(r!=0))
     {
       blit((BITMAP*)levelbgs[bgnum].dat,buffer,a,b,a,b,40,40);
       score+=10;
       save_bitmap("pm.bmp",(BITMAP*)levelpnts[pntnum].dat,pal);
      blit(bp,(BITMAP*)levelpnts[pntnum].dat,a,b,a,b,40,40);
      return 1;
     }
     else
      return 0;
}       
///////////////////////////////////////////////////////////////////         player::move()             //////////////////////////////////////////////////////////////////
void player::move()
{   
    if(key[KEY_ESC])
    {
     allegro_message("PLEASE COMPLETE THE ADVENTURE LATER");
     exit(0);
    }  
    alfont_set_font_size(fnt,30);
   	sprintf(scr,"%d",score); 
   	alfont_textout_ex(buffer,fnt,"SCORE: ",410,0,makecol(255,0,0),-1);
    alfont_textout_ex(buffer,fnt,scr,520,0,makecol(255,255,0),makecol(255,0,0)); 
    int i,j,checkp,k,steplft,steprt,chkdnlft,chkdnrt,p=0,q=0;   
     clear_keybuf();
     readkey();
     if(key[KEY_SPACE])
     {
          for(i=0;i<200;i++)
             {   
                 if(checkup()==0)
                  break;                                                 
                 draw_sprite(buffer,(BITMAP*)right[7].dat,x,y-=2);
                 putonscr();rest(10);
             
             }
              
          k=i;
          for(i=0;i<k;i++)
             {
                 draw_sprite(buffer,(BITMAP*)right[7].dat,x,y+=2);
                 putonscr(); rest(10);             	  
             }
     }                 
     if(key[KEY_LEFT])
     {             
         if(key[KEY_UP]&&checkup()!=0)
         {
             
             for(i=0;i<40;i++)
             {                                                    
                 if(checkup()==0)
                  break;
                 if(x<=0)
                  break;
                 draw_sprite(buffer,(BITMAP*)left[5].dat,x,y-=dist);                                   
                 putonscr();rest(1);
                 
             }
             if(i!=0)
              steplft=stepleft();
             k=i;
             if(steplft==0)
             {
                
                 for(i=0;i<k;i++)
                 {
                      if(x<=0||chkleft()==0)
                       {
                            
                              gravity();
                              break;
                       }  
                       draw_sprite(buffer,(BITMAP*)left[5].dat,x-=2,y);
                       putonscr();            	  
                 }
                 draw_sprite(buffer,(BITMAP*)left[7].dat,x,y);
                 putonscr();
                 gravity();
             } 
             getpoint(2);   
         }
         else if(key[KEY_LEFT])
         {
           
              for(i=0;i<8;i++,x-=5)
              {   
                  
                  if(x<=0||chkleft()==0)
                   {     
                     draw_sprite(buffer,(BITMAP*)left[7].dat,x,y);
                     putonscr();     
                     break;
                   }                    
                  draw_sprite(buffer,(BITMAP*)left[i].dat,x,y);
                  putonscr();
                  if(p==0)
                   p=getpoint(2);
                   
                  rest(50);
              }
             
             gravity();
             
         }
     }    
     else if(key[KEY_RIGHT])
     {
          if(key[KEY_UP]&&checkup()!=0)
          { 
              getpoint(3);                                                                                     
              for(i=0;i<40;i++)
              {
                 if(checkup()==0)
                  break;
                   if(x>=600)
                    break; 
                   draw_sprite(buffer,(BITMAP*)right[5].dat,x,y-=dist);                                
                   putonscr();rest(1);
                  
              }
              if(i!=0)          
              steprt=stepright();                                           
              k=i;     
              if(steprt==0)
              {
                 for(i=0;i<k;i++)
                 {
                      if(x>=600||chkright()==0)
                      {
                       gravity();
                       break; 
                      } 
                      draw_sprite(buffer,(BITMAP*)right[5].dat,x+=2,y);
                      putonscr();                                            
                  }
                  draw_sprite(buffer,(BITMAP*)right[7].dat,x,y);
                  putonscr();
                 gravity();
              } 
          }    
          else if(key[KEY_RIGHT])
          {
              for(i=0;i<8;i+=1,x+=5)
              {
                               
                 if(x>=600||chkright()==0)
                  {
                   draw_sprite(buffer,(BITMAP*)right[7].dat,x,y);
                   putonscr();                       
                   break;
                  } 
                 draw_sprite(buffer,(BITMAP*)right[i].dat,x,y);
                 putonscr();
                 if(q==0)
                  q=getpoint(1);
                 rest(50);                                                                 	
              }
              gravity(); 
                    
          }                           
     } 
}
////////////////////////////////////////           end of class player /////////////////////////////////////////////////////////////


////////////////////////////////////////      CLASS DETAILS     /////////////////////////////////////////////

class details
{
  public :
         int score;
         char name[30];
         int c,i,o,n;
         details();
         void enterdetails();
         void setdetails();
         void show();
}d;         

details::details()
{
 c=0;
 i=0;
 n=0;
 o=0;
}
 
void details::enterdetails()
{
  int ctr=0,pos=0;
  alfont_textout_ex(screen,fnt,"ENTER NAME: ",0,50,makecol(255,0,0),-1);
  alfont_set_font_size(fnt,50);
         while(!key[KEY_ENTER])
         {
               name[ctr]=readkey();
              if(key[KEY_BACKSPACE])
               {  
                   name[ctr-1]=' ';
                   name[ctr]='\0';
                   clear(screen);
                    alfont_textout_ex(screen,fnt,"ENTER NAME: ",0,50,makecol(255,0,0),-1);
                   alfont_textout_ex(screen,fnt,name,100,pos*30+130,makecol(0,0,0),-1);                      
                   ctr--;
               }
               else  
                 ctr++;
               name[ctr]='\0';
               alfont_textout_ex(screen,fnt,name,100,pos*30+130,makecol(255,255,0),-1); 
               rest(1);                    
         }  
         name[ctr-1]='\0';
}


void details::setdetails()
{
   score=totscr;
   
}

void details::show()
{
    alfont_set_font_size(fnt,60);
    alfont_textout_ex(screen,fnt,name,100,100,makecol(255,0,0),-1);
    sprintf(totalscr,"%d",totscr); 
     alfont_set_font_size(fnt,40);
    alfont_textout_ex(screen,fnt,"TOTAL SCORE :  ",100,300,makecol(0,255,0),-1);
    alfont_textout_ex(screen,fnt,totalscr,500,300,makecol(255,255,0),-1);
}
 
 
void storing()
{
     FILE *fout;
  fout=fopen("GREATEST_EXPLORERS.dat","a+");
  fputs(d.name,fout);
   fputs("\n",fout);
  fputs(" ",fout);
  fclose(fout);
}  


void greatest_explorers()
{
     clear(screen);
     BITMAP *grt=create_bitmap(640,3000);
     char line[80],ii[10];
     int i=0,j=80,y=0;
     FILE *fin;
     alfont_set_font_size(fnt,50);
     fin=fopen("GREATEST_EXPLORERS.dat","r");
      alfont_textout_ex(screen,fnt,"GREATEST   EXPLORERS",50,0,makecol(0,255,0),-1); 
       alfont_set_font_size(fnt,40);
     while(!feof(fin))
     {
     fgets(line,40,fin);
     alfont_textout_ex(grt,fnt,line,j,i+=50,makecol(0,255,0),-1); 
     rest(100);
     }
     
      if(i==0)
        {
          alfont_textout_ex(screen,fnt,"NO EXPLORERS !!",200,100,makecol(0,255,0),-1); 
           alfont_set_font_size(fnt,50);
          alfont_textout_ex(screen,fnt," BE THE FIRST !!",100,150,makecol(0,255,0),-1); 
           alfont_set_font_size(fnt,20);
          alfont_textout_ex(screen,fnt," to unravel the secrets of...  ",130,200,makecol(0,255,0),-1); 
           alfont_set_font_size(fnt,50);
           alfont_textout_ex(screen,fnt,"..THE CHOCOLATE FACTORY ",20,300,makecol(0,255,0),-1); 
           rest(2000);
        } 
       else
         {
         while(y<i&&(!key[KEY_ESC]))
          {
         blit(grt,screen,0,y++,200,100,640,480); 
          rest(50); 
         clear(screen);
         alfont_textout_ex(screen,fnt,"GREATEST   EXPLORERS",50,0,makecol(0,255,0),-1);    
         }
        alfont_textout_ex(screen,fnt,"BE THE NEXT ONE :)",150,100,makecol(255,0,0),-1);  
        rest(1000);
        }
             
        fclose(fin);
        alfont_set_font_size(fnt,50); 
      
    } 
        
void credits()
{
     clear(screen);
     BITMAP *crd=create_bitmap(640,3000);
     char line[80],ii[10];
     int i=0,j=80,y=0;
     FILE *fin;
     alfont_set_font_size(fnt,50);
     fin=fopen("credits.txt","r");
      alfont_textout_ex(screen,fnt,"THANK YOU",200,0,makecol(0,255,0),-1); 
      alfont_set_font_size(fnt,40);
     while(!feof(fin))
     {
     fgets(line,40,fin);
     line[strlen(line)-1]='\0';
     alfont_textout_ex(crd,fnt,line,j,i+=50,makecol(0,255,0),-1); 
     rest(100);
     }
     while(y<i&&(!key[KEY_ESC]))
     {
         blit(crd,screen,0,y++,200,100,640,480); 
          rest(50); 
         clear(screen);
         alfont_textout_ex(screen,fnt,"THANK YOU",200,0,makecol(0,255,0),-1);    
     }
}         


             ///////////////////////////////     tramp  ////////////////////////////////
void tramp()
{
int i,k,y=120,j=0;
     clear(screen);
     draw_sprite(screen,(BITMAP*)others[10].dat,120,240);
     save_bitmap("buff.bmp",buffer,pal);
   while(j<3){
     for(i=0;y<=240;i++)
             {                                                   
                 draw_sprite(screen,(BITMAP*)right[7].dat,300,y+=2);
                    rest(1);
                   blit(screen,screen,0,0,300,y,40,40);
             
             }
              
          k=i+(j*50);
          for(i=0;i<k;i++)
             {
                 draw_sprite(screen,(BITMAP*)right[7].dat,300,y-=2);
                 
                  rest(1);
                   blit(screen,screen,0,0,300,y,40,40);                	  
             }
             j++;     
      }    
}


/////////////////////////////////  drill       //////////////////////////

void drillin(int xstart,int ystart,int yend)
{
       save_bitmap("buff.bmp",buffer,pal);
     int x,y,col;
    for(y=ystart;y<=yend;y++)
       {
       for(x=xstart;x<=40;x++)
       {
        col=getpixel((BITMAP*)levelbgs[bgnum].dat,x,y);
        putpixel(screen,x,y,col);
        rest(10);
          
        } 
        draw_sprite(screen,(BITMAP*)others[2].dat,x,y-40);
        rest(1);
        blit((BITMAP*)levelbgs[bgnum].dat,screen,x,y-40,x,y-40,40,40);
        rest(10);
        }   
 }
     



void end_of_level()
{
     BITMAP *bmp;
     bmp=create_bitmap(640,480);
     alfont_set_font_size(fnt,50);
     int siz=10,x=90;
     alfont_set_font_size(fnt,10);
     clear(screen);
     draw_sprite(screen,(BITMAP*)others[3].dat,0,0);
     while(siz<50)
     {
      draw_sprite(bmp,(BITMAP*)others[3].dat,0,0);
     	alfont_set_font_size(fnt,siz+=1);
     alfont_textout_ex(bmp,fnt,"LEVEL COMPLETE",x-=1,240,makecol(255,0,0),-1);
     blit(bmp,screen,0,0,0,0,640,480);
      rest(50);
     clear(bmp);
     }
     rest(2000);
     totscr+=score;
     clear(screen);
}

void end_of_section()
{
     clear(screen);
  for(int i=0;i<70;i++)
  {
     draw_sprite(screen,(BITMAP*)applause[i].dat,0,0);
     alfont_set_font_size(fnt,50);
     alfont_textout_ex(screen,fnt,"STAGE COMPLETE",100,10,makecol(255,255,0),-1);     
     rest(30);
  }
    rest(100);
    clear(screen);
    alfont_textout_ex(screen,fnt,"TOTAL SCORE : ",100,300,makecol(255,0,0),-1);
    sprintf(totalscr,"%d",totscr); 
    alfont_textout_ex(screen,fnt,totalscr,500,300,makecol(255,255,0),-1);
    rest(2000);
}  
////////////////////////////////////////////      chocoland    ///////////////////////////////////
void chocoland()
{
      for(int i=0;i<52;i++)
     {
      draw_sprite(screen,(BITMAP*)choco[i].dat,0,0);
      rest(100);
     }
     rest(1000);
    alfont_set_font_size(fnt,50); 

    score=0;
    int x,y,col;
    bgnum=1;
    bricknum=3;
    pntnum=1; 
    player p1(320,60,1,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
	while (1) {
	p1.move();
	if(p1.gety()==60&&p1.getx()==200&&bricknum<4)
	{
       save_bitmap("buff.bmp",buffer,pal);
       rest(10);
       
	  bricknum+=1;                                                                    
	  p1.load();
    } 
	if(p1.gety()==240&&p1.getx()==560)
	{
     rest(100);
     tramp();
     clear(screen);
     p1.setx(520);
     p1.sety(60);
      p1.load();
    } 
  	else if(p1.gety()==440&&p1.getx()==560&&bricknum==4)
	 {
        end_of_level();
        break;
     } 
  } 

                                 ////////////// level 2 //////////////////////
   
    score=0;
   clear(screen);
    bgnum=2;
    bricknum=5;
    pntnum=2; 
    player p2(0,40,2,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
    readkey();
  	while (!key[KEY_ESC]) {
	p2.move();
     if(p2.gety()==40&&p2.getx()>560)
	  {
        end_of_level();
        break;
     } 
	}
	
	                            //////////////////// level 3 //////////////////
  
  
     score=0;
	int d=0;
    clear(screen);
    bgnum=3;
	bricknum=6;
	pntnum=3;
	player p3(600,40,1,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
	readkey();
    	while (1) {
	p3.move();
	if(p3.gety()==120&&p3.getx()==200)
	{
     rest(100);
     tramp();
     clear(screen);
     p3.setx(120);
     p3.sety(0);
      p3.load();
    } 
   	if(p3.gety()==0&&p3.getx()==0&&bricknum<7)
	 {
      clear(screen);
	  save_bitmap("buff.bmp",buffer,pal);
      draw_sprite(screen,(BITMAP*)others[11].dat,0,0);
      rest(1000);
	  bricknum+=1;                                                                     
	  p3.load();  
      d=1;                                       
	}
	if(p3.gety()==120&&p3.getx()==160&&bricknum==7&&d==1)
	 {
      drillin(40,200,240);
	  bricknum+=1;                                                                     
	  p3.load();
     }  
	if(p3.gety()==280&&p3.getx()==480&&bricknum<9)
	 {
      drillin(280,320,440);
	  bricknum+=1;                                                                 
	  p3.load();                                         
	}
	else if(p3.gety()==440&&p3.getx()==560)
	  {
        end_of_level();
        break;
     } 
   }
                                 ////////////////////// LEVEL 4 /////////////////////////
    
     score=0;
    clear(screen);
    bgnum=4;
	bricknum=10;
	pntnum=4;
	player p4(600,360,2,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
   	readkey();
       while (1) {
	p4.move();
	
	if(p4.gety()==400&&p4.getx()==80)
	 {
	 rest(100);
     tramp();
     clear(screen);
     p4.setx(40);
     p4.sety(120);
      p4.load();
      }
     else if(p4.gety()==200&&p4.getx()==0)
       {
        end_of_level();
        break;
     } 
	}
  end_of_section();
}









//////////////////////////////////////////////      invent        ////////////////////////////////////////////////////////////////
void inventroom()
{
     for(int i=0;i<27;i++)
     {
     draw_sprite(screen,(BITMAP*)invent[i].dat,0,0);
     rest(80);
     }
     rest(1000);
    alfont_set_font_size(fnt,50);   


                     ////////////////   level 1  //////////////
  
    score=0;
  clear(screen);
  bgnum=6;
  bricknum=12;
  pntnum=6;
  player p2(0,40,1,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
  readkey();                  
   while (1) {
	p2.move();
	
  	if(p2.gety()==120&&p2.getx()==320&&bricknum<13)      
	 {
      drillin(560,120,200);
	  bricknum+=1;                                                                  
	  p2.load();                                         
	}
	
	if(p2.gety()==280&&p2.getx()==320&&bricknum<14)
	 {
	   drillin(40,320,440);
	  bricknum+=1;                                                                     
	  p2.load();                                         
	}
	else if(p2.gety()==400&&p2.getx()==520)
      {
        end_of_level();
        break;
     } 
}	


                              ///////////////////   level 2 //////////////////
   
     score=0;
  clear(screen);
  bgnum=7;
  bricknum=15;
  pntnum=7;
  player p3(0,40,2,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
  readkey();                  
   while (1) {
	p3.move();
   	if(p3.gety()==280&&p3.getx()==480&&bricknum<16)
	 {
      
	  drillin(40,280,360);
	  bricknum+=1;                                                                    
	  p3.load();                                         
	}
	if(p3.gety()==280&&p3.getx()==280)
	{
     rest(100);
     tramp();
     clear(screen);
     p3.setx(280);
     p3.sety(40);
      p3.load();
    }
   	else if(p3.gety()==360&&p3.getx()==520) 
   	{
     end_of_level();
     break;
    } 
 }
 end_of_section();
     d.i=1;
}







 ///////////////////////////////////////////////////      nut room        //////////////////////////////////////////////////////////////

void nutroom()
{
   for(int i=0;i<111;i++)
     {
     draw_sprite(screen,(BITMAP*)nut[i].dat,0,0);
     rest(80);
     }
     rest(1000);
     
      alfont_set_font_size(fnt,50); 

   score=0;
  clear(buffer);
  clear(screen);
  
  
                      /////////////   level 2   ////////////////////
   
     score=0;
  clear(screen);
  bgnum=9;
  bricknum=18;
  pntnum=9;
  player p2(600,40,2,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
  readkey();                  
   while (1) {
	p2.move();

	if(p2.gety()==160&&p2.getx()==120&&bricknum<19)
	 {
     
	  drillin(40,120,160);
	  bricknum+=1;                                                                     
	  p2.load();                                         
	}
	
	if(p2.gety()==280&&p2.getx()>400&&bricknum<20)
	 {
      clear(screen);
	  save_bitmap("buff.bmp",buffer,pal);
	  bricknum+=1; 
        draw_sprite(screen,(BITMAP*)others[10].dat,0,0);
     rest(1000);                                                                   
	  p2.load();                                         
	}
	else if(p2.gety()==400&&p2.getx()>520)
	 {
        end_of_level();
        break;
     } 
   	}	
  
     end_of_section();
      d.n=1;
}
 
 
 
 
 
 
 
 
 
     

void oompaland()
{
  alfont_set_font_size(fnt,50); 
     
     score=0;
  clear(screen);
  bgnum=10;
  bricknum=21;
  pntnum=10;
  player p1(0,320,2,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
  readkey();                  
   while (1) {
	p1.move();
	
	if(p1.gety()==240&&p1.getx()==320&&bricknum<22)
	 {
     
	  drillin(600,280,440);
	  bricknum+=1;                                                                    
	  p1.load();                                         
	}
	else if(p1.gety()==400&&p1.getx()<120)
	{
     end_of_level();
	 break;
    }
   }

                 ////////////////////   level 2 /////////////////////////

   score=0;
  clear(screen);
  bgnum=11;
  bricknum=23;
  pntnum=11;
  player p2(0,80,2,(BITMAP*)levelbgs[bgnum].dat,(BITMAP*)levelbricks[bricknum].dat,(BITMAP*)levelpnts[pntnum].dat);
  readkey();                  
   while (1) {
	p2.move();
	
	if(p2.gety()==160&&p2.getx()==240&&bricknum<24)
	 {
      
	  drillin(560,200,440);
	  bricknum+=1;                                                                     
	  p2.load();                                         
	}
	
	else if(p2.gety()==320&&p2.getx()==40)
     {
         end_of_level();
          break;
      }    
   }
    end_of_section();
      d.o=1;
}   	  



void getcolrgb(int col)
{
     rr=getr(col);
     gg=getg(col);
     bb=getb(col);
}          
//////////////////////////////////////////////// gameon()         ///////////////////////////////////////////////////////////////////////////

	
void gameon()
{
     void intro();
 
 clear(screen);
 int col;
 show_mouse(screen);
 set_mouse_sprite((BITMAP*)others[7].dat);

 while(1){
 alfont_set_font_size(fnt,20);
  buffer=load_bitmap("lvelchoose.bmp",pal);
  draw_sprite(screen,sel,0,0);
  show_mouse(screen);
   poll_mouse();
  
  draw_sprite(buffer,(BITMAP*)others[5].dat,((mouse_x/210)*210),((mouse_y/210)*210));
  draw_sprite(screen,buffer,0,0);
  
   clear(buffer);rest(100);
 if(mouse_b==1)
  {
    clear(buffer);
    col=getpixel((BITMAP*)others[4].dat,mouse_x,mouse_y);
    getcolrgb(col);
    show_mouse(NULL);
    if(rr==0&&gg==0&&bb==0)
     {
       alfont_textout_ex(screen,fnt,"CHOCOLAND  ",300,440,makecol(0,255,0),makecol(250,255,0)); 
       rest(1000);
      if(d.c==0)
      chocoland();
      else
        {
          alfont_textout_ex(screen,fnt,"COMPLETED !! ",((mouse_x/210)*210)+35,((mouse_y/210)*210)+80,makecol(0,255,0),makecol(250,255,0));
          rest(1000);
         }
     }
     
     
     
     
    else   if(rr==255&&gg==0&&bb==0)
    {
            alfont_textout_ex(screen,fnt,"INVENTION ROOM",300,440,makecol(0,255,0),makecol(250,255,0)); 
             rest(1000);
     if(d.i==0)
      inventroom();
     else
         {
           alfont_textout_ex(screen,fnt,"COMPLETED !! ",((mouse_x/210)*210)+35,((mouse_y/210)*210)+80,makecol(0,255,0),makecol(250,255,0));
           rest(1000);
         }     
     
     }
     
     
     
     
    else   if(rr==0&&gg==255&&bb==0)
     {
       alfont_textout_ex(screen,fnt,"OOMPALAND",300,440,makecol(0,255,0),makecol(250,255,0)); 
       rest(1000);
     if(d.o==0)
      oompaland();
     else
        {
         alfont_textout_ex(screen,fnt,"COMPLETED !! ",((mouse_x/210)*210)+35,((mouse_y/210)*210)+80,makecol(0,255,0),makecol(250,255,0));
         rest(1000);
        }
     }
     
     
    else   if(rr==0&&gg==0&&bb==255)
    {
      alfont_textout_ex(screen,fnt,"NUT CRACKING ROOM",300,440,makecol(0,255,0),makecol(250,255,0)); 
      rest(1000);
     if(d.n==0)
      nutroom();
     else
         {
          alfont_textout_ex(screen,fnt,"COMPLETED !! ",((mouse_x/210)*210)+35,((mouse_y/210)*210)+80,makecol(0,255,0),makecol(250,255,0));
           rest(1000);
         }
     }
     
     
     else if(rr==255&&gg==255&&bb==0)
      intro();
     else if(rr==255&&gg==255&&bb==255)
      {
          if(d.i==1&&d.n==1&&d.o==1)
                 {
                  allegro_message("YOUR NAME HAS BEEN ADDED TO THE LIST OF GREATEST EXPLORERS");
                  storing();
                  }  
               else
                {
                   clear(screen);
                  d.show();
                  rest(2000);
                  allegro_message("PLEASE COMPLETE THE ADVENTURE LATER");
                } 
               exit(0);
               }
   clear(screen);
  
   rr=gg=bb=255;
   
    draw_sprite(screen,(BITMAP*)others[9].dat,0,0);
    readkey();
  }
 }
}  
//////////////////////////////////////////          intro          ///////////////////////
void intro()
{
 int col;
 show_mouse(screen);
 set_mouse_sprite((BITMAP*)others[7].dat);
 buffer=load_bitmap("menu.bmp",pal);
  draw_sprite(screen,buffer,0,0);
  while(1){ 
  while(!key[KEY_ESC]){
 
  buffer=load_bitmap("menu.bmp",pal);
  show_mouse(screen);
   poll_mouse();
 
  draw_sprite(buffer,(BITMAP*)others[6].dat,0,((mouse_y/80)*80));
  draw_sprite(screen,buffer,0,0);
   
   clear(buffer);rest(100);
  if(mouse_b==1)
  {
    clear(buffer);
    show_mouse(NULL);
   
    switch((mouse_y/80)+1)
    {
     case 1: gameon();break;
     case 2: {while(!key[KEY_ENTER]){draw_sprite(screen,(BITMAP*)others[0].dat,0,0);}
              rest(10);
              while(!key[KEY_ESC]){draw_sprite(screen,(BITMAP*)others[1].dat,0,0);}break;}
     case 3: greatest_explorers();break;
     case 4: {
              clear(screen);
              while(!key[KEY_ESC]){draw_sprite(screen,(BITMAP*)others[8].dat,0,0);}
              break;}
     case 5: credits(); break;
     case 6: {
               if(d.i==1&&d.n==1&&d.o==1)
                 {
                  allegro_message("YOUR NAME HAS BEEN ADDED TO THE LIST OF GREATEST EXPLORERS");
                  storing();
                  }  
               else
               {
                 clear(screen);
                 d.show();
                 rest(2000);
                 allegro_message("PLEASE COMPLETE THE ADVENTURE LATER");
               }  
               exit(0);break;}
    } 
   }
  }
}
} 

 

///////////////////////////////////////              MAIN               //////////////////////////////////////////


int main() {
	init();
     alfont_init();
 
     fnt=alfont_load_font("BROADW.TTF");
	 alfont_set_font_size(fnt,50);
     d.enterdetails();
      
    
     for(int i=0;i<115;i++)
     {
     draw_sprite(screen,(BITMAP*)welcome[i].dat,0,0);
     rest(30);
     }
     rest(1000);
 
     intro();
    
     d.setdetails();
     
     clear(screen);
     d.show();
     rest(2000);
  
	 deinit();
	 return 0;
}
END_OF_MAIN()

//////////////////////////////////////INIT() //////////////////////////

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
    
    levelbgs=load_datafile("levelbgs.dat");
    levelpnts=load_datafile("levelpnts.dat"); 
    levelbricks=load_datafile("levelbricks.dat");
    right=load_datafile("mvr.dat"); 
    left=load_datafile("mvl.dat");
    welcome=load_datafile("data.dat");
    others=load_datafile("others.dat");
    invent=load_datafile("invent.dat");
    choco=load_datafile("choco.dat");
    nut=load_datafile("nut.dat");
    applause=load_datafile("applause.dat");
   
  
  
    sel=load_bitmap("lvelchoose.bmp",pal);
  
}

///////////////////////////////////////DEINIT()////////////////////////////////


void deinit() {
	clear_keybuf();
	
	unload_datafile(levelbgs);
	unload_datafile(levelpnts);
	unload_datafile(levelbricks);
	unload_datafile(right);
	unload_datafile(left);
	unload_datafile(welcome);
	unload_datafile(others);
	unload_datafile(invent);
	unload_datafile(choco);
	unload_datafile(nut);
	unload_datafile(applause);
	}

    
    
    
    
    
    
    
    
              
