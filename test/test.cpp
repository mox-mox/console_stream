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

// A little test program to see if the console streams work as expected
#include "utils.h"
#include "console_stream.hpp"

int main()
{
	// Do check if the streams output data as expected

	for(int i=-1; i<4; i++)
	{
		std::cout<<"==== Log level "<<i<<" ======================================="<<std::endl;
		logger<<setloglevel(i);

		debug<<"Hello"<<std::endl;
		logger<<"these are some"<<std::endl;
		error<<"fancy output streams.\nwith a nice\nlinebreak."<<std::endl;

		red_stream<<"red_stream"<<std::endl;
		green_stream<<"green_stream"<<std::endl;
		yellow_stream<<"yellow_stream"<<std::endl;
		blue_stream<<"blue_stream"<<std::endl;
		magenta_stream<<"magenta_stream"<<std::endl;
		cyan_stream<<"cyan_stream"<<std::endl;
		white_stream<<"white_stream"<<std::endl;

		std::cout<<__FILE__<<':'<<__LINE__<<"::"<<__func__<<"(): Ooopsie, something went wrong."<<std::endl;
		logger<<__FILE__<<':'<<__LINE__<<"::"<<__func__<<"(): Ooopsie, something went wrong."<<std::endl;
		logger<<"and another line"<<std::endl;
		logger<<"and another line"<<std::endl;

		logger<<__FILE__<<':'<<__LINE__<<"::"<<__func__<<"(): Ooopsie, something went wrong."<<std::endl;
	}

	return 0;
}

