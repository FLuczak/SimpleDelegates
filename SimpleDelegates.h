#pragma once
#include <functional>
#include <map>
#include <cassert>

//Simple delegates is a small library created and maintained by Franciszek Luczak.
//It was created for small personal projects created in C++.
//IT IS NOT RECOMMENDED TO USE IN ANY PROJECTS OF HIGH IMPORTANCE OR VALUE
//User is free to use the Simple Delegates library to any extent and up to their will. (Yet with extra causion)

//The design and overall flow is designed to replicate Action delegates in C#:https://learn.microsoft.com/en-us/dotnet/api/system.action-1?view=net-7.0
//The best recommended use can be found in the library's documentation.

//uncomment to remove asserts
//#define NDEBUG

namespace sdel
{
	template <typename>
	class Delegate;

	template <typename ReturnType, typename... Args>
	class Delegate<ReturnType(Args...)>
	{
	public:
		/*
		 * Binds a member  function \param a_method  of type:
		 * \tparam T of an instance: \param t
		 */
		template<typename T>
		void Bind(T* t, ReturnType(T::* a_method)(Args...))
		{
			std::function<ReturnType(Args...)> tempFunction = [=](Args ... as) { (t->*a_method)(as...); };
			auto p = void_cast(a_method);
			m_functions.insert(std::pair<std::pair<void*, int*>, std::function<ReturnType(Args...)>>(std::pair<void*, int*>(static_cast<void*>(t), (int*)p), tempFunction));
		}

		/*
		 * Binds a global  function \param a_method  of type:
		 * \tparam T
		*/
		void Bind(ReturnType(*a_method)(Args...))
		{
			std::function<ReturnType(Args...)> tempFunction = [=](Args ... as) { (*a_method)(as...); };
			m_functions.insert(std::pair<std::pair<void*, int*>, std::function<ReturnType(Args...)>>(std::pair<void*, int*>(static_cast<void*>(this), (int*)a_method), tempFunction));
		}

		/*
		 * \Unbinds member function \param a_method from instance \param t  of type \tparam T
		 */
		template<typename T>
		void Unbind(T* t, ReturnType(T::* a_method)(Args...))
		{
			auto found = m_functions.find(std::pair<void*, int*>(static_cast<void*>(t), ((int*)void_cast(a_method))));
			assert(found != m_functions.end());
			m_functions.erase(found);
		}


		/*
		 * \Unbinds global function \param a_method
		 */
		template<typename T>
		void Unbind(ReturnType(T::* a_method)(Args...))
		{
			auto found = m_functions.find(std::pair<void*, void(*)()>(static_cast<void*>(this), static_cast<void(*)()>(a_method)));
			assert(found != m_functions.end());
			m_functions.erase(found);
		}

		/*
		 * Invoke all bound functions. Can call with arguments
		 * of previously defined types.IMPORTANT: It is not recommended
		 * to bind or call anything with type other than void- it is possible,
		 * but the return value will be discarded...
		 */
		void operator() (Args... args)
		{
			std::map<std::pair<void*, int*>, std::function<ReturnType(Args...)>> duplicate_functions = m_functions;
			if (m_functions.size() == 0)return;
			for (auto& func : duplicate_functions)
			{
				func.second(args...);
			}
		}

		/*
		 * \this removes all bound functions at once.
		 */
		void Clear()
		{
			m_functions.clear();
		}

	private:
		std::map<std::pair<void*, int*>, std::function<ReturnType(Args...)>> m_functions = {};


		//void cast is an idea taken from:https://stackoverflow.com/a/37502759/20211112 thanks to Karlo Mlicevic
		template<typename T, typename R>
		void* void_cast(R(T::* f)(Args...))
		{
			union
			{
				R(T::* pf)(Args...);
				void* p;
			};
			pf = f;
			return p;
		}
	};

}


