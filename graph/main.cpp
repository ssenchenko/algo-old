#include <iostream>
#include "myutil.h"
#include "tests.h"

using std::cout;
using std::endl;

int main() {
	cout << "1 - detection of strong components" << endl;
	cout << "2 - Dijkstra shortest path" << endl;
	cout << "3 - Prim's minimum spanning tree algorithm" << endl;
	cout << "4 - Kruskal's minimum spanning tree algorithm" << endl;
	cout << "5 - Clustering algorithm based on Kruskal's mst" << endl;
	cout << "6 - Bellman-Ford shortest path" << endl;
	cout << "7 - All-pair shortest path" << endl;
	cout << "Choose a test to run: ";

	int test = getInteger();

	switch (test) {
		case 1:
			c2w1_ssc();
			break;
		case 2:
			c2w2_dijkstra_sp();
			break;
		case 3:
			c3w1_prim_mst();
			break;
		case 4:
			c3w2_kruskal_mst();
			break;
		case 5:
			c3w2_kruskal_clustering();
			break;
		case 6:
			c4w1_bellman_ford_sp();
			break;
		case 7:
			c4w1_floyd_warshall_sp();
			break;
		default:
			cout << "Sorry, not a valid option. Bye..." << endl;
	}

	return 0;
}