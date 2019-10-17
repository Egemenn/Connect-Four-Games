//Egemen �A��IRLI 161044101
//Connect4 Game
#include <iostream>
#include <stdlib.h>
#define max 30	//maksimum 20 verince memory'deki baz� X veya O'lar� ortaya ��kard��� i�in maksimum 30 yapt�m. hata d�zeldi.
using namespace std;



void showBoard(char board[][max], int boyut ); //tahtay� g�steren fonksiyon
void makeMoveP1( char board[][max], int boyut);	//player 1 i�in hamle fonks�yonu
void makeMoveP2( char board[][max], int boyut);	//player 2 i�in hamle fonksiyonu
int checkFourP1( char board[][max], int boyut); //player 1'in yan yana, alt alta ve iki �apraz�n d�rtledi�ini kontrol eden fonksiyon
int checkFourP2( char board[][max], int boyut); //player 2'nin yan yana, alt alta ve iki �apraz�n d�rtledi�ini kontrol eden fonksiyon
int noWin(char board[][max], int boyut); //beraberli�i, t�m sat�r ve s�tunlar�n doldu�unu kontrol eden fonksiyon
void firstMoveAI(char board[][max], int boyut); //bilgisayar�n ilk hamlesini rastgele(random) yapt�ran fonksiyon
void makeMoveAI(char board[][max], int boyut); // bilgisayar�n random olmayan hamlelerini yapt�ran fonksiyon
int controlAI(char board[][max], int boyut); //bilgisayar�n oyununda yan yana 2,3,4 tane gelip gelmedi�ini kontrol eden fonksiyon
void showWinner(char board[][max], int boyut); //kazanan oyuncunun kazanan ta�lar�n� k���lten fonksiyon

int main(){
		
	int satir, sutun, boyut, AI;
	char board[max][max];
	
	cout<< "Welcome to Connect for game \n \n";
	cout<< "Enter size (between 4-20 and an even number)";
	cin>>boyut;
		if(boyut<4 || boyut>20 || boyut%2!=0){   //4'ten k���k, 20'den b�y�k ve tek say� girilmesi durumunda do while d�ng�s�n�n i�ine girecek. 
		do{
		cout<< "Please enter between 4 and 20, and an even number (one of 4,6,8,10,12,14,16,18,20)";
		cin>>boyut;	
			}while(boyut<4 || boyut>20 || boyut%2!=0); //kullan�c� do�ru input'u girmedik�e tekrar isteyecek.
		}
	
	int gameMod;
	int control1, control2, draw;
		
	cout<< "1=Player vs Player \n2=Player vs Computer";
	cin>>gameMod;
	
				
		if(gameMod==1){		//player 1 vs player 2 se�ilmesi durumunda buraya girecek.
	
			showBoard(board,boyut);
			
			do{
			makeMoveP1(board, boyut);
			showBoard(board, boyut);
			int control1=checkFourP1(board,boyut);    	
								
				if(control1==1) {						//player 1 d�rtl�y� sa�lad� m� diye kontrol edip return eden de�eri control1'e atad�m.
						showWinner(board, boyut);		//kazand��� takdirde 'X'leri k���lten fonksiyonu buraya ekledim.
						showBoard(board, boyut);		//ard�ndan 'X'lerin k���lm�� halini g�stermek ad�na showBoard fonksiyonunu ekledim.
						cout<<"Player 1 kazandi..!"; 
						break;}							//kazanan�n olmas� halinde do while'dan ��kmas�n�, oyunu bitirmesini sa�lad�m
		
		
			makeMoveP2(board, boyut);
			showBoard(board, boyut);
			int control2=checkFourP2(board,boyut);
				
				if(control2==1) {						//player 2 d�rtl�y� sa�lad� m� diye kontrol edip return eden de�eri control1'e atad�m.
						showWinner(board, boyut);		//kazand��� takdirde 'O'lar� k���lten fonksiyonu buraya ekledim.
						showBoard(board, boyut);		//ard�ndan 'O'lar�n k���lm�� halini g�stermek ad�na showBoard fonksiyonunu ekledim.
						cout<<"Player 2 kazandi..!"; 
						break;}							//kazanan�n olmas� halinde do while'dan ��kmas�n�, oyunu bitirmesini sa�lad�m
					
			
			int draw=noWin(board,boyut);
				if(draw==boyut){
					cout<<"It's draw. No one win :)";       		// noWin fonksiyonunu sadece player 2'den sonra yazd�m,
				}													// sat�r ve s�tunlar�n toplam�n�n say�s� �ift say� olmak zorunda.
				
			}while(control1!=1 || control2!=1 || draw!=boyut);		//bir oyuncu kazanmad�k�a ve brabere bitmedik�e fonksiyonun d�nmesini istedim.
		}
		
		
				
		if(gameMod==2){		// player vs computer se�ilmesi durumunda buraya girecek.	

			showBoard(board,boyut);
			
			do{
			makeMoveP1(board, boyut);
			showBoard(board, boyut);
			int control1=checkFourP1(board,boyut);    
							
				if(control1==1) { 						//player 1 d�rtl�y� sa�lad� m� diye kontrol edip return eden de�eri control1'e atad�m.
						showWinner(board, boyut);		//kazand��� takdirde 'X'leri k���lten fonksiyonu buraya ekledim.
						showBoard(board, boyut);		//ard�ndan 'X'lerin k���lm�� halini g�stermek ad�na showBoard fonksiyonunu ekledim.
						cout<<"CONGRATULATION..!";
						break;}


			int AI=controlAI(board, boyut);			//controlAI fonksiyonun d�nd�rd��� int de�erini AI'a atad�m. 
			if(AI==0)								//AI=0 olmas� durumunda random s�tun se�mesini istedim.
				{firstMoveAI(board, boyut);}	
			else									//AI=0 olmamas� durumunda makeMoveAI fonksiyonuna girmesini istedim.
				{makeMoveAI(board,boyut);}
				showBoard(board, boyut);
			int control2=checkFourP2(board,boyut);	//computer i�in de player 2'nin d�rtl�y� kontol eden fonksiyonunu kulland�m,
													//��nk� bilgisayar da player 2 gibi 'O' karakterini giriyor. 	
				if(control2==1) {					//bilgisayar hamlesi d�rtl�y� sa�lad� m� diye kontrol edip return de�eri control2'ye atad�m 
						showWinner(board, boyut);	//kazand��� takdirde 'O'lar� k���lten fonksiyonu buraya ekledim.
						showBoard(board,boyut);		//ard�ndan 'O'lar�n k���lm�� halini g�stermek ad�na showBoard fonksiyonunu ekledim.
						cout<<"GAME OVER! :/"; 
						break;}
					
			
			int draw=noWin(board,boyut);
				if(draw==boyut){
					cout<<"It's draw. No one win :)";       		// noWin fonksiyonunu sadece player 2'den sonra yazd�m,
				}													// sat�r ve s�tunlar�n toplam�n�n say�s� �ift say� olmak zorunda.
				
			}while(control1!=1 || control2!=1 || draw!=boyut);		//bir oyuncu kazanmad�k�a ve brabere bitmedik�e fonksiyonun d�nmesini istedim.	

		}
						

}	
	




