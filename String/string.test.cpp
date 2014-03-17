// Aaron Battershell 6/3/14
// OOP Assignment 2

#include "string.hpp"
#include <iostream>
using namespace std;

/* .empty() Test */
int empty_1() {
	try {
		String test1("");
		if (test1.empty() == false) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error empty_1" << endl;
		return 1;
	}
}
int empty_2() {
	try {
		String test1("1");
		if (test1.empty() == true) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error empty_2" << endl;
		return 1;
	}
}
int empty_3() {
	try {
		String test1 = String ("") + String("");
		if (test1.empty() == false) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error empty_3" << endl;
		return 1;
	}
}
int empty_4() {
	try {
		String test1;
		if (test1.empty() == false) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error empty_4" << endl;
		return 1;
	}
}
int empty_5() {
	try {
		char *list = new char[5];
		list[0] = '4';
		list[1] = '3';
		list[2] = '\0';
		String test1(list);
		delete [] list;
		if (test1.empty() == true) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error empty_5" << endl;
		return 1;
	}
}

/* .size() Test */
int size_1() {
	try {
		String test1("");
		if (test1.size() != 0) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error size_1" << endl;
		return 1;
	}
}
int size_2() {
	try {
		String test1("1234");
		if (!(test1.size() == 4)) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error size_2" << endl;
		return 1;
	}
}
int size_3() {
	try {
		String test1("waffle");
		String test2(test1);
		if (test1.size() != 6) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error size_3" << endl;
		return 1;
	}
} 
int size_4() {
	try {
		String test1("10=_`df,?.");
		if (!(test1.size() == 10)) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error size_4" << endl;
		return 1;
	}
}
int size_5() {
	try {
		String test1("wasd");
		String test2 = String("") + String("") + String(test1) + String(test1);
		if (test2.size() != 8) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error size_5" << endl;
		return 1;
	}
}

