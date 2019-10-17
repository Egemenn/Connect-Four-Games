//Egemen Çaðþýrlý
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

class ConnectFour
{
	private:
		class Cell
		{
			private:
				int row;
				char column;
			public:
				bool isempty=true;
				char user;
				Cell();
				Cell(char Sign);	
				friend bool operator !=(const Cell& ne1,const Cell& ne2);
				friend bool operator ==(const Cell& e1, const Cell e2);		
				Cell operator ++();	//pre-increment
				Cell operator ++(int ignore);//post-increment 
				Cell operator --();//pre-decrement
				Cell operator --(int ignore);//post-decrement
				
		};

		int gameMod;
		int row;
		int column;
		char choice;
	public:		
		Cell ** gameBoard;
		ConnectFour();	//parametre almayan constructor, 5x5'lik board yazdýracak
		ConnectFour(int rowNumber, int columnNumber);	//row ve column'ý parametre alan constructor fonksiyon
//		ConnectFour( text file? );	//2 parametre alan constructor fonksiyon 
		int getRow();
		int getColumn();
		void setRow(int inputRow);
		void setColumn(int inputColumn);
		
		void readFile();	//writefile fonksiyonu
		void writeFile();	//readfile fonksiyonu
		void showCurrentBoard();	//tabloyu gösteren fonksiyon
		void startingGame();
		void playGame(); //ask board size in it
		inline int play(int& ch, char Sign);	//play fonksiyonu position'ý parametre olarak alýyor
		void play();	//computer için play fonksiyonu
		int move();
		void makeMoveAI();	//computer'i hareket ettiren fonksiyon
		void gameEnded(char user);	//oyunun bitip bitmediðini kontrol eden fonksiyon
		int checkFour(char user);	//dört tane yan yana, üst üste veya çapraz gelip gelmedigini kontrol eden fonksiyon
		int draw();	//beraberliði kontrol eden fonksiyon
		void showWinner();	//4 tane yan yana gelen X ve O'lari küçülten fonksiyon
		bool gameEnd=false;	
		int controlsize();	
		friend bool operator ==(const ConnectFour& game1, const ConnectFour& game2);
		friend bool operator !=(const ConnectFour& game1, const ConnectFour& game2);
		void operator ++();
		void operator --();
		void operator <<(Cell& c);
		void operator >>(Cell& c);

};


int main(){
	
	ConnectFour game1,game2(7,9),game3(8,4),game4,game5;
	game1.startingGame();	//oyun baþlarken load or save game'i soran starting Game fonksiyonu
	game2.startingGame();
	game3.startingGame();
	game4.startingGame();
	game5.startingGame();



	do{
	
	if(game1.gameEnd==false)
	cout<<"\nGame 1 is playing\n";	//game 1'in oynadýðýný belirttim. hepsini tek tek belirttim
	game1.playGame();
	if(game2.gameEnd==false)
	cout<<"\nGame 2 is playing\n";
	game2.playGame();
	if(game3.gameEnd==false)
	cout<<"\nGame 3 is playing\n";
	game3.playGame();
	if(game4.gameEnd==false)
	cout<<"\nGame 4 is playing\n";
	game4.playGame();
	if(game5.gameEnd==false)
	cout<<"\nGame 5 is playing\n";
	game5.playGame();

}while(game1.gameEnd==false && game2.gameEnd==false && game3.gameEnd==false && game4.gameEnd==false && game5.gameEnd==false);

}

ConnectFour::ConnectFour(){	//5x5 row ve column alan constructor
	row=5;
	column=5;
}


ConnectFour::ConnectFour(int rowNumber, int columnNumber){		//row'u 4 ve column'u 6 alan constructor fonkiyon
		row=rowNumber;
		column=columnNumber;
}

ConnectFour::Cell::Cell(char Sign){
	user=Sign;
}

ConnectFour::Cell::Cell(){
}

void ConnectFour::setRow(int inputRow){
		row=inputRow;
}

void ConnectFour::setColumn(int inputColumn){
		column=inputColumn;
}

int ConnectFour::getRow(){
		cout<<"Enter the Row Size..:";
		cin>>row;
		return row;
}

