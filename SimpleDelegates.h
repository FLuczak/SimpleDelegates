#pragma once
#include <functional>
#include <unordered_map>
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
		/**
		 * Binds a member  function \param a_method  of type:
		 * \tparam T of an instance: \param t
		 */
		template<typename T>
		void bind(T* t, ReturnType(T::* a_method)(Args...))
		{
			std::function<ReturnType(Args...)> tempFunction = [=](Args ... as) { (t->*a_method)(as...); };
			m_functions.insert(std::pair<std::pair<void*, void*>, std::function<ReturnType(Args...)>>(std::pair<void*, void*>(static_cast<void*>(t), (void*)(&a_method)), tempFunction));
		}

		/**
		 * \Unbinds member function \param a_method from instance \param t  of type \tparam T
		 */
		template<typename T>
		void unbind(T* t, ReturnType(T::* a_method)(Args...))
		{
			auto found = m_functions.find(std::pair<void*, void*>(static_cast<void*>(t), static_cast<void*>(&a_method)));
			assert(found == m_functions.end(), "Trying to unbind function that is not bound");
			m_functions.erase(found);
		}

		/**
		 * Invoke all bound functions. Can call with arguments
		 * of previously defined types.IMPORTANT: It is not recommended
		 * to bind or call anything with type other than void- it is possible,
		 * but the return value will be discarded...
		 */
		void operator() (Args... args)
		{
			std::unordered_map<std::pair<void*, void*>, std::function<ReturnType(Args...)>> duplicate_functions = m_functions;
			if (m_functions.size() == 0)return;
			for (auto& func : duplicate_functions)
			{
				func.second(args...);
			}
		}

		/**
		 * \this removes all bound functions at once.
		 */
		void clear()
		{
			m_functions.clear();
		}

	private:
		std::unordered_map<std::pair<void*, void*>, std::function<ReturnType(Args...)>> m_functions = {};
	};

}

