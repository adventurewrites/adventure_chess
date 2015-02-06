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
using namespace std;

/*
*char array was changed to string*
char board_tab[][64]={"r","n","b","q","k","b","n","r",
                    "p","p","p","p","p","p","p","p",
                     ".",".",".",".",".",".",".",".",
                     ".",".",".",".",".",".",".",".",
                     ".",".",".",".",".",".",".",".",
                     ".",".",".",".",".",".",".",".",
                     "P","P","P","P","P","P","P","P",
                     "R","N","B","Q","K","B","N","R"};
*/

char move_tab[][64]={"a8","b8","c8","d8","e8","f8","g8","h8",
                     "a7","b7","c7","d7","e7","f7","g7","h7",
                     "a6","b6","c6","d6","e6","f6","g6","h6",
                     "a5","b5","c5","d5","e5","f5","g5","h5",
                     "a4","b4","c4","d4","e4","f4","g4","h4",
                     "a3","b3","c3","d3","e3","f3","g3","h3",
                     "a2","b2","c2","d2","e2","f2","g2","h2",
                     "a1","b1","c1","d1","e1","f1","g1","h1"};

////////////////////CLASS SZACHOWNICA/////////////////////////////////////////
class szachownica
{
private:
  string board_tab;//board definition
  vector<string> l_movies;//history of movies
  vector<string> b_tab;//history of board arrangement
  vector<int> flight_bit;//history of board arrangement
  vector<int> wcastling_w;//history of board arrangement
  vector<int> wcastling_b;//history of board arrangement
  int WCASTLING_W;//was castling white done
  int WCASTLING_B;//was castling black done

  int find_move_tab(string s);//find move s
  int find_pos_of_figure(char s);//find position of any figure
  int find_int_in_table(int i, int size, int *tab);//find integer in table
  int is_check(int from, int to, int _black_or_white);//verify that is check
  int power_of_move(int to);//check the power of move
  int do_move(int _black_or_white,int _wynik, int _h1, int _h2, int castling, string _move);//moving :)
  int rewrite_tab(int backward);//saving last move :)
  int FLIGHT_BIT;//is flight bit possible (position in the table)

public:
  string move;//move string
  string TITLE;
  string BUG_R;
  string NO_MOVIES;
  char *LIST;
  char *BACK;
  char *SAVE;
  char *LOAD;
  char *QUIT;
  char *SHOW;
  char *HELP;
  char *BAD_MOVE;
  char *BAD_MOVE_CHECK;
  char *BAD_SAVE;
  char *GOOD_SAVE;
  char *BAD_LOAD;
  char *GOOD_LOAD;
//  char *FILENAME;
  char *WIN;
  char *LOSE;
  char *WHITE_MOVE;
  char *BLACK_MOVE;
  char *H_LABEL;
  char *H_SHOW;
  char *H_HELP;
  char *H_QUIT;
  char *H_LIST;
  char *H_BACK;
  char *H_SAVE;
  char *H_LOAD;
  unsigned int black_or_white;//checking black or white move (1 - white move)
  int DEBUG;//DEBUG variable

  szachownica(int _i);//constructor

  void show();//showing actual board
  void list();//printing list of movies
  void back(int engine);//backing last move (white and black together
  void save();//saving game to file "filename"
  void load();//loading game from file "filename"
  void help();//printing help screen
  int move_ok(string move, int &_moc);//prechecking right move
  int valid_move_pawn(int from,int to,unsigned int _black_or_white, int &_moc, string _move);//checking right move (pawn only)
  int valid_move_rook(int from,int to,unsigned int _black_or_white, int &_moc, string _move);//checking right move (rook only)
  int valid_move_bishop(int from,int to,unsigned int _black_or_white, int &_moc, string _move);//checking right move (bishop only)
  int valid_move_queen_king(int from,int to,unsigned int _black_or_white,int maxloop, int &_moc, string _move);//checking right move (queen and king)
  int valid_move_knight(int from,int to,unsigned int _black_or_white, int &_moc, string _move);//checking right move (knight only)

  void engine();
  void engine_loop(unsigned int black_or_white,int &MAXmoc,string &MAXmove, int&, int);
};

//***********************************************************************************************************
int szachownica::rewrite_tab(int backward)
//***********************************************************************************************************
{
  int i;
  if (backward)
      { b_tab.push_back(board_tab);
        flight_bit.push_back(FLIGHT_BIT);
        wcastling_w.push_back(WCASTLING_W);
        wcastling_b.push_back(WCASTLING_B);
      }
  else
      { board_tab=b_tab[b_tab.size()-1];
        b_tab.pop_back();
        flight_bit.pop_back();
        wcastling_w.pop_back();
        wcastling_b.pop_back();
//        FLIGHT_BIT=flight_bit[flight_bit.size()-1];
        WCASTLING_W=wcastling_w[wcastling_w.size()-1];
        WCASTLING_B=wcastling_b[wcastling_b.size()-1];
      };
  return 0;
};

