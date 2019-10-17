#include <iostream>
#ifndef CELL_H
#define CELL_H

namespace egemen
{
	
	
class Cell{
	private:
		int row;
		char column;
	public:
		char user;
		bool isempty=true;	//Cell'in bos olup olmadigi bilgisini tutacak, default olarak true olacak.
		void setRow(int inputRow); //kullanicidan row size'i alan fonksiyon
		void setColumn(int inputColumn);//kullanicidan column size'i alan fonksiyon
};
}
#endif
