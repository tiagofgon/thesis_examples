#include <hpx/hpx.hpp>
#include "container.hpp"


template <typename T>
class Queue: public hpx::components::abstract_migration_support< hpx::components::component_base<Queue<T>>, Container >
{

public:
    using base_type = hpx::components::abstract_migration_support<
        hpx::components::component_base<Queue<T>>, Container >;

    typedef typename hpx::components::component_base<Queue<T>>::wrapping_type wrapping_type;
    typedef Queue type_holder;
    typedef Container base_type_holder;

    Queue() = default;
    ~Queue() = default;
    
    Queue(int id) : base_type(id) {}
    
    // Components which should be migrated using hpx::migrate<> need to
    // be Serializable and CopyConstructable. Components can be
    // MoveConstructable in which case the serialized data is moved into the
    // component's constructor.

    Queue(Queue && rhs) :
        base_type(std::move(rhs)), 
        _fifo(std::move(rhs._fifo))
    {}

    Queue& operator=(Queue && rhs)
    {
        this->Container::operator=(std::move(static_cast<Container&>(rhs)));
        _fifo = rhs._fifo;
        return *this;
    }

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

    template <typename Archive>
    void serialize(Archive& ar, unsigned version)
    {
        ar & hpx::serialization::base_object<Container>(*this);
        ar & _fifo;
    }

private:
    std::vector<T> _fifo;
};


#define REGISTER_QUEUE_DECLARATION(type)                  \
    HPX_REGISTER_ACTION_DECLARATION(                        \
        Queue<type>::Pop_action_Queue,                  \
        HPX_PP_CAT(__Queue_Pop_action_Queue_, type));   \
    HPX_REGISTER_ACTION_DECLARATION(                        \
        Queue<type>::Size_action_Queue,                 \
        HPX_PP_CAT(__Queue_Size_action_Queue_, type));  \

#define REGISTER_QUEUE(type)                              \
    HPX_REGISTER_ACTION(                                    \
        Queue<type>::Pop_action_Queue,                  \
        HPX_PP_CAT(__Queue_Pop_action_Queue_, type));   \
    HPX_REGISTER_ACTION(                                    \
        Queue<type>::Size_action_Queue,                 \
        HPX_PP_CAT(__Queue_Size_action_Queue_, type));  \
    typedef ::hpx::components::component<Queue<type>>     \
        HPX_PP_CAT(__Queue_type, type);                   \
    typedef Queue<type>                                   \
        HPX_PP_CAT(__Queue_, type);                       \
    HPX_REGISTER_DERIVED_COMPONENT_FACTORY(HPX_PP_CAT(__Queue_type, type), HPX_PP_CAT(__Queue_, type), "Container")
    