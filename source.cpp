/*


                       1024 GAME


    Created by Dhruv Gupta,Nikhil Rathor,Naman Khare (B12 batch)

*/
#include <stdio.h>
#include "cstdlib"
#include "iostream"
#include "cstring"
#include <ncurses.h>
#include <stack>
#include <vector>
using namespace std;
 
void up(int arr[])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (arr[3*j+i])
            {
                int start=i+3*j+3;
                while(true)
                {
                    if (arr[start])
                    {
                        if (arr[start]==arr[i+3*j])
                        {
                            arr[i+3*j]*=2;
                            arr[start]=0;
                        }
                        else break;
                    }
                    else start+=3;
                    
                    if (start > 9)
                    {
                        break;
                    }
                }
            }
            else
            {
                int start=i+3*j+3;
                while(start < 9)
                {
                    if (arr[start])
                    {
                        arr[i+3*j]=arr[start];
                        arr[start]=0;
                        break;
                    }
                    start+=3;
                }
            }
        }
    }
}
 
void down(int *arr)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 2; j > 0 ; --j)
        {
            int cur=3*j+i;
            int start=3*j+i-3;
 
            if (arr[cur])
            {
                while(start>=0)
                {
                    if (arr[start])
                    {
                        if (arr[start]==arr[cur])
                        {
                            arr[cur]*=2;
                            arr[start]=0;
                        }
                        break;
                    }
                    else start-=3;
                }
            }
            else
            {
                while(start>=0)
                {
                    if (arr[start])
                    {
                        arr[cur]=arr[start];
                        arr[start]=0;
                        break;
                    }
                    start-=3;
                }
            }
        }
    }
}
 
void left(int *arr)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            int cur=i*3+j;
            int start=3*i+j+1;
 
            if (arr[cur])
            {
                while(start<=3*i+2)
                {
                    if (arr[start])
                    {
                        if (arr[start]==arr[cur])
                        {
                            arr[cur]*=2;
                            arr[start]=0;
                        }
                        break;
                    }
                    start++;
                }
            }
            else
            {
                while(start<=3*i+2)
                {
                    if (arr[start])
                    {
                        arr[cur]=arr[start];
                        arr[start]=0;
                        break;
                    }
                    start++;
                }
            }
        }
    }
}
 
void right(int *arr)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 2; j >0 ; --j)
        {
            int cur=i*3+j;
            int start=cur-1;
 
            if (arr[cur])
            {
                while(start>=i*3)
                {
                    if (arr[start])
                    {
                        if (arr[start]==arr[cur])
                        {
                            arr[cur]*=2;
                            arr[start]=0;
                        }
 
                        break;
                    }
                    start--;
                }
            }
            else
            {
                while(start>=3*i)
                {
                    if (arr[start])
                    {
                        arr[cur]=arr[start];
                        arr[start]=0;
                        break;
                    }
                    start--;
                }
            }
        }
    }
}

bool check(int *arr)
{
    bool flag=false;


    for(int j=0;j<4;j++)
    {    
        int temp[9];
        for (int i = 0; i < 9; ++i)
        {
            temp[i]=arr[i];
        }


        if (j==0)
        {
            up(temp);
            for (int i = 0; i < 9; ++i)
            {
                if (temp[i]!=arr[i])
                {
                    return true;
                }
            }
        }
        if (j==1)
        {
            down(temp);
            for (int i = 0; i < 9; ++i)
            {
                if (temp[i]!=arr[i])
                {
                    return true;
                }
            }
        }
        if (j==2)
        {
            left(temp);
            for (int i = 0; i < 9; ++i)
            {
                if (temp[i]!=arr[i])
                {
                   return true;
                }
            }
        }
        if (j==3)
        {
            right(temp);
            for (int i = 0; i < 9; ++i)
            {
                if (temp[i]!=arr[i])
                {
                    return true;
                }
            }
        }
    }

    return false;
}