void showBoard(char board[][max], int boyut){
	
	char harf[30]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};	//tablonun ilk sat�r�nda kullan�labilecek harfler.
	for(int a=0; a<boyut; a++) {
	cout << harf[a] <<" ";			//kullan�c�nn�n girdi�i boyuta g�re tablonun ilk sat�r�ndaki harfleri olu�turdum. Aralarda birer bo�luk b�rakt�m.
	}
	cout<<endl;			//alt sat�ra ge�ip tablonun noktal� k�s�mlar�n� olu�turmak i�in endl kulland�m. 
	
	for(int m=0; m<boyut; m++){
		for(int n=0; n<boyut; n++){
			
			if(board[m][n]!='X' && board[m][n]!='O' && board[m][n]!='x' && board[m][n]!='o'){ //sat�r ve s�tunlar�n de�eri X,O,x veya o olmad�k�a hep nokta ile olu�tur.
			board[m][n]='.'; 	
			}
			cout<< board[m][n] << " ";	//aralarda bir bo�luk b�rakt�k ki daha geni� ve d�zenli g�r�ns�n.
		}
			cout<< endl;	}		
}



void makeMoveP1(char board[][max], int boyut){
	
			int ctrl=0;
			int ch;
			char choice;
			cout<< "\nPlayer 1, choose a column\n";
			cin>> choice;
			ch= choice-'A';
			if(board[0][ch]!='.')
				cout<< "Bu sutun dolu, sira Player2'de..." << endl <<endl;		//e�er player 1 dolu olan s�tuna giri� yaparsa s�ra player 2'ye ge�er.
			else{	
				do{
				if(board[boyut][ch]=='.')	//girilen sat�r ve tablodaki en alt s�tuna 'X' yazd�ran k�s�m. 
				{	
					board[boyut][ch]= 'X'; 				  
					ctrl=1;
				}
				else --boyut;		//en alt doluysa boyutu d�ng�ye sokup birer azaltarak �sttekilere bakmas�n� sa�l�yoruz.

				}while(ctrl==0);
			}
	
}



