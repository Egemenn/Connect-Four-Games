//Egemen ÇAÐÞIRLI
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class ConnectFour
{
	private:
		class Cell{
			private:
				int row;			
				char column;
				
			public:
				char user;
				bool isempty=true;
								
				
	};
			int gameMod;
			int row;
			int column;
			vector< vector<Cell>>gameCells;
			
	public:
			const int getRow();	//satiri input alan fonksiyon
			const int getColumn();	//sütunu input alan fonksiyon
			void setRow(int inputRow);	//satiri döndüren fonksiyon
			void setColumn(int inputColumn);	//sütunu döndüren fonksiyon
			void readFile();	//writefile fonksiyonu
			void writeFile();	//readfile fonksiyonu
			int currentWidth();
			int currentHeight();
			void showCurrentBoard();	//tabloyu gösteren fonksiyon
			void playGame(); //ask board size in it
			void getLivingCell(); //hamleyi sayan livingCell fonksiyonu
			inline int play(char Sign);	//inline'i çok kullanilan bir fonksiyonda kullandim, programi hizlandirmak için
			void play();	//computer için play fonksiyonu
			void makeMoveAI();	//computer'i hareket ettiren fonksiyon
			void gameEnded(char user);	//oyunun bitip bitmediðini kontrol eden fonksiyon
			int checkFour(char user);	//dört tane yan yana, üst üste veya çapraz gelip gelmedigini kontrol eden fonksiyon
			int draw();	//beraberliði kontrol eden fonksiyon
			void showWinner();	//4 tane yan yana gelen X ve O'lari küçülten fonksiyon
			static void numberLivingCell();
			bool gameEnd=false;	
			int controlsize();	
			ConnectFour();	//constructor fonksiyon
			ConnectFour(int x);	//1 parametre alan constructor fonksiyon
			ConnectFour(int x, int y);	//2 parametre alan constructor fonksiyon 
};			int numberLivingCells=0;



int main(){
	
	ConnectFour game1;
	ConnectFour game2(1);
	ConnectFour game3(4,6);
	game1.playGame();
	
	
	
		
}


ConnectFour::ConnectFour(){
	cout<<"Wellcome to the Connect Four Game"<<endl<<endl;
}


ConnectFour::ConnectFour(int x){	//gameMod'u 1 alan constructor fonksiyon
		gameMod==1;
}


ConnectFour::ConnectFour(int x, int y){		//row'u 4 ve column'u 6 alan constructor fonkiyon
		row=4;
		column=6;
}




void ConnectFour::setRow(int inputRow){
		row=inputRow;
}

void ConnectFour::setColumn(int inputColumn){
		column=inputColumn;
}

const int ConnectFour::getRow(){
		cout<<"Enter the Row Size..:";
		cin>>row;
		return row;
}

const int ConnectFour::getColumn(){
		cout<<"Enter the Column Size..:";
		cin>>column;
		return column;
}

int ConnectFour::currentWidth(){	//en son durumdaki sütunu tutan fonksiyon
	return column;
}

int ConnectFour::currentHeight(){	//en son durumdaki satýrý tutan fonksiyon
	return row;
}

void ConnectFour::getLivingCell(){	//oyundaki hamle sayýsýný tutan static fonksiyon
	
	int m,n;
	for(m=0; m<row; m++){
		for(n=0; n<column; n++){
			if(gameCells[m][n].isempty==false)
			numberLivingCells++;
		}
	}
	
	
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
				if(gameCells[m][n].isempty==true){
					gameCells[m][n].user='.';
				}
				cout<<gameCells[m][n].user;
			}	
		cout<<endl;

		}	
}