//***********************************************************************************************************
int szachownica::find_move_tab(string s)//checking is move valid
//***********************************************************************************************************
{
  int _i=0,_wynik=-1;
  while (_i<64)
  {
    if (move_tab[_i]==s)
      { _wynik=_i;
        break;
      };
    _i+=1;
  };
  return _wynik;
};

//***********************************************************************************************************
int szachownica::find_int_in_table(int i, int size, int *tab)//find integer in table
//***********************************************************************************************************
{
  int _i=0,_wynik=-1;
  while (_i<size)
  {
    if (tab[_i]==i)
      { _wynik=_i;
        break;
      };
    _i+=1;
  };
  return _wynik;
};

//***********************************************************************************************************
void szachownica::show()
//***********************************************************************************************************
{
  int _i,_j; //local variables
  unsigned int _k = 9;
  for (_i=0;_i<64;_i++)
  {
    if ((_i%8)==0)
    {
      _k-=1;
      cout << endl;
      cout << _k << "| ";
    };
    cout << board_tab.at(_i)<<" ";
  };
  cout << endl;
  cout << "   _______________"<<endl;
  cout << "   a b c d e f g h"<<endl;
};

//***********************************************************************************************************
void szachownica::list()
//***********************************************************************************************************
{
  unsigned int _i; //local variables
  if (l_movies.size())
    { for (_i=0;_i<l_movies.size();_i++)
      {
        if ((_i%2)==0)
          cout <<_i+1<<". "<<l_movies.at(_i)<< endl;
        else
          cout <<_i+1<<".   "<<l_movies.at(_i)<< endl;
      };
    }
  else
    cout<<NO_MOVIES<<endl;
  cout << endl;
//flight_bit ---- drukujemy tylko gdy DEBUG
if (DEBUG)
{
  if (flight_bit.size())
    { for (_i=0;_i<flight_bit.size();_i++)
      {
        if ((_i%2)==0)
          cout <<_i+1<<". "<<flight_bit.at(_i)<< endl;
        else
          cout <<_i+1<<".   "<<flight_bit.at(_i)<< endl;
      };
    }
  else
    cout<<NO_MOVIES<<endl;
  cout << endl;
}
////////////////////////////////////
};

//***********************************************************************************************************
void szachownica::save()
//***********************************************************************************************************
{
  string temp;
  fstream _file;
//loading filename
  cin >> temp;
  temp = temp+".adv";
  char *_filename = (char*)malloc( sizeof( char ) *(temp.length() +1) );
  strcpy(_filename, temp.c_str() );
  _file.open(_filename,fstream::out);
  if (_file.is_open())
  {
//saving of board status history
    if (b_tab.size())
      { for (int _i=0;_i<b_tab.size();_i++)
        {
            _file << b_tab.at(_i) << "|";
        };
        _file <<endl;
      }
//saving history of movies
    if (l_movies.size())
      { for (int _i=0;_i<l_movies.size();_i++)
        {
            _file << l_movies.at(_i) << "|";
        };
        _file <<endl;
      }
//saving of board status actual
        _file << board_tab << "|";
        _file <<endl;
//saving of flight_bit
    if (flight_bit.size())
      { for (int _i=0;_i<flight_bit.size();_i++)
        {
            _file << flight_bit.at(_i) << "|";
        };
        _file <<endl;
      }
//saving of castling_w
    if (wcastling_w.size())
      { for (int _i=0;_i<wcastling_w.size();_i++)
        {
            _file << wcastling_w.at(_i) << "|";
        };
        _file <<endl;
      }
//saving of castling_b
    if (wcastling_b.size())
      { for (int _i=0;_i<wcastling_b.size();_i++)
        {
            _file << wcastling_b.at(_i) << "|";
        };
        _file <<endl;
      }
//close of file
    _file.close();
    cout << GOOD_SAVE << _filename << endl;
  }
  else
  cout << BAD_SAVE << endl;
}

