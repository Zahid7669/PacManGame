#include<iostream>
#include<graphics.h>


using namespace std;


#define THICKNESS 20
#define BLOCKCOLOR BLACK
#define MOVE 15
#define SIZE 80


class Obstacle{
	protected:
		int x, y;
		int size;
		
	public:
		Obstacle (int _x=0,int _y=0, int _size=0)
		{
				setPosition(_x, _y);
				setSize(_size);
		}
		
		void setX (int _x){x=_x;}
		void setY (int _y){y=_y;}
		void setPosition(int _x, int _y){x = _x; y=_y;}
		void setSize(int _size){ size = _size;}
		
		int getX() const {return x;}
		int getY() const {return y;}
		int getSize() const {return size;}
		
		void getXY(int &_x, int &_y){
			_x = x;
			_y = y;	
		}
		
		virtual void draw() const{
			
		}

		virtual void undraw() const{
		}
		
		virtual int getCenterX() const{
		}
		
		virtual int getCenterY() const{
		}


		virtual int getRadiusX() const{
		}
		
		virtual int getRadiusY() const{
		}


};

class Horizontal : public Obstacle{
	public:
		Horizontal(int _x=0, int _y=0, int _size=SIZE ) : Obstacle (_x,_y,_size)
		{}
	
		void draw() const{
			setcolor (BLOCKCOLOR);
			setfillstyle (SOLID_FILL,BLOCKCOLOR);
			bar(x,y,x+size, y+THICKNESS);
		}
		
		virtual int getCenterX() const{
			return x + size/2.0;
		}
		
		virtual int getCenterY() const{
			return y + THICKNESS/2.0;
		}


		virtual int getRadiusX() const{
			return size/2.0;
		}
		
		virtual int getRadiusY() const{
			return THICKNESS/2.0;
		}

		
};


class Vertical : public Obstacle{
	public:
		Vertical(int _x=0, int _y=0, int _size=SIZE ) : Obstacle (_x,_y,_size)
		{}
	
		void draw() const {
			setcolor (BLOCKCOLOR);
			setfillstyle (SOLID_FILL,BLOCKCOLOR);
			bar(x,y,x+THICKNESS, y+size);
		}
		
		virtual int getCenterX() const{
			return x + THICKNESS/2.0;
		}
		
		virtual int getCenterY() const{
			return y + size/2.0;
		}

		virtual int getRadiusX() const{
			return THICKNESS/2.0;
		}
		
		virtual int getRadiusY() const{
			return size/2.0;
		}
		
};
class Point {
	protected:
		int x1, y1;          // top left corner
		int x2, y2; 
		
	
	public:
		Point(int _x1=0, int _y1=0, int _x2=0, int _y2=0){
			setTopLeft(_x1, _y1);
			setBottomRight(_x2, _y2);
		}
		
		void setTopLeft(int _x1, int _y1){
			x1 = _x1;
			y1 = _y1;
		}

		void setBottomRight(int _x2, int _y2){
			x2 = _x2;
			y2 = _y2;
		}
		
		int getTop() const {return y1;}
		int getLeft() const {return x1;}
		int getBottom() const {return y2;}
		int getRight() const {return x2;}

		void draw(){
			setcolor(BLUE);
			setfillstyle(SOLID_FILL,BLUE);
			bar(x1, y1, x2, y2); 
		}

		void undraw(){
			setcolor(WHITE);
			setfillstyle(SOLID_FILL,WHITE);
			bar(x1, y1, x2, y2); 
		}
		
		int getCenterX() const{
			return (x1+x2)/2.0;
		}
		
		int getCenterY() const{
			return (y1+y2)/2.0;
		}


		int getRadiusX() const{
			return abs(x2-x1) / 2.0;
		}
		
		int getRadiusY() const{
			return abs(y2-y1) / 2.0;
		}


};


