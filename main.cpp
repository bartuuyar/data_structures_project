#include "ds.h"


int main() {
	DSList S;
	S.loadFile("input.txt");
	S.printByName();
	S.printByAge();
	S.saveToFileByAge("ext.txt");
}
