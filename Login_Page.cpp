#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
FILE *fp;
using namespace std;
struct data{
	string name;
	string passwrd;
	int score;
}info;
int check_user(string );
int check_info(string ,string );
 int main(int argc, char const *argv[])
 {
 	initscr();
 	//raw();
// 	keypad(stdscr,TRUE);

start: 	//noecho();
 	cbreak();
 	refresh();
 	WINDOW *homepage,*password,*username;
 	string user,pass;
 	// HOME PAGE

 	int h_h,w_h,sx_h,sy_h,h_p,w_p,sx_p,sy_p,h_u,w_u,sx_u,sy_u;
 	h_h=38;
 	w_h=146;
 	sy_h=sx_h=1;
 	h_p=3;
 	w_p=20;
 	sy_p=25;
 	sx_p=63;
 	h_u=3;
 	w_u=20;
 	sy_u=21;
 	sx_u=63;
 	homepage = newwin(h_h,w_h,sy_h,sx_h);
 	password = newwin(h_p,w_p,sy_p,sx_p);
 	username = newwin(h_u,w_u,sy_u,sx_u);
 	box(homepage,0,0);
 	box(username,0,0);
 	box(password,0,0);
 	wrefresh(homepage);
 	wrefresh(password);
 	wrefresh(username);
 	mvprintw(22,50,"Username : ");
 	mvprintw(26,50,"Password : ");
 	echo();
	int i=0;
 	char k;
 	move(22,64);
  	refresh();
  	refresh();
  	wrefresh(homepage);
 	wrefresh(password);
 	wrefresh(username);
 	keypad(stdscr,TRUE);
 	keypad(homepage,TRUE);
 	int choice,highlight=0;
 	string choices[2]={"New_User","Already_a_user_??"};
 	int m=0;	
 	while(1)
 	{
 		for(int i=0;i<2;i++)
 		{
 			if(i==highlight)
 				wattron(homepage,A_REVERSE);
 			mvwprintw(homepage,1+i,1,choices[i].c_str());
 			wattroff(homepage,A_REVERSE);
 		}
 		wrefresh(homepage);
 		refresh();
 		m=0;
 		choice= wgetch(homepage);
 		wrefresh(homepage);
 		switch(choice)
 		{
 			case KEY_DOWN: highlight++;
 							if(highlight==2)
 								highlight=1;
 							break;
 			case KEY_UP : highlight--;
 							if(highlight==-1)
 								highlight=0;
 							break;
 			default : m=1;
 					  break;
 		}
 		if(m)
 			break;
 		//getch();

 	}
 	int flag_signup=0;
 	if(highlight==0)
 	{
 		mvprintw(22,50,"NEW Username : ");
 		mvprintw(26,50,"NEW Password : ");
 		wrefresh(homepage);
 		wrefresh(password);
 		wrefresh(username);
 		flag_signup=1;
 	}

 	//USERNAME INPUT

// LABEL A
    move(22,64);
    refresh();
    i=0;
 	while((k!='\n')&&(i!=10))
 	{
 		user[i++]=k;
 		refresh();
 		k=getch();
 	}

 	//	PASSWORD INPUT

 	noecho();
 	move(26,64);
 	refresh();
 	k=getch();
 	printw("*");
 	i=0;
 	while((k!='\n')&&(i!=10))
 	{
 		pass[i++]=k;
 		//echo();
 		//wrefresh(username);
 		refresh();
 		k=getch();
 		printw("*");
 	}
 	//scanw("%s",pass);
 	mvprintw(20,30,"input compl");
//1.
 	wrefresh(homepage);
 		wrefresh(password);
 		wrefresh(username);
 	
//  SIGNUP

 	if(flag_signup)
 	{
 		int check = check_user(user);
 		if(check)
 		{	
 			mvprintw(30,64," User already exist");
 			getch();
 			/*int werase(username);
 			int werase(password);*/
 			wrefresh(username);
 			wrefresh(password);
 			mvprintw(20,30,"flag flag_signup check =1");
 			//2.
 			wrefresh(homepage);
 		wrefresh(password);
 		wrefresh(username);
 			goto start;
 		}
 		else
 		{
 		mvprintw(20,30,"flag flag_signup check =0");
 		//6.
 		wrefresh(homepage);
 		wrefresh(password);
 		wrefresh(username);
 			//insert this into file ......
 			fp = fopen("data.txt","ab");
 			//strcpy(info.name,user);
 			info.name=user;
 			//strcpy(info.passwrd,pass);
 			info.passwrd=pass;
 			fwrite(&info,sizeof(info),1,fp);
 			fclose(fp);
 			//5.
 			wrefresh(homepage);
 		wrefresh(password);
 		wrefresh(username);
  		}
 	}
 	else
 	{
 		// login check
 		int check= check_info(user,pass);
 		if(check)
 		{
 			printw(" CORRECT");
 		}
 		else
 		{	
 			mvprintw(30,64," USER does not exist");
 			//4.
 			wrefresh(homepage);
 		wrefresh(password);
 		wrefresh(username);
 			goto start;
 		}
 	}
 	
 //	printw("%s  %s",user,pass);
 	getch();
 	endwin();
 	// END OF  HOME PAGE
 	return 0;
 }
 int check_info(string a,string b)
 {
 	fp = fopen("data.txt","rb");
 	mvprintw(20,30,"flag check info");
 	refresh();
 	while(fread(&info,sizeof(info),1,fp)!=EOF)
 	{
 		//if((strcmp(a,info.name)==0)&&(strcmp(b,info.passwrd)==0))
 		if((a==info.name)&&(b==info.passwrd))
 		{	
 			fclose(fp);
 			return 1;
 		}
 	}
 	fclose(fp);
 	return 0;

 }
 int check_user(string a)
 {
 	mvprintw(20,30,"flag check user");
 	refresh();
 	int flag=0;
 	fp = fopen("data.txt","rb");
 	while(fread(&info,sizeof(info),1,fp)!=EOF)
 	{
 		//if(strcmp(a,info.name)==0)
 		if(a==info.name)
 		{
 			flag=1;
 			break;
 		}
 	}
 	fclose(fp);
 	return flag;
 	//file handling

 }//mvprintw(20,30,"flag");