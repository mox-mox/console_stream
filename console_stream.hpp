/***********************************************************************
*                                                                      *
* (C) 2016, Moritz Nöltner-Augustin                                    *
*                                                                      *
* This program is free software; you can redistribute it and/or modify *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation; either version 3 of the License, or    *
* (at your option) any later version.                                  *
*                                                                      *
* This program is distributed in the hope that it will be useful,      *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU General Public License for more details.                         *
*                                                                      *
* You should have received a copy of the GNU General Public License    *
* along with this program; if not, write to the Free Software          *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 *
* USA                                                                  *
*                                                                      *
***********************************************************************/

#pragma once

#ifndef LOGGING_LEVEL
#define LOGGING_LEVEL 3
#endif



#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
//#include <chrono>
#include <sstream>

/**
 * \brief A stream class providing formatted output
 *
 * This class wrapps around an output stream and provides automated formatted output with the
 * usual stream operators.
 * It is taken from <a href="http://stackoverflow.com/a/2212940/4360539">this post</a> at
 * Stackoverflow, with the addition of a postfix and pre- and postfix parameters for the
 * constructor.
 * Usage:
 *
 * logger << "logging some stuff" << std::endl;
 *
 * Will give something like: [      1000] (LL) logging some stuff
 * with "(LL) logging some stuff" in green, while
 *
 * error << "Oh noes, something went wrong!" << std::endl;
 *
 * Will give something like : [      8467] (EE) Oh noes, something went wrong!
 * with "(EE) Oh noes, something went wrong!" in red.
 * The number in square brackets will be the current value of the milliseconds counter.
 *
 */
class Console_stream_base
{
	public:
	inline static int logging_level = LOGGING_LEVEL;
};

template<class CharT, class Traits = std::char_traits<CharT>, int min_logging_level=3>
class Console_stream: public Console_stream_base, public std::ostream
{
	private:
		/**
		 * A stream buffer that wraps each line within prefix and postfix.
		 */
		class stream_buf: public std::stringbuf
		{
			std::string prefix;
			std::ostream& output;
			std::string postfix;
			public:
				stream_buf(std::string prefix, std::ostream& str_, std::string postfix) : prefix(prefix), output(str_), postfix(postfix)
				{}

				// When we sync the stream with the output.
				// 1) Output prefix then the buffer then the postfix
				// 2) Reset the buffer
				// 3) flush the actual output stream we are using.
				// Active (with real output):     time
				//
				virtual int sync()
				{
					if(logging_level >= min_logging_level)
					{
						std::string line;
						std::stringstream ss(str());
						getline(ss, line, '\n');
						std::time_t t = std::time(nullptr);
						output<<"["<<std::put_time(std::localtime(&t), "%F/%T")<<"] "<<prefix<<line<<'\n';
						while (getline(ss, line, '\n'))
						{
							output<<"                      "<<prefix<<line<<'\n';
						}

						output<<postfix;
						output.flush();
					}

					str("");
					return 0;
				}
		} buffer;
	public:
		// \x1b[37m is an ANSI-escape sequence, see https://en.wikipedia.org/wiki/ANSI_escape_code
		Console_stream(std::string prefix, std::ostream& str = std::cout, std::string postfix = "\x1b[37m") :
			std::ostream(&buffer), buffer(prefix, str, postfix)
		{
		}
};

struct _SetLogLevel
{
	int level;
};

/**
 *  @brief  Manipulator for @c setf.
 *  @param  __base  A numeric base.
 *
 *  Sent to a stream object, this manipulator changes the
 *  @c ios_base::basefield flags to @c oct, @c dec, or @c hex when @a base
 *  is 8, 10, or 16, accordingly, and to 0 if @a __base is any other value.
 */
inline _SetLogLevel setloglevel(int level)
{
	return { level };
}

template<class CharT, class Traits, int min_logging_level>
inline Console_stream<CharT, Traits, min_logging_level>& operator<<(Console_stream<CharT, Traits, min_logging_level>&os, _SetLogLevel f)
{
	os.logging_level = f.level;

	return os;
}


extern Console_stream<char, std::char_traits<char>, 3> debug;
extern Console_stream<char, std::char_traits<char>, 2> logger;
extern Console_stream<char, std::char_traits<char>, 1> error;

#if defined(USE_COLOUR_STREAMS) && USE_COLOUR_STREAMS != 0
	extern Console_stream<char, std::char_traits<char>, 0> red_stream;
	extern Console_stream<char, std::char_traits<char>, 0> green_stream;
	extern Console_stream<char, std::char_traits<char>, 0> yellow_stream;
	extern Console_stream<char, std::char_traits<char>, 0> blue_stream;
	extern Console_stream<char, std::char_traits<char>, 0> magenta_stream;
	extern Console_stream<char, std::char_traits<char>, 0> cyan_stream;
	extern Console_stream<char, std::char_traits<char>, 0> white_stream;
#endif
