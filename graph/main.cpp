#include <iostream>
#include "myutil.h"
#include "tests.h"

using std::cout;
using std::endl;

int main() {
	cout << "1 - detection of strong components" << endl;
	cout << "2 - Dijkstra shortest path" << endl;
	cout << "3 - Prim's minimum spanning tree algorithm" << endl;
	cout << "Choose a test to run: ";

	int test = getInteger();

	switch (test) {
		case 1:
			runTest_c2w1();
			break;
		case 2:
			runTest_c2w2();
			break;
		case 3:
			runTest_c3w1();
			break;
		default:
			cout << "Sorry, not a valid option. Bye..." << endl;
	}

	return 0;
}