int main()
{
    //printf("                     2048                  ");
    initscr();
    noecho();
    long long int score=0;
    mvprintw(5,58," 1024 ");
    mvprintw(25,18," Press W for UPSHIFT ");
    mvprintw(28,18," Press S for DOWNSHIFT ");
    mvprintw(31,18," Press A for LEFTSHIFT ");
    mvprintw(34,18," Press D for RIGHTSHIFT ");
    mvprintw(37,18," Press Q for UNDO ");
    
    WINDOW *lboard=newwin(25,25,10,85);
    refresh();
    box(lboard,0,0);
    mvwprintw(lboard,1,1,"      LEADERBOARD");
    mvwprintw(lboard,2,1," RANK  USERNAME  SCORE");
    mvwprintw(lboard,3,1," ");
    mvwprintw(lboard,4,1," 1     @nikhil25  1890");
    mvwprintw(lboard,5,1," 2     @dhruv167  1650");
    mvwprintw(lboard,6,1," 3     @naman123  1000");
    wrefresh(lboard);
    getch();
    WINDOW *win[10];
    int height=4,width=8,x=50,y=10;
    for(int i=1;i<=9;i++)
    {
        win[i]=newwin(height,width,y,x);
        x+=7;
        if(i%3==0)
        {
            y+=3;
            x=50;
        }
    }
    refresh();
 
    for (int i = 1; i <=9; ++i)
    {
        box(win[i],0,0);
        wrefresh(win[i]);
    }
 
    int arr[9];
    memset(arr,0,sizeof(arr));
    int Randindex;
    Randindex=rand()%9;
    arr[Randindex]=2;
    mvwprintw(win[Randindex+1],1,3,"2");
    wrefresh(win[Randindex+1]);
    int size=8;
    stack<vector<int> > st;

    while(true)
    {
        char c=getch();

        if (size==0)
        {     
            if(!check(arr))
                break;
        }


        for (int i = 1; i <=9; ++i)
        {
            wclear(win[i]);
        }
        for (int i = 1; i <=9; ++i)
        {
            box(win[i],0,0);
            wrefresh(win[i]);
        }
       
        if (c=='W' || c=='w')
        {
            up(arr);
        }
        else if(c=='S' || c=='s')
        {
            down(arr);
        }
        else if(c=='A' || c=='a')
        {
            left(arr);
        }
        else if(c=='D' || c=='d')
        {
            right(arr);
        }
        else if(c=='Q' || c=='q')     //UNDO CONDITION
        {
            if (!st.empty())
            {
                vector<int> v;
                v=st.top();
                st.pop();
                for (int i = 0; i < 9; ++i)
                {
                    arr[i]=v[i];
                }
 
 
                for(int i=1;i<=9;i++)
                {
                    if(arr[i-1])
                    {    
                        mvwprintw(win[i],1,3,"%d",arr[i-1]);
                        score+=arr[i-1];
                    }
                    else
                        mvwprintw(win[i],1,3," ");
                    wrefresh(win[i]);
                }
            }
 
            continue;
        }
 
        int a[10];
        int k=0;
        for (int i = 0; i < 9; ++i)
        {
            if (!arr[i])
            {
                a[k++]=i;
            }
        }
 
        if (k!=0)
        {
            Randindex=rand()%k;
            arr[a[Randindex]]=2;
            size=k-1;
        }
       
        vector<int> v;
        for (int i = 0; i < 9; ++i)
        {
            v.push_back(arr[i]);  
        }
        st.push(v);
 
        for(int i=1;i<=9;i++)
        {
            if(arr[i-1])
            {
                mvwprintw(win[i],1,3,"%d",arr[i-1]);
                score+=arr[i-1];
            }
            else
            {   
                mvwprintw(win[i],1,3," ");
                score+=arr[i-1];
            }
            wrefresh(win[i]);
            refresh();
        }
        mvprintw(10,10,"SCORE : %d",score);
        refresh();
    }
    getch();
    mvprintw(30,58,"GAME OVER!!!!!");
    WINDOW *Over=newwin(15,40,25,50);
    box(Over,0,0);
    mvwprintw(Over,26,51,"Enter your name : ");
    wrefresh(Over);

    getch();
    endwin();
    return 0;
}