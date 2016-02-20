#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>
#include <set>
#include <cassert>
#include <list>
#include <deque>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <queue>
#include <fstream>
#include <ext/hash_map>
#include <ext/hash_set>
#include <time.h>
#include "bitboard.h"
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INF (10000)
#define BF (7)
#define WINDOW (10)
#define PLI pair<unsigned long long, unsigned int> 
       
using namespace std;
using namespace __gnu_cxx;


namespace __gnu_cxx {
     template<typename T1, typename T2>
     struct hash<pair<T1, T2> > {
         size_t operator()(const pair<T1, T2> &pr) const {
             return hash<T1>()(pr.first)*19+hash<T2>()(pr.second)*11+5;
         }
     };
     template<>
     struct hash<unsigned long long>
     {
	     size_t operator()(const unsigned long long &pr) const
	     {
		     return hash<unsigned int>()(pr>>32)*19+hash<unsigned int>()(pr&((1LL<<32)-1))*11+5;
	     }
     };

}

/*
class bitboard
{
	unsigned int WP;
	unsigned int BP;
	unsigned int K;
	unsigned int MU3;
	unsigned int MD3;
	unsigned int MU5;
	unsigned int MD5;
	unsigned int CENTRE;
	unsigned int MASK_ROW7;
	unsigned int MASK_ROW6;
	unsigned int MASK_ROW5;
	unsigned int MASK_ROW4;
	unsigned int MASK_ROW3;
	unsigned int MASK_ROW2;
	unsigned int MASK_ROW1;
	unsigned int MASK_ROW0;
	unsigned int MASK_COL1;
	unsigned int MASK_COL8;
	unsigned int MASK_DCORNER1;
	unsigned int MASK_DCORNER2;
	int highbit[1<<16];
	int bitcount[1<<16];
	unsigned long long jumps;
	unsigned int visited;
	public :
	void display(unsigned int);
	bitboard();
	int evaluateboardwhite();
	int evaluateboardblack();
	int countbits(unsigned int);
	int precountbits(unsigned int);
	unsigned int getwhite();
	unsigned int getblack();
	unsigned int getkings();
	void setkings(unsigned int);
	void setwhite(unsigned int);
	void setblack(unsigned int);
	void domovewhite(int,int);
	void domoveblack(int,int);
	void dojumpwhite(int,int);
	void dojumpblack(int,int);	
	unsigned int getmoverswhite();
	unsigned int getmoversblack();
	unsigned int getjumperswhite();
	unsigned int getjumpersblack();
	void getmoveswhite(int *, int &);
	void getmovesblack(int *, int &);
	void getjumpswhite(unsigned long long *, int &);
	void getjumpsblack(unsigned long long  *, int &);
	bool jumpswhite(short int, int, int, int &);
	bool jumpsblack(short int, int, int, int &);
	int highestbit(unsigned int);
	int lowestbit(unsigned int);
	void debug();
	unsigned int reversebits(unsigned int);
};*/
/*unsigned int bitboard :: reversebits(unsigned int bitpattern)
{
	bitpattern = ((bitpattern & 0xaaaaaaaa) >> 1) | ((bitpattern & 0x55555555) << 1);
	bitpattern = ((bitpattern & 0xcccccccc) >> 2) | ((bitpattern & 0x33333333) << 2);
	bitpattern = ((bitpattern & 0xf0f0f0f0) >> 4) | ((bitpattern & 0x0f0f0f0f) << 4);
	bitpattern = ((bitpattern & 0xff00ff00) >> 8) | ((bitpattern & 0x00ff00ff) << 8);
	bitpattern = ((bitpattern & 0xffff0000) >> 16) | ((bitpattern & 0x0000ffff) << 16);
	return bitpattern;
}*/
class PLAY
{
	bitboard BOARD;
	int color;
	int MOVE;
	int POS;
	long long betacutoffs;
	long long states;
	hash_map< PLI, int> H;
	hash_map< PLI, short int> betacutoff;
	bool WIN;
	int DEPTH;
	int MAXDEPTH;
	int TIME;
	int starttime;
	int endtime;
	double totaltime;
	int lastpos,lastmove,lastadvantage;
	public :
	PLAY();
	int playalphabeta(int , int, bool, short int, short int,int);
	void undomove(int, int, int);
	void playaswhite();
	void playcompwhite();
	void playplayerblack();
	void playasblack();
	void playcompblack();
	void playplayerwhite();
};
inline void PLAY :: playcompwhite()
{
	if(BOARD.getjumperswhite())
	{
		BOARD.dojumpwhite(POS,MOVE);
		BOARD.display(0);
	}
	else
	{
		BOARD.domovewhite(POS,MOVE);
		BOARD.display(0);
	}
}
inline void PLAY :: playcompblack()
{
	if(BOARD.getjumpersblack())
	{
		BOARD.dojumpblack(POS,MOVE);
		BOARD.display(0);
	}
	else
	{
		BOARD.domoveblack(POS,MOVE);
		BOARD.display(0);
	}
}