void makeMoveP2( char board[][max], int boyut ){
	
			int ctrl=0;
			int ch;
			char choice;
			cout<< "\nPlayer 2, choose a column\n";
			cin>> choice;
			ch= choice-'A';			//kullan�c�dan girilen char de�erini (A,B,C,D,...) integer de�erine �eviren fonksiyon.
			if(board[0][ch]!='.')
				cout<< "\nBu sutun dolu, sira Player1'de..." << endl <<endl;	//e�er player 2 dolu olan s�tuna giri� yaparsa s�ra player 1'e ge�er.
			else{
				
				do{
				if(board[boyut][ch]=='.')	//girilen sat�r ve tablodaki en alt s�tuna 'O' yazd�ran k�s�m.
				{	
					board[boyut][ch]= 'O'; 				
					ctrl=1;
				}
				else --boyut;		//en alt doluysa boyutu d�ng�ye sokup birer azaltarak �sttekilere bakmas�n� sa�l�yoruz.
			
				}while(ctrl==0);
			}
}



int checkFourP1(char board[][max], int boyut){								
	
		int i,j;
		int fourP1=0;
		
				for(i=boyut-1; i>=0; i--){									
					for(j=boyut-1; j>=0; j--){
						
					if(board[i][j]=='X' && board[i][j-1]=='X' && board[i][j-2]=='X' && board[i][j-3]=='X')	//4 tane X'in yan yana, alt alta ve iki �apraz �ekilde,
						{fourP1=1;}																			//gelmesini kontrol eden ve bu �artlar olu�tu�u takdirde,
																											//0 olan fourP1 de�erine 1 atayan fonksiyon.
					if(board[i][j]=='X' && board[i-1][j]=='X' && board[i-2][j]=='X' && board[i-3][j]=='X')	//sonras�nda da fourP1 de�erini return ediyor.
						{fourP1=1;}
	
					if(board[i][j]=='X' && board[i-1][j-1]=='X' && board[i-2][j-2]=='X' && board[i-3][j-3]=='X')
						{fourP1=1;}
		
					if(board[i][j]=='X' && board[i-1][j+1]=='X' && board[i-2][j+2]=='X' && board[i-3][j+3]=='X')
						{fourP1=1;}
		}	
	
	}
	return fourP1;
}



int checkFourP2(char board[][max], int boyut){									
	
		int i,j;
		int fourP2=0;

				for(i=boyut; i>0; i--){										
					for(j=boyut; j>0; j--){
						
					if(board[i][j]=='O' && board[i][j-1]=='O' && board[i][j-2]=='O' && board[i][j-3]=='O')	//4 tane X'in yan yana, alt alta ve iki �apraz �ekilde
						{fourP2=1;}																			//gelmesini kontrol eden ve bu �artlar olu�tu�u takdirde,
																											//0 olan fourP1 de�erine 1 atayan fonksiyon.							
					if(board[i][j]=='O' && board[i-1][j]=='O' && board[i-2][j]=='O' && board[i-3][j]=='O')	//sonras�nda da fourP1 de�erini return ediyor.
						{fourP2=1;}
	
					if(board[i][j]=='O' && board[i-1][j-1]=='O' && board[i-2][j-2]=='O' && board[i-3][j-3]=='O')
						{fourP2=1;}
		
					if(board[i][j]=='O' && board[i-1][j+1]=='O' && board[i-2][j+2]=='O' && board[i-3][j+3]=='O')
						{fourP2=1;}
		}	
	
	}
	return fourP2;
}



int noWin(char board[][max], int boyut){

	int f;
	int W=0;
	
	for(f=0; f<boyut; f++)
		{
			if(board[0][f]!='.' )		//en �st sat�r�n t�m s�tunlar�na tek tek bak�p hi�biri '.' de�ilse berabere bitti�ini s�yleyen fonksiyon.
			++W;
			}

	return W;

}



