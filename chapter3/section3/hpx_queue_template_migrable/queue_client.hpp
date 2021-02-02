#include "queue.hpp"
#include <hpx/hpx.hpp>


template <typename T>
class Queue_Client: hpx::components::client_base<Queue_Client<T>, Queue<T>>
{
public:
	friend class hpx::serialization::access;
    typedef hpx::components::client_base<Queue_Client<T>, Queue<T>> base_type;

	Queue_Client() : base_type(hpx::local_new<Queue<T>>())
	{}
	Queue_Client(hpx::id_type locality) : base_type(hpx::new_<Queue<T>>(locality))
	{}

	template <typename ... Args>
	hpx::future<void> Push(Args ... args)
	{
		typedef typename Queue<T>::template Push_action_Queue<Args...> action_type;
		return hpx::async<action_type>(this->get_id(), args...);
	}

	hpx::future<T> Pop() {
		typedef typename Queue<T>::Pop_action_Queue action_type;
		return hpx::async<action_type>(this->get_id());
	}
	
	hpx::future<size_t> Size() {
		typedef typename Queue<T>::Size_action_Queue action_type;
		return hpx::async<action_type>(this->get_id());
	}

	hpx::id_type get_gid() {
		return this->get_id();
	}
};
