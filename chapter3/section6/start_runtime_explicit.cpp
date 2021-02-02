#include <hpx/hpx_init.hpp>


int hpx_main(int argc, char * argv[]) {
    // Any HPX application logic goes here...
    std::cout << "ola" << std::endl;
    return hpx::finalize();
}

int main(int argc, char * argv[]) {
    // Initialize HPX, run hpx_main as the first HPX thread, and
    // wait for hpx::finalize being called.

    const std::vector<std::string> cfg = {
    //"hpx.run_hpx_main==1", // run this code on all localities (SPMD)
    "hpx.expect_connecting_localities!=1" // Make sure networking will not be disabled
    };

   return hpx::init(argc, argv, cfg);
} 