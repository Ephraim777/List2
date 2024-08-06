#include <catch2/catch_test_macros.hpp>

#define CATCH_CONFIG_RUNNER
#include <cstdint>

#include <iostream>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;

            delete extractPrev(current);
       

        }
    }

    void Print() 
    {
        auto current = m_head;
        int index = 0;
        unsigned long Ssize = this->Size();
        while (Ssize != 0)
        {
            Ssize--;
            current = current->next;
            std::cout << "index: " << index << " " << "value:" << " " << current->value << "\n";
        }
    }
private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("Testing", "List") {
    std::cout << "\n";
    SECTION("PushFront")
    {
        List MyList;
        MyList.PushFront(1);
        MyList.PushFront(2);
        MyList.PushFront(3);
        std::cout << "PushFront SECTION\n";
        MyList.Print();
        std::cout << "Size: " << MyList.Size() << "\n";
        CHECK(MyList.Size() == 3);
    }
    std::cout << "\n";
    SECTION("PushBack")
    {
        List MyList;
        MyList.PushBack(1);
        MyList.PushBack(2);
        MyList.PushBack(3);
        std::cout << "PushBack SECTION\n";
        MyList.Print();
        std::cout << "Size: " << MyList.Size() << "\n";
        CHECK(MyList.Size() == 3);
    }

    SECTION("PopBack")
    {
        std::cout << "PopBack SECTION\n";
        List MyList;
        MyList.PushBack(1);
        MyList.PushBack(2);
        MyList.PushBack(3);
        std::cout << "Begin: \n";
        MyList.Print();
        int CounterOfDelete = 1;
        unsigned long counter = MyList.Size();
        while (counter--) 
        {
            
            MyList.PopBack();

            std::cout << "\nDeleting a number: " << CounterOfDelete++ << "\n";
            if (MyList.Empty()) {
                std::cout << "Empty List\n";
                continue;
            }
            
            MyList.Print();

        }
        CHECK(MyList.Empty());
      
    }

    SECTION("PopFront")
    {
        std::cout << "PopFront SECTION\n";
        List MyList;
        MyList.PushFront(1);
        MyList.PushFront(2);
        MyList.PushFront(3);
        std::cout << "Begin: \n";
        MyList.Print();
        int CounterOfDelete = 1;
        unsigned long counter = MyList.Size();
        while (counter--)
        {

            MyList.PopFront();

            std::cout << "\nDeleting a number: " << CounterOfDelete++ << "\n";
            if (MyList.Empty()) {
                std::cout << "Empty List\n";
                continue;
            }

            MyList.Print();

        }
        CHECK(MyList.Empty());

    }
    
}
