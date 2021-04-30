#include <iostream>
#include <limits>
#include "exampleConfig.h"
#include "Menu.h"
#include "Figure.h"
void Foo(){
    std:: cout << "HEJ" << std::endl;
}
int main(){

    // miejsce          = 5;
    // Daniel: wektor /miejce/ = 3.0;
    // x = y + wek.get(0); wek.war[0]
    // wek.get / wek.set / wek.edit
    // cout << wek[miejce]
    // wek = wek
    // wek[miejce] = 5;
    // Daniel: wektor.set_wsp(0, 3);
    std::cout << "Project Rotation 2D based on C++ Boiler Plate by Jakub Delicat v"
              << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
              << "."
              << PROJECT_VERSION_MINOR /* istotne zmiany */
              << "."
              << PROJECT_VERSION_PATCH /* naprawianie bugów */
              << "."
              << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
              << std::endl;

    GnuFigure<double> *figure = nullptr;
    bool isOpened = false;
    figure = new GnuFigure<double>("prostokat.dat", 2);
    figure->animateFPS = 60;
    figure->Draw();

    Menu menu({        
        {"Rotate        - angle, x times", [&figure](){
                        double angle;
                        int times;
                        std::cin >> angle;
                        std::cin >> times;
                        figure->Rotate(angle, times);
                        Vector u(Vector((*figure)[0] - (*figure)[1], (*figure)[1] - (*figure)[2],
                                        (*figure)[2] - (*figure)[3], (*figure)[3] - (*figure)[0] ));
                       
                        std::cout << "Longer edges: "   << u[0].Length() << ", " << u[2].Length() 
                                                        << "\tDifference: " << u[0].Length() - u[2].Length() << std::endl;
                        std::cout << "Shorter edges: "  << u[1].Length() << ", " << u[3].Length() 
                                                        << "\tDifference: " << u[1].Length() - u[3].Length() << std::endl;

        }},
        {"Translation   - Vector", [&figure](){
                        Vector v(0.0, 0.0);
                        figure->Translate(v);
        }},
        {"Show cords", [&figure](){
                        std::cout << *figure;
                        std::cout << "Press Enter to back to menu...\n"; 
                        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                        system("clear");
        }},
        {"Exit", [](){  system("clear");
                        std::cout << "See ya!\nPress Enter to exit...\n"; 
                        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                        system("clear");
                        
                        exit(0);}}
    });
    while(true){
        if(isOpened)
            figure->Draw();
        
        std::cout << menu;
        try{
             std::cin >> menu;
        }   
        catch(std::logic_error &e){
            system("clear");
            std::cerr << e.what();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
       
    }
    delete figure;
}