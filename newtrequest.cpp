#include "newtrequest.h"
#include <cstdlib>
#include <curl/curl.h>
#include <iostream>

namespace NEWT {

///
/// \brief NEWTRequest::NEWTRequest
/// \param url
/// \param payload
/// \param method
///
/// Consturctor, creating http request and sending it to NERSC
///
NEWTRequest::NEWTRequest(std::string url, std::string payload, REQUEST_METHOD method, COOKIE_MODE cookie, std::string cookiefile):
    fRequestURL(url),
    fPayload(payload),
    fResponse(""),
    fCookie(cookiefile),
    fRequestMethod(method),
    fRequestStatus(-1)
{
    SendRequest(cookie);
}

///
/// \brief NEWTRequest::SendRequest
///
/// Send request and process the answer
///
void NEWTRequest::SendRequest(COOKIE_MODE cookie){
    CURL *request = curl_easy_init();
    CURLcode reqstat;
    if(request){
        //curl_easy_setopt(request, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(request, CURLOPT_URL, fRequestURL.c_str());
        struct curl_slist *headers = NULL;
        if(fRequestMethod == kPOST){
            curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(request, CURLOPT_POST, 1);
            curl_easy_setopt(request, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(request, CURLOPT_POSTFIELDS, fPayload.c_str());
        }
        // handle result
        curl_easy_setopt(request, CURLOPT_WRITEFUNCTION, HandleNerscResponse);
        curl_easy_setopt(request, CURLOPT_WRITEDATA, &fResponse);

        if(cookie == kWrite){
            //std::cout << "Setting write cookie file " << fCookie << std::endl;
            curl_easy_setopt(request, CURLOPT_COOKIEJAR, fCookie.c_str());
        } else if(cookie == kRead){
            //std::cout << "Setting read cookie file " << fCookie << std::endl;
            curl_easy_setopt(request, CURLOPT_COOKIEFILE, fCookie.c_str());
        }

        reqstat = curl_easy_perform(request);

        if(reqstat == CURLE_OK){
            fRequestStatus = 1;
        } else
            fRequestStatus = 0;

        std::cout << "Answer received from NERSC: " << fResponse << std::endl;

        // Cleanup after request
        curl_easy_cleanup(request);
        if(fRequestMethod == kPOST){
            curl_slist_free_all(headers);
        }
    }
}

///
/// \brief NEWTRequest::request_callback
/// \param ptr message received from HTTP request
/// \param size
/// \param nmemb
/// \param ourpointer (type std::string) pointer to where to write the answer to
/// \return
///
/// Callback function used to interpret the result of the NEWT request
///
size_t HandleNerscResponse(void *ptr, size_t /*size*/, size_t /*nmemb*/, void *ourpointer){
    std::string *answer = static_cast<std::string *>(ourpointer);
    *answer = static_cast<char *>(ptr);
    return answer->length();
}

}
