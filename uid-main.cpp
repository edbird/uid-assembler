#include "uid_assembler.hpp"



int main()
{
    
    uid_assembler<int> uida;
                    
    uida.add(0);
    uida.add(1);
    uida.add(2);
    uida.add(47);
    
    uida.set_field(0, 0);
    uida.set_field(1, 0);
    uida.set_field(2, 2);
    uida.set_field(47, 0);
    
    uida.finalize();
    
    std::cout << "uid=" << uida.generate() << std::endl;
                
    /*
    for(int d = 0; d <= 4; ++ d)
    {
        for(int c = 0; c + d <= 4; ++ c)
        {
            for(int b = 0; b + c + d <= 4; ++ b)
            {
                for(int a = 0; a + b + c + d <= 4; ++ a)
                {
            
                    uid_assembler<int> uida;
                    
                    uida.add(0);
                    uida.add(1);
                    uida.add(2);
                    uida.add(47);
                    
                    uida.set_field(0, d);
                    uida.set_field(1, c);
                    uida.set_field(2, b);
                    uida.set_field(47, a);
                    
                    uida.finalize();
                    
                    std::cout << "d=" << d << " c=" << c << " b=" << b << " a=" << a << " uid=" << uida.generate() << std::endl;
                
                }
            }
        }
    }
    */

    //std::cin.get();
    
}
