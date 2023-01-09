#include "base/engine.h"

#undef main

/*--------
 TODO:
 [bugs]
 -
 [improvements]
 - 
 [additions]
 - chromosome (large collection of genomes) --hasmany-> 
   genome (collection of genes) --hasmany-> 
   gene (a specific atrabute of the agent [sight, hunger, speed]) --hasmany->
   dna (bit)
 -
--------*/

int main(int argc, char* argv[])
{
    if (base::Init())
    {
        base::Run();
    }
    std::cin.get();
    return 0;
}