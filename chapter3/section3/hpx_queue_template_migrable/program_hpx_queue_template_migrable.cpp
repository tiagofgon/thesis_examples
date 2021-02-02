#include "queue_client.hpp"
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>



class Object {
public:
    void setA(int a) {
        this->a = a;
    }
    void setB(double b) {
        this->b = b;
    }
    void setC(std::string c) {
        this->c = c;
    }

    int getA(){
        return a;
    }
    double getB() {
        return b;
    }
    std::string getC(){
        return c;
    }
    
    template <typename Archive>
    void serialize(Archive& ar, unsigned) {   
        ar& a;
        ar& b;
        ar& c;
    }

private:
    friend class hpx::serialization::access;
    int a = 1;
    double b = 1.1;
    std::string c = "1.2";
};


REGISTER_QUEUE(Object);

int main(int argc, char* argv[]) {

    hpx::id_type locality = hpx::find_here();
    Queue_Client<Object> myqueue(locality);
    Object objA; Object objB; Object objC;
    
    myqueue.Push(objA).get();
    myqueue.Push(objB).get();
    myqueue.Push(objC).get();

    // migrar o componente para a localidade seguinte
    if(hpx::get_num_localities().get() > 1) {
        std::vector<hpx::id_type> remote_localities = hpx::find_remote_localities();
        hpx::id_type dest = remote_localities[0];
        hpx::components::migrate<Queue<Object>>(myqueue.get_gid(), dest);
    }

    auto element = myqueue.Pop().get();
    
    hpx::cout << myqueue.Size().get() << hpx::endl; // irá imprimir 2

    return 0;
}
