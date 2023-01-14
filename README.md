# Fluczak Simple delegates

Simple delegates is a simple implementation of multicast delegates created and maintained by Franciszek Łuczak. It was created to quickly implement multicast delegates in C++ projects. It is a single header library.

For now Simple delegates only handles member functions, however it will be extended to support lambdas, global and static functions.

**IMPORTANT: SIMPLE DELEGATES CAN BE USED FREELY BY THE END USER. IT IS NOT RECOMMENDED TO USE IT IN PROJECTS OF HIGH IMPORTANCE OR VALUE, AS THE LIBRARY WAS NEVER MEANT FOR THEM.**

# Integration
**Simple delegates.h** is the only is the single required file. You need to add:
```
#include "SimpleDelegates.h"
```
in files where you need to use delegates

# Examples

Here are some examples to give you an idea how to use the class:



Having a class
```
class A
{
	..
	void foo();
	void calc(int a, int b);
	..
};
```
We can declare delegates:
```
sdel::Delegate<void()> voidDelegate;
sdel::Delegate<void(int,int)> voidDoubleIntDelegate;
```
We can bind our functions to delegates:
```
void bindDelegates()
{
	..
	A* a = new A;
	voidDelegate.bind(a,&A::foo);
	voidDoubleIntDelegate.bind(a,&A::calc);
	..
}
```
And then we can invoke our delegates as so:
```
void callDelegates()
{
	voidDelegate(); // calls function foo of a
	voidDoubleIntDelegate(1,2); // calls function Calc of a with arguments 1 and 2
}
```
**Important: Delegates have to be unbound. Otherwise you're asking for errors**

```
void unbindDelegates()
{
	voidDelegate.unbind(a,&A::foo);
	voidDoubleIntDelegate.unbind(a,&A::calc);
}
```



# License

Copyright 2023 Franciszek Łuczak

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