class Person {
	protected:
		int x1, y1;          // top left corner
		int x2, y2; 
		Obstacle *obs[100];
		Point *point[100]; // bottom right corner
	public:
		Person(int _x1=0, int _y1=0, int _x2=0, int _y2=0){
			setTopLeft(_x1, _y1);
			setBottomRight(_x2, _y2);
		}
		
		void setTopLeft(int _x1, int _y1){
			x1 = _x1;
			y1 = _y1;
		}

		void setBottomRight(int _x2, int _y2){
			x2 = _x2;
			y2 = _y2;
		}
		
		int getTop() const {return y1;}
		int getLeft() const {return x1;}
		int getBottom() const {return y2;}
		int getRight() const {return x2;}

		void draw(){
			setcolor(RED);
			setfillstyle(SOLID_FILL,RED);
			bar(x1, y1, x2, y2); 
		}

		void undraw(){
			setcolor(WHITE);
			setfillstyle(SOLID_FILL,WHITE);
			bar(x1, y1, x2, y2); 
		}
		
		
		void move(int dx, int dy){
			undraw();
			setTopLeft(x1+dx, y1+dy);
			setBottomRight(x2+dx, y2+dy);
			draw();
		}
		

		void moveLeft(){
			move(-MOVE, 0);
		}

		void moveRight(){
			move(MOVE, 0);
		}
		void moveUp(){
			move(0,-MOVE);
		}
		
		void moveDown(){
			move(0,MOVE);
		}


		bool isCollidingWithObstacle(Obstacle *o)
		{
			int cx1 = (x1 + x2)/2.0;
			int cy1 = (y1 + y2)/2.0;
			int rx1 = abs(x2-x1) / 2.0;
			int ry1 = abs(y2-y1) / 2.0;
			
			int cx2 = o->getCenterX();
			int cy2 = o->getCenterY();
			int rx2 = o->getRadiusX();
			int ry2 = o->getRadiusY();
			

			int dx = abs( cx1 - cx2 );
			int dy = abs( cy1 - cy2 );
			
			
			return  ( dx<=(rx1 + rx2)) && (dy<=(ry1 + ry2));


			

		}
			bool isCollidingWithPoints(Point *o)
		{
			int cx1 = (x1 + x2)/2.0;
			int cy1 = (y1 + y2)/2.0;
			int rx1 = abs(x2-x1) / 2.0;
			int ry1 = abs(y2-y1) / 2.0;
			
			int cx2 = o->getCenterX();
			int cy2 = o->getCenterY();
			int rx2 = o->getRadiusX();
			int ry2 = o->getRadiusY();
			

			int dx = abs( cx1 - cx2 );
			int dy = abs( cy1 - cy2 );
			
			
			return  ( dx<=(rx1 + rx2)) && (dy<=(ry1 + ry2));


			

		}

};
	