void ConnectFour::playGame(){
	
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
	
		row=getRow();
		setRow(row);
		column=getColumn();
		setColumn(column);
		
		gameCells.resize(row);
		for(int m=0; m<row; m++){
			gameCells[m].resize(column);
			}
	
		showCurrentBoard();
		}
		if(gameMod==1){								//PLAYER TO PLAYER KISMI BURADA
					while(1){
					int s=play('X');				//PLAYER 1'ÝN HAMLE YAPTIÐI FONK.
						if(s==1){									
								writeFile();		//DOSYAYI KAYDEDEN FONK.
								play('X');
						}
					showCurrentBoard();	
					gameEnded('X');
					
						if(gameEnd==true){			//GAME END FONK. TRUE ÝSE OYUNU BÝTÝR
							showWinner();
							showCurrentBoard();
							break;
						}
					int s2=play('O');				//PLAYER 2'NÝN HAMLE YAPTIÐI FONK.
					if(s2==1){
							writeFile();			//DOSYAYI KAYDEDEN FONK.
							play('O');
					}
					showCurrentBoard();
					gameEnded('O');					//GAME END FONK. TRUE ÝSE OYUNU BÝTÝR.
						if(gameEnd==true){
							showWinner();
							showCurrentBoard();
							break;
						} 	
					}
		}

		if(gameMod==2){								//PLAYER TO COMPUTER KISMI BURADA
					while(1){
					int s=play('X');				//PLAYER 1'ÝN HAMLE YAPTIÐI FONK.
							if(s==1){									
								writeFile();		//DOSYAYI KAYDEDEN FONK.
								play('X');
							}
					showCurrentBoard();
					gameEnded('X');
						if(gameEnd==true){
							showWinner();
							showCurrentBoard();
							break;
						}
					play();
					showCurrentBoard();					
					gameEnded('O');
						if(gameEnd==true){
							showWinner();
							showCurrentBoard();
							break;
						}
					}
		}	
}



inline int ConnectFour::play(char Sign){
			
			int save=0;	
			int ctrl=0;
			int ch;
			char choice;
			int realRow=row;
		
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

					if(gameCells[0][ch].isempty==false)
						{cerr<< "\nBu sutun dolu, sira diger oyuncuda..." << endl <<endl;//HATA YAPAN KISMI CERR ILE
						}
					else{	
						do{
						if(gameCells[row-1][ch].user=='.')	
						{	
						gameCells[row-1][ch].user=Sign; 	
						gameCells[row-1][ch].isempty=false;
						ctrl=1;
						}
						else --row;	

						}while(ctrl==0);
					}
			}		
				
			else{ 	save=0;  
					ch= choice-'A';
					if(gameCells[0][ch].isempty==false)
						{cerr<< "\nBu sutun dolu, sira diger oyuncuda..." << endl <<endl;	}	//eðer player 		//1 dolu olan sütuna giriþ yaparsa sýra player 2'ye geçer.
					else{	
						do{
						if(gameCells[row-1][ch].user=='.')//girilen satýr ve tablodaki en alt sütuna 'X' yazdýran. 
						{	
						gameCells[row-1][ch].user= Sign; 	
						gameCells[row-1][ch].isempty=false;			  
						ctrl=1;
						}
						else --row;//en alt doluysa boyutu döngüye sokup birer azaltarak üsttekilere bakiyor

						}while(ctrl==0);
					}
			}
			row=realRow;	//--row dediðimizde row sayýsýný azalttýðý için row'u tekrar orjinal sayýsýna eþitledim
	return save;
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
			if(gameCells[0][AI].isempty==false)
			{
				do{	
				AI=rand()%column;
				if(gameCells[0][AI].isempty==true)
				ktrl=1;
				}while(ktrl==0);
			}
		do{
		if(gameCells[m][AI].isempty==true){
				gameCells[m][AI].user='O';
			gameCells[m][AI].isempty=false;
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

					if(gameCells[i][j].user==Sign && gameCells[i][j-1].user==Sign && gameCells[i][j-2].user==Sign && gameCells[i][j-3].user==Sign)	//4 tane X'in yan yana, alt alta ve iki çapraz sekilde,
						{fourC=1;}																			//gelmesini kontrol eden ve bu sartlar oluþtuðu takdirde,
																											//0 olan fourP1 deðerine 1 atayan fonksiyon.
					if(gameCells[i][j].user==Sign && gameCells[i-1][j].user==Sign && gameCells[i-2][j].user==Sign && gameCells[i-3][j].user==Sign)	//sonrasýnda da fourP1 deðerini return ediyor.
						{fourC=1;}

					if(gameCells[i][j].user==Sign && gameCells[i-1][j-1].user==Sign && gameCells[i-2][j-2].user==Sign && gameCells[i-3][j-3].user==Sign)
						{fourC=1;}
		
					if(gameCells[i][j].user==Sign && gameCells[i-1][j+1].user==Sign && gameCells[i-2][j+2].user==Sign && gameCells[i-3][j+3].user==Sign)
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
			if(gameCells[0][f].user!='.' )		//en üst satýrýn tüm sütunlarýna tek tek bakýp hiçbiri '.' deðilse berabere bittiðini söyleyen fonksiyon.
			++D;
			}
	return D;
}



