// 10727130 黃意勛 && 10727124 劉宇廷

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <math.h>

using namespace std ;

typedef char Char1000[1000] ;

struct College {
  int num = 0 ;
  int graduaters = 0 ;
};

class Heap {
  vector<College> list ;
  vector<College> heaplist ;

public:
  College setData( Char1000 cStr, int num ) {
    College temp ;
    string buffer, cut ;
	int tabN = 0 ;
	int indexOfTab = 0 ;
	int i = 0 ;

	temp.num = num ;

	buffer.assign( cStr ) ;     // cStr to string
	while ( tabN < 10 ) {
	  indexOfTab = buffer.find_first_of( '\t', i ) ;

	  if ( tabN == 8 ) {
	    cut = buffer.substr( i, indexOfTab - i ) ;
		temp.graduaters = atoi( cut.c_str() ) ;
	  }

	  i = indexOfTab + 1 ;
	  tabN++ ;
	}
	return temp ;
  }

  void read() {
    FILE *infile ;
	string filenum, filename ;

	cout << endl << "Input a file number: " ;
	cin >> filenum ;
	filename = "input" + filenum + ".txt" ;

    bool isSet = false ;
    while ( !isSet ) {
      infile = fopen( filename.c_str() , "r" ) ;

      if ( infile == NULL ) {
        cout << endl << filename << " does not exit. Try again!" << endl ;
        cout << endl << "Input a file number: " ;
        cin >> filenum ;
        filename = "input" + filenum + ".txt" ;
	  }
      else {
    	Char1000 cStr ;

    	fscanf( infile, "%[^\n]%*c", &cStr ) ;     // three-line title
    	fscanf( infile, "%[^\n]%*c", &cStr ) ;
    	fscanf( infile, "%[^\n]%*c", &cStr ) ;

    	for ( int num = 1 ; fscanf( infile, "%[^\n]%*c", &cStr ) != EOF ; num++ ) {
		  list.push_back( setData( cStr, num ) ) ;
    	}

		fclose( infile ) ;
        isSet = true ;
	  }
	}
  }

  College listToheap( int i ) {
    College temp ;
    temp.num = list.at(i).num ;
	temp.graduaters = list.at(i).graduaters ;
	return temp ;
  }

  void swap( College & i, College & j ) {
    College temp ;
    temp = i ;
    i = j ;
    j = temp ;
  }

  void buildMinheap() {
    heaplist.push_back( listToheap( 0 ) ) ;

	int i = 1 ;
	int position = 0 ;
	bool isChange = false ;

	while( i < list.size() ) {
      heaplist.push_back( listToheap( i ) ) ;

	  if ( heaplist.at( ( i - 1 ) / 2 ).graduaters > heaplist.at( i ).graduaters ) {     // I and dad
        swap( heaplist.at( ( i - 1 ) / 2 ), heaplist.at( i ) )  ;
		isChange = true ;

		while( isChange ) {
		  isChange = false ;
          position = ( position - 1 ) / 2 ;

		  if ( heaplist.at( ( position - 1 ) / 2 ).graduaters > heaplist.at( position ).graduaters ) {     // dad and his dad
		    swap( heaplist.at( ( position - 1 ) / 2 ), heaplist.at( position ) ) ;
		    isChange = true ;
		  }
		}
	  }
	  i++ ;
      position = i ;
    }
  }

  bool isOdd( int i ) {     // true: odd level ; false : even level
    int j = 1 ;
    while ( pow( 2, j ) - 1 < i ) {     // (2^j - 1)
      j++ ;
    }

    if ( pow ( 2, j ) - 1 == i ) {
	  j++ ;
    }

	if ( j % 2 == 1 ) {
	  return true ;
	}
	else {
	  return false ;
	}
  }


