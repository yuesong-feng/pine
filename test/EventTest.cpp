#include "EventLoop.h"
#include <memory>

int main() {
    std::unique_ptr<EventLoop> loop;
    
    loop->Loop();
    return 0;
}