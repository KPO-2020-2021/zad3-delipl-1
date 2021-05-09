#ifndef __MENU_HPP__
#define __MENU_HPP__
#include <vector>
#include <string>
#include <functional>
#include <initializer_list>
class Menu{
    
    public:
    /**
     * @brief menu options
     */
    std::vector<std::pair<std::string, std::function<void(void)>>> options;

    /**
     * @brief Construct a new Menu object
     * @param list of name of option and function. Suggested to use lambda.
     */
    Menu(std::initializer_list<std::pair<std::string, std::function<void(void)>>> list);


    /**
     * @brief Choose options and do option
     * @return choosed option
     */
    void Choose() const; 
};

std::ostream &operator<<(std::ostream &cout, const Menu &menu);
std::istream &operator>>(std::istream &cin, const Menu &menu);
#endif // __MENU_HPP__