int ConnectFour::getColumn(){
		cout<<"Enter the Column Size..:";
		cin>>column;
		return column;
}

void ConnectFour::showCurrentBoard(){
	
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
void ConnectFour::startingGame(){
		
		int a;	
		cout<<"1=Play Game... \n2=Loaded Game";
		cin>>a;

		if(a==2){
			row=controlsize();
			gameMod=1;
			readFile();
			showCurrentBoard();
		}
		else{
	
		char user;
		cout<<"1=Player vs Player \n2=Player vs Computer";
		
		cin>>gameMod;
					if(gameMod!=1 && gameMod!=2)
						{do
							{cerr<<"Enter 1 for Player vs Player, \nEnter 2 for Player vs Computer!";
							 cin>>gameMod;
						}while(gameMod!=1 && gameMod!=2);
						}
	
		/*row=getRow();
		setRow(row);
		column=getColumn();
		setColumn(column);*/
		
		gameBoard=new Cell*[row];
			for(int i=0; i<row; i++)
				gameBoard[i]=new Cell[column];
				
}
showCurrentBoard();
}
void ConnectFour::playGame(){
	
	
	
		showCurrentBoard();
			
	
		
		
		
		if(gameMod==1){								//PLAYER TO PLAYER KISMI BURADA
				//	while(1){
					int s=move();
					play(s, 'X');				//PLAYER 1'ÝN HAMLE YAPTIÐI FONK.
						if(s==1){									
								writeFile();		//DOSYAYI KAYDEDEN FONK.
								move();
								play(s, 'X');
						}
					showCurrentBoard();	
					gameEnded('X');
					
						if(gameEnd==true){			//GAME END FONK. TRUE ÝSE OYUNU BÝTÝR
							showWinner();
							showCurrentBoard();
						//	break;
						}
					int s2=move();
					play(s2, 'O');				//PLAYER 2'NÝN HAMLE YAPTIÐI FONK.
					if(s2==1){
								writeFile();			//DOSYAYI KAYDEDEN FONK.
								move();
								play(s2, 'O');
					}
					showCurrentBoard();
					gameEnded('O');					//GAME END FONK. TRUE ÝSE OYUNU BÝTÝR.
						if(gameEnd==true){
							showWinner();
							showCurrentBoard();
						//	break;
						} 	
				//	}
		}

		if(gameMod==2){								//PLAYER TO COMPUTER KISMI BURADA
				
					int s=move();
					play(s, 'X');				//PLAYER 1'ÝN HAMLE YAPTIÐI FONK.
							if(s==1){									
								writeFile();		//DOSYAYI KAYDEDEN FONK.
								play(s, 'X');
							}
					showCurrentBoard();
					gameEnded('X');
						if(gameEnd==true){
							showWinner();
							showCurrentBoard();
							
						}
					play();
					showCurrentBoard();					
					gameEnded('O');
						if(gameEnd==true){
							showWinner();
							showCurrentBoard();
						
						}
					
		}	
}	
 
 
int ConnectFour::move(){

			int save=0;
			int ch;
			char choice;
			
			cout<< "\nChoose a column \n";
			cin>>choice;

			ch= choice-'A';
			if(choice=='S')
				{
				cout<<"Game Saved";
				save=1;
			}
			else if(ch>column)
				{
				do{
				cerr<<"There is something wrong. Choose a column\n";			//HATA VEREN KISMI CERR ÝLE YAZDIRDIM
				cin>>choice;
				ch=choice-'A';
				}while(ch>=column);	//GÝRÝLEN SÜTUN TAHTA BOYUTUNDAN BÜYÜKSE HATA VERECEK, TEKRAR SÜTUN ÝSTEYECEK.
			}
	return save;
}



inline int ConnectFour::play(int &ch, char Sign){
	
			
			int realRow=row;	
			int ctrl=0;


					/*if(gameBoard[0][ch].isempty==false)
						{cerr<< "\nBu sutun dolu, sira diger oyuncuda..." << endl <<endl;//HATA YAPAN KISMI CERR ILE
						}*/
					//else{	
						do{
						if(gameBoard[row-1][ch].isempty==true)	
						{	
						gameBoard[row-1][ch].user=Sign; 	
						gameBoard[row-1][ch].isempty=false;
						ctrl=1;
						}
						else --row;	

						}while(ctrl==0);
					//}
				
				
			if(ch<=column) 	 {
					ch= choice-'A';
				/*	if(gameBoard[0][ch].isempty==false)
						{cerr<< "\nBu sutun dolu, sira diger oyuncuda..." << endl <<endl;	}	//eðer player 		//1 dolu olan sütuna giriþ yaparsa sýra player 2'ye geçer.
					else{*/	
						do{
						if(gameBoard[row-1][ch].isempty)//girilen satýr ve tablodaki en alt sütuna 'X' yazdýran. 
						{	
						gameBoard[row-1][ch].user= Sign; 	
						gameBoard[row-1][ch].isempty=false;			  
						ctrl=1;
						}
						else --row;//en alt doluysa boyutu döngüye sokup birer azaltarak üsttekilere bakiyor

						}while(ctrl==0);
				//	}
			}
			row=realRow;	//--row dediðimizde row sayýsýný azalttýðý için row'u tekrar orjinal sayýsýna eþitledim
	
} 

void ConnectFour::play(){
	int m=row-1, n=column-1;
	int ctrl=0;
	makeMoveAI();
}

void ConnectFour::makeMoveAI(){
	
		int m=row-1, n=column-1;
		int k=0;
		int ktrl=0;
		int AI=rand()%column;
			if(gameBoard[0][AI].isempty==false)
			{
				do{	
				AI=rand()%column;
				if(gameBoard[0][AI].isempty==true)
				ktrl=1;
				}while(ktrl==0);
			}
		do{
		if(gameBoard[m][AI].isempty==true){
				gameBoard[m][AI].user='O';
			gameBoard[m][AI].isempty=false;
			k=1;}
		else
			--m;
			 
		}while(k==0);
				
}



void ConnectFour::gameEnded(char user){

	checkFour(user);
	int beraber=draw();
	if(beraber==column){
		cout<<"It's Draw...";
		gameEnd=true;
	}

	
	int control=checkFour(user);
	if(control==1){
		gameEnd=true;
		if(gameMod==1){
		
			if(user=='X'){	
				cout<<"Player 1 Won... "	;
			}
			else {
			cout<<"Player 2 Won... ";
			}
		}
		else{
			if(user=='X') cout<<"CONGRATULATION..! :) ";
			else cout<<"GAME OVER..! :/";
		}	
	}
}



int ConnectFour::checkFour(char Sign){								
	
		int i,j;
		int fourC=0;
		
				for(i=row-1; i>=0; i--){									
					for(j=column-1; j>=0; j--){

					if(gameBoard[i][j].user==Sign && gameBoard[i][j-1].user==Sign && gameBoard[i][j-2].user==Sign && gameBoard[i][j-3].user==Sign)	//4 tane X'in yan yana, alt alta ve iki çapraz sekilde,
						{fourC=1;}																			//gelmesini kontrol eden ve bu sartlar oluþtuðu takdirde,
																											//0 olan fourP1 deðerine 1 atayan fonksiyon.
					if(gameBoard[i][j].user==Sign && gameBoard[i-1][j].user==Sign && gameBoard[i-2][j].user==Sign && gameBoard[i-3][j].user==Sign)	//sonrasýnda da fourP1 deðerini return ediyor.
						{fourC=1;}

					if(gameBoard[i][j].user==Sign && gameBoard[i-1][j-1].user==Sign && gameBoard[i-2][j-2].user==Sign && gameBoard[i-3][j-3].user==Sign)
						{fourC=1;}
		
					if(gameBoard[i][j].user==Sign && gameBoard[i-1][j+1].user==Sign && gameBoard[i-2][j+2].user==Sign && gameBoard[i-3][j+3].user==Sign)
						{fourC=1;}
		}	
	
	}
	
	return fourC;
}



int ConnectFour::draw(){
	
	int f;
	int D=0;
	
	for(f=0; f<column; f++)
		{
			if(gameBoard[0][f].isempty==false )		//en üst satýrýn tüm sütunlarýna tek tek bakýp hiçbiri '.' deðilse berabere bittiðini söyleyen fonksiyon.
			++D;
			}
	return D;
}



void ConnectFour::showWinner(){
	
	int ctrl=0;
	int m, n;
				
				
				for(m=0; m<row; m++){
					for(n=0; n<column; n++){
						
						if(gameBoard[m][n].user=='X' && gameBoard[m][n-1].user=='X' && gameBoard[m][n-2].user=='X' && gameBoard[m][n-3].user=='X')	//4 tane 'X' yan yana geldiyse hepsini 'x' yap.
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
					for(n=0; n<column; n++){
						
						if(gameBoard[m][n].user=='O' && gameBoard[m][n-1].user=='O' && gameBoard[m][n-2].user=='O' && gameBoard[m][n-3].user=='O')	//4 tane 'O' yan yana geldiyse hepsini 'o' yap.
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



void ConnectFour::writeFile(){
	
	ofstream file;
	file.open("Connect4 Saved File.txt");
	file<<row<<endl;

	for(int m=0; m<row; m++){
		for(int n=0; n<column; n++){
			
			if(gameBoard[m][n].user!='X' && gameBoard[m][n].user!='O' && gameBoard[m][n].user!='x' && gameBoard[m][n].user!='o'){ 
			gameBoard[m][n].user='.'; 	
			}
			file<< gameBoard[m][n].user << " ";	
		}
			file<<endl;	}
			file<<endl;

	file.close();	
}
			
			
			
void ConnectFour::readFile(){
	std::ifstream file("Connect4 Saved File.txt",std::ifstream::in); 	
	
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

int ConnectFour::controlsize() {
   
   std::ifstream loadsize("Connect4 Saved File.txt",std::ifstream::in);
 //  int row;
   loadsize>>column;
   return column;	
}


bool operator ==(const ConnectFour& game1, const ConnectFour& game2){	//iki nesnenin x ve o'larýnýn yerlerini karþýlaþtýran fonksiyon
	if((game1.row==game2.row)&&(game1.column==game2.column)){	//game1 ve game2'nin row ve column'u aynýysa Cell'leri kontrol et 
		bool result=true;
		for(int i=0;i<game1.row; i++){
			for(int j=0;j<game1.column; j++){
				if(game1.gameBoard[i][j].user!=game2.gameBoard[i][j].user){	//herhangi iki Cell eþit olmazsa bile result false olur.
					result=false;
				}
			}
		}
	return result;	//result'ý return et
	}
	else return false;	//row ve column sayýlarý eþit deðilse false return et
}

ConnectFour::Cell ConnectFour::Cell::operator++(){
		if(user=='.') {user='X'; this->isempty=true;}	//empty->user1
		if(user=='O') {user='.'; this->isempty=false;}	//user2-> AI or user2-> empty
		if(user=='X') user='O';	//user-> user2 or user->AI
		return Cell(user);
}

ConnectFour::Cell ConnectFour::Cell::operator++(int ignore){
		char otherUser=user;
		if(user=='.') {user='X'; this->isempty=true;}	//empty->user1
		if(user=='X') user='O';	//user-> user2 or user->AI
		if(user=='O') {user='.'; this->isempty=false;}	//user2 or AI -> empty
		return Cell(otherUser);
}
		
ConnectFour::Cell ConnectFour::Cell::operator--(){
		if(user=='X') {user='.'; this->isempty=false;}	
		if(user=='O') user='X';	//user2->user
		if(user=='.') {user='O'; this->isempty=true;}
		return Cell(user);
}
				
ConnectFour::Cell ConnectFour::Cell::operator--(int ignore){
		char otherUser=user;
		if(user=='X') {user='.'; this->isempty=false;}	//user-> empty
		if(user=='O') user='X';		//user2->user
		if(user=='.') {user='O'; this->isempty=true;}	//user2 or AI -> empty
		return Cell(otherUser);	
}