//***********************************************************************************************************
void szachownica::load()
//***********************************************************************************************************
{
  string temp;
  fstream _file;
  string _line, _lin1;
  int found;
  int _k,_l,_length;
  char *cstr;
//loading filename
  cin >> temp;
  temp = temp+".adv";
  char *_filename = (char*)malloc( sizeof( char ) *(temp.length() +1) );
  strcpy(_filename, temp.c_str() );
  _file.open(_filename,fstream::in);
  if (_file.is_open())
  {
//reading of file line - status of board history
    getline(_file,_line);
    if (_line!="\n")
    { _k = _l = 0;
      b_tab.clear();
      found=_line.find_first_of("|");
      while (found!=string::npos)
      {
        _l = found;
//      cout << _line.substr(_k,_l-_k) << endl;
        b_tab.push_back(_line.substr(_k,_l-_k));
        _k = _l+1;
        found=_line.find_first_of("|",found+1);
      }
    }
    getline(_file,_line);
    if (_line!="\n")
    { _k = _l = 0;
      l_movies.clear();
      found=_line.find_first_of("|");
      while (found!=string::npos)
      {
        _l = found;
        l_movies.push_back(_line.substr(_k,_l-_k));
        _k = _l+1;
        found=_line.find_first_of("|",found+1);
      }
    }
//reading status of board actual setting
    getline(_file,_line);
    if (_line!="\n")
      board_tab = _line.substr(0,64);
//reading of file line - status of flight_bit
    getline(_file,_line);
    if (_line!="\n")
    { _k = _l = 0;
      flight_bit.clear();
      found=_line.find_first_of("|");
      while (found!=string::npos)
      {
        _l = found;
//************************************************
//changing string to integer
              _lin1 = _line.substr(_k,_l-_k);
              cstr = new char [_lin1.size()+1];
              strcpy (cstr, _lin1.c_str());
//************************************************
        flight_bit.push_back(atoi(cstr));
        delete[] cstr;
        _k = _l+1;
        found=_line.find_first_of("|",found+1);
      }
    }
//reading of file line - status of wcastling_w
    getline(_file,_line);
    if (_line!="\n")
    { _k = _l = 0;
      wcastling_w.clear();
      found=_line.find_first_of("|");
      while (found!=string::npos)
      {
        _l = found;
//************************************************
//changing string to integer
              _lin1 = _line.substr(_k,_l-_k);
              cstr = new char [_lin1.size()+1];
              strcpy (cstr, _lin1.c_str());
//************************************************
        wcastling_w.push_back(atoi(cstr));
        delete[] cstr;
        _k = _l+1;
        found=_line.find_first_of("|",found+1);
      }
    }
//reading of file line - status of wcastling_b
    getline(_file,_line);
    if (_line!="\n")
    { _k = _l = 0;
      wcastling_b.clear();
      found=_line.find_first_of("|");
      while (found!=string::npos)
      {
        _l = found;
//************************************************
//changing string to integer
              _lin1 = _line.substr(_k,_l-_k);
              cstr = new char [_lin1.size()+1];
              strcpy (cstr, _lin1.c_str());
//************************************************
        wcastling_b.push_back(atoi(cstr));
        delete[] cstr;
        _k = _l+1;
        found=_line.find_first_of("|",found+1);
      }
    }
//-------------------------------------------------------------------------------
    _file.close();
    cout << GOOD_LOAD << _filename << endl;
  }
  else
  cout << BAD_LOAD << endl;
}


//***********************************************************************************************************
void szachownica::back(int engine)
//***********************************************************************************************************
{
  if ((b_tab.size() && b_tab.size()%2!=0) || engine)//backing one move (only if black)
    {  rewrite_tab(0);
       l_movies.pop_back();
//       show();
       if (engine)
          black_or_white=0;
       else
          black_or_white=1;
    }
  else if (b_tab.size() && b_tab.size()%2==0)//backing two moves (only if white)
    {  rewrite_tab(0);
       rewrite_tab(0);
       l_movies.pop_back();
       l_movies.pop_back();
//       show();
    }
  else
    cout<<NO_MOVIES<<endl;
};

//***********************************************************************************************************
void szachownica::help()
//***********************************************************************************************************
{
  cout << endl;
  cout << TITLE << endl;
  cout << BUG_R << endl;
  cout << H_LABEL << endl;
  cout << H_HELP << endl;
  cout << H_SHOW << endl;
  cout << H_LIST << endl;
  cout << H_BACK << endl;
  cout << H_SAVE << endl;
  cout << H_LOAD << endl;
  cout << H_QUIT << endl;
};

