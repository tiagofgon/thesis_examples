#include "queue.hpp"
#include <hpx/hpx.hpp>


class Queue_Client: hpx::components::client_base<Queue_Client, Queue>
{
public:
    typedef hpx::components::client_base<Queue_Client, Queue> base_type;
	Queue_Client() : base_type(hpx::local_new<Queue>())
	{}
	Queue_Client(hpx::id_type locality) : base_type(hpx::new_<Queue>(locality))
	{}

	template <typename ... Args>
	hpx::future<void> Push(Args&& ... args) {
		typedef Queue::Push_action_Queue<Args...> action_type;
		return hpx::async<action_type>(this->get_id(), std::forward<Args>(args)...);
	}

	hpx::future<int> Pop() {
		typedef Queue::Pop_action_Queue action_type;
		return hpx::async<action_type>(this->get_id());
	}
	
	hpx::future<size_t> Size() {
		typedef Queue::Size_action_Queue action_type;
		return hpx::async<action_type>(this->get_id());
	}
};
