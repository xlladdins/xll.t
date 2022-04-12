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

template<class X>
int test_str()
{
	{
		XOPER<X> s(data<X>::abc);
		XOPER<X> s2{ s };
		ensure(s == s2);
		s = s2;
		ensure(!(s != s2));

		ensure(s == data<X>::abc);
	}
	{
		OPER4 s("4");
		s.append("def");
		ensure(s == "4def");
	}
	{
		OPER s(L"12");
		s.append(L"def");
		ensure(s == L"12def");
	}

	return 0;
}
int test_str4 = test_str<XLOPER>();
int test_str12 = test_str<XLOPER12>();

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

		XOPER<X> m2{ m };
		ensure(m2 == m);
		m = m2;
		ensure(!(m != m2));
	}
	{
		XOPER<X> m(2, 3);
		m[1] = data<X>::abc;
		m[0] = m;
		m[0][0] = m;
		ensure(m[0][0][1] == data<X>::abc);
	}
	{
		XOPER<X> m(2, 3);
		m.stack(m);
		ensure(4 == m.rows());
		ensure(3 == m.columns());
	}
	{
		XOPER<X> m;
		XOPER<X> m0(data<X>::abc);
		m.stack(m0);
		ensure(m == m0);
		m0.stack(m0);
		ensure(xltypeMulti == m0.type());
		ensure(2 == m0.rows());
		ensure(1 == m0.columns());
		ensure(m0[0] == data<X>::abc);
		ensure(m0(1, 0) == data<X>::abc);
		ensure(m0(0, 0) == m);
	}
	{
		XOPER<X> m(3, 2);
		m.resize(0, 0);
		ensure(xltypeNil == m.type());
		ensure(m == XNil<X>);
	}

	return 0;
}
int test_multi4 = test_multi<XLOPER>();
//int test_multi12 = test_multi<XLOPER12>();

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
/*
template<class X>
int test_json()
{
	{
		ensure(JSON_t::Null == XJSON<X>{}.jstype());
		ensure(JSON_t::False == XJSON<X>(false).jstype());
		ensure(JSON_t::True == XJSON<X>(true).jstype());
		ensure(JSON_t::Number == XJSON<X>(1.23).jstype());
		ensure(JSON_t::String == XJSON<X>(data<X>::abc).jstype());
		ensure(JSON_t::Array == XJSON<X>({ XJSON<X>{}, XJSON<X>(1.23)}).jstype());
		//ensure(JSON_t::Object == XJSON<X>({ {data<X>::abc, XJSON<X>(1.23)}, {data<X>::def, XJSON<X>(4.56)} }).jstype());
	}
	{
		//XJSON<X> o(std::map( {{ data<X>::abc, XOPER<X>(1.23) } }));
	}

	return 0;
}
int test_json4 = test_json<XLOPER>();
int test_json12 = test_json<XLOPER12>();
*/
//Macro xai_foo();

extern "C" __declspec(dllexport) int WINAPI macro(void)
{
	//XLL_INFO("It worked!");

	return TRUE;
}
