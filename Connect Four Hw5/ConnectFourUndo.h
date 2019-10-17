#ifndef CONNECTFOURUNDO_H
#define CONNECTFOURUNDO_H
#include"ConnectFourPlus.h"
#include <vector>
#include <string>
namespace egemen
{
	
class ConnectFourUndo:public ConnectFourPlus{
	
	public:	
		int undo=0;
		int checkFour(char Sign);
		//void writeFile(string fileName);
		//void readFile(string fileName);
		int move(); 
		void undoGame();
		
};
}
#endif
