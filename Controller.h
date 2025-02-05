// Controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Model.h"
#include "View.h"
#include "SessionManager.h"

class Controller : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override {
        Model model;
        auto items = model.getItems();

	// Initialize session manager
        SessionManager::initialize();

        // Get session ID from cookies
        std::string sessionId = SessionManager::getSessionIdFromCookies(request);

        if (sessionId.empty()) {
            // Create a new session if no session ID is found
            sessionId = SessionManager::createSession();
            SessionManager::setSessionIdInCookies(response, sessionId);
        }

        // Retrieve session data
        Poco::JSON::Object sessionData = SessionManager::getSession(sessionId);

        // Example: Store or update session data
        if (!sessionData.has("visit_count")) {
            sessionData.set("visit_count", 1);
        } else {
            int visitCount = sessionData.getValue<int>("visit_count");
            sessionData.set("visit_count", visitCount + 1);
        }

        // Save updated session data
        SessionManager::saveSession(sessionId, sessionData);

        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.setContentType("text/html");

        std::ostream& ostr = response.send();
        //ostr << View::render(items);
	ostr << "<html><body>";
        ostr << "<h1>Session Data</h1>";
        ostr << "<p>Session ID: " << sessionId << "</p>";
        ostr << "<p>Visit Count: " << sessionData.getValue<int>("visit_count") << "</p>";
        ostr << "</body></html>";
    }
};

#endif // CONTROLLER_H
