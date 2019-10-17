//Egemen ÇAÐÞIRLI 161044101
//Connect4 Game
#include <iostream>
#include <stdlib.h>
#include <fstream>
#define max 30	//maksimum 20 verince memory'deki bazý X veya O'larý ortaya çýkardýðý için maksimum 30 yaptým. hata düzeldi.
using namespace std;



void showBoard( char board[][max], int& boyut); //tahtayý gösteren fonksiyon	//PARAMETER BAY REFERENCE
int makeMoveP1( char board[][max], int boyut, char sign='X');	//player 1 için hamle fonksiyonu			//DEFAULT ARGUMENT		
int makeMoveP2( char board[][max], int boyut, char sign='O');	//player 2 için hamle fonksiyonu			//DEFAULT ARGUMENT
int checkFourP1( char board[][max], const int& boyut); //player 1'in yan yana, alt alta ve iki çaprazýn dörtlediðini kontrol eden fonksiyon  //CONSTANT PARAMETER BY REF.
int checkFourP2( char board[][max], const int& boyut); //player 2'nin yan yana, alt alta ve iki çaprazýn dörtlediðini kontrol eden fonksiyon //CONSTANT PARAMETER BY REF.
int noWin(char board[][max], int boyut); //beraberliði, tüm satýr ve sütunlarýn dolduðunu kontrol eden fonksiyon
void firstMoveAI(char board[][max], int boyut); //bilgisayarýn ilk hamlesini rastgele(random) yaptýran fonksiyon
void makeMoveAI(char board[][max], int boyut); // bilgisayarýn random olmayan hamlelerini yaptýran fonksiyon
int controlAI(char board[][max], int boyut); //bilgisayarýn oyununda yan yana 2,3,4 tane gelip gelmediðini kontrol eden fonksiyon
void showWinner(char board[][max], int boyut); //kazanan oyuncunun kazanan taþlarýný küçülten fonksiyon
void SaveFile(char board[][max], int boyut);
void LoadFile(char board[][max], int boyut);
 int controlsize(char dizi[][max]);


