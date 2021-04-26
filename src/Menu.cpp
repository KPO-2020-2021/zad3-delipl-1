#include "Menu.h"
#include <iostream>


Menu::Menu(std::initializer_list<std::pair<std::string, std::function<void(void)>>> list){
    for(auto &elem: list)
        this->options.push_back(elem);
}


std::ostream &operator<<(std::ostream &cout, const Menu &menu){
    std::size_t i = 0;
    cout << std::endl;
    for(auto &optionName: menu.options){
        ++i;
        cout << i << ". " << optionName.first << std::endl; 
        
    }
    return cout;
}
std::istream &operator>>(std::istream &cin, const Menu &menu){

    std::size_t i = 0;
    cin >> i; 
    if(!cin)
        throw std::logic_error("Menu input error");

    system("clear");
    if(i == 0 || i > menu.options.size()){
        return cin;
    }
    menu.options[i-1].second();
    
    return cin;
}