// test.cpp
#include "../xll22/xll.h"
#include "../xll22/json.h"

using namespace xll;

template<class X>
using xchar = traits<X>::xchar;

template<class X> struct data {};
template<>
struct data<XLOPER> {
	static inline const char* abc = "abc";
	static inline const char* def = "def";
};
template<>
struct data<XLOPER12> {
	static inline const wchar_t* abc = L"abc";
	static inline const wchar_t* def = L"def";
};

template<class X>
int test_num()
{
	{
		auto num = XOPER<X>(1.23);
		ensure(xltypeNum == num.xltype);
		ensure(1.23 == num.val.num);
		ensure(num == 1.23);
		XOPER<X> n2(2.34);
		ensure(xltypeNum == n2.xltype);
		ensure(2.34 == n2.val.num);
		double d = num + n2;
		ensure(1.23 + 2.34 == d);
	}

	return 0;
}
int test_num4 = test_num<XLOPER>();
int test_num12 = test_num<XLOPER12>();


int test_str()
{
	{
		OPER4 s("abc");
		OPER4 s2{ s };
		ensure(s == s2);
		//s = s2;
		ensure(!(s != s2));

		ensure(s == "abc");
	}
	{
		OPER s(L"abc");
		OPER s2{ s };
		ensure(s == s2);
		//s = s2;
		ensure(!(s != s2));
	}
	{
		OPER4 s("abc");
		s.append("def");
		ensure(s == "abcdef");
	}
	{
		OPER s(L"abc");
		s.append(L"def");
		ensure(s == L"abcdef");
	}

	return 0;
}
int test_str_ = test_str();

template<class X>
int test_multi()
{
	{
		XOPER<X> m(2,3);
		ensure(6 == m.size());
		ensure(2 == m.rows());
		ensure(3 == m.columns());
		ensure(nullptr != m.array());
		ensure(XNil<X> == m[0]);
		m[0] = XOPER<X>(1.23);
		ensure(m[0] == 1.23);
		XOPER<X>& o = m[0];
		ensure(o == 1.23);
		ensure(1.23 == o);
		m[1] = XOPER<X>(data<X>::abc);
		ensure(m[1] == data<X>::abc);
		m[2] = data<X>::abc;
		ensure(m[2] == data<X>::abc);
	}
	{
		XOPER<X> m(2, 3);
		m[1] = data<X>::abc;
		m[0] = m;
		m[0][0] = m;
		ensure(m[0][0][1] == data<X>::abc);
	}

	return 0;
}
int test_multi4 = test_multi<XLOPER>();
int test_multi12 = test_multi<XLOPER12>();

template<class X>
int test_oper()
{
	{
		XOPER<X> x;
		ensure(xltypeNil == x.xltype);
		ensure(x == XNil<X>);
	}
	{
		XOPER<X> o(data<X>::abc);
		ensure(xltypeStr == o.xltype);
		ensure(3 == o.val.str[0]);
		ensure('c' == o.val.str[3]);
	}
	{
		XOPER<X> m(2, 3);
	}

	return 0;
}
int test_oper4 = test_oper<XLOPER>();
int test_oper12 = test_oper<XLOPER12>();

template<class X>
int test_json()
{
	{
		ensure(JSONtype::Null == XJSON<X>{}.jstype());
		ensure(JSONtype::False == XJSON<X>(false).jstype());
		ensure(JSONtype::True == XJSON<X>(true).jstype());
		ensure(JSONtype::Number == XJSON<X>(1.23).jstype());
		ensure(JSONtype::String == XJSON<X>(data<X>::abc).jstype());
		ensure(JSONtype::Array == XJSON<X>({ XJSON<X>{}, XJSON<X>(1.23)}).jstype());
		//ensure(JSONtype::Object == XJSON<X>({ {data<X>::abc, XJSON<X>(1.23)}, {data<X>::def, XJSON<X>(4.56)} }).jstype());
	}
	{
		//XJSON<X> o(std::map( {{ data<X>::abc, XOPER<X>(1.23) } }));
	}

	return 0;
}
int test_json4 = test_json<XLOPER>();
int test_json12 = test_json<XLOPER12>();

//Macro xai_foo();

extern "C" __declspec(dllexport) int WINAPI macro(void)
{
	//XLL_INFO("It worked!");

	return TRUE;
}
