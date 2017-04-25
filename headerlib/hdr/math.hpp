#ifndef HEADERLIB_HDR_MATH_HPP
#define HEADERLIB_HDR_MATH_HPP
/*
 * math.hpp
 * Common mathematical constructs
 *
 *  Created on: 04.04.2016
 *      Author: andreas
 */
#include "hdr/core.hpp"
namespace hdr::math {
using ::hdr::std::Apply;
using ::hdr::std::False;
using ::hdr::std::True;
using ::hdr::std::flip;
using ::hdr::lambda::_0;
using ::hdr::lambda::_1;
using ::hdr::lambda::Lambda;
using ::hdr::lambda::IApply;
/**	Utility to convert integers to types
 */
template<unsigned u> using Unsigned = Value<u>;
template<signed s> 	 using Signed 	= Value<s>;
template<bool b> 		 using Bool 		= Value<b>;

template<typename _Tp, _Tp a, _Tp b>
struct Plus<Value<a>, Value<b>> { using type = Value<a+b>; };
template<bool a, bool b>
struct Plus<Bool<a>, Bool<b>>   { using type = Bool<a || b>; };

template<typename _Tp, _Tp a, _Tp b>
struct Mult<Value<a>, Value<b>> { using type = Value<a*b>; };
template<bool a, bool b>
struct Mult<Bool<a>, Bool<b>>   { using type = Bool<a && b>; };

template<typename _Tp, _Tp a, _Tp b>
struct Minus<Value<a>, Value<b>> { using type = Value<a-b>; };
template<bool a, bool b>
struct Minus<Bool<a>, Bool<b>>;

template<typename _Tp, _Tp a, _Tp b>
struct Div<Value<a>, Value<b>> { using type = Value<a/b>; };
template<typename _Tp, _Tp a>
struct Div<Value<a>, Value<0>>;
template<bool a, bool b>
struct Div<Bool<a>, Bool<b>>;

/// Boolean manipulators
using not_     = Lambda<_0, False, True>;
using and_     = Lambda<_0, _1,    False>;
using or_      = Lambda<_0, True,  _1>;
using xor_     = Lambda<_0, IApply<not_, _1>, _1>;

template<typename Smaller>
struct TotalOrder {
	using smaller = Smaller;
	using greater = Apply<flip, smaller>;
	using unequal = Lambda<or_,  IApply<compare, _0, _1>, IApply<compare, _1, _0>>;
	using equal   = Lambda<not_, IApply<unequal, _0, _1>>;
};

} // hdrstd::math

namespace hdr::std {

template<unsigned long v>
struct Printer<hdr::math::Value<v>>{
	static void print(){
		printf("%lu", v);
	}
};

template<typename _Tp, _Tp v>
struct Printer<hdr::math::Value<v>>{
	static void print(){
		printf("%i", v);
	}
};

}
#endif //HEADERLIB_HDR_MATH_HPP