inline void PLAY :: playplayerblack()
{
	int i,j,b;
	int move[20];
	int pos[20];
	int counter=0;
	int initpos;
	int t[20],sz=0;
	unsigned long long tt[10];
	int ttsz=0;
	counter=0;
	int m;
	int p,pt;
	if(BOARD.getjumpersblack())
	{
		BOARD.getjumpsblack(tt,ttsz);
		for(i=0;i<ttsz;i++)
		{
			pt=tt[i]%100;
			tt[i]/=100;
			while(tt[i])
			{
				cout<<(++counter)<<"."<<pt<<" TO ";
				pos[counter]=pt;
				p=pt;
				m=tt[i]%10000;
				tt[i]/=10000;
				move[counter]=m;
				while(m)
				{
					if(m%10>5)
					{
						if(m==8 || m==6)
						{
							cout<<(p-4)<<" ";
							p-=4;
						}
						else
						{
							if((p/2)%2)
							{
								cout<<(p-5)<<" ";
								p-=5;
							}
							else
							{
								cout<<(p-3)<<" ";
								p-=3;
							}
						}
						cout<<((p-((m%10)-3)))<<" ";
						p-=((m%10)-3);
					}
					else
					{
						if(m==3 || m==5)
						{
							cout<<(p+4)<<" ";
							p+=4;
						}
						else
						{
							if((p/2)%2)
							{
								cout<<(p+3)<<" ";
								p+=3;
							}
							else
							{
								cout<<(p+5)<<" ";
								p+=5;
							}
						}
						cout<<(m%10+p)<<" ";
						p+=m%10;
					}
					m/=10;
				}
				cout<<endl;
			}
			cout<<endl;
		}
		cout<<"Enter your move :";
		cin>>b;
		BOARD.dojumpblack(pos[b],move[b]);
		BOARD.display(0);
	}
	else
	{
		BOARD.getmovesblack(t,sz);
		for(i=0;i<sz;i++)
		{
			initpos=t[i]%100;
			t[i]/=100;
			while(t[i])
			{
				cout<<(++counter)<<". "<<initpos<<" TO ";
				pos[counter]=initpos;
				move[counter]=t[i]%10;
				if(t[i]%10>5)
					cout<<(initpos-(t[i]%10-3))<<" ";
				else
					cout<<(initpos+(t[i]%10))<<" ";
				t[i]/=10;
				cout<<endl;
			}
		}
		cout<<endl;
		cout<<"Enter your move: ";
		cin>>b;
		BOARD.domoveblack(pos[b],move[b]);
		BOARD.display(0);
	}
}
inline void PLAY :: playplayerwhite()
{
	int i,j,b;
	int move[20];
	int pos[20];
	int counter=0;
	int initpos;
	int t[20],sz=0;
	unsigned long long tt[10];
	int ttsz=0;
	counter=0;
	int m;
	int p,pt;
	if(BOARD.getjumperswhite())
	{
		BOARD.getjumpswhite(tt,ttsz);
		for(i=0;i<ttsz;i++)
		{
			pt=tt[i]%100;
			tt[i]/=100;
			while(tt[i])
			{
				cout<<(++counter)<<"."<<pt<<" TO ";
				pos[counter]=pt;
				p=pt;
				m=tt[i]%10000;
				tt[i]/=10000;
				move[counter]=m;
				while(m)
				{
					if(m%10>5)
					{
						if(m==8 || m==6)
						{
							cout<<(p-4)<<" ";
							p-=4;
						}
						else
						{
							if((p/2)%2)
							{
								cout<<(p-5)<<" ";
								p-=5;
							}
							else
							{
								cout<<(p-3)<<" ";
								p-=3;
							}
						}
						cout<<((p-((m%10)-3)))<<" ";
						p-=((m%10)-3);
					}
					else
					{
						if(m==3 || m==5)
						{
							cout<<(p+4)<<" ";
							p+=4;
						}
						else
						{
							if((p/2)%2)
							{
								cout<<(p+3)<<" ";
								p+=3;
							}
							else
							{
								cout<<(p+5)<<" ";
								p+=5;
							}
						}
						cout<<(m%10+p)<<" ";
						p+=m%10;
					}
					m/=10;
				}
				cout<<endl;
			}
			cout<<endl;
		}
		cout<<"Enter your move :";
		cin>>b;
		BOARD.dojumpwhite(pos[b],move[b]);
		BOARD.display(0);
	}
	else
	{
		BOARD.getmoveswhite(t,sz);
		for(i=0;i<sz;i++)
		{
			initpos=t[i]%100;
			t[i]/=100;
			while(t[i])
			{
				cout<<(++counter)<<". "<<initpos<<" TO ";
				pos[counter]=initpos;
				move[counter]=t[i]%10;
				if(t[i]%10>5)
					cout<<(initpos-(t[i]%10-3))<<" ";
				else
					cout<<(initpos+(t[i]%10))<<" ";
				t[i]/=10;
				cout<<endl;
			}
		}
		cout<<endl;
		cout<<"Enter your move: ";
		cin>>b;
		BOARD.domovewhite(pos[b],move[b]);
		BOARD.display(0);
	}
}
inline void PLAY :: playaswhite()
{
	int advantage;
	int alpha,beta;
	int count;
	while(1)
	{
		states=0;
		DEPTH=12;
		totaltime=0;
		if(BOARD.getmoverswhite()==0 && BOARD.getjumperswhite()==0)
		{
			cout<<"You have WON!!!"<<endl;
			break;
		}
		cout<<"Calculating next move ";
		MAXDEPTH=0;
		advantage=playalphabeta(-INF,INF,1,DEPTH,0,0);
		DEPTH+=2;
		do
		{
			alpha=advantage-WINDOW;
			beta=advantage+WINDOW;
			starttime=clock();
			count=0;
			while(count<100)
			{
				H.clear();
				MAXDEPTH=0;
				advantage=playalphabeta(alpha,beta,1,DEPTH,0,0);
				if(advantage<alpha || advantage>beta)
				{
					alpha=advantage-WINDOW;
					beta=advantage+WINDOW;
				}
				else
					break;
				count++;

			}
			endtime=clock();
			DEPTH+=2;
			H.clear();
			if((endtime-starttime)*BF+(int)(totaltime+0.5)*CLOCKS_PER_SEC>TIME*CLOCKS_PER_SEC)
			{
				totaltime+=((double)(endtime-starttime)/CLOCKS_PER_SEC);
				break;
			}
			totaltime+=((double)(endtime-starttime)/CLOCKS_PER_SEC);
		}while(TIME-(totaltime)>1e-9 && DEPTH<=100);
		cout<<endl<<"Computer has an advantage of : "<<advantage<<endl;
		cout<<"Time : "<<totaltime<<"s"<<endl;
		cout<<"Depth : "<<(DEPTH-2)<<endl;
		cout<<"Maxdepth : "<<MAXDEPTH<<endl;
		if(advantage>=INF)
			WIN=1;
		playcompwhite();
		if(BOARD.getmoversblack()==0 && BOARD.getjumpersblack()==0)
		{
			cout<<"You have LOST!!!"<<endl;
			break;
		}
		cout<<"Your move options : "<<endl;
		playplayerblack();
	}
}
inline void PLAY :: playasblack()
{
	int advantage,alpha,beta,count;
	BOARD.display(0);
	while(1)
	{
		DEPTH=12;
		totaltime=0;
		if(BOARD.getmoverswhite()==0 && BOARD.getjumperswhite()==0)
		{
			cout<<"You have LOST!!!"<<endl;
			break;
		}
		cout<<"Your move options : "<<endl;
		playplayerwhite();
		if(BOARD.getmoversblack()==0 && BOARD.getjumpersblack()==0)
		{
			cout<<"You have WON!!!"<<endl;
			break;
		}
		cout<<"Calculating next move ";
		MAXDEPTH=0;
		advantage=playalphabeta(-INF,INF,0,DEPTH,0,0);
		DEPTH+=2;
		do
		{
			alpha=advantage-WINDOW;
			beta=advantage+WINDOW;
			starttime=clock();
			count=0;
			while(count<100)
			{
				H.clear();
				MAXDEPTH=0;
				advantage=playalphabeta(alpha,beta,0,DEPTH,0,0);
				if(advantage<alpha)
				{
					alpha=advantage-WINDOW;
					beta=advantage+WINDOW;
				}
				else
					break;
				count++;

			}
			endtime=clock();
			DEPTH+=2;
			H.clear();
			if((endtime-starttime)*BF+(int)(totaltime+0.5)*CLOCKS_PER_SEC>TIME*CLOCKS_PER_SEC)
			{
				totaltime+=((double)(endtime-starttime)/CLOCKS_PER_SEC);
				break;
			}
			totaltime+=((double)(endtime-starttime)/CLOCKS_PER_SEC);
		}while(TIME-(totaltime)>1e-9 && DEPTH<=100);
		cout<<endl<<"Computer has an advantage of : "<<advantage<<endl;
		cout<<"Time : "<<totaltime<<"s"<<endl;
		cout<<"Depth : "<<(DEPTH-2)<<endl;
		cout<<"Maxdepth : "<<MAXDEPTH<<endl;
		if(advantage>=INF)
			WIN=1;
		playcompblack();
	}
}
PLAY :: PLAY()
{
	BOARD.display(0);
	int choice;
	int ch[]={1,5,10,20,30};
	cout<<"Enter the color you wish to play with : "<<endl;
	cout<<"1. WHITE"<<endl;
	cout<<"2. BLACK"<<endl;
	cin>>color;
	color--;
	if(color)
		cout<<endl<<"You play as Black in this game"<<endl;
	else
		cout<<endl<<"You play as White in this game"<<endl;
	WIN=0;
	cout<<"Enter time per move for computer : "<<endl;
	cout<<"1. 1s\n2. 5s\n3. 10s\n4. 20s\n5. 30s"<<endl;
	cin>>choice;
	TIME=ch[choice-1];
	if(color)
		playaswhite();
	else
		playasblack();
}
inline void PLAY :: undomove(int W,int B,int K)
{
	BOARD.setwhite(W);
	BOARD.setblack(B);
	BOARD.setkings(K);
}
int PLAY :: playalphabeta(int alpha,int beta, bool color, short int depth, short int extra, int d)
{
	
	MAXDEPTH=MAX(MAXDEPTH,d);
	if(depth==((DEPTH/2)+2) && !WIN)
	{
		int temp=playalphabeta(alpha,beta,color,(DEPTH/4)+1,extra,d+1);
		if(temp<alpha-100 || temp>beta+100)
			return temp;
	}
	if(depth==0 && color && (BOARD.getjumperswhite()==0 || extra>4))
		return (BOARD.evaluateboardwhite()-BOARD.evaluateboardblack());
	else if(depth==0 && !color && (BOARD.getjumpersblack()==0 || extra>4))
		return (BOARD.evaluateboardblack()-BOARD.evaluateboardwhite());
	unsigned int W=BOARD.getwhite();
	unsigned int B=BOARD.getblack();
	unsigned int K=BOARD.getkings();
	unsigned int W1=W;
	unsigned int B1=B;
	int adjust=0;
	if(WIN)
		adjust=3*(18-depth);
	if(!color)
	{
		W1=BOARD.reversebits(W);
		B1=BOARD.reversebits(B);
	}
	unsigned long long WB=((long long)W1<<32)+B1;
	PLI hash(WB,K);
	if(depth+(DEPTH/4)<DEPTH && betacutoff.find(hash)!=betacutoff.end() && betacutoff[hash]>=beta)
		return betacutoff[hash]+adjust;
	if(H.find(hash)!=H.end())
	{
		if(depth<=(H[hash]>>16))
		return (((H[hash])&((1<<16)-1))-11000)+adjust;
	}
	int localalpha=alpha,bestvalue=-INF,i,j;
	int pos,move,value;
	unsigned long long tt[10];
	int ttsz=0;
	int t[20],sz=0;
	int moves=0;
	unsigned long long jumpslist;
	int moveslist;
	if(color)
	{
		if(BOARD.getjumperswhite())
		{
			BOARD.getjumpswhite(tt,ttsz);
			for(i=0;i<ttsz;i++)
			{
				jumpslist=tt[i];
				pos=jumpslist%100;
				jumpslist/=100;
				while(jumpslist)
				{
					move=jumpslist%10000;
					jumpslist/=10000;
					if(ttsz==1 && jumpslist==0 && depth==DEPTH)
					{
						MOVE=move;
						POS=pos;
						return 0;
					}
					BOARD.dojumpwhite(pos,move);
					if(depth==0 && ttsz==1 && jumpslist==0)
						value=-playalphabeta(-beta,-localalpha,!color,depth,extra,d+1);
					else if(depth==0)
						value=-playalphabeta(-beta,-localalpha,!color,depth,extra+1,d+1);
					else
						value=-playalphabeta(-beta,-localalpha,!color,depth-1,extra,d+1);
					undomove(W,B,K);
					if(!moves && depth==DEPTH)
					{
						MOVE=move;
						POS=pos;
					}
					bestvalue=MAX(value,bestvalue);
					if(bestvalue>=beta)
					{
						moves++;
						if(depth==DEPTH)
						{
							MOVE=move;
							POS=pos;
						}
						if(depth>=(DEPTH/2)+2)
							betacutoff[hash]=bestvalue;
						else if(depth>2 && H.size()<=9999999)
							H[hash]=((int)depth<<16)+bestvalue+11000;
						return bestvalue+adjust;
					}
					if(bestvalue>localalpha)
					{
						if(depth==DEPTH)
						{
							MOVE=move;
							POS=pos;
						}
						moves++;
						localalpha=bestvalue;
					}
				}
			}
		}
		else
		{
			BOARD.getmoveswhite(t,sz);
			for(i=0;i<sz;i++)
			{
				moveslist=t[i];
				pos=moveslist%100;
				moveslist/=100;
				while(moveslist)
				{
					move=moveslist%10;
					moveslist/=10;
					BOARD.domovewhite(pos,move);
					value=-playalphabeta(-beta,-localalpha,!color,depth-1,extra,d+1);
					undomove(W,B,K);
					if(depth==DEPTH)
						cout<<"."<<flush;
					if(!moves && depth==DEPTH)
					{
						MOVE=move;
						POS=pos;
					}
					bestvalue=MAX(value,bestvalue);
					if(bestvalue>=beta)
					{
						moves++;
						if(depth==DEPTH)
						{
							MOVE=move;
							POS=pos;
						}
						if(depth>=(DEPTH/2)+2)
							betacutoff[hash]=bestvalue;
						else if(depth>2 && H.size()<=9999999)
							H[hash]=((int)depth<<16)+bestvalue+11000;
						return bestvalue+adjust;
					}
					if(bestvalue>localalpha)
					{
						moves++;
						if(depth==DEPTH)
						{
							MOVE=move;
							POS=pos;
						}
						localalpha=bestvalue;
					}
				}
			}
		}
					
	}
	else
	{
		if(BOARD.getjumpersblack())
		{
			BOARD.getjumpsblack(tt,ttsz);
			for(i=0;i<ttsz;i++)
			{
				jumpslist=tt[i];
				pos=jumpslist%100;
				jumpslist/=100;
				while(jumpslist)
				{
					move=jumpslist%10000;
					jumpslist/=10000;
					if(ttsz==1 && jumpslist==0 && depth==DEPTH)
					{
						MOVE=move;
						POS=pos;
						return 0;
					}
					BOARD.dojumpblack(pos,move);
					if(depth==0 && ttsz==1 && jumpslist==0)
						value=-playalphabeta(-beta,-localalpha,!color,depth,extra,d+1);
					else if(depth==0)
						value=-playalphabeta(-beta,-localalpha,!color,depth,extra+1,d+1);
					else
						value=-playalphabeta(-beta,-localalpha,!color,depth-1,extra,d+1);
					undomove(W,B,K);
					if(!moves && depth==DEPTH)
					{
						MOVE=move;
						POS=pos;
					}
					bestvalue=MAX(bestvalue,value);
					if(bestvalue>=beta)
					{
						moves++;
						if(depth==DEPTH)
						{
							MOVE=move;
							POS=pos;
						}
						if(depth>=(DEPTH/2)+2)
							betacutoff[hash]=bestvalue;
						else if(depth>2 && H.size()<=9999999)
							H[hash]=((int)depth<<16)+bestvalue+11000;
						return bestvalue+adjust;
					}
					if(bestvalue>localalpha)
					{
						moves++;
						if(depth==DEPTH)
						{
							MOVE=move;
							POS=pos;
						}
						localalpha=bestvalue;
					}
				}
			}
		}
		else
		{
			BOARD.getmovesblack(t,sz);
			for(i=0;i<sz;i++)
			{
				moveslist=t[i];
				pos=moveslist%100;
				moveslist/=100;
				while(moveslist)
				{
					move=moveslist%10;
					moveslist/=10;
					BOARD.domoveblack(pos,move);
					value=-playalphabeta(-beta,-localalpha,!color,depth-1,extra,d+1);
					undomove(W,B,K);
					if(depth==DEPTH)
						cout<<"."<<flush;
					if(!moves && depth==DEPTH)
					{
						MOVE=move;
						POS=pos;
					}
					bestvalue=MAX(value,bestvalue);
					if(bestvalue>=beta)
					{
						moves++;
						if(depth==DEPTH)
						{
							MOVE=move;
							POS=pos;
						}
						if(depth>=(DEPTH/2)+2)
							betacutoff[hash]=bestvalue;
						else if(depth>2 && H.size()<=9999999)
							H[hash]=((int)depth<<16)+bestvalue+11000;
						return bestvalue+adjust;
					}
					if(bestvalue>localalpha)
					{
						moves++;
						if(depth==DEPTH)
						{
							MOVE=move;
							POS=pos;
						}
						localalpha=bestvalue;
					}
				}
			}
		}
	}
	if(bestvalue==-INF)
		return bestvalue+adjust;
	else
	{
		if(depth>2 && H.size()<=9999999)
		H[hash]=(depth<<16)+bestvalue+11000;
		return bestvalue+adjust;
	}
}
/*
inline int bitboard :: evaluateboardwhite()
{
	int value=0;
	unsigned int control=0;
	unsigned int temp=0;
	unsigned int empty=~(WP|BP);
	unsigned int mobility=((((WP&(~K))<<4)&empty) | (((WP&(~K))<<3)&(empty&MU3)) | (((WP&(~K))<<5)&(empty&MU5)));
	unsigned int lastrow=(((empty>>4)&(MASK_ROW6)) | (((empty&MU3)>>3)&(MASK_ROW6)) | (((empty&MU5)>>5)&(MASK_ROW6)));
	temp=((WP&(~K))<<4)&empty;
	control=((((empty&MU3)>>3)&temp) | (((empty&MU5)>>5)&temp));
	value+=countbits(control)*15;
	temp=(((WP&(~K))<<3)&(empty&MU3) | ((WP&(~K))<<5)&(empty&MU5));
	control=((empty>>4)&temp);
	value+=countbits(control)*15;
	value+=countbits((WP&MASK_ROW0))*15;
	value+=countbits((WP&(~K))&lastrow)*100;
	value+=countbits(WP)*200;
	value+=countbits(WP&K)*250;
	value+=countbits(WP&CENTRE)*20;
	value+=countbits((WP&(~K))&MASK_ROW6)*36;
	value+=countbits((WP&(~K))&MASK_ROW5)*25;
	value+=countbits((WP&(~K))&MASK_ROW4)*16;
	value+=countbits((WP&(~K))&MASK_ROW3)*9;
	value+=countbits((WP&(~K))&MASK_ROW2)*4;
	value+=countbits((WP&(~K))&MASK_ROW1);
	value+=countbits((WP&K)&MASK_ROW0)*(-20);
	value+=countbits((WP&K)&MASK_ROW7)*(-20);
	value+=countbits((WP&K)&MASK_COL1)*(-20);
	value+=countbits((WP&K)&MASK_COL8)*(-20);
	value+=countbits(mobility)*15;
	value+=countbits((WP&(~K))&(MASK_COL1|MASK_COL8))*(-10);
	return value;
}
inline int bitboard :: evaluateboardblack()
{
	int value=0;
	unsigned int control=0;
	unsigned int temp=0;
	unsigned int empty=~(WP|BP);
	unsigned int mobility=((((BP&(~K))>>4)&empty) | (((BP&(~K))>>3)&(empty&MD3)) | (((BP&(~K))>>5)&(empty&MD5)));
	unsigned int lastrow=(((empty<<4)&(MASK_ROW1)) | (((empty&MD3)<<3)&(MASK_ROW1)) | (((empty&MD5)<<5)&(MASK_ROW1)));
	temp=((BP&(~K))>>4)&empty;
	control=((((empty&MD3)<<3)&temp) | (((empty&MD5)<<5)&temp));
	value+=countbits(control)*15;
	temp=(((BP&(~K))>>3)&(empty&MD3) | ((BP&(~K))>>5)&(empty&MD5));
	control=((empty<<4)&temp);
	value+=countbits(control)*15;
	value+=countbits((BP&MASK_ROW7))*15;
	value+=countbits((BP&(~K))&lastrow)*100;
	value+=countbits(BP)*200;
	value+=countbits(BP&K)*250;
	value+=countbits(BP&CENTRE)*20;
	value+=countbits((BP&(~K))&MASK_ROW6);
	value+=countbits((BP&(~K))&MASK_ROW5)*4;
	value+=countbits((BP&(~K))&MASK_ROW4)*9;
	value+=countbits((BP&(~K))&MASK_ROW3)*16;
	value+=countbits((BP&(~K))&MASK_ROW2)*25;
	value+=countbits((BP&(~K))&MASK_ROW1)*36;
	value+=countbits((BP&K)&MASK_ROW0)*(-20);
	value+=countbits((BP&K)&MASK_ROW7)*(-20);
	value+=countbits((BP&K)&MASK_COL1)*(-20);
	value+=countbits((BP&K)&MASK_COL8)*(-20);
	value+=countbits(mobility)*15;
	value+=countbits((BP&(~K))&(MASK_COL1|MASK_COL8))*(-10);
	return value;
}
inline int bitboard :: precountbits(unsigned int bitpattern)
{
	int ret=0;
	int pos;
	while(bitpattern)
	{
		pos=highestbit(bitpattern);
		bitpattern&=(~(1<<pos));
		ret++;
	}
	return ret;
}
inline int bitboard :: countbits(unsigned int bitpattern)
{
	return bitcount[bitpattern&((1<<16)-1)]+bitcount[bitpattern>>16];
}
	
inline unsigned int bitboard :: getwhite()
{
	return WP;
}
inline unsigned int bitboard :: getblack()
{
	return BP;
}
inline void bitboard :: setwhite(unsigned int W)
{
	WP=W;
}
inline void bitboard :: setblack(unsigned int B)
{
	BP=B;
}
inline unsigned int bitboard :: getkings()
{
	return K;
}
inline void bitboard :: setkings(unsigned int k)
{
	K=k;
}
inline void bitboard :: dojumpwhite(int pos, int move)
{
	while(move)
	{
		int m=move%10;
		move/=10;
		if(m>5)
		{
			if(m==8 || m==6)
			{
				domovewhite(pos,7);
				pos-=4;
			}
			else
			{
				if(((BP&MD5)<<5)&(1<<pos))
				{
					domovewhite(pos,8);
					pos-=5;
				}
				else
				{
					domovewhite(pos,6);
					pos-=3;
				}
			}
			domovewhite(pos,m);
			pos-=(m-3);
		}
		else
		{
			if(m==3 || m==5)
			{
				domovewhite(pos,4);
				pos+=4;
			}
			else
			{
				if(((BP&MU5)>>5)&(1<<pos))
				{
					domovewhite(pos,5);
					pos+=5;
				}
				else
				{
					domovewhite(pos,3);
					pos+=3;
				}
			}
			domovewhite(pos,m);
			pos+=m;
		}
	}
}
inline void bitboard :: dojumpblack(int pos, int move)
{
	while(move)
	{
		int m=move%10;
		move/=10;
		if(m>5)
		{
			if(m==8 || m==6)
			{
				domoveblack(pos,7);
				pos-=4;
			}
			else
			{
				if(((WP&MD5)<<5)&(1<<pos))
				{
					domoveblack(pos,8);
					pos-=5;
				}
				else
				{
					domoveblack(pos,6);
					pos-=3;
				}
			}
			domoveblack(pos,m);
			pos-=(m-3);
		}
		else
		{
			if(m==3 || m==5)
			{
				domoveblack(pos,4);
				pos+=4;
			}
			else
			{
				if(((WP&MU5)>>5)&(1<<pos))
				{
					domoveblack(pos,5);
					pos+=5;
				}
				else
				{
					domoveblack(pos,3);
					pos+=3;
				}
			}
			domoveblack(pos,m);
			pos+=m;
		}
	}
}
inline void bitboard :: domovewhite(int pos, int move)
{	
	if(move>5)
	{
		move-=3;
		WP&=(~(1<<pos));
		K&=(~(1<<pos));
		WP|=(1<<(pos-move));
		K|=(1<<(pos-move));
		BP&=(~(1<<(pos-move)));
	}
	else
	{
		if((1<<pos)&K)
		{
			WP&=(~(1<<pos));
			K&=(~(1<<pos));
			WP|=(1<<(pos+move));
			K|=(1<<(pos+move));
			BP&=(~(1<<(pos+move)));
		}
		else
		{
			WP&=(~(1<<pos));
			WP|=(1<<(pos+move));
			BP&=(~(1<<(pos+move)));
			if(pos+move>=28)
				K|=(1<<(pos+move));
			else
			K&=(~(1<<(pos+move)));
		}
	}
}	
inline void bitboard :: domoveblack(int pos, int move)
{	
	if(move>5)
	{
		move-=3;
		if((1<<pos)&K)
		{
			BP&=(~(1<<pos));
			K&=(~(1<<pos));
			BP|=(1<<(pos-move));
			K|=(1<<(pos-move));
			WP&=(~(1<<(pos-move)));
		}
		else
		{
			BP&=(~(1<<pos));
			BP|=(1<<(pos-move));
			if(pos-move<=3)
				K|=(1<<(pos-move));
			else
			K&=(~(1<<(pos-move)));
			WP&=(~(1<<(pos-move)));
		}
	}
	else
	{
		BP&=(~(1<<pos));
		K&=(~(1<<pos));
		BP|=(1<<(pos+move));
		K|=(1<<(pos+move));
		WP&=(~(1<<(pos+move)));
	}
}
bool bitboard :: jumpswhite(short int pos,int seq,int pow,int &in)
{
	unsigned int test=1<<pos,tempmask,empty=~(WP|BP);
	unsigned int k=1<<in;
	bool end=1;
	if((visited)&(1<<pos))
		return 1;
	visited|=(1<<pos);
	tempmask=(empty>>4)&BP;
	if(tempmask)
	{
		if(((tempmask&MU3)>>3)&test)
			end&=jumpswhite(pos+7,pow*4+seq,pow*10,in);
		if(((tempmask&MU5)>>5)&test)
			end&=jumpswhite(pos+9,pow*4+seq,pow*10,in);
	}
	tempmask=((empty&MU3)>>3)&BP;
	if(tempmask)
	{
		if(((tempmask)>>4)&test)
			end&=jumpswhite(pos+7,pow*3+seq,pow*10,in);
	}
	tempmask=((empty&MU5)>>5)&BP;
	if(tempmask)
	{
		if(((tempmask)>>4)&test)
			end&=jumpswhite(pos+9,pow*5+seq,pow*10,in);
	}
	if(k&K)
	{
		tempmask=(empty<<4)&BP;
		if(tempmask)
		{
			if(((tempmask&MD3)<<3)&test)
				end&=jumpswhite(pos-7,pow*7+seq,pow*10,in);
			if(((tempmask&MD5)<<5)&test)
				end&=jumpswhite(pos-9,pow*7+seq,pow*10,in);
		}
		tempmask=((empty&MD3)<<3)&BP;
		if(tempmask)
		{
			if(((tempmask)<<4)&test)
				end&=jumpswhite(pos-7,pow*6+seq,pow*10,in);
		}
		tempmask=((empty&MD5)<<5)&BP;
		if(tempmask)
		{
			if(((tempmask)<<4)&test)
				end&=jumpswhite(pos-9,pow*8+seq,pow*10,in);
		}
	}
	if(end)
	{
		if(jumps<(1ULL<<63)/10000)
		{
			jumps*=10000;
			jumps+=seq;
		}
	}
	return 0;
}
bool bitboard :: jumpsblack(short int pos,int seq,int pow,int &in)
{
	unsigned int test=1<<pos,tempmask,empty=~(WP|BP);
	unsigned int k=1<<in;
	if((visited)&(1<<pos))
		return 1;
	visited|=(1<<pos);
	tempmask=(empty<<4)&WP;
	bool end=1;
	if(tempmask)
	{
		if(((tempmask&MD3)<<3)&test)
			end&=jumpsblack(pos-7,pow*7+seq,pow*10,in);
		if(((tempmask&MD5)<<5)&test)
			end&=jumpsblack(pos-9,pow*7+seq,pow*10,in);
	}
	tempmask=((empty&MD3)<<3)&WP;
	if(tempmask)
	{
		if(((tempmask)<<4)&test)
			end&=jumpsblack(pos-7,pow*6+seq,pow*10,in);
	}
	tempmask=((empty&MD5)<<5)&WP;
	if(tempmask)
	{
		if(((tempmask)<<4)&test)
			end&=jumpsblack(pos-9,pow*8+seq,pow*10,in);
	}
	if(k&K)
	{
		tempmask=(empty>>4)&WP;
		if(tempmask)
		{
			if(((tempmask&MU3)>>3)&test)
				end&=jumpsblack(pos+7,pow*4+seq,pow*10,in);
			if(((tempmask&MU5)>>5)&test)
				end&=jumpsblack(pos+9,pow*4+seq,pow*10,in);
		}
		tempmask=((empty&MU3)>>3)&WP;
		if(tempmask)
		{
			if(((tempmask)>>4)&test)
				end&=jumpsblack(pos+7,pow*3+seq,pow*10,in);
		}
		tempmask=((empty&MU5)>>5)&WP;
		if(tempmask)
		{
			if(((tempmask)>>4)&test)
				end&=jumpsblack(pos+9,pow*5+seq,pow*10,in);
		}
	}
	if(end)
	{
		if(jumps<(1ULL<<63)/10000)
		{
			jumps*=10000;
			jumps+=seq;
		}
	}
	return 0;
}

inline void bitboard :: getjumpswhite(unsigned long long *ret, int &size)
{
	unsigned int empty=~(WP|BP);
	unsigned int movers=getjumperswhite();
	int bit;
	bool temp;
	while(movers)
	{
		int temp=0;
		unsigned int tempmask=0;
		bit=highestbit(movers);
		unsigned int test=1<<bit;
		movers&=(~(test));
		visited=0;
		jumps=0;
		temp=jumpswhite(bit,0,1,bit);
		jumps=jumps*100+bit;
		ret[size++]=jumps;
	}
}
inline void bitboard :: getjumpsblack(unsigned long long *ret, int &size)
{
	unsigned int empty=~(WP|BP);
	unsigned int movers=getjumpersblack();
	int bit;
	bool temp;
	while(movers)
	{
		int temp=0;
		unsigned int tempmask=0;
		bit=lowestbit(movers);
		unsigned int test=1<<bit;
		movers&=(~(test));
		jumps=0;
		visited=0;
		temp=jumpsblack(bit,0,1,bit);
		jumps=jumps*100+bit;
		ret[size++]=jumps;
	}
}

inline void bitboard :: getmoveswhite(int *ret, int &size)
{
	unsigned int empty=~(WP|BP);
	unsigned int movers=getmoverswhite();
	int bit;
	while(movers)
	{
		int temp=0;
		bit=highestbit(movers);
		unsigned int test=1<<bit;
		movers&=(~(test));
		if((empty>>4)&test)
		temp=temp*10+4;
		if(((empty&MU3)>>3)&test)
				temp=temp*10+3;
		if(((empty&MU5)>>5)&test)
				temp=temp*10+5;
		if((test)&K)
		{
			if((empty<<4)&test)
				temp=temp*10+7;
			if(((empty&MD3)<<3)&test)
				temp=temp*10+6;
			if(((empty&MD5)<<5)&test)
				temp=temp*10+8;
		}
		temp=temp*100+bit;
		ret[size++]=temp;
	}
}
inline void bitboard :: getmovesblack(int *ret, int &size)
{
	unsigned int empty=~(WP|BP);
	unsigned int movers=getmoversblack();
	int bit;
	while(movers)
	{
		int temp=0;
		bit=lowestbit(movers);
		unsigned int test=1<<bit;
		movers&=(~(test));
		if((empty<<4)&test)
		temp=temp*10+7;
		if(((empty&MD3)<<3)&test)
				temp=temp*10+6;
		if(((empty&MD5)<<5)&test)
				temp=temp*10+8;
		if((test)&K)
		{
			if(((empty&MU3)>>3)&test)
				temp=temp*10+3;
			if(((empty&MU5)>>5)&test)
				temp=temp*10+5;
			if((empty>>4)&test)
			temp=temp*10+4;
		}
		temp=temp*100+bit;
		ret[size++]=temp;
	}
}
inline unsigned int bitboard :: getjumperswhite()
{
	unsigned int empty=~(WP|BP);
	unsigned int WK=WP&K;
	unsigned int movers=0;
	unsigned int temp=0;
	temp=(empty>>4)&BP;
	if(temp)
		movers|=((((temp&MU3)>>3)&WP) | (((temp&MU5)>>5)&WP));
	temp=(((empty&MU3)>>3)&BP) | (((empty&MU5)>>5)&BP);
	if(temp)
		movers|=((temp>>4)&WP);
	if(WK)
	{
		temp=(empty<<4)&BP;
		if(temp)
			movers|=((((temp&MD3)<<3)&WK) | (((temp&MD5)<<5)&WK));
		temp=(((empty&MD3)<<3)&BP) | (((empty&MD5)<<5)&BP);
		if(temp)
			movers|=((temp<<4)&WK);
	}
	return movers;
}
inline unsigned int bitboard :: getjumpersblack()
{
	unsigned int empty=~(WP|BP);
	unsigned int BK=BP&K;
	unsigned int movers=0;
	unsigned int temp=0;
	temp=(empty<<4)&WP;
	if(temp)
		movers|=((((temp&MD3)<<3)&BP) | (((temp&MD5)<<5)&BP));
	temp=(((empty&MD3)<<3)&WP) | (((empty&MD5)<<5)&WP);
	if(temp)
		movers|=((temp<<4)&BP);
	if(BK)
	{
		temp=(empty>>4)&WP;
		if(temp)
			movers|=((((temp&MU3)>>3)&BK) | (((temp&MU5)>>5)&BK));
		temp=(((empty&MU3)>>3)&WP) | (((empty&MU5)>>5)&WP);
		if(temp)
			movers|=((temp>>4)&BK);
	}
	return movers;
}
inline int bitboard :: lowestbit(unsigned int bitpattern)
{
	bitpattern=reversebits(bitpattern);
	return 31-highestbit(bitpattern);
}
inline int bitboard :: highestbit(unsigned int bitpattern)
{
	if((bitpattern>>16) & 65535)
		return highbit[(bitpattern>>16) & 65535]+16;
	if(bitpattern & 65535)
		return highbit[bitpattern & 65535];
	return 0;
}
inline unsigned int bitboard :: getmoverswhite()
{
	unsigned int empty=~(WP|BP);
	unsigned int WK=WP&K;
	unsigned int movers=0;
	movers|=((empty>>4)&WP);
	movers|=(((empty&MU3)>>3)&WP);
	movers|=(((empty&MU5)>>5)&WP);
	if(WK)
	{
		movers|=((empty<<4)&WK);
		movers|=(((empty&MD3)<<3)&WK);
		movers|=(((empty&MD5)<<5)&WK);
	}
	return movers;
}
inline unsigned int bitboard :: getmoversblack()
{
	unsigned int empty=~(WP|BP);
	unsigned int BK=BP&K;
	unsigned int movers=0;
	movers|=((empty<<4)&BP);
	movers|=(((empty&MD3)<<3)&BP);
	movers|=(((empty&MD5)<<5)&BP);
	if(BK)
	{
		movers|=((empty>>4)&BK);
		movers|=(((empty&MU3)>>3)&BK);
		movers|=(((empty&MU5)>>5)&BK);
	}
	return movers;
}
void bitboard :: debug()
{
	int b,m;
	int i,j;
	int t[20],sz;
	display(WP|BP);
	
	while(1)
	{
		sz=0;
		vector <unsigned long long> tt;
		if(getjumperswhite())
		{
			getjumpswhite(tt);
			for(i=0;i<tt.size();i++)
				cout<<tt[i]<<endl;
			cin>>b>>m;
			dojumpwhite(b,m);
			display(WP|BP);
		}
		else
		{
			getmoveswhite(t,sz);
			for(i=0;i<sz;i++)
				cout<<t[i]<<" ";
			cout<<endl;
			cin>>b>>m;
			domovewhite(b,m);
			display(WP|BP);
		}
		tt.clear();
		sz=0;
		if(getjumpersblack())
		{
			getjumpsblack(tt);
			for(i=0;i<tt.size();i++)
				cout<<tt[i]<<endl;
			cin>>b>>m;
			dojumpblack(b,m);
			display(WP|BP);
		}
		else
		{
			getmovesblack(t,sz);
			for(i=0;i<sz;i++)
				cout<<t[i]<<" ";
			cout<<endl;
			cin>>b>>m;
			domoveblack(b,m);
			display(WP|BP);
		}
	}
		
}
bitboard :: bitboard()
{
	WP=0xfff;
	BP=(0xfff)<<20;
	K=0;
	MU3=0x70707070;
	MD3=0x0e0e0e0e;
	MU5=0x0e0e0e00;
	MD5=0x00707070;
	CENTRE=0x42000;
	MASK_ROW7=(0xf)<<28;
	MASK_ROW6=(0xf)<<24;
	MASK_ROW5=(0xf)<<20;
	MASK_ROW4=(0xf)<<16;
	MASK_ROW3=(0xf)<<12;
	MASK_ROW2=(0xf)<<8;
	MASK_ROW1=(0xf)<<4;
	MASK_ROW0=0xf;
	MASK_COL1=(0x01010101);
	MASK_COL8=(0x80808080);
	MASK_DCORNER1=(0x88)<<24;
	MASK_DCORNER2=(0x88);
	int i,j;
	j=0;
	for(i=1;i<(1<<16);i++)
	{
		if(i==(1<<(j+1)))
			j++;
		highbit[i]=j;
	}
	for(i=0;i<(1<<16);i++)
		bitcount[i]=precountbits(i);
}
void bitboard :: display(unsigned int bitpattern)
{
	int i,j;
	int pos;
	int t;
	for(i=0;i<8;i++)
	{
		cout<<endl;
		for(j=0,t=0;j<8;j++)
		{
			if(((i*8+j)/8)%2==0 && j%2==0)
			{
				cout<<"#"<<" ";
				continue;
			}
			if(((i*8+j)/8)%2!=0 && j%2!=0)
			{
				cout<<"#"<<" ";
				continue;
			}
			pos=28-(4*i)+t;
			t++;
			if(((1<<pos)&(WP&(~K)))!=0)
				cout<<"w"<<" ";
			else if(((1<<pos)&WP)!=0)
				cout<<"W"<<" ";
			else if(((1<<pos)&(BP&(~K)))!=0)
				cout<<"b"<<" ";
			else if(((1<<pos)&BP)!=0)
				cout<<"B"<<" ";
			else
				cout<<"."<<" ";
		}
		cout<<"                  ";
		for(j=0,t=0;j<8;j++)
		{
			if(((i*8+j)/8)%2==0 && j%2==0)
			{
				cout<<"#"<<" ";
				continue;
			}
			if(((i*8+j)/8)%2!=0 && j%2!=0)
			{
				cout<<"#"<<" ";
				continue;
			}
			pos=28-(4*i)+t;
			t++;
			if(pos/10==0)
				cout<<"0";
			cout<<pos<<" ";
		}
		
	}
	cout<<endl;
}*/
int main()
{
	PLAY OBJ;
	return 0;
}