/* [] Test */
int bracket_1() {
	try {
		char *string1 = new char[5];
		string1[0] = 'a';
		string1[1] = '\0';
		String test1(string1);
		delete [] string1;
		if (test1[0] != 'a') {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error bracket_1" << endl;
		return 1;
	}
}
int bracket_2() {
	try {
		char *string1 = new char[5];
		string1[0] = 'a';
		string1[1] = 'b';
		string1[2] = 's';
		string1[3] = '-';
		string1[4] = '\0';
		String test1(string1);
		delete [] string1;
		if (!(test1[3] == '-')) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error bracket_2" << endl;
		return 1;
	}
}
int bracket_3() {
	try {
		String test1("0001000");
		if (!(test1[3] == '1')) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error bracket_3" << endl;
		return 1;
	}
}
int bracket_4() {
	try {
		String test1("()()()()()");
		if (test1[2] == '(' && !(test1[4] != ')')) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error bracket_4" << endl;
		return 1;
	}
}
int bracket_5() {
	try {
		String test1("*");
		if (!(test1[0] == '*')) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error bracket_5" << endl;
		return 1;
	}
}

/* == Tests */
int equalEqual_1() {
	try {
		if (!(String("1") == String("1"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equalEqual_1" << endl;
		return 1;
	}
}
int	equalEqual_2() {
	try {
		if (!(String("000001") == String("000001"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equalEqual_2" << endl;
		return 1;
	}
}
int equalEqual_3() {
	try {
		if (!(String("") == String(""))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equalEqual_3" << endl;
		return 1;
	}
}
int equalEqual_4() {
	try {
		if (!(String("__") == String("__"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equalEqual_4" << endl;
		return 1;
	}
}
int equalEqual_5() {
	String test1("~1a?/");
	try {
		if (!(String(test1) == String("~1a?/"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equalEqual_5" << endl;
		return 1;
	}
}

/* != Tests */
int notEqual_1() {
	String test1("~1a?/");
	try {
		if (String(test1) != String("~1a?/")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error notEqual_1" << endl;
		return 1;
	}
}
int notEqual_2() {
	try {
		if (String("__") != String("__")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error notEqual_2" << endl;
		return 1;
	}
}
int notEqual_3() {
	try {
		if (String("") != String("")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error notEqual_3" << endl;
		return 1;
	}
}
int notEqual_4() {
	try {
		if (String("000001") != String("000001")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error notEqual_4" << endl;
		return 1;
	}
}
int notEqual_5() {
	try {
		if (String("1") != String("1")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error notEqual_5" << endl;
		return 1;
	}
}

/* < Test */
int lesser_1() {
	try {
		if (String("a") < String("a")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lesser_1" << endl;
		return 1;
	}
}
int lesser_2() {
	try {
		if (!(String("a") < String("aa"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lesser_2" << endl;
		return 1;
	}
}
int lesser_3() {
	try {
		if (String("") < String("")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lesser_3" << endl;
		return 1;
	}
}
int lesser_4() {
	try {
		String test1("543");
		String test2("345");
		if (String(test1) < String(test2)) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lesser_4" << endl;
		return 1;
	}
}
int lesser_5() {
	try {
		String test1("345");
		String test2("543");
		if (!(String(test1) < String("aa"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lesser_5" << endl;
		return 1;
	}
}

/* > Test */
int greater_1() {
	try {
		if (String("a") > String("a")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greater_1" << endl;
		return 1;
	}
}
int greater_2() {
	try {
		if (String("a") > String("aa")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greater_2" << endl;
		return 1;
	}
}
int greater_3() {
	try {
		if (String("") > String("")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greater_3" << endl;
		return 1;
	}
}
int greater_4() {
	try {
		String test1("543");
		String test2("345");
		if (!(String(test1) > String(test2))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greater_4" << endl;
		return 1;
	}
}
int greater_5() {
	try {
		String test1("345");
		String test2("543");
		if (String(test1) > String("aa")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greater_5" << endl;
		return 1;
	}
}

/* <= Test*/
int lessEqual_1() {
	try {
		String test1("aaa");
		if (String(test1) <= String("aa")) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lessEqual_1" << endl;
		return 1;
	}
}
int	lessEqual_2() {
	try {
		String test1("aaa");
		if (!(String("aa") <= String(test1))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lessEqual_2" << endl;
		return 1;
	}
}
int lessEqual_3() {
	try {
		String test1(""), test2("");
		if (!(String(test1) <= String(test2))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lessEqual_3" << endl;
		return 1;
	}
}
int lessEqual_4() {
	try {
		String test1("44"), test2("1");
		if (String(test1) <= String(test2)) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lessEqual_4" << endl;
		return 1;
	}
}
int lessEqual_5() {
	try {
		if (!(String("\0") <= String("\0"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error lessEqual_5" << endl;
		return 1;
	}
}

/* >= Test */
int greatEqual_1() {
	try {
		String test1("aaa");
		if (!(String(test1) >= String("aa"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greatEqual_1" << endl;
		return 1;
	}
}
int	greatEqual_2() {
	try {
		String test1("aaa");
		if (String("aa") >= String(test1)) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greatEqual_2" << endl;
		return 1;
	}
}
int greatEqual_3() {
	try {
		String test1(""), test2("");
		if (!(String(test1) >= String(test2))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greatEqual_3" << endl;
		return 1;
	}
}
int greatEqual_4() {
	try {
		String test1("44"), test2("1");
		if (!(String(test1) >= String(test2))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greatEqual_4" << endl;
		return 1;
	}
}
int greatEqual_5() {
	try {
		if (!(String("\0") >= String("\0"))) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error greatEqual_5" << endl;
		return 1;
	}
}

/* = Test */
int equal_1() {
	try {
		String test1(""), test2;
		test2 = test1;
		if (test1 != test2) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equal_1" << endl;
		return 1;
	}
}
int equal_2() {
	try {
		String test1("1234"), test2;
		test2 = test1;
		if (test1 != test2) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equal_2" << endl;
		return 1;
	}
}
int equal_3() {
	try {
		char *string1 = new char[10];
		string1[0] = 't';
		string1[1] = 'd';
		string1[2] = 's';
		string1[3] = '\0';
		String test1("rand"), test2(string1);
		test2 = test1;
		delete [] string1;
		if (test1 != test2) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equal_3" << endl;
		return 1;
	}
}
int equal_4() {
	try {
		char *string1 = new char[10];
		string1[0] = 'w';
		string1[1] = 'o';
		string1[2] = 't';
		string1[3] = '\0';
		String test1("rand"), test2(string1);
		test1 = test2;
		delete [] string1;
		if (test1 != test2) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equal_4" << endl;
		return 1;
	}
}
int equal_5() {
	try {
		String test1("20percentcooler"), original;
		original = test1;
		test1 = test1;
		if (test1 != original) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error equal_5" << endl;
		return 1;
	}
}

/* + Test */
int plus_1() {
	try {
		String test1("123"), test2("456"), test3("123456");
		if (test1 + test2 != test3) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plus_1" << endl;
		return 1;
	}
}
int plus_2() {
	try {
		String test1(""), test2(""), test3("");
		if (test1 + test2 != test3) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plus_2" << endl;
		return 1;
	}
}
int plus_3() {
	try {
		String test1("5"), test2("5"), test3("10");
		if (test1 + test2 == test3) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plus_3" << endl;
		return 1;
	}
}
int plus_4() {
	try {
		String test1("5 "), test2("3"), test3("53");
		if (test1 + test2 == test3) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plus_4" << endl;
		return 1;
	}
}
int plus_5() {
	try {
		String test1("Debuggin is fun"), test2(""), test3("Debuggin is fun");
		if (test2 + test3 != test1) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plus_5" << endl;
		return 1;
	}
}

/* += Test */
int plusEqual_1() {
	try {
		String test1(""), test2(""), test3("");
		String original(test1);
		test1 += (test2 + test3);
		if (test1 != original) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plusEqual_1" << endl;
		return 1;
	}
}
int plusEqual_2() {
	try {
		String test1("4"), test2("3 "), test3("1");
		String sum("43 1");
		test1 += (test2 + test3);
		if (!(test1 == sum)) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plusEqual_2" << endl;
		return 1;
	}
}
int plusEqual_3() {
	try {
		String test1("0123456789"), test2("0123456789");
		String original(test1);
		test1 += (test2);
		if (test1 == original) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plusEqual_3" << endl;
		return 1;
	}
}
int plusEqual_4() {
	try {
		String test1("012345678901234567890123456789"), test2("");
		String original(test1);
		test1 += (test2);
		if (test1 != original) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plusEqual_4" << endl;
		return 1;
	}
}
int plusEqual_5() {
	try {
		String test1("0"), test2(" 9");
		String sum("0 9");
		test1 += (test2);
		if (!(test1 == sum)) {
			throw(1);
		} else {
			return 0;
		}
	} catch (int) {
		cout << "Error plusEqual_5" << endl;
		return 1;
	}
}

int empty() {
	return empty_1() + 
		empty_2() + 
		empty_3() + 
		empty_4() + 
		empty_5();
}
int size() {
	return size_1() + 
		size_2() + 
		size_3() + 
		size_4() + 
		size_5();
}
int bracket() {
	return bracket_1() + 
		bracket_2() + 
		bracket_3() + 
		bracket_4() + 
		bracket_5();
}
int equalEqual() {
		return equalEqual_1() + 
		equalEqual_2() + 
		equalEqual_3() + 
		equalEqual_4() + 
		equalEqual_5();
}
int notEqual() {
	return notEqual_1() + 
		notEqual_2() + 
		notEqual_3() + 
		notEqual_4() + 
		notEqual_5();
}
int lesser() {
	return lesser_1() + 
		lesser_2() + 
		lesser_3() + 
		lesser_4() + 
		lesser_5();
}
int Greater() {
	return greater_1() + 
		greater_2() + 
		greater_3() + 
		greater_4() + 
		greater_5();
}
int lessEqual() {
	return lessEqual_1() + 
		lessEqual_2() + 
		lessEqual_3() + 
		lessEqual_4() + 
		lessEqual_5();
}
int greatEqual() {
	return greatEqual_1() + 
		greatEqual_2() + 
		greatEqual_3() + 
		greatEqual_4() + 
		greatEqual_5();
}
int equal() {
	return equal_1() + 
		equal_2() + 
		equal_3() + 
		equal_4() + 
		equal_5();
}
int Plus() {
	return plus_1() + 
		plus_2() + 
		plus_3() + 
		plus_4() + 
		plus_5();
}
int plusEqual() {
	return plusEqual_1() + 
		plusEqual_2() + 
		plusEqual_3() + 
		plusEqual_4() + 
		plusEqual_5();
}

int main(int argc, char** argl) {
	return empty() +
		size() +
		bracket() +
		equalEqual() +
		notEqual() +
		lesser() +
		Greater() +
		lessEqual() +
		greatEqual() +
		equal() +
		Plus() + 
		plusEqual();
}