//***********************************************************************************************************
int szachownica::move_ok(string _move, int &_moc)
//***********************************************************************************************************
//valid move checking
{
  int _wynik;//return of function
  int _h1,_h2;//help vars
  int _vp;//is valid pawn
  string from,to;//object of string - moves from..to
  string _fig1,_fig2;
  from=_move.substr(0,2);
  to=_move.substr(2,2);
  string _filename;//name of file for saving and loading of game
  if (_move!=QUIT)
    { _wynik=100;
      if (_move==HELP)//help screen
        {
          _wynik=3;
          help();
        }
      else if (_move==SHOW)//showing board
        { _wynik=3;
          show();
        }
      else if (_move==LIST)//printing list of movies
        { _wynik=3;
          list();
        }
      else if (_move==BACK)//backing last move
        { _wynik=3;
          back(0);
        }
      else if (_move==SAVE)//saving game to file
        { _wynik=3;
          save();
        }
      else if (_move==LOAD)//saving game to file
        { _wynik=3;
          load();
        }
      else
        {
           _h1=find_move_tab(from);
           _h2=find_move_tab(to);
           if (black_or_white)
//checking when black side want to move white figure and when black figure want to beat black one
              { _fig1="RNBQKP";
                _fig2="rnbqkp.";
                _vp=(_fig1.find(board_tab[_h1])!=_fig1.npos && _fig2.find(board_tab[_h2])!=_fig2.npos);
              }
           else
//checking when white side want to move black figure and when white figure want to beat white one
              { _fig1="rnbqkp";
                _fig2="RNBQKP.";
                _vp=(_fig1.find(board_tab[_h1])!=_fig1.npos && _fig2.find(board_tab[_h2])!=_fig2.npos);
              }
//--------------------------------------
           if ( _h1!=-1 && _h2!=-1
                && board_tab[_h1]!='.'
                && _vp
               )
               {
//valid move checking-------------------------------------------------
                 _wynik=1;
                 if (board_tab[_h1]=='p' || board_tab[_h1]=='P')//test that pawn move is valid
                    _wynik=valid_move_pawn(_h1,_h2,black_or_white,_moc,_move);
                 else if (board_tab[_h1]=='r' || board_tab[_h1]=='R')//test that rook move is valid
                    _wynik=valid_move_rook(_h1,_h2,black_or_white,_moc,_move);
                 else if (board_tab[_h1]=='b' || board_tab[_h1]=='B')//test that bishop move is valid
                    _wynik=valid_move_bishop(_h1,_h2,black_or_white,_moc,_move);
                 else if (board_tab[_h1]=='q' || board_tab[_h1]=='Q')//test that queen move is valid
                    _wynik=valid_move_queen_king(_h1,_h2,black_or_white,7,_moc,_move);
                 else if (board_tab[_h1]=='k' || board_tab[_h1]=='K')//test that king move is valid
                    _wynik=valid_move_queen_king(_h1,_h2,black_or_white,1,_moc,_move);
                 else if (board_tab[_h1]=='n' || board_tab[_h1]=='N')//test that knight move is valid
                    _wynik=valid_move_knight(_h1,_h2,black_or_white,_moc,_move);
//--------------------------------------------------------------------
//making move
                 if (_wynik==1 || _wynik==2)
//ordinary move
                   {
//check black or white move
                     if (black_or_white)
                       black_or_white=0;
                     else
                       black_or_white=1;
                   }
                 else if (_wynik==-1)
                    _wynik=101;//king is checked (bad move)
                 else
                    _wynik=100;//bad move
               };
           if (!_wynik)
              _wynik=100;//bad move
        };
    }
  else
    {
      _wynik=0;
    };
  return _wynik;
};

//***********************************************************************************************************
int szachownica::do_move(int _black_or_white,int _wynik,int _h1, int _h2, int castling, string _move)
//***********************************************************************************************************
{
  if (_wynik==1)
     {
       rewrite_tab(1);//storing last move
       board_tab[_h2]=board_tab[_h1];
       board_tab[_h1]='.';
       if (castling)
         { if (_h2==62)
            { board_tab[61]=board_tab[63];
              board_tab[63]='.';
            }
           else if (_h2==58)
            { board_tab[59]=board_tab[56];
              board_tab[56]='.';
            }
           else if (_h2==6)
            { board_tab[5]=board_tab[7];
              board_tab[7]='.';
            }
           else if (_h2==2)
            { board_tab[3]=board_tab[0];
              board_tab[0]='.';
            }
           else _wynik=0;
         };
       l_movies.push_back(_move);//saving last move in moves list
     }
  else if (_wynik==2)//_wynik=2
     {
       rewrite_tab(1);//storing last move
       if (_black_or_white)
         board_tab[_h2]='Q';//change pawn for queen (white)
       else
         board_tab[_h2]='q';//change pawn for queen (black)
       board_tab[_h1]='.';
       l_movies.push_back(_move);//saving last move in moves list
     };
  return _wynik;
};

//***********************************************************************************************************
int szachownica::find_pos_of_figure(char s)
//***********************************************************************************************************
{
  int _pos=0;
  while (board_tab[_pos]!=s && _pos<64)
    {
      _pos++;
    };
  return _pos;
};

