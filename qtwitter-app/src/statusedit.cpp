/***************************************************************************
 *   Copyright (C) 2008-2009 by Dominik Kapusta       <d@ayoy.net>         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "statusedit.h"

const int StatusEdit::STATUS_MAX_LENGTH = 140;

StatusEdit::StatusEdit( QWidget * parent ) :
  QLineEdit( parent ),
  statusClean( true ),
  inReplyToId( -1 )
  {}

void StatusEdit::focusInEvent( QFocusEvent *event )
{
  if ( statusClean ) {
    setText( "" );
    statusClean = false;
  }
  QLineEdit::focusInEvent( event );
}

void StatusEdit::focusOutEvent( QFocusEvent *event )
{
  if ( !text().compare( "" ) ) {
    initialize();
  }
  QLineEdit::focusOutEvent( event );
}

void StatusEdit::initialize()
{
  setText( tr( "What are you doing?" ) );
  inReplyToId = -1;
  statusClean = true;
}

bool StatusEdit::isStatusClean() const
{
  return statusClean;
}

int StatusEdit::getInReplyTo() const
{
  return inReplyToId;
}

QString StatusEdit::getSelectedUrl() const
{
  return selectedUrl;
}

void StatusEdit::cancelEditing()
{
  initialize();
  clearFocus();
}

void StatusEdit::addReplyString( const QString &name, int inReplyTo )
{
  if ( statusClean ) {
    setText( "@" + name + " ");
    statusClean = false;
  } else {
    insert( "@" + name + " ");
  }
  inReplyToId = inReplyTo;
  setFocus();
  emit textChanged( text() );
  update();
}

void StatusEdit::addRetweetString( QString message )
{
  if ( message.length() > StatusEdit::STATUS_MAX_LENGTH ) {
    emit errorMessage( tr( "The message is too long and it will be truncated." ) );
    message.truncate( StatusEdit::STATUS_MAX_LENGTH );
  }
  setText( message );
  statusClean = false;
  setFocus();
  emit textChanged( text() );
}

void StatusEdit::shortenUrl()
{ 
  if( hasSelectedText() ) {
    selectedUrl = selectedText();
    emit shortenUrl( selectedUrl );
  }
}

int StatusEdit::charsLeft() const
{
  return isStatusClean() ? STATUS_MAX_LENGTH : STATUS_MAX_LENGTH - text().length();
}

/*! \class StatusEdit
    \brief A customized QLineEdit class.

    This class inherits from QLineEdit and reimplements focus events so as to fit
    to the application requirements.
*/

/*! \var static const int StatusEdit::STATUS_MAX_LENGTH
    This value stores maximum length of the posted update.
*/

/*! \fn StatusEdit::StatusEdit( QWidget * parent = 0 );
    Creates a new status edit field object, with a given \a parent.
*/

/*! \fn void StatusEdit::focusInEvent( QFocusEvent * event )
    Clears the status edit field if it contained "What are you doing?" when entering.
    \param event A QFocusEvent event's representation.
    \sa focusOutEvent(), initialize()
*/

/*! \fn void StatusEdit::focusOutEvent( QFocusEvent * event )
    Makes the status edit field initialized if it contains an empty
    string when losing focus.
    \param event A QFocusEvent event's representation.
    \sa focusInEvent(), initialize()
*/

/*! \fn void StatusEdit::initialize()
  Clears status and sets the status edit field to initial "What are you doing?".
*/

/*! \fn bool StatusEdit::isStatusClean() const
    Checks wether the status edit field is initialized.
    \returns true when the status edit field is initialized, otherwise returns false.
*/

/*! \fn int StatusEdit::getInReplyTo() const
    Gets the reply status Id if exists.
    \returns Id of the status to which a reply is posted. If the status is not a reply, returns -1.
*/

/*! \fn void StatusEdit::cancelEditing()
    Initializes status edit field and clears focus.
*/

/*! \fn void StatusEdit::addReplyString( const QString &name, int inReplyTo )
    Adds user login in Twitter replying convention (\a \@user).
    \param name User login to be added to status edit field.
    \param inReplyTo Id of the existing status to which the reply is posted.
*/

/*! \fn void StatusEdit::addRetweetString( QString message )
    Adds a retweet message to status field.
    \param message Message to be added to status edit field.
*/

/*! \fn void StatusEdit::errorMessage( const QString &message )
    Emitted to inform user about encountered problems.
    \param message Error message.
*/

/*! \fn int StatusEdit::charsLeft()
    Counts number of characters left
    \returns number of characters left
*/
