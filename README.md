----------------
   DISCLAIMER
----------------

This file is part of qFilter.

    qFilter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.


qFilter has been developed by Michele Schimd (skimmoz@gmail.com) as part of a
Ph.D. thesis, as that it may not use best options and best algorithms and it
may be not as easy to use as many other public software. However, in the hope
if it being useful to somebody, it is still publicly available to download

    http://www.dei.unipd.it/~schimdmi/qFilter/


----------------
     NOTES
----------------

qCluster is a collection of python script and algorithms all used in a pipeline,
various part of the software have different dependance, here are listed all of
them.

Python dependancies
* Python 2.7 (not sure about backward compatibility of Pythhon 3)
* BioPython (1.59 is used)

C/C++ dependancies
* g++ 4.7+ has been used to compile the files in this repository (c++11 code is used)
* some files require stxxl library to run, be sure to have it installed (1.4-dev has been used)
