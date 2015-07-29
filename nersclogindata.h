/***************************************************************************
 * Simple monitoring program for the PDSF cluster at NERSC using NEWT.     *
 * Copyright (C) 2015  Markus Fasel, Lawrence Berkeley National Laboratory *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

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
