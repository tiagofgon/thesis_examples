#include <hpx/hpx.hpp>


class Container: public hpx::components::abstract_base_migration_support< hpx::components::abstract_component_base<Container> >
{

public:
    typedef hpx::components::abstract_base_migration_support< hpx::components::abstract_component_base<Container> > base_type;

    Container(int id = 42) :
        _id(id)
    {}

    virtual ~Container() = default;;
    
    Container(Container const& rhs)
      : base_type(rhs), _id(rhs._id)
    {}

    Container(Container && rhs)
      : base_type(std::move(rhs)), _id(rhs._id)
    {}

    Container& operator=(Container const & rhs)
    {
        _id = rhs._id;
        return *this;
    }
    Container& operator=(Container && rhs)
    {
        _id = rhs._id;
        return *this;
    }

    virtual int GetId() const;
    int GetId_nonvirt() const;

    HPX_DEFINE_COMPONENT_ACTION(Container, GetId_nonvirt, GetId_action_Container);
    
    template <typename Archive>
    void serialize(Archive& ar, unsigned version)
    {
        ar & _id;
    }

private:
    friend class hpx::serialization::access;
    int _id;
};

typedef Container::GetId_action_Container GetId_action_Container;
HPX_REGISTER_ACTION_DECLARATION(GetId_action_Container);