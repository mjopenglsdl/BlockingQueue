
#include "BlockingQueue.h"

#include <thread>

#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
    BlockingQueue<std::string> queue;

    // create another thread to insert items
    std::thread th([&queue]{
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // test item
        std::string one_item{"111"};

        // push
        queue.put(one_item);
    });


    // get
    cout<<"start getting item"<<endl;
    std::string the_item = queue.take();

    cout<<"the_item: "<<the_item<<endl;
    th.join();

return 0;
}