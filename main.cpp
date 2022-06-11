#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <filesystem>

std::string With {"/"};
std::string Goal {"main"};

namespace cpath = std::filesystem;

std::vector<cpath::path> Vec;

void Search(){
		cpath::directory_iterator end;
		cpath::directory_iterator it(With);

		for(it; it !=end; ++it){
				std::cout << it->path() << std::endl;
		}

}


int main(){
		std::thread th1(Search);
		std::thread th2(Search);
		std::thread th3(Search);

		Search();

		th1.join();
		th2.join();
		th3.join();
}