void makeMoveAI(char board[][max], int boyut){									
	
			int ctrl=0;
			int i=boyut, j=boyut; 
						
			do{
			for(i; i<0; i--){
			 	for(j; j<0; j--){
			 		
			 		if(board[i][j]=='X' && board[i][j-1]=='X' && board[i][j-2]=='X' )	//yan yana 3 'X' varsa yan�na 'O' koyan k�s�m.
			 			board[i][j-3]='O', ctrl=1;
			 	
				 	else if(board[i][j]=='X' && board[i-1][j]=='X' && board[i-2][j]=='X')
			 			board[i-3][j]='O', ctrl=1;
			 	
				 	else if(board[i][j]=='X' && board[i-1][j-1]=='X' && board[i-2][j-2]=='X')
						board[i-3][j-3]='O', ctrl=1;
					
					else if(board[i][j]=='X' && board[i+1][j-1]=='X' && board[i+1][j-2]=='X')
						board[i+3][j-3]='O', ctrl=1;
						 }
					 }
	
			for(i; i<0; i--){
				for(j; j<0; j--){
			
					if(board[i][j]=='O' && board[i][j-1]=='O' && board[i][j-2]=='O')	//yan yana 3 'O' varsa yan�na 'O' koyan k�s�m.
						board[i][j-3]='O', ctrl=1;
			
					else if(board[i][j]=='O' && board[i-1][j]=='O' && board[i-2][j]=='O')
						board[i-3][j]='O', ctrl=1;
				
					else if(board[i][j]=='O' && board[i-1][j-1]=='O' && board[i-2][j-2]=='O')
						board[i+3][j]='O', ctrl=1;
				
					else if(board[i][j]=='O' && board[i+1][j-1]=='O' && board[i+2][j-2]=='O')
						board[i][j+3]='O', ctrl=1;	
						
					else if(board[i][j]=='O' && board[i][j+2]=='O' && board[i][j+3]=='O')			
						board[i][j+1]='O', ctrl=1;	
						
					else if(board[i][j]=='O' && board[i][j+1]=='O' && board[i][j+3]=='O')
						board[i][j+2]='O', ctrl=1;
						}
					}
	
			for(i; i<0; i--){
				for(j; j<0; j--){
					
					if(board[i][j]=='O' && board[i][j-1]=='O')
			 			board[i][j-2]='O', ctrl=1;

				 	else if(board[i][j]=='O' && board[i-1][j]=='O')
			 			board[i-2][j]='O', ctrl=1;

				 	else if(board[i][j]=='O' && board[i-1][j-1]=='O')
						board[i-2][j-2]='O', ctrl=1;
					
					else if(board[i][j]=='O' && board[i+1][j-1]=='O')
						board[i+2][j-2]='O', ctrl=1;	
						}
					}

			for(i; i<0; i--){
				for(j; j<0; j--){
					
					if(board[i][j]=='O')
			 			board[i][j-1]='O', ctrl=1;
			 		
			 		else if(board[i][j]=='O')
			 			board[i][j+1]='O', ctrl=1;
			 		
				 	else if(board[i][j]=='O')
			 			board[i-1][j]='O', ctrl=1;
			 	
				 	else if(board[i][j]=='O')
						board[i-1][j-1]='O', ctrl=1;
					
					else if(board[i][j]=='O')
						board[i+1][j-1]='O', ctrl=1;	
						}
					}				
					
			}while(ctrl==0);
			
}
			
			
			
void firstMoveAI(char board[][max], int boyut){							//daha iyi bir ��z�m yoksa bilgisayar random �ekilde hamle yap�yor.

			int k=0;
			int ctrl=0;
			int firstAI=rand()%boyut;		//kullan�c�n girdi�i boyutla 0 aras�nda random say� giren fonksiyon.
			
			if(board[0][firstAI]!='.')		//random se�ilen s�tun dolu ise bir yan�na 'O' giriliyor bilgisayar taraf�ndan. 
				{
				int f=boyut;
				do{
					if(board[f][firstAI+1]!='.')	
						--f;
					else k=1;
					
				}while(k=0);
					board[f][firstAI+1]='O';
				}
			else{							//bir yandaki s�tunun da en alt sat�r� doluysa, bo� olan sat�ra kadar fonksiyonu d�nerip bo� olana giri� yap�yor.
			do{
				if(board[boyut][firstAI]=='.')
				{
					board[boyut][firstAI]= 'O';
					ctrl=1; 
				}	
				else --boyut;
					
				}while(ctrl==0);		
}
}



