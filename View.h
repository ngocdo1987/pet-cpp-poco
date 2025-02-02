// View.h
#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include "Model.h"

class View {
public:
    static std::string render(const std::vector<Model::Item>& items) {
        std::string html = "<html><body><h1>Items</h1><ul>";
        for (const auto& item : items) {
            html += "<li>" + std::to_string(item.id) + ": " + item.name + "</li>";
        }
        html += "</ul></body></html>";
        return html;
    }
};

#endif // VIEW_H
