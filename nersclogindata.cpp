#include "nersclogindata.h"

#include <cstdlib>

namespace NEWT{
///
/// \brief NERSCLoginData::NERSCLoginData
///
/// Default constructor:
/// Setting empty strings to username and password
///
NERSCLoginData::NERSCLoginData():
    fUsername(""),
    fPassword(""),
    fIsLoggedIn(false)
{
}

///
/// \brief NERSCLoginData::NERSCLoginData
/// \param username
/// \param password
///
/// Constructor:
/// Initialises the login data files with username and password
///
NERSCLoginData::NERSCLoginData(std::string username, std::string password):
    fUsername(username),
    fPassword(password),
    fIsLoggedIn(false)
{
}

///
/// \brief NERSCLoginData::~NERSCLoginData
///
/// Destructor:
/// Overwriting strings for username and password with random values to protect users privacy
NERSCLoginData::~NERSCLoginData(){
    for(size_t i = 0; i < fUsername.size(); i++){
        fUsername[i] = static_cast<char>(rand() % 256);
    }

    for(size_t i = 0; i < fPassword.size(); i++){
        fPassword[i] = static_cast<char>(rand() % 256);
    }
}

}
