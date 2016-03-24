#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>


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
		++it;
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
		++scit;
	}

	if (_elims.size() > 0) {
		cout << endl << "Eliminated:" << endl;

		auto nit = _elims.begin();
		while (nit != _elims.end()) {
			cout << right << setw(3) << setfill(' ') << (*nit).first << ". " << (*nit).second << endl;
			++nit;
		}
	}
	cout << endl;	
}

void Elimination::initPoints()
{
	// Build the points for each story
	auto it = _names.begin();
	while (it != _names.end()) {
		_points.insert(make_pair((*it).second, _votes));
		++it;
	}
}

/*	
 * Random voting.
 */
void Elimination::sim()
{
	initPoints();
		
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


/* 
 * Players have their own preferences, so set them and use their preferences
 * to drive how they vote.
 */
void Elimination::psim()
{
	initPoints();

	static const int MAX_PLAYERS = 8;
	vector<string> pref[MAX_PLAYERS];
	int p;

	// Set up players with a randomized preference order.
	for (p = 0; p < MAX_PLAYERS; ++p) {
		while (pref[p].size() < _names.size()) {
			int r = Rndm::number(1, _names.size());
			auto nit = _names.begin();
			advance(nit, r-1); // zero-based
			
			auto prit = find(pref[p].begin(), pref[p].end(), nit->second);
			if (prit == pref[p].end()) {
				pref[p].push_back(nit->second); 
			}
		}
	}	

#if 0
	// Print out players' voting prefs.
	for (p = 0; p < MAX_PLAYERS; ++p) {
		int i = 0;
		for (auto v : pref[p]) {
			cout << "P" << p << " " << setw(2) << ++i << " " << v << endl; 
		}
		cout <<"------" << endl;
	}
#endif

	string pbuf, mbuf;
	
	while (_points.size() > 1) {
		for (p = 0; p < MAX_PLAYERS; ++p) {
			if (_points.size() <= 1) {
				break;
			}

			cout << "Player " << p << endl;
			++_turn;

			// find plus story
			auto prit = pref[p].begin();
			while (prit != pref[p].end()) {
				auto pit = _points.find(*prit); 
				if (pit != _points.end()) {
					pit->second += UP_VOTE;
					stringstream ss;
					ss << pit->first << " [" << pit->second << "] " << UP_VOTE;
					pbuf = ss.str();
					break;
				}
				++prit;
			}

			// find minus story
			auto rrit = pref[p].rbegin();
			while (rrit != pref[p].rend()) {
				auto pit = _points.find(*rrit);
				if (pit != _points.end()) {
					pit->second += DOWN_VOTE;
					stringstream ss;
					ss << pit->first << " [" << pit->second << "] " << DOWN_VOTE;
					mbuf = ss.str();

					// Was minus story eliminated?
					if (pit->second <= 0) {
						_elims.insert(make_pair(_names.size() - _elims.size(), pit->first));
						_points.erase(pit);
						pit = _points.begin();
					}

					break;
				}
				++rrit;
			}

			print(&pbuf, &mbuf);
// getline (cin, pbuf);

		}

	}

	// Print out player's choice that matches winner.
	for (p = 0; p < MAX_PLAYERS; ++p) {
		auto prit = find(pref[p].begin(), pref[p].end(), (_points.begin())->first);
		int dist = distance(pref[p].begin(), prit);

		cout << "Player " << p << " choice " << dist + 1 << endl;
	}

}

