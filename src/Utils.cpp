#include "../include/Utils.h"

namespace Utils {
	int MSK(int x, int y) {
		return 8 * x + y;
	}
	std::pair<int, int> UNMSK(int n) {
		return {n / 8, n % 8};
	}
}
