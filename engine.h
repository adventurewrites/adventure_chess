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
#include "teksty_en.h"

void szachownica::engine()
{
  int MAXmoc=-1000;
  int MAXLOOP=2;
  int LOOP=0;
  int _moc;//help variable
  string MAXmove="----";
//single loop!!!!!!!!!!!!!!!!!!!!!!!!
  engine_loop(1,MAXmoc,MAXmove,LOOP,MAXLOOP);
//-----------------------------------------------------------
  if (DEBUG)
  {
    cout<<MAXmove<<endl;
    cout<<MAXmoc<<endl;
  }
//-----------------------------------------------------------
//show of engine move
  if (black_or_white)
    { cout <<"  "<< WHITE_MOVE;
    }
  else
    { cout <<"  "<< BLACK_MOVE;
    };
  cout<<MAXmove<<endl;
  if (MAXmove!="----")
    {
      move_ok(MAXmove,_moc);
      if (MAXmoc==1000)
         cout<<LOSE<<endl;
    }
  else
    { cout<<WIN<<endl;
    }
};

void szachownica::engine_loop(unsigned int _black_or_white,int &MAXmoc,string &MAXmove, int &LOOP, int MAXLOOP)
{
  int _i,_j,_k,_l;
  int TotalMoc,MAXmoc_white;
  string ActMove;
  unsigned int from,to,ffrom,tto;
  int moc;//power of move
//  int _param;
  string _fig1,_fig2,_fig3,_fig4,_move;
  int _wynik;
  if (_black_or_white)
    { _fig1="pqkrbn";
      _fig2="PQRBN.";
      _fig3="PQKRBN";
      _fig4="pqrbn.";
//      _param=0;
    }
  else
    { _fig1="PQKRBN";
      _fig2="pqrbn.";
      _fig3="pqkrbn";
      _fig4="PQRBN.";
//      _param=1;
    };
  LOOP++;
//-----------------------------------------------------------------------
  for (_i=0;_i<64;_i++)
  { if (_fig1.find(board_tab[_i])!=_fig1.npos)
      {  from=_i;
         for (_j=0;_j<64;_j++)
           { if (_fig2.find(board_tab[_j])!=_fig2.npos)
               { to=_j;
                 _move=move_tab[from];
                 _move+=move_tab[to];
                 moc=0;
                 _wynik=move_ok(_move,moc);
//--------------------------------------------------------------------
//making move
                 if (_wynik==1 || _wynik==2)
                  {
//power of machine move calculation
                    TotalMoc=moc;
                    ActMove=_move;
                    MAXmoc_white = 0;
//checking man move
                          _wynik=0;
//--------------------------------------------------------------------
                          for (_k=0;_k<64;_k++)
                          { if (_fig3.find(board_tab[_k])!=_fig3.npos)
                              {  ffrom=_k;
                                for (_l=0;_l<64;_l++)
                                  { if (_fig4.find(board_tab[_l])!=_fig4.npos)
                                      { tto=_l;
                                        _move=move_tab[ffrom];
                                        _move+=move_tab[tto];
                                        moc=0;
                                        _wynik=move_ok(_move,moc);
//making move
                                        if (_wynik==1 || _wynik==2)
                                          {
//power of man move calculation
                                              if (moc>MAXmoc_white)
                                              MAXmoc_white=moc;
//level of game choosing - future option
//                                              MAXmoc_white=0;
//------------------------------------------------------------------
                                            back(0);
                                          };
                                      };
                                  };
                              };
                          };

//white move end of calculation-------------------------------------------
// not aplicable now :)///////////////////////////////////////////////////
//                    if (LOOP<MAXLOOP)
//                        engine_loop(_param,MAXmoc,MAXmove,LOOP,MAXLOOP);
//////////////////////////////////////////////////////////////////////////
//machine wins
                    if (MAXmoc_white==0)
                      {
                        MAXmoc=1000;
                        MAXmove=ActMove;
                      }
//------------------------------------------------------------------------
                    else
                      {
                        TotalMoc-=MAXmoc_white;
                        if (TotalMoc>MAXmoc)
                          { MAXmoc=TotalMoc;
                            MAXmove=ActMove;
                          };
                      };
                    back(1);
                  };
               };
           };
      };
  };
  LOOP--;
//-------------------------------------------------------------
};

//***********************************************************************************************************
int szachownica::power_of_move(int to)
//***********************************************************************************************************
{
  int _wynik=0;
/*****************************************/
  int PowP=1;
  int PowB=6;
  int PowN=6;
  int PowR=11;
  int PowQ=16;
  int PowK=21;
/*****************************************/
//power of biting*************************/
  if (board_tab[to]=='p' || board_tab[to]=='P')
    _wynik+=PowP;
  else if (board_tab[to]=='b' || board_tab[to]=='B')
    _wynik+=PowB;
  else if (board_tab[to]=='n' || board_tab[to]=='N')
    _wynik+=PowN;
  else if (board_tab[to]=='r' || board_tab[to]=='R')
    _wynik+=PowR;
  else if (board_tab[to]=='q' || board_tab[to]=='Q')
    _wynik+=PowQ;
//power of board pole
/*
11111111
12222221
12333321
12345321
12345321
12333321
12222221
11111111
*/
  switch (to)
  {
    case 28:
    case 36:
     _wynik+=4;
     break;
    case 27:
    case 35:
     _wynik+=3;
     break;
    case 18:
    case 19:
    case 20:
    case 21:
    case 26:
    case 29:
    case 34:
    case 37:
    case 42:
    case 43:
    case 44:
    case 45:
    _wynik+=2;
     break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 17:
    case 22:
    case 25:
    case 30:
    case 33:
    case 38:
    case 41:
    case 46:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    _wynik+=1;
     break;
  };
  return _wynik;
}
