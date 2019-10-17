#include <iostream>
#include"ConnectFourDiagonal.h"
#include"Cell.h"
using namespace std;

namespace egemen
{

ConnectFourDiagonal::ConnectFourDiagonal(){
	playGame();
}

int ConnectFourDiagonal::checkFour(char Sign){	//diagonal fonksiyonunda alttan uste, sagdan sola olanlara bakmýyor.							
	
		int i,j;
		int fourC=0;
		
				for(i=row-1; i>=0; i--){									
					for(j=column-1; j>=0; j--){

					if(	gameBoard[i][j].user==Sign && 	//sadece capraz olanlara bakýyor, kontrol ediyor
						gameBoard[i-1][j-1].user==Sign && 
						gameBoard[i-2][j-2].user==Sign && 
						gameBoard[i-3][j-3].user==Sign)
						{fourC=1;}
		
					if(	gameBoard[i][j].user==Sign && 
						gameBoard[i-1][j+1].user==Sign && 
						gameBoard[i-2][j+2].user==Sign && 
						gameBoard[i-3][j+3].user==Sign)
						{fourC=1;}
		}	
	}
	
	return fourC;
}
void ConnectFourDiagonal::showBoard(){

		int s;
		cout<<endl;
		for(s=0; s<column; s++){
			char row_letter= 'A'+s;
			cout<< row_letter;
		}
		cout<<endl;
	
		for(int m=0; m<row; m++){
			for(int n=0; n<column; n++){
				if(gameBoard[m][n].isempty==true){
					gameBoard[m][n].user='*';
				}
				cout<<gameBoard[m][n].user;
			}	
		cout<<endl;
		}
}


void ConnectFourDiagonal::showWinner(){ 
	
	int ctrl=0;
	int m, n;
				for(m=0; m<row; m++){
					for(n=0; n<column; n++){//4 tane 'X' yan yana geldiyse hepsini kucuk 'x' yapan kýsým
							
					
					if(gameBoard[m][n].user=='X' && gameBoard[m-1][n-1].user=='X' && gameBoard[m-2][n-2].user=='X' && gameBoard[m-3][n-3].user=='X')
					 {gameBoard[m][n].user= 'x',   gameBoard[m-1][n-1].user= 'x',   gameBoard[m-2][n-2].user= 'x',   gameBoard[m-3][n-3].user= 'x';
					  	ctrl=1;}
					
					if(gameBoard[m][n].user=='X' && gameBoard[m+1][n-1].user=='X' && gameBoard[m+2][n-2].user=='X' && gameBoard[m+3][n-3].user=='X')
					  {gameBoard[m][n].user= 'x',   gameBoard[m+1][n-1].user= 'x',   gameBoard[m+2][n-2].user= 'x',   gameBoard[m+3][n-3].user= 'x';
					  	ctrl=1;}
	
					}
				}
	
		if(ctrl==0){
	
				for(m=0; m<row; m++){
					for(n=0; n<column; n++){	//4 tane 'O' yan yana geldiyse hepsini 'o' yapan kýsým
						
					
						if(gameBoard[m][n].user=='O' && gameBoard[m-1][n-1].user=='O' && gameBoard[m-2][n-2].user=='O' && gameBoard[m-3][n-3].user=='O')
						  {gameBoard[m][n].user= 'o',   gameBoard[m-1][n-1].user= 'o',   gameBoard[m-2][n-2].user= 'o',   gameBoard[m-3][n-3].user= 'o';}
					
						if(gameBoard[m][n].user=='O' && gameBoard[m+1][n-1].user=='O' && gameBoard[m+2][n-2].user=='O' && gameBoard[m+3][n+3].user=='O')
						  {gameBoard[m][n].user= 'o',   gameBoard[m+1][n-1].user= 'o',   gameBoard[m+2][n-2].user= 'o',   gameBoard[m+3][n+3].user= 'o';}
					
					}
				}
		}	
}


}
	

