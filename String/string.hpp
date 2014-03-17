// Aaron Battershell 6/3/14
// OOP Assignment 2

#ifndef STRING_HPP
#define STRING_HPP

class String {
	private:
		char *ptr;
		int capacity;
		int _size() const;

	public:
		String();
		String(const String&);
		String(const char*);
		~String();
		
		bool empty() const;
		int size() const;
		
		char operator [] (const int) const;
		bool operator == (const String &) const;
		bool operator != (const String &) const;
		bool operator < (const String &) const;
		bool operator > (const String &) const;
		bool operator <= (const String &) const;
		bool operator >= (const String &) const;
		void operator = (const String &);
		String operator + (const String &);
		void operator += (const String &);
};

#endif