#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
  }
    // copy
    Array (Array const& a)
        :m_size(a.m_size)
        ,m_array(new T[m_size])
        {
            try{
                for(size_t i=0; i!=m_size; ++i) m_array[i]=a.m_array[i];
                }
                catch (...)
                {
                    delete [] m_array;
                    throw;
                }
        }
    // dop function
    void localswap (Array &a)
    {
        size_t const t1=m_size;
        m_size=a.m_size;
        a.m_size=t1;
        T * const t2 = m_array;
        m_array=a.m_array;
        a.m_array=t2;
    }
//move-constructor
    Array (Array&& a) 
    : m_size(0)
    , m_array(nullptr)
    {
        m_array = a.m_array;
        m_size = a.m_size;
        a.m_array = nullptr;
        a.m_size =0;
    }
//move-operator
    Array & operator=(Array const& a)
    {
        if(this != &a){
            Array tmp(a);
            tmp.localswap(*this);
        }
        return *this;
    }
//destructor
    ~Array ()
    {
        delete [] m_array;
    }
  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }

private:
  size_t m_size;
  T* m_array;
};
