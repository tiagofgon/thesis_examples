#include "container.hpp"

int Container::GetId() const {
    return _id;
}

int Container::GetId_nonvirt() const {
    return GetId();
}


typedef Container Container;
HPX_DEFINE_GET_COMPONENT_TYPE(Container);

typedef Container::GetId_action_Container GetId_action_Container;
HPX_REGISTER_ACTION(GetId_action_Container);