int main(){
		
	int satir, sutun, boyut, gameMod, AI;
	int control1, control2, draw;
	char board[max][max];
	int a;	
	cout<< "Welcome to Connect for game \n \n";
	cout<<"Do you want to loaded game?  yes=1   no=0\n";
	cin>>a;
	
	if(a==1){
		boyut=controlsize(board);
		gameMod=1;
		LoadFile(board,boyut);
		showBoard(board,boyut);
		
	}
	else{
	cout<< "Enter size (between 4-20 and an even number)";
	cin>>boyut;
		if(boyut<4 || boyut>20 || boyut%2!=0){  					 //4'ten küçük, 20'den büyük ve tek sayý girilmesi durumunda do while döngüsünün içine girecek. 
		do{
		cerr<< "Please enter between 4 and 20, and an even number (one of 4,6,8,10,12,14,16,18,20)";
		cin>>boyut;	
		}while(boyut<4 || boyut>20 || boyut%2!=0);					 //kullanýcý doðru input'u girmedikçe tekrar isteyecek.
		}
	
	 

		
	cout<< "1=Player vs Player \n2=Player vs Computer";
	cin>>gameMod;
	if(gameMod!=1 && gameMod!=2)
		{
		do{
		cerr<<"There is something wrong! \n\nEnter 1=Player vs Player \nEnter 2=Player vs Computer";
		cin>>gameMod;
		}while(gameMod!=1 && gameMod!=2);
		}
				showBoard(board,boyut);
	}
		if(gameMod==1){		//player 1 vs player 2 seçilmesi durumunda buraya girecek.
			
			cout<<"Press 'S' to save the game";
			
				do{
				int s=makeMoveP1(board, boyut);			//PLAYER 1 HAMLEYÝ YAPTI. s=MAKEMOVEP1 FONKSÝYONUNUN RETURN ETTÝÐÝ DEÐER
			
				if(s==1){								//EÐER s=1 ÝSE SAVE FÝLE FONKSÝYONUNU GÝRECEK.
					SaveFile(board, boyut);
					makeMoveP1(board, boyut); 
					}							//KAYDETMEK ÝSTENMÝÞSE KAYDEDÝLECEK VE OYUN BÝTECEK.
				showBoard(board, boyut);				//s=1 DEÐÝLSE, YANÝ KAYDETMEK ÝSTENMEDÝYSE DE OYUN YÝNE OLAÐAN AKIÞINDA DEVAM EDECEK.
				auto control1=checkFourP1(board,boyut);    	
				if(control1==1) {						//player 1 dörtlüyü saðladý mý diye kontrol edip return eden deðeri control1'e atadým.
						showWinner(board, boyut);		//kazandýðý takdirde 'X'leri küçülten fonksiyonu buraya ekledim.
						showBoard(board, boyut);		//ardýndan 'X'lerin küçülmüþ halini göstermek adýna showBoard fonksiyonunu ekledim.
						cout<<"Player 1 kazandi..!"; 
						break;}							//kazananýn olmasý halinde do while'dan çýkmasýný, oyunu bitirmesini saðladým
			
		
		
				 s=makeMoveP2(board, boyut);				//PLAYER TO PLAYER SEÇENEÐÝNDE OLDUÐU GÝBÝ KULLANICI KAYDETMEK ÝSTERSE KAYDEDECEK.
			
				if(s==1){
					SaveFile(board, boyut); 
					makeMoveP2(board, boyut); 
					}
				showBoard(board, boyut);						//KAYDETMEZSE DE OYUN OLAÐAN AKIÞINDA DEVAM EDECEK.
				auto control2=checkFourP2(board,boyut);
				if(control2==1) {						//player 2 dörtlüyü saðladý mý diye kontrol edip return eden deðeri control1'e atadým.
						showWinner(board, boyut);		//kazandýðý takdirde 'O'larý küçülten fonksiyonu buraya ekledim.
						showBoard(board, boyut);		//ardýndan 'O'larýn küçülmüþ halini göstermek adýna showBoard fonksiyonunu ekledim.
						cout<<"Player 2 kazandi..!"; 
						break;}							//kazananýn olmasý halinde do while'dan çýkmasýný, oyunu bitirmesini saðladým
					
			
				auto draw=noWin(board,boyut);
				if(draw==boyut){
					cout<<"It's draw. No one win :)";       		// noWin fonksiyonunu sadece player 2'den sonra yazdým,
					}													// satýr ve sütunlarýn toplamýnýn sayýsý çift sayý olmak zorunda.
				
				}while(control1!=1 || control2!=1 || draw!=boyut);		//bir oyuncu kazanmadýkça ve brabere bitmedikçe fonksiyonun dönmesini istedim.
		}
		
		
				
		if(gameMod==2){		// player vs computer seçilmesi durumunda buraya girecek.	
				cout<<"Press 'S' to save the game";
				showBoard(board,boyut);
			
				do{
				int s=makeMoveP1(board, boyut);
			
				if(s==1){
					SaveFile(board, boyut);
					makeMoveP1(board, boyut);
					}
				showBoard(board, boyut);
				auto control1=checkFourP1(board,boyut);    
				if(control1==1) { 						//player 1 dörtlüyü saðladý mý diye kontrol edip return eden deðeri control1'e atadým.
						showWinner(board, boyut);		//kazandýðý takdirde 'X'leri küçülten fonksiyonu buraya ekledim.
						showBoard(board, boyut);		//ardýndan 'X'lerin küçülmüþ halini göstermek adýna showBoard fonksiyonunu ekledim.
						cout<<"CONGRATULATION..!";
						break;}
			

				auto AI=controlAI(board, boyut);			//controlAI fonksiyonun döndürdüðü int deðerini AI'a atadým. 
				if(AI==0)								//AI=0 olmasý durumunda random sütun seçmesini istedim.
					{firstMoveAI(board, boyut);}	
				else									//AI=0 olmamasý durumunda makeMoveAI fonksiyonuna girmesini istedim.
					{makeMoveAI(board,boyut);}
				showBoard(board, boyut);
				auto control2=checkFourP2(board,boyut);	//computer için de player 2'nin dörtlüyü kontol eden fonksiyonunu kullandým,
													//çünkü bilgisayar da player 2 gibi 'O' karakterini giriyor. 	
				if(control2==1) {					//bilgisayar hamlesi dörtlüyü saðladý mý diye kontrol edip return deðeri control2'ye atadým 
						showWinner(board, boyut);	//kazandýðý takdirde 'O'larý küçülten fonksiyonu buraya ekledim.
						showBoard(board,boyut);		//ardýndan 'O'larýn küçülmüþ halini göstermek adýna showBoard fonksiyonunu ekledim.
						cout<<"GAME OVER! :/"; 
						break;}
					
			
		
				auto draw=noWin(board,boyut);
				if(draw==boyut){
					cout<<"It's draw. No one win :)";       		// noWin fonksiyonunu sadece player 2'den sonra yazdým,
					}												// satýr ve sütunlarýn toplamýnýn sayýsý çift sayý olmak zorunda.
				
				}while(control1!=1 || control2!=1 || draw!=boyut);		//bir oyuncu kazanmadýkça ve brabere bitmedikçe fonksiyonun dönmesini istedim.	
		}
}	
	