void ConnectFour::showWinner(){
	
	int ctrl=0;
	int m, n;
				
				
				for(m=0; m<row; m++){
					for(n=0; n<column; n++){
						
						if(gameCells[m][n].user=='X' && gameCells[m][n-1].user=='X' && gameCells[m][n-2].user=='X' && gameCells[m][n-3].user=='X')	//4 tane 'X' yan yana geldiyse hepsini 'x' yap.
					  	  {gameCells[m][n].user= 'x',   gameCells[m][n-1].user= 'x',   gameCells[m][n-2].user= 'x',   gameCells[m][n-3].user= 'x';
							ctrl=1;}
							
						if(gameCells[m][n].user=='X' && gameCells[m-1][n].user=='X' && gameCells[m-2][n].user=='X' && gameCells[m-3][n].user=='X')
					      {gameCells[m][n].user= 'x',   gameCells[m-1][n].user= 'x',   gameCells[m-2][n].user= 'x',   gameCells[m-3][n].user= 'x';
						  	ctrl=1;}		
					
						if(gameCells[m][n].user=='X' && gameCells[m-1][n-1].user=='X' && gameCells[m-2][n-2].user=='X' && gameCells[m-3][n-3].user=='X')
						  {gameCells[m][n].user= 'x',   gameCells[m-1][n-1].user= 'x',   gameCells[m-2][n-2].user= 'x',   gameCells[m-3][n-3].user= 'x';
						  	ctrl=1;}
					
						if(gameCells[m][n].user=='X' && gameCells[m+1][n-1].user=='X' && gameCells[m+2][n-2].user=='X' && gameCells[m+3][n-3].user=='X')
						  {gameCells[m][n].user= 'x',   gameCells[m+1][n-1].user= 'x',   gameCells[m+2][n-2].user= 'x',   gameCells[m+3][n-3].user= 'x';
						  	ctrl=1;}
	
					}
				}
	
		if(ctrl==0){
	
				for(m=0; m<row; m++){
					for(n=0; n<column; n++){
						
						if(gameCells[m][n].user=='O' && gameCells[m][n-1].user=='O' && gameCells[m][n-2].user=='O' && gameCells[m][n-3].user=='O')	//4 tane 'O' yan yana geldiyse hepsini 'o' yap.
					  	  {gameCells[m][n].user= 'o',   gameCells[m][n-1].user= 'o',  gameCells[m][n-2].user= 'o',    gameCells[m][n-3].user= 'o';}
							
						if(gameCells[m][n].user=='O' && gameCells[m-1][n].user=='O' && gameCells[m-2][n].user=='O' && gameCells[m-3][n].user=='O')
						  {gameCells[m][n].user= 'o',   gameCells[m-1][n].user= 'o',   gameCells[m-2][n].user= 'o',   gameCells[m-3][n].user= 'o';}
					
						if(gameCells[m][n].user=='O' && gameCells[m-1][n-1].user=='O' && gameCells[m-2][n-2].user=='O' && gameCells[m-3][n-3].user=='O')
						  {gameCells[m][n].user= 'o',   gameCells[m-1][n-1].user= 'o',   gameCells[m-2][n-2].user= 'o',   gameCells[m-3][n-3].user= 'o';}
					
						if(gameCells[m][n].user=='O' && gameCells[m+1][n-1].user=='O' && gameCells[m+2][n-2].user=='O' && gameCells[m+3][n+3].user=='O')
						  {gameCells[m][n].user= 'o',   gameCells[m+1][n-1].user= 'o',   gameCells[m+2][n-2].user= 'o',   gameCells[m+3][n+3].user= 'o';}
					
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
			
			if(gameCells[m][n].user!='X' && gameCells[m][n].user!='O' && gameCells[m][n].user!='x' && gameCells[m][n].user!='o'){ 
			gameCells[m][n].user='.'; 	
			}
			file<< gameCells[m][n].user << " ";	
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
			gameCells[i][j].user=a;	
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
