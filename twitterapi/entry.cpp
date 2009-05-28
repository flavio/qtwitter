/***************************************************************************
 *   Copyright (C) 2008-2009 by Dominik Kapusta       <d@ayoy.net>         *
 *   Copyright (C) 2009 by Anna Nowak           <wiorka@gmail.com>         *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of      *
 *   the License, or (at your option) any later version.                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to                     *
 *   the Free Software Foundation, Inc.,                                   *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#include <QString>
#include <QDateTime>
#include "entry.h"

Entry::Entry( Entry::Type entryType ) :
  type( entryType ),
  isOwn( false ),
  id( -1 ),
  text( QString() ),
  originalText( QString() ),
//  name( QString() ),
//  screenName( QString() ),
//  image( QString() ),
//  homepage( QString() ),
//  hasHomepage( false ),
  timestamp( QDateTime() ),
  localTime( QDateTime() ),
  hasInReplyToStatusId( false ),
  inReplyToStatusId( -1 ),
  inReplyToScreenName( QString() ),
  userInfo( UserInfo() )
{}

void Entry::initialize()
{
  isOwn = false;
  id = -1;
//  name = QString();
//  screenName = QString();
//  homepage = QString();
//  hasHomepage = false;
//  image = QString();
  text = QString();
  originalText = QString();
  timestamp = QDateTime();
  localTime = QDateTime();
  hasInReplyToStatusId = false;
  inReplyToStatusId = -1;
  inReplyToScreenName = QString();
  userInfo.initialize();
}

bool Entry::checkContents()
{
  if ( !hasInReplyToStatusId ) {
    inReplyToStatusId = -1;
    inReplyToScreenName = QString();
  }
  if ( userInfo.checkContents() ) {
    if ( ( id != -1 ) &&
         ( type == Status ? !userInfo.imageUrl.isNull() : true ) &&  //todo: reference to userinfo here is lame
         !text.isNull() &&
         !timestamp.isNull() &&
         !localTime.isNull()  &&
         ( hasInReplyToStatusId ? inReplyToStatusId != -1 : true ) &&
         ( hasInReplyToStatusId ? !inReplyToScreenName.isNull() : true ) ) {
      return true;
    }
  }
    return false;
}

bool Entry::operator== (const Entry &other )
{
  return ( type == other.type
           && isOwn == other.isOwn
           && id == other.id
           && text == other.text
           && originalText == other.originalText
           && userInfo.name == other.userInfo.name
           && userInfo.screenName == other.userInfo.screenName
           && userInfo.imageUrl == other.userInfo.imageUrl
           && userInfo.homepage == other.userInfo.homepage
           && userInfo.hasHomepage == other.userInfo.hasHomepage
           && timestamp == other.timestamp
           && localTime == other.localTime
           && hasInReplyToStatusId == other.hasInReplyToStatusId
           && inReplyToStatusId == other.inReplyToStatusId
           && inReplyToScreenName == other.inReplyToScreenName );
}


/*! \struct Entry
    \brief A struct containing status data.

    This struct contains all the parameters for each status or direct message
    extracted by an XML parser.
*/

/*! \enum Entry::Type
    \brief Type of the entry.

    Needed to specify whether an entry is a status or a direct message.
*/

/*! \var Entry::Type Entry::Status
    An entry is a status.
*/

/*! \var Entry::Type Entry::DirectMessage
    An entry is a direct message.
*/

/*! \fn Entry::Entry( Entry::Type entryType = Status )
    Constructs an empty entry with a given \a entryType.
*/

/*! \fn void Entry::initialize()
    Resets fields of the entry.
*/

/*! \fn bool Entry::checkContents();
    \brief Checks if the entry is complete.

    Checks an entry for the existence of required fields and returns true
    if it contains all of the required data.
*/

/*! \var Entry::Type Entry::type
    Stores the entry type.
    \sa Type
*/

/*! \var bool Entry::isOwn
    Used to indicate whether an entry belongs to the user authenticated currently.
*/

/*! \var int Entry::id
    Stores the entry id.
*/

/*! \var QString Entry::text
    Stores the entry status equipped with HTML tags for recognizing URL links.
*/

/*! \var QString Entry::originalText
    Stores the plain entry status.
*/

/*! \var QString Entry::name
    Stores the status owner's real name.
*/

/*! \var QString Entry::screenName
    Stores the status owner's login/screen name.
*/

/*! \var QString Entry::image
    Stores the status owner's image URL.
*/

/*! \var QString Entry::homepage
    Stores the status owner's homepage URL.
*/

/*! \var bool Entry::hasHomepage
    Indicates if status owner has a homepage defined.
*/

/*! \var QDateTime Entry::timestamp
    Stores the entry timestamp.
*/