void showBoard(char board[][max], int& boyut){
	
	char harf[30]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};	//tablonun ilk satýrýnda kullanýlabilecek harfler.
	for(int a=0; a<boyut; a++) {
	cout << harf[a] <<" ";			//kullanýcýnnýn girdiði boyuta göre tablonun ilk satýrýndaki harfleri oluþturdum. Aralarda birer boþluk býraktým.
	}
	cout<<endl;			//alt satýra geçip tablonun noktalý kýsýmlarýný oluþturmak için endl kullandým. 
	
	for(int m=0; m<boyut; m++){
		for(int n=0; n<boyut; n++){
			
			if(board[m][n]!='X' && board[m][n]!='O' && board[m][n]!='x' && board[m][n]!='o'){ //satýr ve sütunlarýn deðeri X,O,x veya o olmadýkça hep nokta ile oluþtur.
			board[m][n]='.'; 	
			}
			cout<< board[m][n] << " ";	//aralarda bir boþluk býraktýk ki daha geniþ ve düzenli görünsün.
		}
			cout<< endl;	}		
}



int makeMoveP1(char board[][max], int boyut, char sign){
			
			int save=0;	
			int ctrl=0;
			int ch;
			decltype(sign) choice;
		
			cout<< "\nPlayer 1, choose a column\n";
			cin>> choice;
			ch= choice-'A';
			if(choice=='S')
				{
					cout<<"Game Saved";
				save=1;
				}
			else if(ch>boyut)
				{
				do{
				cerr<<"There is something wrong. Choose a column\n";			//HATA VEREN KISMI CERR ÝLE YAZDIRDIM
				cin>>choice;
				ch=choice-'A';
				}while(ch>=boyut);													//GÝRÝLEN SÜTUN TAHTA BOYUTUNDAN BÜYÜKSE HATA VERECEK, TEKRAR SÜTUN ÝSTEYECEK.
				
					if(board[0][ch]=='X' || board[0][ch]=='O')
						{cerr<< "\nBu sutun dolu, sira Player2'de..." << endl <<endl;	//HATA YAPAN KISMI CERR ÝLE YAZDIRDIM
						}
					else{	
						do{
						if(board[boyut][ch]=='.')	
						{	
						board[boyut][ch]= sign; 				  
						ctrl=1;
						}
						else --boyut;	

						}while(ctrl==0);
				}}
				
			else{ 	save=0;  
					ch= choice-'A';
					if(board[0][ch]=='X' || board[0][ch]=='O')
						{cerr<< "\nBu sutun dolu, sira Player2'de..." << endl <<endl;	}	//eðer player 1 dolu olan sütuna giriþ yaparsa sýra player 2'ye geçer.
					else{	
						do{
						if(board[boyut][ch]=='.')	//girilen satýr ve tablodaki en alt sütuna 'X' yazdýran kýsým. 
						{	
						board[boyut][ch]= sign; 				  
						ctrl=1;
						}
						else --boyut;		//en alt doluysa boyutu döngüye sokup birer azaltarak üsttekilere bakmasýný saðlýyoruz.

						}while(ctrl==0);
				}}

	return save;	

}



int makeMoveP2( char board[][max], int boyut, char sign ){

			
			int save=0;
			int ctrl=0;
			int ch;
			decltype(sign) choice;
		
			cout<< "\nPlayer 2, choose a column\n";
			cin>> choice;
			ch=choice-'A';
			if(choice=='S')
				{
				save=1;
				}
			else if(ch>boyut)
				{
				do{
				cerr<<"There is something wrong. Choose a column\n";
				cin>>choice;
				ch=choice-'A';
				}while(ch>=boyut);
				
					if(board[0][ch]=='X' || board[0][ch]=='O')
						{cerr<< "\nBu sutun dolu, sira Player2'de..." << endl <<endl;	}
					else{	
						do{
						if(board[boyut][ch]=='.')	
						{	
						board[boyut][ch]= sign; 				  
						ctrl=1;
						}
						else --boyut;	

						}while(ctrl==0);
				}}
					
			else{ 	save=0;
					ch= choice-'A';			//kullanýcýdan girilen char deðerini (A,B,C,D,...) integer deðerine çeviren fonksiyon.
				
					if(board[0][ch]=='X' || board[0][ch]=='O')
						{cerr<< "\nBu sutun dolu, sira Player1'de..." << endl <<endl;}	//eðer player 2 dolu olan sütuna giriþ yaparsa sýra player 1'e geçer.
					else
						{
						do{
						if(board[boyut][ch]=='.')	//girilen satýr ve tablodaki en alt sütuna 'O' yazdýran kýsým.
						{	
						board[boyut][ch]= sign; 				
						ctrl=1;
						}
						else --boyut;		//en alt doluysa boyutu döngüye sokup birer azaltarak üsttekilere bakmasýný saðlýyoruz.
			
						}while(ctrl==0);
				}}
	return save;
}



