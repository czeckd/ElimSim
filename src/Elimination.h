#ifndef __ELIMINATION_H__
#define __ELIMINATION_H__

#include <string>
#include <map>


class Elimination
{
typedef std::map<int, std::string, std::less<int> > names;
typedef std::map<std::string, int, std::less<std::string> > points;

public:
	
	Elimination();

	void load();
	void list();
	void print(std::string *pbuf = NULL, std::string *mbuf = NULL);
	void sim();
	void psim();
	
	inline void setFilename(std::string filename) {
		_filename = filename;
	}


private:
	void initPoints();


	static const int MAX_VOTES = 20;
	static const int UP_VOTE = 1;
	static const int DOWN_VOTE = -2;

	int          _votes;
	int          _turn;

	std::string  _filename;
	names        _names;
	points       _points;
	names        _elims;
};

#endif // __ELIMINATION_H__
