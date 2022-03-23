#include"calc.h"

int main()
{
	colebrook_f f;
	f.prep_data();
	float ans = f.iterative_3_pt();
	std::cout << "friction factor - by my algorithm " << ans;
	ans = f.p_drop();
	std::cout << "\n\n p drop is " << ans <<" in pascals";
	size_t ch = 0;
	std::cout << "\n\n press 1 for newtons raphsons method : ";
	std::cin >> ch;
	if (ch != 0)
	{
		ans = f.newton_raphson();
		std::cout << "\n\nfriction factor - newton " << ans;
	}
	std::cin.get();
	std::cin.get();
	return 0;
}