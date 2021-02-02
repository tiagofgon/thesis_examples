#include <hpx/hpx.hpp>


template <typename T>
class Queue: public hpx::components::locking_hook< hpx::components::component_base<Queue<T>> >
{
public:
    template <typename ... Args>
    void Push(Args ... args) {
        (_fifo.push_back(args), ...);
    }

    T Pop() {
        T element = _fifo.front();
        _fifo.erase(_fifo.begin());
        return element;
    }

    size_t Size() {
        return _fifo.size();
    }

    HPX_DEFINE_COMPONENT_ACTION(Queue, Pop, Pop_action_Queue);
    HPX_DEFINE_COMPONENT_ACTION(Queue, Size, Size_action_Queue);

    template <typename ... Args>
    struct Push_action_Queue
    : hpx::actions::make_action<
        decltype(&Queue::Push<Args...>),
        &Queue::Push<Args...>
    >::type {};
    
private:
    std::vector<T> _fifo;
};

#define REGISTER_QUEUE_DECLARATION(type)                  \
    HPX_REGISTER_ACTION_DECLARATION(                      \
        Queue<type>::Pop_action_Queue,                    \
        HPX_PP_CAT(__Queue_Pop_action_Queue_, type));     \
    HPX_REGISTER_ACTION_DECLARATION(                      \
        Queue<type>::Size_action_Queue,                   \
        HPX_PP_CAT(__Queue_Size_action_Queue_, type));
/**/

#define REGISTER_QUEUE(type)                              \
    HPX_REGISTER_ACTION(                                  \
        Queue<type>::Pop_action_Queue,                    \
        HPX_PP_CAT(__Queue_Pop_action_Queue_, type));     \
    HPX_REGISTER_ACTION(                                  \
        Queue<type>::Size_action_Queue,                   \
        HPX_PP_CAT(__Queue_Size_action_Queue_, type));    \
    typedef ::hpx::components::component< Queue<type> > HPX_PP_CAT(__Queue_, type); \
    HPX_REGISTER_COMPONENT(HPX_PP_CAT(__Queue_, type))
/**/