#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T, typename Context>
class Singleton
{
public:
    T* operator->()
    {
        return m_pInstance;
    }
    const T* operator->() const
    {
        return m_pInstance;
    }
    T& operator*()
    {
        return *m_pInstance;
    }
    const T& operator*() const
    {
        return *m_pInstance;
    }

protected:
    Singleton()
    {
        static bool static_init = []()
        {
            m_pInstance = new T;
            return true;
        }();
    }

    Singleton(int)
    {
        static bool static_init = []()
        {
            m_pInstance = Context::init();
            return true;
        }();
    }

private:
    static T* m_pInstance;
};

template<typename T, typename Context>
T* Singleton<T, Context>::m_pInstance;

#endif // SINGLETON_H