#include "queue.hpp"


int Queue::Pop() {
    int element = _fifo.front();
    _fifo.erase(_fifo.begin());
    return element;
}
size_t Queue::Size() {
    return _fifo.size();
}

typedef hpx::components::component<Queue> Queue_type;
HPX_REGISTER_COMPONENT(Queue_type, Queue);

typedef Queue::Pop_action_Queue Pop_action_Queue;
typedef Queue::Size_action_Queue Size_action_Queue;
HPX_REGISTER_ACTION(Pop_action_Queue);
HPX_REGISTER_ACTION(Size_action_Queue);