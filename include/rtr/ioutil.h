#ifndef _IO_UTIL_H_
#define _IO_UTIL_H_

/*
 * This software is developed to allow stl removal from the conv node
 * with a minimal intrusion into the conv code itself.
 * The idea is to provide replacements for the STL constructs like cout, cin, etc.
 *
 * The following are the steps to use this software in the conv_nostl version:
 * 1) create convCache_nostl project by copying convCache project
 * 2) add _RDEV_NO_STL_ definition to convCache_nostl project 
 * 3) modify linking in convCache_nostl to link against cxxut_nostl
 * 4) remove stl linking from the convCache_nostl project
 * 5) replace <iostream>, <ostream>, <iomanip> and alike includes in the convCache files
 *    with "OutputUtil.h"
 * 6) do not attempt to change any other line of code in any convCache file
 * 7) link convCache_nostl project with this convOutputUtil project
 * 8) repeat the same procedure for convAnsi, convMfFidDb, and convMfParser as needed
 *
 * this software is a responsibility of the API team.
 */

#if !defined (_RDEV_NO_STL_)
 the _RDEV_NO_STL_ must be defined
#endif
 
#include <stdio.h>
#include <string.h>

// replacements for the STL names
#define cout COUT
#define cerr CERR
#define std  ioutil

namespace ioutil {

// base ios class implementation
class ios
{
public :

	enum openmode { 
		in = 0x01,
		out = 0x02,
		binary = 0x04,
		app = 0x08,
		trunc = 0x10
	};

	enum _FormatFlags { _all = 0xffff, _zero = 0 };

	typedef _FormatFlags fmtflags;

	// formatting flags
	static const _FormatFlags hex		= (_FormatFlags)0x0001;
	static const _FormatFlags oct		= (_FormatFlags)0x0002;
	static const _FormatFlags dec		= (_FormatFlags)0x0004;
	static const _FormatFlags uppercase	= (_FormatFlags)0x0008;

	// formatting mask
	static const _FormatFlags basefield = (_FormatFlags)( hex | oct | dec );

	ios() {}
	virtual ~ios() {}

	virtual size_t width() const = 0;
	virtual size_t width( size_t ) = 0;
};


// basic input steam implementation
class istream : public ios
{
public :

	istream() {}
	virtual ~istream() {}

	virtual int peek() = 0;
	virtual int get() = 0;
	virtual istream& get( char& ) = 0;
	virtual istream& getline( char* , size_t , char delim = '\n' ) = 0;
	virtual istream& unget() = 0;
	virtual size_t gcount() const = 0;

	virtual istream& ignore_ws() = 0;
	virtual istream& ignore_nws() = 0;
};


// input string stream class implementation
class istringstream : public istream
{
public :

	istringstream( const char* , openmode = in );
	virtual ~istringstream();

	// formatted operations -> remove whitespaces
	istream& operator>>( char* );
	istream& operator>>( unsigned char* );

	istream& operator>>( short& );
	istream& operator>>( unsigned short& );

	istream& operator>>( int& );
	istream& operator>>( unsigned int& );

	istream& operator>>( long& );
	istream& operator>>( unsigned long& );

	istream& operator>>( long long& );
	istream& operator>>( unsigned long long& );

	// unformatted operations -> do not remove white spaces
	int peek();
	int get();
	istream& get( char& );
	istream& getline( char* , size_t , char delim = '\n' );
	istream& unget();
	size_t gcount() const { return _gcount; }

	size_t width() const { return _width; }
	size_t width( size_t );

	// operator required to do ws, and similar constructs
	istream& operator>>( istream& (*iPfn)( istream& ) );

	// ignores white spaces
	istream& ignore_ws();
	
	// ignores non white spaces
	istream& ignore_nws();

private :

	// returns true if passed in character is a white space char
	bool is_ws( int );