/*
class Game{
	private:
		Obstacle *obstacles[100];
		int nObstacle;
		
	public:
		Game()
		{
			nObstacle = 0;
		}
		
		void addObstacle(Obstacle *o)
		{
			obstacles[nObstacle] = o;
			nObstacle++;
		}
		
		int getObstacleCount() const {return nObstacle;}
};
*/	
int main()
{
	int graphic_window_width = getmaxwidth();
    int graphic_window_height = getmaxheight();
    
	initwindow(graphic_window_width, graphic_window_height, "Pacman");
	setfillstyle(SOLID_FILL,WHITE); // make the background white instead of black
	bar(0,0,graphic_window_width, graphic_window_height);
	

	
	//Game game;
	
	//game.addObstacle( new Horizontal(320,50,SIZE) );
	//game.addObstacle( new Horizontal(320,50,SIZE) );

	
		Obstacle *obstacles[100];
	
		obstacles[0]=new Horizontal(330,50,660);//Top border
		obstacles[1]=new Horizontal(330,690,660);//bottom border
		obstacles[2]=new Vertical(970,50,650);//Right border
		obstacles[3]=new Vertical(330,50,650);//Left border
		obstacles[4]=new Horizontal(380,100,100);
		obstacles[5]=new Horizontal(380,100+THICKNESS,100);
		obstacles[6]=new Horizontal(380,180,100);
		obstacles[7]=new Vertical(460,240,100);
		obstacles[8]=new Horizontal(380,340,100);
		obstacles[9]=new Horizontal(380,400,100);
		obstacles[10]=new Vertical(460,400,120);
		obstacles[11]=new Horizontal(380,560,100);
		obstacles[12]=new Horizontal(380,620,100);
		obstacles[13]=new Horizontal(380,620+THICKNESS,100);
		obstacles[14]=new Horizontal(840,100,100);
		obstacles[15]=new Horizontal(840,100+THICKNESS,100);
		obstacles[16]=new Horizontal(840,180,100);
		obstacles[17]=new Vertical(840,240,100);
		obstacles[18]=new Horizontal(840,340,100);
		obstacles[19]=new Horizontal(840,400,100);
		obstacles[20]=new Vertical(840,400,120);
		obstacles[21]=new Horizontal(840,560,100);
		obstacles[22]=new Horizontal(840,620,100);
		obstacles[23]=new Horizontal(840,620+THICKNESS,100);
		obstacles[24]=new Vertical(660,130,160);
		obstacles[25]=new Horizontal(600,200,140);
		obstacles[26]=new Horizontal(600,530,140);
		obstacles[27]=new Vertical(660,460,160);
		obstacles[28]=new Horizontal(600,400,140);
		obstacles[29]=new Vertical(600,340,60);
		obstacles[30]=new Vertical(720,340,60);
		obstacles[31]=new Horizontal(600,340,50);
		obstacles[32]=new Horizontal(690,340,50);
		obstacles[33]=new Horizontal(520,130,100);
		obstacles[34]=new Horizontal(520,130+THICKNESS,100);
		obstacles[35]=new Horizontal(520,580,100);
		obstacles[36]=new Horizontal(520,580+THICKNESS,100);
		obstacles[37]=new Horizontal(710,580+THICKNESS,100);
		obstacles[38]=new Horizontal(710,580,100);
		obstacles[39]=new Horizontal(710,130,100);
		obstacles[40]=new Horizontal(710,130+THICKNESS,100);
		obstacles[41]=new Vertical(520,310,140);
		obstacles[42]=new Vertical(790,310,140);
		obstacles[43]=new Horizontal(520,470,100);
		obstacles[44]=new Horizontal(710,470,100);
		obstacles[45]=new Vertical(520,200,80);
		obstacles[46]=new Horizontal(520,260,100);
		obstacles[47]=new Vertical(790,200,80);
		obstacles[48]=new Horizontal(710,260,80);
		obstacles[49]=new Horizontal(330,270,70);
		obstacles[50]=new Horizontal(330,510,70);
		obstacles[51]=new Horizontal(920,510,70);
		obstacles[52]=new Horizontal(920,270,70);
		obstacles[53]=new Vertical(630,50,70);
		obstacles[54]=new Vertical(630,630,70);
		obstacles[55]=new Horizontal(490,390,50);
		obstacles[56]=new Horizontal(790,390,40);
		obstacles[57]=new Vertical(850,160,40);
		obstacles[58]=new Vertical(390,160,40);
	
		for (int j=0;j<59;j++)
		{
			obstacles[j]->draw();
		}	

	char ch = 0;
	Person okj (355,75,370,90);
	okj.draw();
	
	
	//okj.moveRight();
	
	Point *p[200];
	p[0]=new Point(360,100,365,105);
	p[1]=new Point(360,140,365,145);
	p[2]=new Point(360,180,365,185);
	p[3]=new Point(360,220,365,225);
	p[4]=new Point(360,260,365,265);
	p[5]=new Point(360,300,365,305);
	p[6]=new Point(940,80,945,85);
	p[7]=new Point(900,80,905,85);
	p[8]=new Point(360,340,365,345);
	p[9]=new Point(360,380,365,385);
	p[10]=new Point(360,420,365,425);
	p[11]=new Point(360,460,365,465);
	p[12]=new Point(360,500,365,505);
	p[13]=new Point(360,540,365,545);
	p[14]=new Point(360,580,365,585);
	p[15]=new Point(860,80,865,85);
	p[16]=new Point(360,620,365,625);
	p[17]=new Point(360,660,365,665);
	p[18]=new Point(490,100,495,105);
	p[19]=new Point(490,140,495,145);
	p[20]=new Point(490,180,495,185);
	p[21]=new Point(490,220,495,225);
	p[22]=new Point(490,260,495,265);
	p[23]=new Point(820,80,825,85);
	p[24]=new Point(490,300,495,305);
	p[25]=new Point(490,340,495,345);
	p[26]=new Point(490,380,495,385);
	p[27]=new Point(490,420,495,425);
	p[28]=new Point(490,460,495,465);
	p[29]=new Point(490,500,495,505);
	p[30]=new Point(490,540,495,545);
	p[31]=new Point(780,80,785,85);
	p[32]=new Point(490,580,495,585);
	p[33]=new Point(490,620,495,625);
	p[34]=new Point(490,650,495,655);
	p[35]=new Point(820,100,825,105);
	p[36]=new Point(820,140,825,145);
	p[37]=new Point(820,180,825,185);
	p[38]=new Point(820,220,825,225);
	p[39]=new Point(740,80,745,85);
	p[40]=new Point(820,260,825,265);
	p[41]=new Point(820,300,825,305);
	p[42]=new Point(820,340,825,345);
	p[43]=new Point(820,380,825,385);
	p[44]=new Point(820,420,825,425);
	p[45]=new Point(820,460,825,465);
	p[46]=new Point(820,500,825,505);
	p[47]=new Point(700,80,705,85);
	p[48]=new Point(820,540,825,545);
	p[49]=new Point(820,580,825,585);
	p[50]=new Point(820,620,825,625);
	p[51]=new Point(820,650,825,655);
	p[52]=new Point(950,100,955,105);
	p[53]=new Point(950,140,955,145);
	p[54]=new Point(950,180,955,185);
	p[55]=new Point(660,80,665,85);
	p[56]=new Point(950,220,955,225);
	p[57]=new Point(950,260,955,265);
	p[58]=new Point(950,300,955,305);
	p[59]=new Point(950,340,955,345);
	p[60]=new Point(950,380,955,385);
	p[61]=new Point(950,420,955,425);
	p[62]=new Point(950,460,955,465);
	p[63]=new Point(620,80,625,85);
	p[64]=new Point(950,500,955,505);
	p[65]=new Point(950,540,955,545);
	p[66]=new Point(950,580,955,585);
	p[67]=new Point(950,620,955,625);
	p[68]=new Point(950,650,955,655);
	p[69]=new Point(380,80,385,85);
	p[70]=new Point(420,80,425,85);
	p[71]=new Point(580,80,585,85);
	p[72]=new Point(380,670,385,675);
	p[73]=new Point(420,670,425,675);
	p[74]=new Point(460,670,465,675);
	p[75]=new Point(500,670,505,675);
	p[76]=new Point(540,670,545,675);
	p[77]=new Point(580,670,585,675);
	p[78]=new Point(940,670,945,675);
	p[79]=new Point(540,80,545,85);
	p[80]=new Point(620,670,625,675);
	p[81]=new Point(660,670,665,675);
	p[82]=new Point(700,670,705,675);
	p[83]=new Point(740,670,745,675);
	p[84]=new Point(780,670,785,675);
	p[85]=new Point(820,670,825,675);
	p[86]=new Point(860,670,865,675);
	p[87]=new Point(900,670,905,675);
	p[88]=new Point(445,230,450,235);
	p[89]=new Point(445,260,450,265);
	p[90]=new Point(445,290,450,295);
	p[91]=new Point(445,320,450,325);
	p[92]=new Point(380,320,385,325);
	p[93]=new Point(415,320,420,325);
	p[94]=new Point(380,165,385,170);
	p[95]=new Point(415,165,420,170);
	p[96]=new Point(380,425,385,430);
	p[97]=new Point(410,425,415,430);
	p[98]=new Point(445,425,450,430);
	p[99]=new Point(445,445,450,450);
	p[100]=new Point(445,470,450,475);
	p[101]=new Point(445,500,450,505);
	p[102]=new Point(380,585,385,590);
	p[103]=new Point(410,585,415,590);
	p[104]=new Point(840,170,845,175);
	p[105]=new Point(880,170,885,175);
	p[106]=new Point(920,170,925,175);
	p[107]=new Point(865,230,870,235);
	p[108]=new Point(865,260,870,265);
	p[109]=new Point(865,290,870,295);
	p[110]=new Point(865,330,870,335);
	p[111]=new Point(440,585,445,590);
	p[112]=new Point(895,330,900,335);
	p[113]=new Point(925,330,930,335);
	p[114]=new Point(865,425,870,430);
	p[115]=new Point(895,425,900,430);
	p[116]=new Point(925,425,930,430);
	p[117]=new Point(865,450,870,455);
	p[118]=new Point(865,475,870,480);
	p[119]=new Point(450,165,455,170);
	p[120]=new Point(865,500,870,505);
	p[121]=new Point(840,585,845,590);
	p[122]=new Point(870,585,875,590);
	p[123]=new Point(900,585,905,590);
	p[124]=new Point(685,130,690,135);
	p[125]=new Point(685,160,690,165);
	p[126]=new Point(685,190,690,195);
	p[127]=new Point(685,225,690,230);
	p[128]=new Point(650,255,655,260);
	p[129]=new Point(650,285,655,290);
	p[130]=new Point(650,460,655,465);
	p[131]=new Point(650,490,655,495);
	p[132]=new Point(650,520,655,525);
	p[133]=new Point(685,555,690,560);
	p[134]=new Point(685,585,690,590);
	p[135]=new Point(685,615,690,620);
	p[136]=new Point(715,190,720,195);
	p[137]=new Point(745,190,750,195);
	p[138]=new Point(620,225,625,230);
	p[139]=new Point(585,225,590,230);
	p[140]=new Point(620,520,625,525);
	p[141]=new Point(585,520,590,525);
	p[142]=new Point(715,555,720,560);
	p[143]=new Point(745,555,750,560);
	p[144]=new Point(545,310,550,315);
	p[145]=new Point(545,340,550,345);
	p[146]=new Point(545,370,550,375);
	p[147]=new Point(545,400,550,405);
	p[148]=new Point(545,430,550,435);
	p[149]=new Point(545,460,550,465);
	p[150]=new Point(575,460,580,465);
	p[151]=new Point(605,460,610,465);
	p[152]=new Point(780,310,785,315);
	p[153]=new Point(780,340,785,345);
	p[154]=new Point(780,370,785,375);
	p[155]=new Point(780,400,785,405);
	p[156]=new Point(780,430,785,435);
	p[157]=new Point(780,460,785,465);
	p[158]=new Point(745,460,750,465);
	p[159]=new Point(710,460,715,465);
	p[160]=new Point(520,175,525,180);
	p[161]=new Point(550,175,555,180);
	p[162]=new Point(580,175,585,180);
	p[163]=new Point(610,175,615,180);
	p[164]=new Point(710,120,715,125);
	p[165]=new Point(740,120,745,125);
	p[166]=new Point(770,120,775,125);
	p[167]=new Point(800,120,805,125);
	p[168]=new Point(520,570,525,575);
	p[169]=new Point(550,570,555,575);
	p[170]=new Point(580,570,585,575);
	p[171]=new Point(610,570,615,575);
	p[172]=new Point(710,625,715,630);
	p[173]=new Point(740,625,745,630);
	p[174]=new Point(770,625,775,630);
	p[175]=new Point(800,625,805,630);
	p[176]=new Point(625,365,630,370);
	p[177]=new Point(625,390,630,395);
	p[178]=new Point(655,390,660,395);
	p[179]=new Point(655,365,660,370);
	p[180]=new Point(685,390,690,395);
	p[181]=new Point(685,365,690,370);
	p[182]=new Point(710,365,715,370);
	p[183]=new Point(710,390,715,395);
	p[184]=new Point(545,200,550,205);
	p[185]=new Point(545,225,550,230);
	p[186]=new Point(545,250,550,255);
	p[187]=new Point(575,250,580,255);
	p[188]=new Point(605,250,610,255);
	p[189]=new Point(780,200,785,205);
	p[190]=new Point(780,225,785,230);
	p[191]=new Point(780,250,785,255);
	p[192]=new Point(750,250,755,255);
	p[193]=new Point(720,250,725,255);
	p[194]=new Point(500,80,505,85);
	
	
	for (int i=0;i<195;i++){
	p[i]->draw();}
	
	
	bool collide;
	bool collidePoint;
	int points=0;
	
	while ( ch !=27)
	{
		collide = false;
		
			
	//	delay(50);
		while ( (kbhit())&&(ch=getch())== 0){
			
			ch = getch();
			
			switch (ch){
					
				case 75: collide = false;
						collidePoint = false;
						for (int i=0;((!collide)&& i<59);i++)collide = okj.isCollidingWithObstacle(obstacles[i]);
						
							if (collide){
						
							cout<<"game over";
							exit(ALL_WINDOWS);
							}
						if (!collide) okj.moveLeft();
						 
						 
						for (int i=0;((!collidePoint)&& i<195);i++)
						{
						collidePoint =okj.isCollidingWithPoints(p[i]);
						
						
							if (collidePoint)
							{points++;}
					}
						 break;
						 
				case 80:  collide = false;
						collidePoint = false;
								for (int i=0;((!collidePoint)&& i<195);i++)
						
						collidePoint =okj.isCollidingWithPoints(p[i]);
						
						
						
							if (collidePoint)
							{points++;}
					
						for (int i=0;((!collide)&& i<59);i++){
						collide = okj.isCollidingWithObstacle(obstacles[i]);
						
						}
						if (collide){
						
						cout<<"game over"<<endl;
						cout<<points;
						exit(ALL_WINDOWS);
						}
						 if (!collide) okj.moveDown();
						 break;
						 
				case 72: collide = false;
						collidePoint = false;
								for (int i=0;((!collidePoint)&& i<195);i++)
						{
						collidePoint =okj.isCollidingWithPoints(p[i]);
						
						
						
							if (collidePoint)
							{points++;}
						}
					
						for (int i=0;((!collide)&& i<59);i++)collide = okj.isCollidingWithObstacle(obstacles[i]);
							if (collide){
						
						cout<<"game over"<<endl;
						cout<<points;
						exit(ALL_WINDOWS);
						}	
						
						 if (!collide) okj.moveUp();
						 break;
						 
				case 77: collide = false;
						collidePoint = false;
								for (int i=0;((!collidePoint)&& i<195);i++)
						{
						collidePoint =okj.isCollidingWithPoints(p[i]);
						
						
						
							if (collidePoint)
							{points++;}
					}
					
						for (int i=0;((!collide)&& i<59);i++)collide = okj.isCollidingWithObstacle(obstacles[i]);
							if (collide){
						
						cout<<"game over"<<endl;
						cout<<points;
						exit(ALL_WINDOWS);
						}	
							
						 if (!collide) okj.moveRight();
						 break;
						 
						 
				
				

			}
			delay(50);		
			
		}
		

	
	char ch=getch();
	switch (ch){
		 
				case 'a': collide = false;
						collidePoint = false;
						for (int i=0;((!collide)&& i<59);i++)collide = okj.isCollidingWithObstacle(obstacles[i]);
						
							if (collide){
						
							cout<<"game over";
							exit(ALL_WINDOWS);
							}
						if (!collide) okj.moveLeft();
						 
						 
						for (int i=0;((!collidePoint)&& i<195);i++)
						{
						collidePoint =okj.isCollidingWithPoints(p[i]);
						
						
							if (collidePoint)
							{points++;}
					}
						 break;
						 
				case 's':  collide = false;
						collidePoint = false;
								for (int i=0;((!collidePoint)&& i<195);i++)
						
						collidePoint =okj.isCollidingWithPoints(p[i]);
						
						
						
							if (collidePoint)
							{points++;}
					
						for (int i=0;((!collide)&& i<59);i++){
						collide = okj.isCollidingWithObstacle(obstacles[i]);
						
						}
						if (collide){
						
						cout<<"game over"<<endl;
						cout<<points;
						exit(ALL_WINDOWS);
						}
						 if (!collide) okj.moveDown();
						 break;
						 
				case 'w': collide = false;
						collidePoint = false;
								for (int i=0;((!collidePoint)&& i<195);i++)
						{
						collidePoint =okj.isCollidingWithPoints(p[i]);
						
						
						
							if (collidePoint)
							{points++;}
						}
					
						for (int i=0;((!collide)&& i<59);i++)collide = okj.isCollidingWithObstacle(obstacles[i]);
							if (collide){
						
						cout<<"game over"<<endl;
						cout<<points;
						exit(ALL_WINDOWS);
						}	
						
						 if (!collide) okj.moveUp();
						 break;
						 
				case 'd': collide = false;
						collidePoint = false;
								for (int i=0;((!collidePoint)&& i<195);i++)
						{
						collidePoint =okj.isCollidingWithPoints(p[i]);
						
						
						
							if (collidePoint)
							{points++;}
					}
					
						for (int i=0;((!collide)&& i<59);i++)collide = okj.isCollidingWithObstacle(obstacles[i]);
							if (collide){
						
						cout<<"game over"<<endl;
						cout<<points;
						exit(ALL_WINDOWS);
						}	
							
						 if (!collide) okj.moveRight();
						 break;
						 
						 
				
		

	}	
	}
	return 0;
}

	

	/*int n=2;
	Person enemies[2] = {{200,300,400,500}, {800,100,900,200} };
	int movements[2] = {10, -20};
	

	for (int i=0; i<n; i++)
			enemies[i].draw();
	while (!kbhit())
	{
			
	for (int i=0; i<n; i++)
			enemies[i].move(movements[i],0);
			delay(200);		
}*/
		
