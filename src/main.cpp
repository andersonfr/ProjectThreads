#include <string>
#include <thread>
#include <functional>
#include <vector>
#include "ProjectThreadsConfig.h"
#include "FileManager.h"

int main () 
{
    std::cout << "Project Major Version " << ProjectThreads_VERSION_MAJOR << std::endl;
    std::cout << "Project Minor Version " << ProjectThreads_VERSION_MINOR << std::endl;

    Threads::FileManager fm;
    fm.Start();

    return 0;
}