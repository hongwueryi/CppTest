#include "gtest/gtest.h"
class TestClassCase {
public:
	int Foo(int a, int b)
	{
		if (a == 0 || b == 0)
			throw "dont do that";
		int c = a % b;
		if (c == 0)
			return b;
		return Foo(b, c);
	}

	static int add(int a, int b)
	{
		return a + b;
	}
};

int Foo2(int a, int b)
{
	if (a == 0 || b == 0)
		throw "dont do that";
	int c = a % b;
	if (c == 0)
		return b;
	return Foo2(b, c);
}

//TEST����꣬���������������ٷ��Ķ������������Ľ���Ϊ��[TestCaseName��TestName]
TEST(TestCase1, Foofunc)
{
	TestClassCase case1;
	EXPECT_EQ(2, case1.Foo(4, 10));
	EXPECT_EQ(4, case1.Foo(4, 10));
	ASSERT_EQ(3, TestClassCase::add(1, 2));
	ASSERT_EQ(3, TestClassCase::add(1, 1));
}

TEST(TestCase3, Foofunc)
{
	ASSERT_EQ(3, TestClassCase::add(1, 1)); //һ��ʧ�ܣ�����ִ�б������к�����test
	ASSERT_EQ(3, TestClassCase::add(1, 2));
}

TEST(TestCase2, Foo2Func)
{
	EXPECT_EQ(2, Foo2(4, 10));
	EXPECT_EQ(4, Foo2(4, 10));
}