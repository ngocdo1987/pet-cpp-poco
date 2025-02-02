// SessionManager.h
#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "Poco/Net/HTTPCookie.h"
#include "Poco/JSON/Object.h"
#include "Poco/FileStream.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include <string>
#include <map>

class SessionManager {
public:
    static const std::string SESSION_ID_COOKIE;
    static const std::string SESSION_DIR;

    // Initialize session directory
    static void initialize() {
        if (!Poco::File(SESSION_DIR).exists()) {
            Poco::File(SESSION_DIR).createDirectory();
        }
    }

    // Create a new session and return the session ID
    static std::string createSession() {
        std::string sessionId = Poco::UUIDGenerator().createRandom().toString();
        Poco::JSON::Object sessionData;
        saveSession(sessionId, sessionData);
        return sessionId;
    }

    // Retrieve session data by session ID
    static Poco::JSON::Object getSession(const std::string& sessionId) {
        Poco::JSON::Object sessionData;
        std::string filePath = SESSION_DIR + sessionId + ".json";

        if (Poco::File(filePath).exists()) {
            std::ifstream ifs(filePath);
            Poco::JSON::Parser parser;
            sessionData = *parser.parse(ifs).extract<Poco::JSON::Object::Ptr>();
            ifs.close();
        }

        return sessionData;
    }

    // Save session data to a file
    static void saveSession(const std::string& sessionId, const Poco::JSON::Object& sessionData) {
        std::string filePath = SESSION_DIR + sessionId + ".json";
        std::ofstream ofs(filePath);
        sessionData.stringify(ofs);
        ofs.close();
    }

    // Delete a session
    static void deleteSession(const std::string& sessionId) {
        std::string filePath = SESSION_DIR + sessionId + ".json";
        if (Poco::File(filePath).exists()) {
            Poco::File(filePath).remove();
        }
    }

    // Get session ID from cookies
    static std::string getSessionIdFromCookies(const Poco::Net::HTTPServerRequest& request) {
        Poco::Net::NameValueCollection cookies;
        request.getCookies(cookies);

        if (cookies.has(SESSION_ID_COOKIE)) {
            return cookies[SESSION_ID_COOKIE];
        }

        return "";
    }

    // Set session ID in response cookies
    static void setSessionIdInCookies(Poco::Net::HTTPServerResponse& response, const std::string& sessionId) {
        Poco::Net::HTTPCookie cookie(SESSION_ID_COOKIE, sessionId);
        cookie.setPath("/");
        cookie.setMaxAge(3600);  // Session expires after 1 hour
        response.addCookie(cookie);
    }
};

const std::string SessionManager::SESSION_ID_COOKIE = "session_id";
const std::string SessionManager::SESSION_DIR = "./sessions/";

#endif // SESSIONMANAGER_H
