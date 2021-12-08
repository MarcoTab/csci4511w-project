#ifndef DLX_H
#define DLX_H

#include <string>

class ColumnObject {
	public:
		int s;

		ColumnObject(int s);
};

class DataObject {
	public:
		ColumnObject *c;
		std::string id;
		DataObject *u;
		DataObject *d;
		DataObject *l;
		DataObject *r;

		DataObject(ColumnObject *c, std::string id);
};

class Dlx {
	public:
		ColumnObject *h;
};

#endif //end DLX_H header guard
