#include "ArrayList.hpp"

int main()
{
    ArrayList<int> ids;
    ArrayList<std::string> names;
    for (int i = 0; i < 10; ++i)
    {
        unsigned int id;
        std::string name;
        
        std::cin >> id;
        ids.add(id);

        std::cin.ignore(1);
        std::getline(std::cin, name);
        names.add(name);
    }

    for (int i = 0; i < 10; ++i)
    {
        std::cout << names.at(i) << " (ID#" << ids.at(i) << ")" << std::endl;
    }

    return 0;
}

