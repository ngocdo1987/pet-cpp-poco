// Controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Model.h"
#include "View.h"

class Controller : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override {
        Model model;
        auto items = model.getItems();

        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.setContentType("text/html");

        std::ostream& ostr = response.send();
        ostr << View::render(items);
    }
};

#endif // CONTROLLER_H
