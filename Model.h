// Model.h
#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

class Model {
public:
    struct Item {
        int id;
        std::string name;
    };

    std::vector<Item> getItems() const {
        return items;
    }

private:
    std::vector<Item> items = {
        {1, "Item 1"},
        {2, "Item 2"},
        {3, "Item 3"}
    };
};

#endif // MODEL_H
