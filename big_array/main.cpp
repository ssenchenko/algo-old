#include "tests.hpp"
#include "myutil.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	cout << "1 - Count number of inversions in array" << endl;
	cout << "2 - Quick sort" << endl;
	cout << "Choose a test to run: ";

	int test = getInteger();

	switch (test) {
		case 1:
			c1w2_inversions();
			break;
		case 2:
			c1w3_quickSort();
			break;
		default:
			cout << "Sorry, not a valid option. Bye..." << endl;
	}

	return 0;
}