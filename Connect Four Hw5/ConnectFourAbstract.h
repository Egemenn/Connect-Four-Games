#include<string>
#include "string.h"
#include <iostream>
#include <vector>
#include"Cell.h"
#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H
using namespace std;
namespace egemen
{

class ConnectFourAbstract{
	
	protected: 
		
		int row;
		int column;
		vector<int>Record;
		char modChoice;//plus, diyagonal veya undo modunu se�en P, D veya U olan oyun modu
		char gameMod;//playertoPlayer veya playertoComputer modunu se�en, P veya C olan oyun modu
		char user;//s�ra hangi kullan�c�daysa onun imzasini X veya O �eklinde b�rakan de�er
		bool gameEnd=false;//gameEnd false olarak baslattik, ��nk� o true olunca oyun bitecek	
		Cell** gameBoard;//
		void showBoard();//tahtan�n son halini yazd�ran fonksiyon
		void play();//bilgisayarin play fonksiyonu, parametre almiyor
		int play(int &ch, char Sign);//kullanicilarin play fonksiyonu. Cell position'i parametre olarak aliyor.
		virtual int move();//hamleyi kullan�c�dan alan fonksiyon. 
		void makeMoveAI();//bilgisayar�n hamle yaptigi fonksiyon
		virtual int checkFour(char Sign);//dortlu olup olmadigini kontrol eden fonksiyon
		void gameEnded(char user);//oyunun bitip bitmedigini kontrol eden, oyun bitttiyse gameEnd'i true yapan fonksiyon
		int draw();//beraberligi kontrol eden fonksiyon. butun sutunlar doluysa erabere bitmistir.
		void chooseGameMod();//PtoP ve PtoC modlarini soran fonksiyon
		void setRow();//kullan�c�dan Row size'i alan fonksiyon	
		void setColumn();//kullanicidan Column size'i alan fonksiyon
		void playertoPlayer();//playerToPlayer modunun oynandigi fonksiyon. icinde move, play ve gameEnded'i bar�nd�r�yor
		void playertoComputer();//playerToComputer modunun oynandigi fonksiyon
		virtual void readFile(string fileName);
		virtual void writeFile(string fileName);
		int currentWidth();//son column degerini tutan fonksiyon
		int currentHeight();//son row degerini tutan fonksiyon
		virtual void showWinner();
		virtual void undoGame();
		
	public:
		void playGame();//i�erisinde oyunun oynandigi, play fonksiyonlarini barindiran, kullanicidan row ve columnsize'lar alan fonk.
};
}
#endif
