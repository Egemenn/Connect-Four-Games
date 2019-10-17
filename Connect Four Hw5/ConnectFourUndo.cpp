#include"ConnectFourUndo.h"
#include"Cell.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
namespace egemen{


void ConnectFourUndo::undoGame(){	//undo oynayan fonksiyon
	
	int m=0, undoControl=0;
	int UR=Record[Record.size()-1];	//UR'ye vektorun uzunlugu-1 sayisini atadýk. bunu asagida kullanacagiz
	do{
		if(gameBoard[m][UR].isempty==false){ 
			gameBoard[m][UR].user=='*';
			gameBoard[m][UR].isempty=true;
			undoControl=1;
		}
		m++;
	}while(undoControl==0);
	
	Record.pop_back();	//vektorun son elemanýný cýkardýk. vektorumuzun uzunlugu bir kisalmis oldu 
	
}
	

int ConnectFourUndo::move(){
	char move;
	int ch=-1;	//compiler'ýn kendisi bir integer atayýp hata vermemesi için ch'ye -1 atadýk
	string fileName;
	string choice;
	string input;	
		
	do{
		cout<< "\nChoose a column \n";
		cin>>choice;
		getline(cin,input);
			if(cin.eof()){
				cerr<<endl<<"ERROR: cin eof"<<endl;
				exit(1);
			}
		string parsing(input);
		string firstEmpty=" ";
		fileName=parsing.substr(parsing.find_first_of(firstEmpty)+1);
			
			if(choice=="SAVE"){
				cout<<"Game Saved"<<endl;
				writeFile(fileName);
				undo=0;
			}
			
			else if(choice=="LOAD"){
				cout<<"LOADING GAME"<<endl;
				readFile(fileName);
				showBoard();
				undo=-1;
				ch=0;
			}
			
			else if(choice=="UNDO"){
				cout<<"Move is back";	
				undoGame();
				showBoard();
				undo=-1;
				ch=0;//whiledan çýkmasý için ch'ye 0 atadýk, zaten return etmiyoruz
			}
			
			else if(choice.length()==1)
			{
				move=choice[0];
				ch= move-'A';
				undo=0;
					if(gameBoard[0][ch].isempty==false){
						cerr<<"This column is full, choose an other column.";
						ch=-1;
					}
					else if(ch>column){
						cerr<<"There is no column that!";
						ch=-1;	
					}
			
			}
		
	}while(ch<0||ch>column);
	
		if(undo!=-1){	//eger undo -1 degilse ch'yi return et
			Record.push_back(ch);	
			return ch;
		}
	else return undo;	//undo -1 ise undoyu return et. bunu C.F.abstract'te play fonksiyonunda kullanýyoruz
}


int ConnectFourUndo::checkFour(char Sign){								
	
		int i,j;
		int fourC=0;
		
				for(i=row-1; i>=0; i--){									
					for(j=column-1; j>=0; j--){


					if(	gameBoard[i][j].user==Sign && 
						gameBoard[i][j-1].user==Sign && 
						gameBoard[i][j-2].user==Sign && 
						gameBoard[i][j-3].user==Sign)	
						{fourC=1;}																		
																											
					if(	gameBoard[i][j].user==Sign && 
						gameBoard[i-1][j].user==Sign && 
						gameBoard[i-2][j].user==Sign && 
						gameBoard[i-3][j].user==Sign)	
						{fourC=1;}
		}
	}
	return fourC;
}

/*void ConnectFourUndo::writeFile(string fileName){
	
	ofstream file;
	file.open(fileName.c_str());

	for(int m=0; m<row; m++){
		for(int n=0; n<column; n++){
			
			if(gameBoard[m][n].user!='X' && gameBoard[m][n].user!='O' && gameBoard[m][n].user!='x' && gameBoard[m][n].user!='o'){ 
			gameBoard[m][n].user='*'; 	
			}
			file<<gameBoard[m][n].user << " ";	
		}
			file<<endl;	}
			file<<endl;

	file.close();	
}


void ConnectFourUndo::readFile(string fileName){
	std::ifstream file(fileName.c_str(),std::ifstream::in); 	
	
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
*/

}
