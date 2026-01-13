#include <iostream>
#include <stdexcept>

class Stack
{
private:
    int *tab;
    int size;
    int nb;

public:
    Stack(int s) : nb(0)
    {
        size = s;
        tab = new int[size];
    }
    ~Stack()
    {
        delete[] tab;
    }

    Stack(const Stack &tbl)
    {
        size = tbl.size;
        nb = tbl.nb;
        tab = new int[size];
        for (int i = 0; i < nb; i++)
        {
            tab[i] = tbl.tab[i];
        }
    }

    Stack &operator=(const Stack &tbl)
    {
        if (this == &tbl) 
        {
            return *this;
        }
        nb = tbl.nb;
        size = tbl.size;
        delete[] tab;
        tab = new int[size];
        for (int i = 0; i < nb; i++)
        {
            tab[i] = tbl.tab[i];
        }
        return *this; 
    }

    bool is_full()
    {
        return nb >= size;
    }

    void push(int value)
    {
        if (is_full())
        {
            throw std::overflow_error("pile pleine ");
        }
        else
        {
            tab[nb] = value;
            nb += 1;
        }
    }
};

int main()
{
    
    {

        Stack tab(8);
        {
            Stack tab2(3);
            tab2.push(2);
            tab = tab2; 
        }
        tab.push(17); 
    }
   
    {
        Stack st(10);
        {
            Stack st2 = st; 
        }
        st.push(42); 
    }

    return 0;
}   