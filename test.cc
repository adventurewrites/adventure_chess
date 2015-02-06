/***************************************************************************
 *   Copyright (C) 2007 by raso                                            *
 *   Rafal Sowiak (sowiakr@interia.pl) - www.adventure.go.pl               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

#include "engine.h"
//#include <teksty_en.h>//if language=english then include teksty_en.h otherwise include teksty_pl.h


using namespace std;

int main(int argc, char *argv[])
{
//declare
  int _moc=0;//help value
  int dalej=0;//checking end of program (0 - end of program)
  szachownica board(1);//object of szachownica with constructor
//program label
  cout << board.TITLE;
//board showing
  board.show();
//main loop
  do
  {
    if (board.black_or_white)
      { cout << board.WHITE_MOVE;
      }
    else
      { cout << board.BLACK_MOVE;
      };
    cin >> board.move;
//last statement rewriting
    if (board.DEBUG)
     cout << board.move << endl;
//end game checking
  dalej=board.move_ok(board.move,_moc);
//  cout << dalej << endl;
  if  (dalej==100)
       cout << board.BAD_MOVE << endl;
  else if  (dalej==101)
       cout << board.BAD_MOVE_CHECK << endl;
  else if (dalej!=3 && dalej)
       board.engine();
  }
  while (dalej);
//end of program
return 0;
}
