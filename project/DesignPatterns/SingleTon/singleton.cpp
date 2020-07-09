#include <iostream>
#include <memory>
#include <mutex>
#define SINGLETON_SAMPLE1
//------------------------------单例模板-------------------------------//
//#ifdef SINGLETON_SAMPLE1
//
//template <typename T>
//class Singleton
//{
//public:
//    static T &getInstance();
//    Singleton(const Singleton &other) = default;
//    Singleton<T> &operator=(const Singleton &other) = default;
//
//private:
//    static std::mutex mutex;
//    static std::unique_ptr<T> instance;
//};
//
//template <typename T> std::mutex Singleton<T>::mutex;
//template <typename T> std::unique_ptr<T> Singleton<T>::instance;
//
//template<typename T>
//T &Singleton<T>::getInstance()
//{
//    if (instance.isNull()) {
//        std::lock_guard<std::mutex> locker(mutex);
//        if (instance.isNull()) {
//            instance.reset(new T());
//        }
//    }
//    return *instance.data();
//};
//
//#define SINGLETON(Class) \
//    private: \
//    Class(); \
//    ~Class(); \
//    Class(const Class &other); \
//    Class &operator =(const Class &other); \
//    friend class Singleton<Class>; \
//	
//class ConcreteSingleton
//{
//    SINGLETON(ConcreteSingleton)
//public:
//	inline void testSingleTon(){
//		std::cout << "create singleton success" << std::endl;
//	}
//};
//	
//int main()
//{
//	Singleton<ConcreteSingleton>::getInstance().testSingleTon();
//    getchar();
//    return 0;
//}
//#endif 

//------------------------------单例模板-2-------------------------------//
template<class T>
class SingletonTemplate2
{
protected:
	SingletonTemplate2(){}
	virtual ~SingletonTemplate2() {}
public:
	static T& instance(){
		static T t;
		return t;
	}
};

class ConcreteSingleton2 : public SingletonTemplate2<ConcreteSingleton2>
{
public:
	inline void print(){
		std::cout << "create singleton (use template ConcreteSingleton2) success" << std::endl;
	}
private:
    ConcreteSingleton2(){}
	~ConcreteSingleton2(){}
	friend SingletonTemplate2<ConcreteSingleton2>;
};

//------------------------------单例—懒汉式-1-------------------------------//
#include <mutex>
class SingleTon1_1
{
public:
	static SingleTon1_1& instance(){
	    if(m_pInstance.get() == NULL){
	    	std::lock_guard<std::mutex> lock(m_mtx);
	    	if(m_pInstance.get() == NULL){
	    		m_pInstance.reset(new SingleTon1_1());
	    	}
	    }
	    return *m_pInstance;
    }
	inline void print(){
		std::cout << "test SingleTon1_1" << std::endl;
	}
private:
	SingleTon1_1(){};
	~SingleTon1_1(){};
	SingleTon1_1(const SingleTon1_1&) = delete;
	SingleTon1_1& operator=(const SingleTon1_1&) = delete;
	static std::mutex m_mtx;
	static std::auto_ptr<SingleTon1_1> m_pInstance; //使用auto_ptr容易把指针悬空，要特别注意
	friend class std::auto_ptr<SingleTon1_1>;
};
std::auto_ptr<SingleTon1_1> SingleTon1_1::m_pInstance;
std::mutex SingleTon1_1::m_mtx;

//------------------------------单例—懒汉式-1_2-------------------------------//
#include <mutex>
class SingleTon1_2
{
public:
	static SingleTon1_2& instance(){
	    if(!m_pInstance){
	    	std::unique_lock<std::mutex> lock(m_mtx);
	    	if(!m_pInstance){
	    		m_pInstance.reset(new SingleTon1_2());
	    	}
	    }
	    return *m_pInstance;
    }
	inline void print(){
		std::cout << "test SingleTon1_2" << std::endl;
	}
private:
	SingleTon1_2(){};
	~SingleTon1_2(){};
	SingleTon1_2(const SingleTon1_2&) = delete;
	SingleTon1_2& operator=(const SingleTon1_2&) = delete;
	static std::mutex m_mtx;
	static std::shared_ptr<SingleTon1_2> m_pInstance; //使用auto_ptr容易把指针悬空，要特别注意
	friend class std::shared_ptr<SingleTon1_2>;
};
std::shared_ptr<SingleTon1_2> SingleTon1_2::m_pInstance;
std::mutex SingleTon1_2::m_mtx;


//------------------------------单例—懒汉式-2_1-------------------------------//
class SingleTon2_1
{
public:
	static SingleTon2_1* instance(){
	    static SingleTon2_1 instance;
	    return &instance;
    }
	inline void print(){
		std::cout << "test SingleTon2_1" << std::endl;
	}
private:
	SingleTon2_1(){};
	~SingleTon2_1(){};
	SingleTon2_1(const SingleTon2_1&) = delete;
	SingleTon2_1& operator=(const SingleTon2_1&) = delete;
};

//------------------------------单例—懒汉式-2_2-------------------------------//
class SingleTon2_2
{
public:
	static SingleTon2_2& instance(){
	    static SingleTon2_2 instance;
	    return instance;
    }
	inline void print(){
		std::cout << "test SingleTon2_2" << std::endl;
	}
private:
	SingleTon2_2(){};
	~SingleTon2_2(){};
	SingleTon2_2(const SingleTon2_2&) = delete;
	SingleTon2_2& operator=(const SingleTon2_2&) = delete;
};

int main()
{
	//Singleton<ConcreteSingleton>::getInstance().testSingleTon();
	SingleTon1_1::instance().print();
	SingleTon2_1::instance()->print();
	SingleTon2_2::instance().print();
	
	ConcreteSingleton2::instance().print();
    getchar();
    return 0;
}