//***********************************************************************************************************
int szachownica::is_check(int from, int to, int _black_or_white)
//***********************************************************************************************************
{
  int _wynik=1;
  int _iter=0;
  int _pos;
  int _pool;
  string _fig,_fig1,_fig2,_fig3,_fig1a,_fig2a;
  if (!_black_or_white)
    { _pos=find_pos_of_figure('k');
      _fig1="RQK";
      _fig2="QBK";
      _fig3="QBKP";
      _fig1a="RQ";
      _fig2a="QB";
    }
  else
    { _pos=find_pos_of_figure('K');
      _fig1="rqk";
      _fig2="qbk";
      _fig3="qbkp";
      _fig1a="rq";
      _fig2a="qb";
    };
//first case: checking are rook, queen or king (from down of board)
  _pool=_pos+8;
  _fig=_fig1;
  while (_wynik==1 && _iter<7 && _pool<64 && _pool>=0)
    {
      _iter++;
      if (_fig.find(board_tab[_pool])!=_fig.npos)
        _wynik=-1;
      else if (board_tab[_pool]!='.')
        _wynik=0;
      _fig=_fig1a;
      _pool+=8;
    };

//second case: checking are rook, queen or king (from up of board)
  _pool=_pos-8;
  _fig=_fig1;
  _iter=0;
  if (!_wynik)
     _wynik=1;
  while (_wynik==1 && _iter<7 && _pool<64 && _pool>=0)
    {
      _iter++;
      if (_fig.find(board_tab[_pool])!=_fig.npos)
        _wynik=-1;
      else if (board_tab[_pool]!='.')
        _wynik=0;
      _fig=_fig1a;
      _pool-=8;
    };

//third case: checking are rook, queen or king (from right of board)
  _pool=_pos+1;
  _fig=_fig1;
  _iter=0;
  if (!_wynik)
     _wynik=1;
  while (_wynik==1 && _iter<7 && _pool<64 && _pool>=0)
    {
      _iter++;
      if (_fig.find(board_tab[_pool])!=_fig.npos)
        _wynik=-1;
      else if (board_tab[_pool]!='.')
        _wynik=0;
      _fig=_fig1a;
      _pool+=1;
    };

//forth case: checking are rook, queen or king (from left of board)
  _pool=_pos-1;
  _fig=_fig1;
  _iter=0;
  if (!_wynik)
     _wynik=1;
  while (_wynik==1 && _iter<7 && _pool<64 && _pool>=0)
    {
      _iter++;
      if (_fig.find(board_tab[_pool])!=_fig.npos)
        _wynik=-1;
      else if (board_tab[_pool]!='.')
        _wynik=0;
      _fig=_fig1a;
      _pool-=1;
    };

//fifth case: checking are bishop, queen or king (pawn) (from up-left of board)
  _pool=_pos-9;
  if (_black_or_white)
      _fig=_fig3;
  else
      _fig=_fig2;
  _iter=0;
  if (!_wynik)
     _wynik=1;
  while (_wynik==1 && _iter<7 && _pool<64 && _pool>=0)
    {
      _iter++;
      if (_fig.find(board_tab[_pool])!=_fig.npos)
        _wynik=-1;
      else if (board_tab[_pool]!='.')
        _wynik=0;
      _fig=_fig2a;
      _pool-=9;
    };

//sixth case: checking are bishop, queen or king (pawn) (from up-right of board)
  _pool=_pos-7;
  if (_black_or_white)
      _fig=_fig3;
  else
      _fig=_fig2;
  _iter=0;
  if (!_wynik)
     _wynik=1;
  while (_wynik==1 && _iter<7 && _pool<64 && _pool>=0)
    {
      _iter++;
      if (_fig.find(board_tab[_pool])!=_fig.npos)
        _wynik=-1;
      else if (board_tab[_pool]!='.')
        _wynik=0;
      _fig=_fig2a;
      _pool-=7;
    };

//seventh case: checking are bishop, queen or king (pawn) (from down-left of board)
  _pool=_pos+9;
  if (!_black_or_white)
      _fig=_fig3;
  else
      _fig=_fig2;
  _iter=0;
  if (!_wynik)
     _wynik=1;
  while (_wynik==1 && _iter<7 && _pool<64 && _pool>=0)
    {
      _iter++;
      if (_fig.find(board_tab[_pool])!=_fig.npos)
        _wynik=-1;
      else if (board_tab[_pool]!='.')
        _wynik=0;
      _fig=_fig2a;
      _pool+=9;
    };

//eighth case: checking are bishop, queen or king (pawn) (from down-right of board)
  _pool=_pos+7;
  if (!_black_or_white)
      _fig=_fig3;
  else
      _fig=_fig2;
  _iter=0;
  if (!_wynik)
     _wynik=1;
  while (_wynik==1 && _iter<7 && _pool<64 && _pool>=0)
    {
      _iter++;
      if (_fig.find(board_tab[_pool])!=_fig.npos)
        _wynik=-1;
      else if (board_tab[_pool]!='.')
        _wynik=0;
      _fig=_fig2a;
      _pool+=7;
    };

//nineth case: checking are knight
  if (!_black_or_white)
      _fig="N";
  else
      _fig="n";
  _iter=0;
  if (!_wynik)
     _wynik=1;
  for (int _x=0;_x<8;_x++)
  {
    switch (_x)
      {
        case 0:
          _pool=_pos+6;
          break;
        case 1:
          _pool=_pos+10;
          break;
        case 2:
          _pool=_pos+15;
          break;
        case 3:
          _pool=_pos+17;
          break;
        case 4:
          _pool=_pos-17;
          break;
        case 5:
          _pool=_pos-15;
          break;
        case 6:
          _pool=_pos-10;
          break;
        case 7:
          _pool=_pos-6;
          break;
        default:
          _pool=_pos;
      };
    while (_wynik==1 && _iter<1 && _pool<64 && _pool>=0)
      {
        _iter++;
        if (_fig.find(board_tab[_pool])!=_fig.npos)
          _wynik=-1;
      };
      _iter = 0;
  };
  if (!_wynik)
     _wynik=1;
  return _wynik;
}

