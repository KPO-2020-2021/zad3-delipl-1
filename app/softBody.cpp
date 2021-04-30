#include <iostream>
#include <limits>
#include <ctime>
#include "exampleConfig.h"
#include "Menu.h"
#include "Figure.h"
#include "frameRate.h"

enum Draw{
    goToDraw
};

int main(int argc, const char** argv) { 
    GnuFigure<double> *figure = new GnuFigure<double>("spring.dat", 2);

    std::clock_t timer;
    int i=0;
    std::cout << timer << "   " << (float)clock()/CLOCKS_PER_SEC << std::endl;

    while(true){
        std::clock_t diff = (clock() - timer)/CLOCKS_PER_SEC;
        /* -------------------------------------------------------------------------- */
        /*                         CHECKING TIME FOR INTERRUPT                        */
        /* -------------------------------------------------------------------------- */
        try{
            if(diff >= dt*1000){
                // dopasować czas zeby gnuplots sie n ie jebval
                std::cout << "Printing...\t" << "Took: "<< (float)clock()/CLOCKS_PER_SEC << std::endl;
                throw Draw::goToDraw;
            }

            // if(currentTime - refTime >= dt){
            //     refTime = std::time(nullptr);
            //    
            // }
            
            std::cout << "Poza pętlą" << std::endl;
        }
        catch(Draw){
            figure->EveryFrame();
        }
    }



    // delete figure;
    return 0;
}