  void buildMinMaxheap() {
    heaplist.push_back( listToheap( 0 ) ) ;

	int i = 1 ;
    bool isChange = false ;
    int dad = 0 ;
    int dadG = 0 ;
	int grandpa ;
    int grandpaG = 0 ;

	while( i < list.size() ) {
      heaplist.push_back( listToheap( i ) ) ;

	  if ( isOdd( i ) ) {     // in odd level
        if ( heaplist.at( ( i - 1 ) / 2 ).graduaters < heaplist.at( i ).graduaters ) {     // I and dad
          swap( heaplist.at( ( i - 1 ) / 2 ), heaplist.at( i ) ) ;

		  dad = ( i - 1 ) / 2 ;
		  dadG = (dad - 1) / 2 ;
          dadG = (dadG - 1) / 2 ;

          if ( dad > 2 && heaplist.at( dad ).graduaters > heaplist.at( dadG ).graduaters ) {     // dad and his grandpa( if dad has )
            swap( heaplist.at( dad ), heaplist.at( dadG ) )  ;
			isChange = true ;

			while ( isChange ) {
	  		  isChange = false ;
			  dad = dadG ;
			  dadG = ( dadG - 1 ) / 2 ;
			  dadG = ( dadG - 1 ) / 2 ;

			  if ( dad > 2 && heaplist.at( dad ).graduaters > heaplist.at( dadG ).graduaters ) {
			    swap( heaplist.at( dad ), heaplist.at( dadG ) )  ;
				isChange = true ;
			  }
            }
          }
        }

		grandpa = ( i - 1 ) / 2 ;
		grandpa = ( grandpa - 1 ) / 2 ;
		if ( i > 2 && heaplist.at( grandpa ).graduaters > heaplist.at( i ).graduaters ) {    // I and grandpa
	  	  swap( heaplist.at( grandpa ), heaplist.at( i ) )  ;
		  isChange = true ;

		  while ( isChange ) {
		    isChange = false ;
			grandpa = grandpaG ;
			grandpaG = ( grandpa - 1 ) / 2 ;
			grandpaG = ( grandpaG - 1 ) / 2 ;

			if ( grandpa > 2 && heaplist.at( grandpaG ).graduaters > heaplist.at( grandpa ).graduaters ) {     // grandpa and his grandpa( if grandpa has )
			  swap( heaplist.at( grandpaG ), heaplist.at( grandpa ) )  ;
			  isChange = true ;
			}
		  }
		}
	  }
      else {     // in even level
        if ( heaplist.at( ( i - 1 ) / 2 ).graduaters > heaplist.at( i ).graduaters ) {     // I and dad
		  swap( heaplist.at( ( i - 1 ) / 2 ), heaplist.at( i ) ) ;

		  dad = ( i - 1 ) / 2 ;
		  dadG = (dad - 1) / 2 ;
		  dadG = (dadG - 1) / 2 ;

		  if ( dad > 2 && heaplist.at( dad ).graduaters < heaplist.at( dadG ).graduaters ) {     // dad and his grandpa( if dad has )
            swap( heaplist.at( dad ), heaplist.at( dadG ) )  ;
			isChange = true ;

			while ( isChange ) {
			  isChange = false ;
			  dad = dadG ;
			  dadG = ( dadG - 1 ) / 2 ;
			  dadG = ( dadG - 1 ) / 2 ;

			  if ( dad > 2 && heaplist.at( dad ).graduaters < heaplist.at( dadG ).graduaters ) {
                swap( heaplist.at( dad ), heaplist.at( dadG ) )  ;
				isChange = true ;
              }
			}
          }
        }

		grandpa = ( i - 1 ) / 2 ;
		grandpa = ( grandpa - 1 ) / 2 ;
		if ( i > 2 && heaplist.at( grandpa ).graduaters < heaplist.at( i ).graduaters ) {     // I and grandpa
		  swap( heaplist.at( grandpa ), heaplist.at( i ) )  ;
		  isChange = true ;

		  while ( isChange ) {
		    isChange = false ;
			grandpa = grandpaG ;
			grandpaG = ( grandpa - 1 ) / 2 ;
			grandpaG = ( grandpaG - 1 ) / 2 ;

			if ( grandpa > 2 && heaplist.at( grandpaG ).graduaters < heaplist.at( grandpa ).graduaters ) {     // grandpa and his grandpa( if grandpa has )
			  isChange = true ;
			  swap( heaplist.at( grandpaG ), heaplist.at( grandpa ) )  ;
			}
          }
        }
	  }
	  i++ ;
    }
  }

  void ans() {
    cout << "root: " << "[" << heaplist.at(0).num << "] " << heaplist.at(0).graduaters << endl ;
	cout << "bottom: " << "[" << heaplist.at( heaplist.size() - 1 ).num << "] " << heaplist.at( heaplist.size() - 1 ).graduaters << endl ;

	int i = 0, j = 0 ;
	while ( i <= heaplist.size() - 1 ) {     // "<=" 3/17 modify
	  j = i ;
      i = ( i * 2 ) + 1 ;
	}
    cout << "leftmost bottom: " << "[" << heaplist.at( j ).num << "] " << heaplist.at( j ).graduaters << endl << endl ;
  }

  void clear(){
    list.clear() ;
	heaplist.clear() ;
  }

  void printTitle() {
    cout << "***** Heap Construction *****" << endl ;
    cout << "* 0. Quit                   *" << endl ;
    cout << "* 1. Build a min heap       *" << endl ;
    cout << "* 2. Build a min-max heap   *" << endl ;
    cout << "*****************************" << endl ;
    cout << "Input a choice(0, 1, 2): " ;
  }
};

int main() {
  string choice ;
  Heap heap ;
  heap.printTitle() ;
  cin >> choice ;

  while ( choice != "0" ) {
    if ( choice == "1" ) {
	  heap.read() ;
	  heap.buildMinheap() ;
	  cout << endl << "<min heap>" << endl ;
	  heap.ans() ;
	  heap.clear() ;
	}
	else if ( choice == "2" ) {
	  heap.read() ;
	  heap.buildMinMaxheap() ;
	  cout << endl << "<min-max heap>" << endl ;
	  heap.ans() ;
	  heap.clear() ;
	}

	if ( choice != "1" && choice != "2" ) {
	  cout << endl << "Command does not exit!"  << endl << endl ;
	}

	heap.printTitle() ;
	cin >> choice ;
  }
}
