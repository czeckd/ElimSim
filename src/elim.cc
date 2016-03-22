#include <string>
#include <map>

#include <iostream>
#include <iomanip>

#include "Elimination.h"
#include "Rndm.h"

using namespace std;

int main(int argc, char *argv[], char *envp[])
{
#if 0
	map<int, int, less<int>> x;

	for (int i = 0; i < 1000; i++) {
		int r = Rndm::number(1,6) + Rndm::number(1,6) + Rndm::number(1,6) ;
		
		auto f = x.find(r);
		if (f == x.end()) {
			x[r] = 1;
		} else {
			x[r]++;
		}
	}

	for (auto xm : x) {
		cout << setw(2) << xm.first << " " << xm.second << endl;
	}

exit(0);
#endif

	if (argc > 1) {
		Elimination elim;
		
		elim.setFilename(argv[1]);
		elim.load();
		elim.sim();
	} else {
		cerr << "Usage: " << argv[0] << " datafile" << endl;
	}

	return 0;
}
