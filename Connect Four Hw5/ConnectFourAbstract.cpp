#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "string.h"
#include"ConnectFourAbstract.h"
#include"Cell.h"
using namespace std;
namespace egemen
{


void ConnectFourAbstract::showBoard(){	//board'i gosteren fonksiyon
		int s;
		cout<<endl;
		for(s=0; s<column; s++){
			char row_letter= 'A'+s;	
			cout<< row_letter; //board'in en üst kismini, harfleri yazdirdik
		}
		cout<<endl;
		
		
		for(int m=0; m<row; m++){
			for(int n=0; n<column; n++){
				if(gameBoard[m][n].isempty==true){
					gameBoard[m][n].user='*';	//bos olan cell'lere * koyacak. user=* olacak
				}
				cout<<gameBoard[m][n].user;
			}	
		cout<<endl;	//alt satira geçmesi için iki for'un arasina endl koyduk
		}
		
}
void ConnectFourAbstract::chooseGameMod(){
	
	//char user;
	cout<<"P = Player vs Player \nC = Player vs Computer"<<endl; //bilgisayara karsi mi player vs player mi? diye soruyoruz
	cin>>gameMod;
	if(gameMod!='P' && gameMod!='C') //P veya C girilmediginde tekrar girilmesini isteyecek
			do{
				cerr<<"Enter P for Player vs Player, \nEnter P for Player vs Computer!"<<endl; //
					 cin>>gameMod;
				}while(gameMod!='P' && gameMod!='C'); //P veya C girilene kadar aynýsýný isteyecek
			}
int ConnectFourAbstract::play(int& ch, char Sign){	//parametre alan play fonksiyonu
	
		
		int realRow=row; //asagisaki do-while dongusunde row'u bie azaltacagimiz icin, row'u baska yere kaydettik.
		int ctrl=0;

		do{
			if(gameBoard[row-1][ch].isempty==true){	//en alt satir boþsa o satiri Sign yap. degilse row'u bir azalt
				gameBoard[row-1][ch].user=Sign; 	
				gameBoard[row-1][ch].isempty=false;
				ctrl=1;	//bos olan en alt satir dolunca ctrl'yi 1 yapi donguden cik
			}
			else --row;	//en alt satirin bir ustune bakmasý icin row'u bir azalt.

		}while(ctrl==0);
		
		row=realRow; //row'u tekrar en basta atadigimiz yedeginden aliyoruz
}
void ConnectFourAbstract::play(){ 
	int m=row-1, n=column-1;
	int ctrl=0;
	makeMoveAI(); //bilgisayarin hamlesini makemovAI fonksiyonuna gönderiyor
}
void ConnectFourAbstract::makeMoveAI(){ //bilgisayarin hamle yaptigi fonksiyon
	
		int m=row-1, n=column-1;
		int k=0;
		int ktrl=0;
		int AI=rand()%column; //bilgisayarin smart olmasi istenmedigi icin hamleyi random aliyor
			if(gameBoard[0][AI].isempty==false) //ilk random aldigi cellin columnu doluysa buraya giriyor
			{
				do{	
				AI=rand()%column;
				if(gameBoard[0][AI].isempty==true)
				ktrl=1;
				}while(ktrl==0);
			}
		do{
		if(gameBoard[m][AI].isempty==true){ //random secilen cell doluysa bir usttekine koyuyor.
				gameBoard[m][AI].user='O';
			gameBoard[m][AI].isempty=false;
			k=1;}
		else	
			--m;	//cell'in dolu olmasi halinde bir usttekine bakmasi icin
			 
		}while(k==0);
		
		Record.push_back(AI);	//undoGame fonkiyonunda hamleyi geri alabilmek için hamleyi vektorun ardina ekliyoruz.
				
}
int ConnectFourAbstract::move(){
	char move;
	int ch=-1;
	string fileName;
	string choice; //kullanicidan alacak oldugumuz input
	string input;		
	do{
	cout<< "\nChoose a column \n";
	cin>>choice;
	getline(cin,input);
	string parsing(input);
	string firstEmpty=" ";
	fileName=parsing.substr(parsing.find_first_of(firstEmpty)+1); //fileName'i ilk bosluga kadar parse ediyoruz.
			if(choice=="SAVE"){		//ilk bosluktan sonrasý kaydedilen dosyanýn adý olacak
			cout<<"Game Saved"<<endl;
			writeFile(fileName);	//Save 1.txt yazilmasi durumunda dosyayi 1 isminde kaydedecek
			}
			else if(choice=="LOAD"){
			cout<<"LOADING GAME"<<endl;
			readFile(fileName);	//load 1.txt yazilmasi durumunda 1 ismiyle kaydedilen dosyayi yükleyecek
			showBoard();
			}

			else if(choice.length()==1)	//eger choice'in uzunlugu 1'se a,b,c vs.dir secilen column'a koyacak x veya o'yu
			{
				move=choice[0];
				ch= move-'A';
					if(gameBoard[0][ch].isempty==false){ //dolu olan bir sutun secilmesi halinde
						cerr<<"This column is full, choose an other column.";
						ch=-1;
					}
					else if(ch>column){
						cerr<<"There is no column that!";	//olmayan bir sutun secilmesi halinde
						ch=-1;	
					}
				
			}
		
	}while(ch<0||ch>column);
	
	return ch; //ch'yi yani secilen sutunu return ediyor
}


void ConnectFourAbstract::playertoPlayer(){
	do{
		int s1=move();
		if(s1!=-1){	//EGER S1=-1'SE UNDO YAZILMISTIR. O YUZDEN HAMLE SIRASI 2.PLAYERDA OLACAK
		play(s1, 'X'); //PLAYER 1'IN HAMLE YAPTIGI FONK.	
		showBoard();	
		gameEnded('X');
			if(gameEnd==true){	//GAME END FONK. TRUE ISE OYUNU BITIRECEK
				showWinner();
				showBoard();
			}
		}
	if(gameEnd!=true){
		int s2=move();
		if(s2!=-1){
		play(s2, 'O');	//PLAYER 2'NIN HAMLE YAPTIGI FONK.
		showBoard();
		gameEnded('O');			//GAME END FONK. TRUE ISE OYUNU BITIRECEK.
			if(gameEnd==true){
				showWinner();
				showBoard();
			}
		}
	}
	}while(gameEnd==false);
}
void ConnectFourAbstract::playertoComputer(){
	do{
		int s1=move();
		if(s1!=-1){	//EGER S1=-1'SE UNDO YAZILMIS DEMEKTIR. O YUZDEN BURAYA GIRMEYECEK VE COMPUTER OYNAYACAK.
		play(s1, 'X'); //PLAYER 1'IN HAMLE YAPTIGI FONK.
		showBoard();
		gameEnded('X');
			if(gameEnd==true){ //GAME END FONK. TRUE ISE OYUNU BITIR
				showWinner();
				showBoard();
			}
		}
	if(gameEnd!=true){
		play();
		showBoard();					
		gameEnded('O');
			if(gameEnd==true){
				showWinner();
				showBoard();
			}
	}
	
	}while(gameEnd==false);
}
void ConnectFourAbstract::playGame(){
	setRow();
	setColumn();
	chooseGameMod();
	
	gameBoard=new Cell*[row];	//Cell Hücrelerini olusturdugumuz kýsým
		for(int i=0; i<row; i++)
			gameBoard[i]=new Cell[column];

	showBoard();
	
	if(gameMod=='P'){
		playertoPlayer();	//P secilmesi halinde playertoPlayer fonksiyonuna gidecek
	}
	
	if(gameMod=='C'){	//C secilmesi halinde playertoComputer fonksiyonuna gidecek
		playertoComputer();
	}
	
}

void ConnectFourAbstract::undoGame(){	

}

void ConnectFourAbstract::setRow(){
		cout<<"Enter the Row Size..:";	//Row Size'i user'dan aldýk
		cin>>row;
}
void ConnectFourAbstract::setColumn(){
		cout<<"Enter the Column Size..:";	//Column Size'i user'dan aldik
		cin>>column;
}
int ConnectFourAbstract::currentWidth(){	//en son durumdaki sütunu tutan fonksiyon
	return column;
}
int ConnectFourAbstract::currentHeight(){	//en son durumdaki satiri tutan fonksiyon
	return row;
}
int ConnectFourAbstract::checkFour(char Sign){								
	
		int i,j;
		int fourC=0;
		
				for(i=row-1; i>=0; i--){									
					for(j=column-1; j>=0; j--){

					if(	gameBoard[i][j].user==Sign && 
						gameBoard[i][j-1].user==Sign && 
						gameBoard[i][j-2].user==Sign && 
						gameBoard[i][j-3].user==Sign)	//4 tane X'in yan yana, alt alta ve iki çapraz sekilde,
						{fourC=1;}	//gelmesini kontrol eden ve bu sartlar oluþtugu takdirde,
								//0 olan fourP1 deðerine 1 atayan fonksiyon.

					if(gameBoard[i][j].user==Sign && 
						gameBoard[i-1][j].user==Sign && 
						gameBoard[i-2][j].user==Sign && 
						gameBoard[i-3][j].user==Sign)	//sonrasinda da fourP1 degerini return ediyor.
						{fourC=1;}

					if(gameBoard[i][j].user==Sign && 
					gameBoard[i-1][j-1].user==Sign && 
					gameBoard[i-2][j-2].user==Sign && 
					gameBoard[i-3][j-3].user==Sign)
						{fourC=1;}
		
					if(gameBoard[i][j].user==Sign && 
					gameBoard[i-1][j+1].user==Sign && 
					gameBoard[i-2][j+2].user==Sign && 
					gameBoard[i-3][j+3].user==Sign)
						{fourC=1;}
		}	
	
	}
	
	return fourC;
}
void ConnectFourAbstract::gameEnded(char user){

	checkFour(user);	//gameEnden fonksiyonu checkfour'la kontrol ediyor 4'lu olup olmadigini
	int beraber=draw();	//berabere olmasi durumunda it's draw yazdiriyor.
	if(beraber==column){
		cout<<"It's Draw...";
		gameEnd=true;
	}

	int control=checkFour(user);
	if(control==1){	//checkfour'dan donen return 1 ise oyun bitmistir.
		gameEnd=true;
		if(gameMod=='P'){
			if(user=='X'){	cout<<"Player 1 Won... ";}
			else{			cout<<"Player 2 Won... ";}
		}
		
		else{	//bilgisayara karsi oynanan oyun bittiginde
			if(user=='X') cout<<"CONGRATULATION..! :) ";
			else cout<<"GAME OVER..! :/";
		}
	}
}
int ConnectFourAbstract::draw(){
	
	int f;
	int D=0;
	
	for(f=0; f<column; f++)
		{
			if(gameBoard[0][f].isempty==false )//en ust satirin tüm sütunlarina tek tek bakip hicbiri '*' degilse berabere bittigini soyleyen fonksiyon.
			++D;
			}
	return D;
}
void ConnectFourAbstract::showWinner(){ 
	
	int ctrl=0;
	int m, n;
				for(m=0; m<row; m++){
					for(n=0; n<column; n++){//4 tane 'X' yan yana geldiyse hepsini kucuk 'x' yapan kisim
						
					if(gameBoard[m][n].user=='X' && gameBoard[m][n-1].user=='X' && gameBoard[m][n-2].user=='X' && gameBoard[m][n-3].user=='X')	
					  {gameBoard[m][n].user= 'x',   gameBoard[m][n-1].user= 'x',   gameBoard[m][n-2].user= 'x',   gameBoard[m][n-3].user= 'x';
						ctrl=1;}
							
					if(gameBoard[m][n].user=='X' && gameBoard[m-1][n].user=='X' && gameBoard[m-2][n].user=='X' && gameBoard[m-3][n].user=='X')
				     {gameBoard[m][n].user= 'x',   gameBoard[m-1][n].user= 'x',   gameBoard[m-2][n].user= 'x',   gameBoard[m-3][n].user= 'x';
					  	ctrl=1;}		
					
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
					for(n=0; n<column; n++){	//4 tane 'O' yan yana geldiyse hepsini 'o' yapan kisim
						
						if(gameBoard[m][n].user=='O' && gameBoard[m][n-1].user=='O' && gameBoard[m][n-2].user=='O' && gameBoard[m][n-3].user=='O')
					  	  {gameBoard[m][n].user= 'o',   gameBoard[m][n-1].user= 'o',  gameBoard[m][n-2].user= 'o',    gameBoard[m][n-3].user= 'o';}
							
						if(gameBoard[m][n].user=='O' && gameBoard[m-1][n].user=='O' && gameBoard[m-2][n].user=='O' && gameBoard[m-3][n].user=='O')
						  {gameBoard[m][n].user= 'o',   gameBoard[m-1][n].user= 'o',   gameBoard[m-2][n].user= 'o',   gameBoard[m-3][n].user= 'o';}
					
						if(gameBoard[m][n].user=='O' && gameBoard[m-1][n-1].user=='O' && gameBoard[m-2][n-2].user=='O' && gameBoard[m-3][n-3].user=='O')
						  {gameBoard[m][n].user= 'o',   gameBoard[m-1][n-1].user= 'o',   gameBoard[m-2][n-2].user= 'o',   gameBoard[m-3][n-3].user= 'o';}
					
						if(gameBoard[m][n].user=='O' && gameBoard[m+1][n-1].user=='O' && gameBoard[m+2][n-2].user=='O' && gameBoard[m+3][n+3].user=='O')
						  {gameBoard[m][n].user= 'o',   gameBoard[m+1][n-1].user= 'o',   gameBoard[m+2][n-2].user= 'o',   gameBoard[m+3][n+3].user= 'o';}
					
					}
				}
		}	
}
void ConnectFourAbstract::writeFile(string fileName){ //move'da oluþturduðumuzu fileName'i parametre olarak aldý
	
	ofstream file;
	file.open(fileName.c_str());

	for(int m=0; m<row; m++){
		for(int n=0; n<column; n++){
			
			if(gameBoard[m][n].user!='X' && gameBoard[m][n].user!='O' && gameBoard[m][n].user!='x' && gameBoard[m][n].user!='o'){ 
			gameBoard[m][n].user='*';	//X,O,x veya o degilse o cell'i * yap
			}
			file<<gameBoard[m][n].user << " ";	
		}
			file<<endl;	
	}
			file<<endl;

	file.close();	
}
void ConnectFourAbstract::readFile(string fileName){
	std::ifstream file(fileName.c_str(),std::ifstream::in); //readFile fonksiyonu. kaydedilen dosyayi yukluyor.
	
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++ ){
		
			char a;
			file>>a;
			gameBoard[i][j].user=a;	
		}	
	}
		cout<<endl;
		file.close();	
}

}