//***********************************************************************************************************
int szachownica::valid_move_pawn(int from, int to, unsigned int _black_or_white,int &_moc,string _move)
//***********************************************************************************************************
{
  int _wynik=0;
  int _mnoznik;
  int _double_posible;//is double move posible
  int _change_for_queen;//is change for queen posible
  unsigned int ffrom=from;
  unsigned int tto=to;
  string _fig;
  FLIGHT_BIT = 0;
  int forbidden_right[8] = {0,8,16,24,32,40,48,56};
  int forbidden_left[8] = {7,15,23,31,39,47,55,63};
//czy mozliwy podwojny ruch pionem i czy mozliwa zamiana piona na krolowa
//piona mozna na razie zamieniac TYLKO na krolowa
  if (!_black_or_white)
     { _fig="RNBQP";
       _mnoznik=-1;
       _double_posible=(from<16);
       _change_for_queen=(to>55);
     }
  else
     { _fig="rnbqp";
       _mnoznik=1;
       _double_posible=(from>47);
       _change_for_queen=(to<8);
     };
//right move
  if (from-(8*_mnoznik)==to && board_tab[to]=='.')//move on one pole
    {
      if (_change_for_queen)
        { _wynik=2;//exchange pawn for queen
          _moc=16;
        }
      else
        { _wynik=1;
          _moc=0;
        }
//      FLIGHT_BIT=0;
    }
  else if (from-(16*_mnoznik)==to && board_tab[to-(8*(-_mnoznik))]=='.' && board_tab[to]=='.' && _double_posible)//move on two poles
    {
      _wynik=1;
//      _moc=0;
      FLIGHT_BIT=to-(8*(-_mnoznik));
    }
  else if (((from-(7*_mnoznik)==to && (((_mnoznik==-1 && find_int_in_table(from,8,forbidden_right)==-1))||((_mnoznik==1 && find_int_in_table(from,8,forbidden_left)==-1))))||((from-(9*_mnoznik)==to && (((_mnoznik==-1 && find_int_in_table(from,8,forbidden_left)==-1))||((_mnoznik==1 && find_int_in_table(from,8,forbidden_right)==-1)))))) && _fig.find(board_tab[to])!=_fig.npos)//bit any figure
    {
      if (_change_for_queen)
        { _wynik=2;//exchange pawn for queen
          _moc=16;
        }
      else
        { _wynik=1;
          _moc=0;
        }
//      FLIGHT_BIT=0;
    }
  else if ((from-(7*_mnoznik)==to || from-(9*_mnoznik)==to) && flight_bit.at(flight_bit.size()-1)==to)//bit in flight
    {
      _wynik=1;
      _moc=1;
      board_tab[FLIGHT_BIT-(8*(-_mnoznik))]='.';
//      FLIGHT_BIT=0;
    };
//----------------------------------------------------------------------------------------------------------
  _moc+=power_of_move(tto);
  do_move(_black_or_white,_wynik,ffrom,to,0,_move);
  if (_wynik)//verify that is check
     _wynik=is_check(ffrom,to,_black_or_white);

  if (_wynik==-1)//if check then restore last position
     {  rewrite_tab(0);
        l_movies.pop_back();
     };

  return _wynik;
};

//***********************************************************************************************************
int szachownica::valid_move_rook(int from,int to,unsigned int _black_or_white, int &_moc, string _move)
//***********************************************************************************************************
{
  int _wynik=1;
  int _mnoznik,_znak;
  int _i=0;
  unsigned int ffrom=from;
  unsigned int tto=to;
  string _fig;
  FLIGHT_BIT=0;
  if (!_black_or_white)//is black or white moving
     _fig="RNBQP";
  else
     _fig="rnbqp";
  if (from>to)//side of move
    _znak=-1;
  else
    _znak=1;
  if (abs(to-from)>7)//vertical or horizontal move
    _mnoznik=8;
  else
    _mnoznik=1;
//----------------------------------end of variables setting--------------------------------------
  do
  {
    from+=_mnoznik*_znak;
    _i+=1;
    if (from!=to && board_tab[from]!='.')
      _wynik=0;
    else if (from==to && _fig.find(board_tab[from])==_fig.npos && board_tab[from]!='.')
      _wynik=0;
    else if (_i>7)
      _wynik=0;
  } while (from!=to && _wynik);
//----------------------------------------------------------------------------------------------
//  rewrite_tab(1);//storing last move
  _moc=power_of_move(tto);
  do_move(_black_or_white,_wynik,ffrom,to,0,_move);
  if (_wynik)//verify that is check
     _wynik=is_check(ffrom,to,_black_or_white);
  if (_wynik==-1)//if check then restore last position
     {  rewrite_tab(0);
        l_movies.pop_back();
     }
  return _wynik;
};