int controlAI(char board[][max], int boyut){		
	

			int ctrl=0;
			int i=boyut, j=boyut; 
			
			
			for(i; i<0; i--){
			 	for(j; j<0; j--){
			 		
			 		if(board[i][j]=='X' && board[i][j-1]=='X' && board[i][j-2]=='X' )
			 			ctrl=1;
			 	
				 	else if(board[i][j]=='X' && board[i-1][j]=='X' && board[i-2][j]=='X')
			 			ctrl=1;
			 	
				 	else if(board[i][j]=='X' && board[i-1][j-1]=='X' && board[i-2][j-2]=='X')
						ctrl=1;
					
					else if(board[i][j]=='X' && board[i+1][j-1]=='X' && board[i+1][j-2]=='X')
						ctrl=1;
						 }
					 }
	
	
			for(i; i<0; i--){
				for(j; j<0; j--){
					
					if(board[i][j]=='O')
			 			ctrl=1;
			 	
				 	else if(board[i][j]=='O')
			 			ctrl=1;
			 	
				 	else if(board[i][j]=='O')
						ctrl=1;
					
					else if(board[i][j]=='O')
						ctrl=1;	
						}
					}	
			
	
			for(i; i<0; i--){
				for(j; j<0; j--){
					
					if(board[i][j]=='O' && board[i][j-1]=='O')
			 			ctrl=1;
			 	
				 	else if(board[i][j]=='O' && board[i-1][j]=='O')
			 			ctrl=1;
			 	
				 	else if(board[i][j]=='O' && board[i-1][j-1]=='O')
						ctrl=1;
					
					else if(board[i][j]=='O' && board[i+1][j-1]=='O')
						ctrl=1;	
						}
					}
			
				 
			 for(i; i<0; i--){
				for(j; j<0; j--){
			
					if(board[i][j]=='O' && board[i][j-1]=='O' && board[i][j-2]=='O')
						ctrl=1;
			
					else if(board[i][j]=='O' && board[i-1][j]=='O' && board[i-2][j]=='O')
						ctrl=1;
				
					else if(board[i][j]=='O' && board[i-1][j-1]=='O' && board[i-2][j-2]=='O')
						ctrl=1;
				
					else if(board[i][j]=='O' && board[i+1][j-1]=='O' && board[i+2][j-2]=='O')
						ctrl=1;				
							}
						}
					
		
	
	return ctrl;		
}



void showWinner(char board[][max], int boyut){
		
		
				int asd=0;
				int m, n;
				
				
				for(m=0; m<boyut; m++){
					for(n=0; n<boyut; n++){
						
						if(board[m][n]=='X' && board[m][n-1]=='X' && board[m][n-2]=='X' && board[m][n-3]=='X')	//4 tane 'X' yan yana geldiyse hepsini 'x' yap.
					  	  {board[m][n]= 'x',   board[m][n-1]= 'x',   board[m][n-2]= 'x',   board[m][n-3]= 'x';}
							
						if(board[m][n]=='X' && board[m-1][n]=='X' && board[m-2][n]=='X' && board[m-3][n]=='X')
					      {board[m][n]= 'x',   board[m-1][n]= 'x',   board[m-2][n]= 'x',   board[m-3][n]= 'x';}		
					
						if(board[m][n]=='X' && board[m-1][n-1]=='X' && board[m-2][n-2]=='X' && board[m-3][n-3]=='X')
						  {board[m][n]= 'x',   board[m-1][n-1]= 'x',   board[m-2][n-2]= 'x',   board[m-3][n-3]= 'x';}
					
						if(board[m][n]=='X' && board[m+1][n-1]=='X' && board[m+2][n-2]=='X' && board[m+3][n+3]=='X')
						  {board[m][n]= 'x',   board[m+1][n-1]= 'x',   board[m+2][n-2]= 'x',   board[m+3][n+3]= 'x';}
	
					}
				}
	
	
				for(m=0; m<boyut; m++){
					for(n=0; n<boyut; n++){
						
						if(board[m][n]=='O' && board[m][n-1]=='O' && board[m][n-2]=='O' && board[m][n-3]=='O')	//4 tane 'O' yan yana geldiyse hepsini 'o' yap.
					  	  {board[m][n]= 'o',   board[m][n-1]= 'o',  board[m][n-2]= 'o',    board[m][n-3]= 'o';}
							
						if(board[m][n]=='O' && board[m-1][n]=='O' && board[m-2][n]=='O' && board[m-3][n]=='O')
						  {board[m][n]= 'o',   board[m-1][n]= 'o',   board[m-2][n]= 'o',   board[m-3][n]= 'o';}
					
						if(board[m][n]=='O' && board[m-1][n-1]=='O' && board[m-2][n-2]=='O' && board[m-3][n-3]=='O')
						  {board[m][n]= 'o',   board[m-1][n-1]= 'o',   board[m-2][n-2]= 'o',   board[m-3][n-3]= 'o';}
					
						if(board[m][n]=='O' && board[m+1][n-1]=='O' && board[m+2][n-2]=='O' && board[m+3][n+3]=='O')
						  {board[m][n]= 'o',   board[m+1][n-1]= 'o',   board[m+2][n-2]= 'o',   board[m+3][n+3]= 'o';}
					
					}
				}
	
	
}
