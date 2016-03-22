#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "Elimination.h"
#include "Rndm.h"

using namespace std;

Elimination::Elimination() : _votes(MAX_VOTES), _turn(0)
{
}

void Elimination::load()
{
	ifstream file(_filename.c_str());
	if (file.is_open() && file.good()) {

		int i = 0;
		string line;
		while (getline(file, line)) {

			// sloppy trim
			line.erase(line.find_last_not_of(" \n\r\t") + 1);
			_names[++i] = line;
		}
		file.close();
	}
}
	
void Elimination::list()
{
	auto it = _names.begin();
	while (it != _names.end()) {
		cout << (*it).second << endl;
		it++;
	}
}

void Elimination::print(string *pbuf, string *mbuf)
{
	// Print out current score.
	cout << "Turn " << setw(3) << setfill(' ') << _turn << " " << setfill('-') << setw(38) << "" << endl;

	if (pbuf && !pbuf->empty()) {
		cout << *pbuf << endl;
	}
	if (mbuf && !mbuf->empty()) {
		cout << *mbuf << endl;
	}
	cout << endl;	

	auto scit = _points.begin();
	while (scit != _points.end()) {
		if (_points.size() == 1) {
			cout << "Winner: " << endl;
		}
		cout << left << setfill(' ') << setw(34) << scit->first << " [" << scit->second << "]" << endl;
		scit++;
	}

	if (_elims.size() > 0) {
		cout << endl << "Eliminated:" << endl;

		auto nit = _elims.begin();
		while (nit != _elims.end()) {
			cout << right << setw(3) << setfill(' ') << (*nit).first << ". " << (*nit).second << endl;
			nit++;
		}
	}
	cout << endl;	
}
	
void Elimination::sim()
{
	// Build the points for each story
	auto it = _names.begin();
	while (it != _names.end()) {
		_points.insert(make_pair((*it).second, _votes));
		it++;
	}
		
	while (_points.size() > 1) {
		++_turn;
	
		string pbuf, mbuf;
		int plus = Rndm::number(1, _points.size());
		int minus = plus;
		while (minus == plus) {
			minus = Rndm::number(1, _points.size());
		}

		stringstream ss;			
		auto pit = _points.begin();

		// Adjust the plus story
		advance(pit, plus - 1);
		pit->second += UP_VOTE;
		ss << pit->first << " [" << pit->second << "] " << UP_VOTE;
		pbuf = ss.str();
			
		pit = _points.begin();
		// Adjust the minus story
		advance(pit, minus - 1);
		pit->second += DOWN_VOTE;
		ss.str(string()); // reset
		ss << pit->first << " [" << pit->second << "] " << DOWN_VOTE;
		mbuf = ss.str();
			
		// Was minus story eliminated?
		if (pit->second <= 0) {
			_elims.insert(make_pair(_names.size() - _elims.size(), pit->first));
			_points.erase(pit);
			pit = _points.begin();
		}

		print(&pbuf, &mbuf);
// getline (cin, pbuf);
	}
}
