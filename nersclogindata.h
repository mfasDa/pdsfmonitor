#ifndef NERSCLOGINDATA_H
#define NERSCLOGINDATA_H

#include <string>
namespace NEWT{

class NERSCLoginData
{
public:
    NERSCLoginData();
    NERSCLoginData(std::string username, std::string passwort);
    ~NERSCLoginData();

    void SetUserName(std::string username) { fUsername = username; }
    void SetPassword(std::string password) { fPassword = password; }
    void SetLoggedIn(bool loggedIn) { fIsLoggedIn = loggedIn; }
    void SetSessionLifetime(int lifetime) { fSessionLifetime = lifetime; }
    void SetSessionID(std::string sessionID) { fSessionID = sessionID; }
    void SetCookie(std::string cookie) { fCookie = cookie; }

    std::string GetUserName() const { return fUsername; }
    std::string GetPassword() const { return fPassword; }
    std::string GetSessionID() const { return fSessionID; }
    std::string GetCookie() const { return fCookie; }
    bool IsLoggedIn() const { return fIsLoggedIn; }
    int GetSessionLifetime() const { return fSessionLifetime; }

private:
    std::string         fUsername;
    std::string         fPassword;
    bool                fIsLoggedIn;
    int                 fSessionLifetime;
    std::string         fSessionID;
    std::string         fCookie;
};

}
#endif // NERSCLOGINDATA_H
