
#include <utility>
#include <iostream>
#include <memory>
#include <vector>

void foo(std::unique_ptr<int>& q)
{
	*q = 4;
}

void bar()
{
	std::unique_ptr<int> p{new int};
	*p = 3;
	foo(p);
	std::cout << *p << std::endl;
}

int main()
{
	std::vector<int> v{1, 2, 3, 4, 5};
	for (auto i : v)
	{
		std::cout << i << std::endl;
	}	

    return 0;
}

