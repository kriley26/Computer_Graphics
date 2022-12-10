#include <chrono>
#include <thread>
#include <iostream>

#include "src/menu.hpp"

using namespace std;

namespace cge {

	Menu::Menu() {
		NUMOPTS = 0;
	}

	Menu::Menu(char* labels[]) {
		NUMOPTS = sizeof(&labels);
		cout << NUMOPTS << endl;
		cout << labels << endl;
	}


}
