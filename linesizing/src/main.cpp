#include"calc.h"

int main()
{
	std::cout << "*******************************************************\n";
	std::cout << "***** Pressure Drop calculation - colebrook equation ****\n";
	std::cout << "********************************************************\n\n";

	colebrook_f f;
	f.prep_data();
	f.initialize();
	f.report();

	std::cout << "Wanna play with dia ----- >  ";
	uint16_t ch = 0;
	std::cin >> ch;
	while (ch != 0)
	{
		f.get_data(&f.dia, 1e-03, "new diameter in mm");
		f.initialize();
		f.report();

		std::cout << "Wanna play with dia again ----- >  ";
		std::cin >> ch;

	}

	std::cout << "\n\nvarataaaaaa ............\n\n";
	std::cin.get();
	return 0;
}