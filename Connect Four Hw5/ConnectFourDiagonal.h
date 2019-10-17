#include"ConnectFourAbstract.h"
#ifndef CONNECTFOURDIAGONAL_H
#define CONNECTFOURDIAGONAL_H
using namespace std;

namespace egemen
{

class ConnectFourDiagonal:public ConnectFourAbstract{
	
	public:
		ConnectFourDiagonal();
		void showBoard();	
		int checkFour(char Sign);	
		void showWinner();
};
}
#endif
