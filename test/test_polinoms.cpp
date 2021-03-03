#include "polinoms.h"

#include<gtest.h>

TEST(TMonom, can_create_monom_c) {
	Monom m(4, 123);
	ASSERT_EQ(m.coeff, 4);
}

TEST(TMonom, can_create_monom_d) {
	Monom m(1, 999);
	ASSERT_EQ(m.deg, 999);
}

TEST(TMonom, throws_if_degree_is_not_correct)
{
	ASSERT_ANY_THROW(Monom m(1, 1000));
}

TEST(TMonom, can_compare_monoms_1) {
	Monom m1(2, 345);
	Monom m2(3, 123);
	ASSERT_EQ(m1 == m2, 0);
}

TEST(TMonom, can_compare_monoms_2) {
	Monom m1(2, 345);
	Monom m2(2, 345);
	ASSERT_EQ(m1 == m2, 1);
}

TEST(TMonom, can_not_add_two_monoms)
{
	Monom m1(1, 123);
	Monom m2(2, 456);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMonom, can_add_two_monoms)
{
	Monom m1(1, 123);
	Monom m2(2, 123);
	ASSERT_NO_THROW(m1 + m2);
}

TEST(TMonom, correct_add_two_monoms)
{
	Monom m1(1, 123);
	Monom m2(2, 123);
	Monom res(3, 123);
	ASSERT_EQ(m1 + m2, res);
}

TEST(TMonom, can_mult_two_monoms)
{
	Monom m1(1, 123);
	Monom m2(2, 456);
	ASSERT_NO_THROW(m1 * m2);
}

TEST (TMonom, throws_mult_two_monoms_when_overflowing_deg)
{
	Monom m1(1, 923);
	Monom m2(2, 456);
	ASSERT_ANY_THROW(m1 * m2);
}

TEST(TMonom, correct_mult_two_monoms)
{
	Monom m1(1, 123);
	Monom m2(2, 456);
	Monom res(2, 579);
	ASSERT_EQ((m1 * m2), res);
}

TEST(Polinom, can_add_two_polinoms) {
	Polinom p1, p2, p3;
	Monom m1(1, 123), m2(2, 210), m3(3, 333);
	p1.Push_back(m1);
	p1.Push_back(m2);
	p2.Push_back(m3);
	p3.Push_back(m1);
	p3.Push_back(m2);
	p3.Push_back(m3);
	EXPECT_EQ(p1 + p2,p3);
}

TEST(Polinom, can_mult_two_polinoms) {
	Polinom p1, p2, res;
	Monom m1(1, 100), m2(2, 200), m3(4, 100), m4(5, 000), m5(8, 300), m6(14, 200), m7(5, 100);
	p1.Push_back(m1);
	p1.Push_back(m2);
	p2.Push_back(m3);
	p2.Push_back(m4);
	res.Push_back(m5);
	res.Push_back(m6);
	res.Push_back(m7);
	ASSERT_EQ(p1 * p2, res);
}


TEST(TPolynom, can_mult_monom_with_polynom)
{
	Monom m;
	Polinom p1, p2, res;
	Monom m1(1, 123), m2(1, 120), m3(3, 123),m4(1,243),m5(3,246);
	p1.Push_back(m1);
	p2.Push_back(m2);
	p2.Push_back(m3);
	res.Push_back(m4);
	res.Push_back(m5);
	ASSERT_EQ(p1 + p2, res);
}

