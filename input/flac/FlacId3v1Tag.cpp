//---------------------------------------------------------------------------
//  Provide read-only access to flac stream tags.  Supports id3v1 tags
//  without any additional libraries.
//
//  Copyright (c) 2002 by Drew Hess <dhess@bothan.net>
//
//  code theft from Josh Coalson's flac xmms plugin (C) 2001 by Josh Coalson
//
/*  This file is part of AlsaPlayer.
 *
 *  AlsaPlayer is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  AlsaPlayer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
//--------------------------------------------------------------------------


#include "FlacId3Tag.h"

#include <cstdio>
#include <cstring>
#include "reader.h"

static bool
findId3Tag (reader_type * f, char * tag)
{
    if (reader_seek (f, -128, SEEK_END) != 0)
	return false;
    if (reader_read (tag, 128, f) != 128)
	return false;
    return strncmp (tag, "TAG", 3) == 0 ? true : false;

} // findId3Tag


namespace Flac
{

typedef struct {
    char raw[128];
    char title[31];
    char artist[31];
    char album[31];
    char comment[31];
    char year[5];
    char track[4];
    char genre[4];
} id3v1_struct;

// static
bool
FlacId3Tag::hasId3 (const std::string & name)
{
    static char tag[128];

    reader_type * f = reader_open (name.c_str (), NULL, NULL);
    if (!f)
	return false;

    bool status = findId3Tag (f, tag);
    reader_close (f);
    return status;

} // FlacId3Tag::hasId3


FlacId3Tag::FlacId3Tag (const std::string & name)
    : FlacTag (name)
{
    reader_type * f = reader_open (name.c_str (), NULL, NULL);
    if (!f)
	return;

    id3v1_struct tag_;
    memset ((void *) & tag_, 0, sizeof (id3v1_struct));
    if (!findId3Tag (f, tag_.raw))
	return;

    memcpy(tag_.title, tag_.raw+3, 30);
    memcpy(tag_.artist, tag_.raw+33, 30);
    memcpy(tag_.album, tag_.raw+63, 30);
    memcpy(tag_.year, tag_.raw+93, 4);
    memcpy(tag_.comment, tag_.raw+97, 30);
    snprintf (tag_.genre, sizeof (tag_.genre), "%u", (unsigned char) tag_.raw[127]);
    snprintf (tag_.track, sizeof (tag_.track), "%u", (unsigned char) tag_.raw[126]);

    _artist  = tag_.artist;
    _title   = tag_.title;
    _track   = tag_.track;
    _album   = tag_.album;
    _year    = tag_.year;
    _comment = tag_.comment;
    _genre   = tag_.genre;

} // FlacId3Tag::FlacId3Tag

} // namespace Flac
