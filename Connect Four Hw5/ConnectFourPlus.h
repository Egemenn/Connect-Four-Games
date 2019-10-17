#include"ConnectFourAbstract.h"
#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
using namespace std;

namespace egemen
{

class ConnectFourPlus:public ConnectFourAbstract{
	
	public:
		int checkFour(char Sign);	
		void showWinner();
};
}
#endif
