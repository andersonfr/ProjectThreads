#include <iostream>
#include <thread>
#include "ProjectThreadsConfig.h"

int main () 
{
    std::cout << "Hello World" << std::endl;
    std::cout << "Project Major Version " << ProjectThreads_VERSION_MAJOR << std::endl;
    std::cout << "Project Minor Version " << ProjectThreads_VERSION_MINOR << std::endl; 
    std::thread thread = std::thread([]() { std::cout << "I'm a thread" << std::endl;});
    thread.join();
    std::cout << "I'm main thread finalizing";
    return 0;
}