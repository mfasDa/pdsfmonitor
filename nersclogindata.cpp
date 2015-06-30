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
