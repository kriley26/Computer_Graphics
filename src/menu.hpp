
#include <chrono>
#include <thread>

using namespace std;

namespace cge {
	class Menu {

	private:
		uint32_t time;
		int x, y;
		int NUMOPTS;

	public:
		Menu();
		Menu(char* labels[]);
	};
}