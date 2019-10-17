#include <iostream>
#include <fstream>
#include <string>
#include"ConnectFourAbstract.h"
//#include"ConnectFourAbstract.cpp"
#include"ConnectFourPlus.h"
//#include"ConnectFourPlus.cpp"
#include"ConnectFourDiagonal.h"
//#include"ConnectFourDiagonal.cpp"
#include"ConnectFourUndo.h"
//#include"ConnectFourUndo.cpp"
#include"Cell.h"
//#include"Cell.cpp"
using namespace std;
using namespace egemen;

main(){

	ConnectFourPlus C4_Plus;
	
	ConnectFourUndo C4_Undo;
		
	cout<<"Welcome to the Connect4 Game..!"<<endl<<endl;
	cout<<"Choose the Game Mod:"<<endl<<"Enter P = C4-Plus \nEnter D = C4-Diagonal \nEnter U = C4-Undo"<<endl;
	char modChoice;
	cin>>modChoice;
	
	do{
		if(modChoice!='P' && modChoice!='D' && modChoice!='U'){ //Hatalý input girildiginde hatayi söyleyecek.
			cerr<<"Wrong choice! please enter P, D or U"<<endl;
			cin>>modChoice;
		}
	}while(modChoice!='P' && modChoice!='D' && modChoice!='U');	//P, D veya U girene kadar devam edecek.
	
	if(modChoice=='P'){	//P secilirse Plus oynayacak
		C4_Plus.playGame();
	}
	
	else if(modChoice=='D'){ //D secilirse Diagonal oynayacak
		ConnectFourDiagonal C4_Diagonal;
	}
	
	else if(modChoice=='U'){
		C4_Undo.playGame();
	}


}


	

