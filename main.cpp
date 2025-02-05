// main.cpp
#include <iostream>
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Controller.h"
#include "SessionManager.h"

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest&) override {
        return new Controller();
    }
};

int main(int argc, char** argv) {
    // Initialize session manager
    SessionManager::initialize();

    Poco::Net::ServerSocket socket(1240);
    Poco::Net::HTTPServer server(new RequestHandlerFactory(), socket, new Poco::Net::HTTPServerParams);

    server.start();
    std::cout << "Server started on port 1240..." << std::endl;

    // Keep the server running
    while (true) {
        Poco::Thread::sleep(1000);
    }

    server.stop();
    return 0;
}
