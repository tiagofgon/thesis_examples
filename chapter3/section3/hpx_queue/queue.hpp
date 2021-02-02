#include <hpx/hpx.hpp>


class Queue: public hpx::components::locking_hook< hpx::components::component_base<Queue> >
{
public:
    template <typename ... Args>
    void Push(Args&& ... args) {
        (_fifo.push_back(std::forward<Args>(args)), ...);
    }
    int Pop();
    size_t Size();

    HPX_DEFINE_COMPONENT_ACTION(Queue, Pop, Pop_action_Queue);
    HPX_DEFINE_COMPONENT_ACTION(Queue, Size, Size_action_Queue);

    template <typename ... Args>
    struct Push_action_Queue
    : hpx::actions::make_action<
        decltype(&Queue::Push<Args...>),
        &Queue::Push<Args...>
    >::type {};

private:
    std::vector<int> _fifo;
};

typedef Queue::Pop_action_Queue Pop_action_Queue;
typedef Queue::Size_action_Queue Size_action_Queue;
HPX_REGISTER_ACTION_DECLARATION(Pop_action_Queue);
HPX_REGISTER_ACTION_DECLARATION(Size_action_Queue);