/*	Board b(100,100,getmaxwidth()/2,getmaxheight()-150);
	
	b.draw();
	
	Person p (100,200,300,400);
	p.draw();
	
	int n=2;
	Person enemies[2] = {{200,300,400,500}, {800,100,900,200} };
	int movements[2] = {10, -20};
	
	for (int i=0; i<n; i++)
			enemies[i].draw();
	
	Obstacle ob[100];
	


	char c = 0;
	while ( c !=27)
	{

		if (kbhit() && ( (c=getch())== 0) ){
			c = getch();
			switch (c){
				//bool collide=false;
				p.collideTestObstacle()
				case 75: for (int i=0; i<nObstacles; i++){  
								collide = p.collideTestObstacle(&obstacles[i]);
								if (collide) break;
				         }
				         
				         if (!collide) p.moveLeft();
				         
						 break;
				         
				case 77: p.moveRight(); break;
			}
		}
		
		for (int i=0; i<nObstacle; i++){
			if ( p.collideTestObstacle(&obstacles[i]) ){
				// dx = 0; dy=0; p.dontMove();
				break;
			}
		}

			
		//p.collideTestGiant(&enemy);
		
		for (int i=0; i<n; i++)
			enemies[i].move(movements[i],0);
			
		delay(100);
	}


//p.draw();
//	getch();
//	return 0;
*/


