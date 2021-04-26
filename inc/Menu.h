#pragma once
#include <vector>
#include <string>
#include <functional>
class Menu{
    
    public:
    /**
     * @brief menu options
     */
    std::vector<std::pair<std::string, std::function<void(void)>>> options;

    Menu(std::initializer_list<std::pair<std::string, std::function<void(void)>>> list);


    /**
     * @brief Choose options and do option
     * @return choosed option
     */
    void Choose() const; 
};

std::ostream &operator<<(std::ostream &cout, const Menu &menu);
std::istream &operator>>(std::istream &cin, const Menu &menu);