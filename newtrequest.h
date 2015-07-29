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

#ifndef NEWTREQUEST_H
#define NEWTREQUEST_H

#include <string>

namespace NEWT {

class NEWTRequest
{
public:
    enum REQUEST_METHOD {
        kGET = 1,
        kPOST = 2
    };
    enum COOKIE_MODE{
        kNoCookie = 0,
        kRead = 1,
        kWrite = 2
    };
    NEWTRequest(std::string url, std::string payload, REQUEST_METHOD method, COOKIE_MODE cookie = kNoCookie, std::string cookiefile = "");

    int GetRequestStatus() const { return fRequestStatus; }
    const std::string &GetNERSCResponse() const { return fResponse; }
    const std::string &GetUrl() const { return fRequestURL; }
    const std::string &GetPayload() const { return fPayload; }
    REQUEST_METHOD GetRequestMethod() { return fRequestMethod; }
    const std::string &GetCookie() const { return fCookie; }

protected:
    void SendRequest(COOKIE_MODE cookie);

private:
    std::string             fRequestURL;
    std::string             fPayload;
    std::string             fResponse;
    std::string             fCookie;
    REQUEST_METHOD          fRequestMethod;
    int                     fRequestStatus;
};

size_t HandleNerscResponse(void *ptr, size_t size, size_t nmemb, void *ourpointer);

}
#endif // NEWTREQUEST_H