int checkFourP1(char board[][max], const int& boyut){								
	
		int i,j;
		int fourP1=0;
		
				for(i=boyut-1; i>=0; i--){									
					for(j=boyut-1; j>=0; j--){
						
					if(board[i][j]=='X' && board[i][j-1]=='X' && board[i][j-2]=='X' && board[i][j-3]=='X')	//4 tane X'in yan yana, alt alta ve iki çapraz þekilde,
						{fourP1=1;}																			//gelmesini kontrol eden ve bu þartlar oluþtuðu takdirde,
																											//0 olan fourP1 deðerine 1 atayan fonksiyon.
					if(board[i][j]=='X' && board[i-1][j]=='X' && board[i-2][j]=='X' && board[i-3][j]=='X')	//sonrasýnda da fourP1 deðerini return ediyor.
						{fourP1=1;}
	
					if(board[i][j]=='X' && board[i-1][j-1]=='X' && board[i-2][j-2]=='X' && board[i-3][j-3]=='X')
						{fourP1=1;}
		
					if(board[i][j]=='X' && board[i-1][j+1]=='X' && board[i-2][j+2]=='X' && board[i-3][j+3]=='X')
						{fourP1=1;}
		}	
	
	}
	return fourP1;
}



int checkFourP2(char board[][max], const int& boyut){									
	
		int i,j;
		int fourP2=0;

				for(i=boyut; i>0; i--){										
					for(j=boyut; j>0; j--){
						
					if(board[i][j]=='O' && board[i][j-1]=='O' && board[i][j-2]=='O' && board[i][j-3]=='O')	//4 tane X'in yan yana, alt alta ve iki çapraz þekilde
						{fourP2=1;}																			//gelmesini kontrol eden ve bu þartlar oluþtuðu takdirde,
																											//0 olan fourP1 deðerine 1 atayan fonksiyon.							
					if(board[i][j]=='O' && board[i-1][j]=='O' && board[i-2][j]=='O' && board[i-3][j]=='O')	//sonrasýnda da fourP1 deðerini return ediyor.
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
			if(board[0][f]!='.' )		//en üst satýrýn tüm sütunlarýna tek tek bakýp hiçbiri '.' deðilse berabere bittiðini söyleyen fonksiyon.
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
			 		
			 		if(board[i][j]=='X' && board[i][j-1]=='X' && board[i][j-2]=='X' )	//yan yana 3 'X' varsa yanýna 'O' koyan kýsým.
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
			
					if(board[i][j]=='O' && board[i][j-1]=='O' && board[i][j-2]=='O')	//yan yana 3 'O' varsa yanýna 'O' koyan kýsým.
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
			
			
			
void firstMoveAI(char board[][max], int boyut){							//daha iyi bir çözüm yoksa bilgisayar random þekilde hamle yapýyor.

			int k=0;
			int ctrl=0;
			int firstAI=rand()%boyut;		//kullanýcýn girdiði boyutla 0 arasýnda random sayý giren fonksiyon.
			
			if(board[0][firstAI]!='.')		//random seçilen sütun dolu ise bir yanýna 'O' giriliyor bilgisayar tarafýndan. 
				{
				int f=boyut;
				do{
					if(board[f][firstAI+1]!='.')	
						--f;
					else k=1;
					
				}while(k==0);
					board[f][firstAI+1]='O';
				}
			else{							//bir yandaki sütunun da en alt satýrý doluysa, boþ olan satýra kadar fonksiyonu dönerip boþ olana giriþ yapýyor.
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




void SaveFile(char board[][max], int boyut){

	
	ofstream file;
	file.open("Connect4 Saved File.txt");
	file<<boyut<<endl;

	for(int m=0; m<boyut; m++){
		for(int n=0; n<boyut; n++){
			
			if(board[m][n]!='X' && board[m][n]!='O' && board[m][n]!='x' && board[m][n]!='o'){ 
			board[m][n]='.'; 	
			}
			file<< board[m][n] << " ";	
		}
			file<<endl;	}
			file<<endl;
			
			
			
	


	file.close();
}





  void LoadFile(char board[][max], int boyut){
		
	
	std::ifstream file("Connect4 Saved File.txt",std::ifstream::in); 	
	
	for(int i=0; i<boyut; i++){
		
		for(int j=0; j<boyut; j++ ){
		
			char a;
			file>>a;
			board[i][j]=a;	
		}	
	}
		cout<<endl;
		file.close();	
}
   int controlsize(char board[][max]) {
   
   std::ifstream loadsize("Connect4 Saved File.txt",std::ifstream::in);
   int boyut;
   loadsize>>boyut;
   return boyut;
   }
