//
// Created by Ernest Pokropek
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Dictionary.h"

using testing::Eq;

namespace{
class Dictionary_Test : public testing::Test{
    friend class Dictionary;
public:
    Dictionary<int, int> obj;


    virtual void insert_samples(){
        obj.insert(2,99);
        obj.insert(3,4);
        obj.insert(44,3);
        obj.insert(12,6);
    };


};
}

TEST_F(Dictionary_Test, exist_test){



    obj.insert(33, 2);
    EXPECT_EQ(true, obj.exists(33));
    EXPECT_EQ(false, obj.exists(666));
    EXPECT_EQ(false, obj.exists(836));
    EXPECT_EQ(false, obj.exists(-2));

}

TEST_F(Dictionary_Test, insertion_test) {

    insert_samples();

    EXPECT_EQ(true, obj.exists(44));
    EXPECT_EQ(true, obj.exists(2));
    EXPECT_EQ(true, obj.exists(12));
    EXPECT_EQ(true, obj.exists(3));
    EXPECT_EQ(false, obj.exists(666));
    EXPECT_EQ(false, obj.exists(-2));

}

TEST_F(Dictionary_Test, removal_test){

    insert_samples();
    EXPECT_EQ(true, obj.exists(44));
    obj.remove(44);
    EXPECT_EQ(false, obj.exists(44));

    EXPECT_EQ(true, obj.exists(2));
    obj.remove(2);
    EXPECT_EQ(false, obj.exists(2));

    EXPECT_EQ(true, obj.exists(3));
    obj.remove(3);
    EXPECT_EQ(false, obj.exists(3));

    EXPECT_EQ(false, obj.exists(666));
    obj.remove(666);
    EXPECT_EQ(false, obj.exists(666));

}

TEST_F(Dictionary_Test, clear_test){

    insert_samples();
    EXPECT_EQ(true, obj.exists(44));
    EXPECT_EQ(true, obj.exists(2));
    EXPECT_EQ(true, obj.exists(12));
    EXPECT_EQ(true, obj.exists(3));

    obj.clear();

    EXPECT_EQ(false, obj.exists(44));
    EXPECT_EQ(false, obj.exists(2));
    EXPECT_EQ(false, obj.exists(12));
    EXPECT_EQ(false, obj.exists(3));

}

TEST_F(Dictionary_Test, equality_test){

    insert_samples();
    EXPECT_EQ(true, obj.exists(44));
    EXPECT_EQ(true, obj.exists(2));
    EXPECT_EQ(true, obj.exists(12));
    EXPECT_EQ(true, obj.exists(3));

    Dictionary<int, int> obj2;
    obj2 = obj;

    EXPECT_EQ(true, obj2.exists(44));
    EXPECT_EQ(true, obj2.exists(2));
    EXPECT_EQ(true, obj2.exists(12));
    EXPECT_EQ(true, obj2.exists(3));

}

TEST_F(Dictionary_Test, height_test){

    insert_samples();
    EXPECT_EQ(3, obj.height());

    obj.remove(12);
    EXPECT_EQ(2, obj.height());

    obj.insert(666, 66);
    obj.insert(32, 102);
    obj.insert(55,3);
    obj.insert(-2, 8);
    EXPECT_EQ(4, obj.height());

    obj.clear();
    EXPECT_EQ(0, obj.height());

}