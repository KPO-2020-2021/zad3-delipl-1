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
    Menu menu({
        {"Open Gnuplot", [&figure, &isOpened](){
                        if(figure == nullptr){
                            std::cout << "Empty Figure" << std::endl;
                            std::cout << "Press Enter to back to menu...\n"; 
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            return;
                        }
                        std::cout << "File name: " << figure->Name() << std::endl;
                        isOpened = figure->Draw();
        }},
        {"Show cords", [&figure](){
                        if(figure == nullptr){
                            std::cout << "Empty Figure" << std::endl;
                            std::cout << "Press Enter to back to menu...\n"; 
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            return;
                        }
                        std::cout << *figure;
                        std::cout << "Press Enter to back to menu...\n"; 
                        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                        system("clear");
        }},
        {"Open file     - File name", [&figure](){
                        std::string name;
                        std::cin >> name;
                        // GnuFigure<double> x(name, 2);
                        if(figure != nullptr)
                            delete figure;
                            

                        figure = new GnuFigure<double>(name, 2);
                        figure->Read(name);
                        std::cout << "Cords:" << std::endl;
                        std::cout << *figure;
                        std::cout << "Press Enter to back to menu...\n"; 
                        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                        system("clear");

        }},
        {"Save file", [&figure](){
                        std::string name;
                        std::cin >> name;
                        if(figure == nullptr){
                            std::cout << "Empty Figure" << std::endl;
                            std::cout << "Press Enter to back to menu...\n"; 
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            return;
                        }
                        figure->Save(name);
        }},
        {"Animate       - FPS", [&figure](){
                          if(figure == nullptr){
                            std::cout << "Empty Figure" << std::endl;
                            std::cout << "Press Enter to back to menu...\n"; 
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            return;
                        }
                        std::size_t fps;
                        std::cin >> fps;
                        figure->animateFPS = fps;
        }},
        {"Translation   - Vector", Foo},
        {"Rotate        - angle, x times", [&figure](){
                        if(figure == nullptr){
                            std::cout << "Empty Figure" << std::endl;
                            std::cout << "Press Enter to back to menu...\n"; 
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                            return;
                        }
                        double angle;
                        int times;
                        std::cin >> angle;
                        std::cin >> times;
                        figure->Rotate(angle, times);
                        // Edges as Vectors in u
                        Vector u(Vector((*figure)[0] - (*figure)[1], (*figure)[1] - (*figure)[2],
                                        (*figure)[2] - (*figure)[3], (*figure)[3] - (*figure)[0] ));
                       
                        std::cout << "Longer edges: "   << u[0].Length() << ", " << u[2].Length() 
                                                        << "\tDifference: " << u[0].Length() - u[2].Length() << std::endl;
                        std::cout << "Shorter edges: "  << u[1].Length() << ", " << u[3].Length() 
                                                        << "\tDifference: " << u[1].Length() - u[3].Length() << std::endl;

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