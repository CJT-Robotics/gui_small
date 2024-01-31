#include <gtest/gtest.h>
#include "DataRepository.h"


//Test Singleton works!!!
TEST(package_name, a_first_test)
{
  DataRepository* i = &DataRepository::getInstance();
  i->exit();
  DataRepository* i2 = &DataRepository::getInstance();
  ASSERT_EQ(i,i2);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}