//***********************************************************************************************************
int szachownica::valid_move_bishop(int from,int to,unsigned int _black_or_white, int &_moc, string _move)
//***********************************************************************************************************
{
  int _wynik=1;
  int _znak,_mnoznik;
  int _i=0;
  unsigned int ffrom=from;
  unsigned int tto=to;
  string _fig;
  FLIGHT_BIT=0;
  if (!_black_or_white)//is black or white  moving
     _fig="RNBQP";
  else
     _fig="rnbqp";
  if (from>to)//side of move
    _znak=-1;
  else
    _znak=1;
  if ((from-to)%7==0)
    _mnoznik=7;
  else if ((from-to)%9==0)
    _mnoznik=9;
  else
    _wynik=0;
//check wall
  if (_wynik)
  {
    if ((ffrom%8>=tto%8 && _mnoznik==9 && _znak==1)
       ||  (ffrom%8<=tto%8 && _mnoznik==9 && _znak==-1)
       ||  (ffrom%8<=tto%8 && _mnoznik==7 && _znak==1)
       ||  (ffrom%8>=tto%8 && _mnoznik==7 && _znak==-1))
      _wynik=0;
  }
//----------------------------------end of variables setting--------------------------------------
  if (_wynik)
  {  do
    {
      from+=_mnoznik*_znak;
      _i+=1;
      if (from!=to && board_tab[from]!='.')
        _wynik=0;
      else if (from==to && _fig.find(board_tab[from])==_fig.npos && board_tab[from]!='.')
        _wynik=0;
      else if (_i>7)
        _wynik=0;
    } while (from!=to && _wynik && from%7 && from%8);
  };
//----------------------------------------------------------------------------------------------
  _moc=power_of_move(tto);
  do_move(_black_or_white,_wynik,ffrom,to,0,_move);
  if (_wynik)//verify that is check
     _wynik=is_check(ffrom,to,_black_or_white);
  if (_wynik==-1)//if check then restore last position
     {  rewrite_tab(0);
        l_movies.pop_back();
     }

  return _wynik;
};

//***********************************************************************************************************
int szachownica::valid_move_queen_king(int from,int to,unsigned int _black_or_white,int maxloop, int &_moc, string _move)
//***********************************************************************************************************
{
  int _wynik=1;
  int _znak,_mnoznik;
  int _i=0;
  unsigned int ffrom=from;
  unsigned int tto=to;
  string _fig;
  FLIGHT_BIT=0;
  if (!_black_or_white)//is black or white moving
     _fig="RNBQP";
  else
     _fig="rnbqp";
  if (from>to)//side of move
    _znak=-1;
  else
    _znak=1;
  if ((from-to)%7==0 && (from-to)%8!=0 && (from-to)%9!=0)//obligue move
    _mnoznik=7;
  else if ((from-to)%9==0)//obligue move
    _mnoznik=9;
  else if ((from-to)%8==0)//vertical move
    _mnoznik=8;
  else if (abs(to-from)<8)//horizontal move
    _mnoznik=1;
  else
    _wynik=0;
//check wall
  if (_wynik)
  {
    if ((ffrom%8>=tto%8 && _mnoznik==9 && _znak==1)
       ||  (ffrom%8<=tto%8 && _mnoznik==9 && _znak==-1)
       ||  (ffrom%8<=tto%8 && _mnoznik==7 && _znak==1)
       ||  (ffrom%8>=tto%8 && _mnoznik==7 && _znak==-1))
      _wynik=0;
  }
//----------------------------------end of variables setting--------------------------------------
  if (_wynik)
  {  do
    {
      from+=_mnoznik*_znak;
      _i+=1;
      if (from!=to && board_tab[from]!='.')
        _wynik=0;
      else if (from==to && _fig.find(board_tab[from])==_fig.npos && board_tab[from]!='.')
        _wynik=0;
      else if (_i>maxloop)
        _wynik=0;
    } while (from!=to && _wynik);
  };
//----------------------------------------------------------------------------------------------
  _moc=power_of_move(tto);
  do_move(_black_or_white,_wynik,ffrom,to,0,_move);
  if (_wynik)//verify that is check
     _wynik=is_check(ffrom,to,_black_or_white);
  if (_wynik==-1)//if check then restore last position
     {  rewrite_tab(0);
        l_movies.pop_back();
     }
//--------------------------------------castling move-------------------------------------------
  if (maxloop==1)
  {
    if (_wynik==1)
       {
         if (_black_or_white)
           WCASTLING_W=1;
         else
           WCASTLING_B=1;
       }
    else if (!_wynik)
       {
         if ((ffrom==4 && board_tab[ffrom]=='k' && !black_or_white && !WCASTLING_B &&
            ((to==6 && board_tab[5]=='.' && board_tab[6]=='.' && board_tab[7]=='r') ||
             (to==2 && board_tab[3]=='.' && board_tab[2]=='.' && board_tab[1]=='.' && board_tab[0]=='r')))
         || (ffrom==60 && board_tab[ffrom]=='K' && black_or_white && !WCASTLING_W &&
            ((to==62 && board_tab[61]=='.' && board_tab[62]=='.' && board_tab[63]=='R') ||
             (to==58 && board_tab[59]=='.' && board_tab[58]=='.' && board_tab[57]=='.' &&
              board_tab[56]=='R'))))
            {
               int k;
               int j=2;
               int _krok=0;
               _wynik=1;
               while (j>0 && _wynik!=-1)
                 {
                   _krok++;
                   j--;
                   do_move(_black_or_white,_wynik,ffrom+(_znak*_krok)-(_znak*1),to-(_znak*j),1,_move);
                   if (_wynik)//verify that is check
                   _wynik=is_check(ffrom+(_znak*_krok)-(_znak*1),to-(_znak*j),_black_or_white);
//---------------------------------------------------------------------------------------------
                   if (DEBUG)
                   {
                     cout<<j<<": wynik: "<<_wynik<<endl;
                     cout<<"from: "<<(ffrom+(_znak*_krok)-(_znak*1))<<endl;
                     cout<<"to: "<<(to-(_znak*j))<<endl;
                   }
                   if (_wynik==-1)//if check then restore last position
                     { for (k=0;k<_krok;k++)
                       {  rewrite_tab(0);
                          l_movies.pop_back();
                       };
                     };
                 };
               if (_wynik==1)
                  {
                    if (_black_or_white)
                      WCASTLING_W=1;
                    else
                      WCASTLING_B=1;
                    b_tab.pop_back();
                    flight_bit.pop_back();
                    wcastling_w.pop_back();
                    wcastling_b.pop_back();
                    l_movies.pop_back();
                    l_movies.pop_back();
                    l_movies.push_back(move);

                  };
            };
       };
  };
//-----------------------------------end of castling move----------------------------------------

  return _wynik;
};