	char*			_string;
	openmode		_mode;
	size_t			_size;
	size_t			_position;
	size_t			_gcount;
	size_t			_width;
	bool			_widthSet;
};

// special unary operator required to do ws
istream& ws( istream&);


// basic output stream class declaration
// this class is used to simulate cout and cerr utilities from std
class ostream : public ios
{
public :
	
	ostream( FILE* stream ) : _stream( stream ), _flags( _zero ) {}
	virtual ~ostream() { _stream = NULL; _flags = _zero; }

	// basic output operators for different data types
	// these are formatted operations -> they remove white spaces
	virtual ostream& operator<<( char );
	virtual ostream& operator<<( unsigned char );

	virtual ostream& operator<<( const char* );

	virtual ostream& operator<<( int );
	virtual ostream& operator<<( unsigned int );

	virtual ostream& operator<<( long );
	virtual ostream& operator<<( unsigned long );

	virtual ostream& operator<<( long long );
	virtual ostream& operator<<( unsigned long long );

	virtual ostream& operator<<( const void* );

	virtual ostream& operator<<( bool );

	// format setting utilities
	virtual ios::fmtflags setf( fmtflags );
	virtual ios::fmtflags setf( fmtflags, fmtflags );

	virtual size_t width() const { return _width; }
	virtual size_t width( size_t );

	virtual ostream& write( const char* , int );

	// buffer flushing utility
	virtual ostream& flush();

	// operator required to do endl, and io manipulators w/o margs
	virtual ostream& operator<<( ostream& (*oPfn)( ostream& ) );

protected :

	ostream() : _stream( NULL ), _flags( _zero ) {}

	void setStream( FILE* stream ) { _stream = stream; }

	FILE* getStream() const { return _stream; }

private :

	// note: these utilities MUSt be used as prescribed in the .C file
	void formatString( char* , char );
	void formatString( char* , unsigned char );

	void formatString( char* , int );
	void formatString( char* , unsigned int );

	void formatString( char* , long );
	void formatString( char* , unsigned long );

	void formatString( char* , long long );
	void formatString( char* , unsigned long long );

	void formatString( char* , const void* );

	void formatWidth( char* );

	ostream( const ostream& );

	FILE*			_stream;

	// stream state variables
	ios::fmtflags	_flags;
	size_t			_width;
	bool			_widthSet;
};

// special unary operators / manipulators required by ostream and istream
ostream& endl( ostream& );
ostream& dec( ostream& );
ostream& hex( ostream& );
ostream& oct( ostream& );

// implementation of manipulators with arguments of type T for ostream class
template< class T >
class smanip {
public:
	smanip( ostream& (*f)( ostream& , T ), T arg ) : _f( f ), _arg( arg ) {}

	ostream& (*_f)( ostream& , T );
	T _arg;
};

template< class T >
inline ostream& operator<< ( ostream& os, smanip< T > m )
{
	return m._f( os, m._arg );
}

inline ostream& set_width( ostream& s, int n )
{
	s.width( n );
	return s;
}

// setw( int ) manipulator
// it sets the field length for the next numeric output
inline smanip< int > setw( int n ) { return smanip< int >( set_width, n ); }


// basic file input output utility
class fstream : public ostream
{
public :

	fstream();
	fstream( const char* , openmode mode = (openmode)(in | out) );
	virtual ~fstream();

	void open( const char* , openmode mode = (openmode)(in | out) );
	void close();

	bool is_open() const;

	fstream* rdbuf();

	// unformatted operations
	int peek();
	ostream& getline( char* , size_t , int delim = '\n' );
	ostream& ignore( size_t n = 1, int delim = EOF );
	size_t gcount() const { return _gcount; }

private :

	openmode		_mode;
	size_t			_gcount;
};


// singleton objects provided by this library as replacements for cout and cerr
extern ostream COUT;
extern ostream CERR;

} // namespace ioutil

#endif // _IO_UTIL_H_
