#include "uid_assembler.hpp"



int main()
{

    uid_assembler<int> uida;
    
    uida.add(0);
    uida.add(1);
    uida.add(2);
    uida.add(3);
    
    uida.set_field(0, 3);
    uida.set_field(1, 1);
    uida.set_field(2, 1);
    
    uida.finalize();
    
    std::cout << uida.generate() << std::endl;
    
}