//***********************************************************************************************************
int szachownica::valid_move_knight(int from,int to,unsigned int _black_or_white, int &_moc, string _move)
//***********************************************************************************************************
{
//debug
//if (from==6 && to==0)
//  cout << "debug" << endl;
////////////////////

  int _wynik=1;
  int _znak,_mnoznik;
  int _i=0;
  FLIGHT_BIT=0;
  unsigned int ffrom=from;
  unsigned int tto=to;
  int forbidden_6_right[16] = {0,1,8,9,16,17,24,25,32,33,40,41,48,49,56,57};
  int forbidden_6_left[16] = {6,7,14,15,22,23,30,31,38,39,46,47,54,55,62,63};
  int forbidden_15_right[8] = {0,8,16,24,32,40,48,56};
  int forbidden_15_left[8] = {7,15,23,31,39,47,55,63};
  string _fig;
  if (!_black_or_white)//is black or white moving
     _fig="RNBQP";
  else
     _fig="rnbqp";
  if (from>to)//side of move
    _znak=-1;
  else
    _znak=1;
  if ((from-to)%6==0 && ((_znak==1 && find_int_in_table(from,16,forbidden_6_right)==-1)||(_znak==-1 && find_int_in_table(from,16,forbidden_6_left)==-1)) )//knight move one
    _mnoznik=6;
  else if ((from-to)%10==0)//knight move two
    _mnoznik=10;
  else if ((from-to)%15==0 && ((_znak==1 && find_int_in_table(from,8,forbidden_15_right)==-1)||(_znak==-1 && find_int_in_table(from,8,forbidden_15_left)==-1)) )//knight move three
    _mnoznik=15;
  else if ((from-to)%17==0)//knight move four
    _mnoznik=17;
  else
    _wynik=0;
//----------------------------------end of variables setting--------------------------------------
  if (_wynik)
  {  do
    {
      from+=_mnoznik*_znak;
      _i+=1;
      if (from!=to && board_tab[from]!='.')
        _wynik=0;
      else if (from==to && _fig.find(board_tab[from])==_fig.npos && board_tab[from]!='.')
        _wynik=0;
      else if (_i>1)
        _wynik=0;
    } while (from!=to && _wynik);
  };
//----------------------------------------------------------------------------------------------
  if (_wynik)//verify that is check
     { _moc=power_of_move(tto);
       do_move(_black_or_white,_wynik,ffrom,to,0,_move);
     _wynik=is_check(ffrom,to,_black_or_white);
     }
  if (_wynik==-1)//if check then restore last position
     {  rewrite_tab(0);
        l_movies.pop_back();
     }
  return _wynik;
};
