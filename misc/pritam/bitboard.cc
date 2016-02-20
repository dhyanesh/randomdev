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
#include "bitboard.h"

using namespace std;

unsigned int bitboard :: reversebits(unsigned int bitpattern)
{
	bitpattern = ((bitpattern & 0xaaaaaaaa) >> 1) | ((bitpattern & 0x55555555) << 1);
	bitpattern = ((bitpattern & 0xcccccccc) >> 2) | ((bitpattern & 0x33333333) << 2);
	bitpattern = ((bitpattern & 0xf0f0f0f0) >> 4) | ((bitpattern & 0x0f0f0f0f) << 4);
	bitpattern = ((bitpattern & 0xff00ff00) >> 8) | ((bitpattern & 0x00ff00ff) << 8);
	bitpattern = ((bitpattern & 0xffff0000) >> 16) | ((bitpattern & 0x0000ffff) << 16);
	return bitpattern;
}
 int bitboard :: evaluateboardwhite()
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
 int bitboard :: evaluateboardblack()
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
 int bitboard :: precountbits(unsigned int bitpattern)
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
 int bitboard :: countbits(unsigned int bitpattern)
{
	return bitcount[bitpattern&((1<<16)-1)]+bitcount[bitpattern>>16];
}
	
 unsigned int bitboard :: getwhite()
{
	return WP;
}
 unsigned int bitboard :: getblack()
{
	return BP;
}
 void bitboard :: setwhite(unsigned int W)
{
	WP=W;
}
 void bitboard :: setblack(unsigned int B)
{
	BP=B;
}
 unsigned int bitboard :: getkings()
{
	return K;
}
 void bitboard :: setkings(unsigned int k)
{
	K=k;
}
 void bitboard :: dojumpwhite(int pos, int move)
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
 void bitboard :: dojumpblack(int pos, int move)
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
 void bitboard :: domovewhite(int pos, int move)
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
 void bitboard :: domoveblack(int pos, int move)
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

 void bitboard :: getjumpswhite(unsigned long long *ret, int &size)
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
 void bitboard :: getjumpsblack(unsigned long long *ret, int &size)
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

 void bitboard :: getmoveswhite(int *ret, int &size)
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
 void bitboard :: getmovesblack(int *ret, int &size)
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
 unsigned int bitboard :: getjumperswhite()
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
 unsigned int bitboard :: getjumpersblack()
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
 int bitboard :: lowestbit(unsigned int bitpattern)
{
	bitpattern=reversebits(bitpattern);
	return 31-highestbit(bitpattern);
}
 int bitboard :: highestbit(unsigned int bitpattern)
{
	if((bitpattern>>16) & 65535)
		return highbit[(bitpattern>>16) & 65535]+16;
	if(bitpattern & 65535)
		return highbit[bitpattern & 65535];
	return 0;
}
 unsigned int bitboard :: getmoverswhite()
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
 unsigned int bitboard :: getmoversblack()
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
	/*
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
	}*/
		
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
}
