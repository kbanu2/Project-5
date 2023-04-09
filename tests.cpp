#include <gtest/gtest.h>
#include <iostream>
#include "priorityqueue.h"
using namespace std;

/// @brief Test if the constructor initializes datamembers properly to 0
///        Additionally uses Size, Begin, Next, toString
/// @param  
TEST(priorityqueue, constructor){
    priorityqueue<int> t;
    int val, pri;

    t.begin();
    EXPECT_EQ(t.Size(), 0);
    EXPECT_EQ(t.next(val, pri), false);
    t.toString();
}

TEST(priorityqueue, enqueue_balanced){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(0, 2);
    t.enqueue(1, 1);
    t.enqueue(5, 3);
    t.begin();

    EXPECT_EQ(t.Size(), 3);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 1);
    EXPECT_EQ(pri, 1);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 0);
    EXPECT_EQ(pri, 2);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 5);
    EXPECT_EQ(pri, 3);
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, enqueue_subtree){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(5,5);
    t.enqueue(3,3);
    t.enqueue(4,4);
    t.enqueue(2,2);
    t.begin();

    EXPECT_EQ(t.Size(), 4);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 2);
    EXPECT_EQ(pri, 2);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 3);
    EXPECT_EQ(pri, 3);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 4);
    EXPECT_EQ(pri, 4);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 5);
    EXPECT_EQ(pri, 5);
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, dequeue_left){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(3,5);
    t.enqueue(1,2);
    t.enqueue(4,8);
    

    EXPECT_EQ(t.Size(), 3);
    EXPECT_EQ(t.dequeue(), 1);
    EXPECT_EQ(t.Size(), 2);
    t.begin();
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 3);
    EXPECT_EQ(pri, 5);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 4);
    EXPECT_EQ(pri, 8);
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, dequeue_root){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(1,2);
    EXPECT_EQ(t.Size(), 1);
    EXPECT_EQ(t.dequeue(), 1);
    t.begin();
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, dequeue_root_additional){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(1,2);
    t.enqueue(4,8);
    t.enqueue(3,5);
    t.enqueue(8,10);

    EXPECT_EQ(t.Size(), 4);
    EXPECT_EQ(t.dequeue(), 1);
    EXPECT_EQ(t.Size(), 3);
    t.begin();
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 3);
    EXPECT_EQ(pri, 5);
}

TEST(priorityqueue, dequeue_entire){
    priorityqueue<int> t;

    t.enqueue(4,10);
    t.enqueue(1,5);
    t.enqueue(3,3);
    t.enqueue(4,10);
    t.enqueue(5,7);
    t.enqueue(10,15);
    t.enqueue(8,12);
    t.enqueue(9,20);
    t.enqueue(0, 13);
    t.enqueue(4,10);

    EXPECT_EQ(t.Size(), 10);
    EXPECT_EQ(t.dequeue(), 3);
    EXPECT_EQ(t.dequeue(), 1);
    EXPECT_EQ(t.dequeue(), 5);
    EXPECT_EQ(t.dequeue(), 4);
    EXPECT_EQ(t.dequeue(), 4);
    EXPECT_EQ(t.dequeue(), 4);
    EXPECT_EQ(t.dequeue(), 8);
    EXPECT_EQ(t.dequeue(), 0);
    EXPECT_EQ(t.dequeue(), 10);
    EXPECT_EQ(t.dequeue(), 9);
}

TEST(priorityqueue, assignment){
    priorityqueue<int> t;
    priorityqueue<int> h;
    int valT, priT, valH, priH;

    t.enqueue(4,10);
    t.enqueue(1,5);
    t.enqueue(3,3);
    t.enqueue(5,7);
    t.enqueue(10,15);
    t.enqueue(8,12);
    t.enqueue(9,20);
    t.enqueue(0, 13);

    h = t;

    h.begin();
    t.begin();
    EXPECT_EQ(t.Size(), h.Size());
    EXPECT_EQ((t == h), true);
    while(t.next(valT, priT) && h.next(valH, priH)){
        EXPECT_EQ(valT, valH);
        EXPECT_EQ(priT, priH);
    }

    while (h.Size() > 0){
        h.dequeue();
    }
    
    EXPECT_EQ(t.Size(), 8);
    t.begin();
    EXPECT_EQ(t.next(valT, priT), true);
    EXPECT_EQ(valT, 3);
    EXPECT_EQ(priT, 3);
}

