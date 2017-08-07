#include "stdafx.h"
#include <gtest/gtest.h>

class Environment : public ::testing::Environment
{
protected:
	// запускается перед выполнением ВСЕХ тестов
	virtual void SetUp()
	{
		if(0)
		{
			FAIL() << "Can't Load";
		}
	}
};

int main(int argc, _TCHAR* argv[])
{
	::CoInitialize(NULL);
	::testing::InitGoogleTest(&argc, argv);
	testing::GTEST_FLAG(print_time) = true; // Force print tests times
//	testing::GTEST_FLAG(filter) = "XSLT.*"; // Filter tests

	::testing::AddGlobalTestEnvironment(new Environment());
	int rc = RUN_ALL_TESTS();
	::CoUninitialize();
	if(0 != rc)
		DebugBreak();
	return rc;
}
