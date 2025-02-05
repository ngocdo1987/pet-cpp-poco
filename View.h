// View.h
#ifndef VIEW_H
#define VIEW_H

#include <inja/inja.hpp>
#include <string>
#include <vector>
#include "Model.h"

class View {
public:
    // Render the template with given data using Inja
    static std::string render(const std::string& templateName, const std::map<std::string, std::string>& data) {
        // Load the template file
        std::string templatePath = "templates/" + templateName;
        inja::Environment env;

        // Render the template with the provided data
        return env.render_file(templatePath, data);
    }
};

#endif // VIEW_H
