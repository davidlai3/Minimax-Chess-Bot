#ifndef UTILS_H
#define UTILS_H

#include <utility>

namespace Utils {
	// returns the index of the bit that position (x, y) refers to
	int MSK(int x, int y);
	// inverse of MSK
	std::pair<int, int> UNMSK(int n);
};

#endif
