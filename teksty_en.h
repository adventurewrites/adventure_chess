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
#include "szach.h"

szachownica::szachownica(int _i)//constructor for szachownica class
{
//from 1 august 2007
TITLE="Adventure chess v.0,028b20081120 \nCopyleft Rafal Sowiak 2007-2008 (www.adventure.host22.com)\nType \"help\" for command list\n";//title statement
BUG_R="Any bugs please report to: rafalowapoczta@gmail.com";
NO_MOVIES="There were no movies yet.";
LIST="list";//printing list of moves
BACK="back";//printing list of moves
QUIT="quit";//quit of game statement
SHOW="show";//printout of board
SAVE="save";//saving game to file
LOAD="load";//loading game from file
HELP="help";//help screen
BAD_MOVE="Bad move!";//bad move printout
BAD_MOVE_CHECK="Bad move! Your king is checked.";//bad move printout
BAD_SAVE="Game not saved: error opening file";//faulty save
BAD_LOAD="Game not loaded: error opening file";//faulty save
WIN="You won! The game is finished.";//faulty load
LOSE="You lost! You are checkmated.";//faulty load
//FILENAME="Please enter the filename: ";
GOOD_SAVE="Game saved in file ";//proper save
GOOD_LOAD="Game loaded from file ";//proper load
WHITE_MOVE="White move: ";//white move label
BLACK_MOVE="Black move: ";//black move label
H_LABEL="Description of commands:";//help screen label
H_HELP="help - print this screen";
H_SHOW="show - print board actual arrangement";
H_LIST="list - print list of movies";
H_BACK="back - back last move";
H_SAVE="save <filename> - save game in file";
H_LOAD="load <filename> - load game from file";
H_QUIT="quit - end of this game end quit program";
FLIGHT_BIT=0;//set flight bit possibility to false
WCASTLING_W=0;
WCASTLING_B=0;
DEBUG=0;

black_or_white=_i;//set black_or_white move - future option
board_tab="rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";//definition of board
/*
board_tab="rnbqkbnr
           pppppppp
           ........
           ........
           ........
           ........
           PPPPPPPP
           RNBQKBNR";//definition of board
*/

};
