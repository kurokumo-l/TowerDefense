#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <typename T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	static T& Instance()
	{
		static T instance{ Token{} };
		return instance;
	}

protected:
	struct Token
	{
	};
	Singleton() = default;
	virtual ~Singleton() = default;
};

#endif