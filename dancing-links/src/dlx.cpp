#include "dlx.h"

ColumnObject::ColumnObject(int s) {
	this->s = s;
}

DataObject::DataObject(ColumnObject *c, std::string id) {
	this->c = c;
	this->id = id;
}
