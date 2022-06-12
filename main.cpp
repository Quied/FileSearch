#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <filesystem>

std::string With {"/"};
std::string Goal {"main"};
bool success = false;
namespace cpath = std::filesystem;

std::vector<cpath::path> MainDirectory;
std::vector<std::vector<cpath::path>> Dirs;

void Search(std::vector<cpath::path> &PathVec){
  
    for(int i = 0; i < PathVec.size(); i++){
    cpath::recursive_directory_iterator it(PathVec[i],
					cpath::directory_options::skip_permission_denied);
    for(const cpath::directory_entry &dir : it){
		std::cout << dir.path() << std::endl;
        if(success == true) return;
        if(dir.path().filename() == Goal){
            std::cout << dir.path() << std::endl;
            success = true;
            return;
      }
    }
   }
}


int main(){

    [] {
        cpath::directory_iterator end;
        cpath::directory_iterator it(With);
        for(it; it != end; ++it){
            MainDirectory.push_back(it->path());
        }
        
        std::vector<cpath::path> Vec;
        size_t temp = MainDirectory.size() / 4;

        for(int k = 0; k < 3; k++){
        for(int i = 0; i < temp; i++){
        Vec.push_back(MainDirectory[i]);
        MainDirectory.erase(MainDirectory.begin());
          }
        Dirs.push_back(Vec);
        Vec.clear();
        }

        for(int i = 0; i < MainDirectory.size(); i++){
        Vec.push_back(MainDirectory[i]);
        }
        Dirs.push_back(Vec);
        Vec.clear();
        
    }();

    std::thread th1(Search, std::ref(Dirs[0]));
    std::thread th2(Search, std::ref(Dirs[1]));
    std::thread th3(Search, std::ref(Dirs[2]));

    Search(std::ref(Dirs[3]));

    th1.join();
    th2.join();
    th3.join();


}
