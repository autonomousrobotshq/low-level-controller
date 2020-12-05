#include <iostream>
#include "Common/SigFilter.hpp"

using namespace std;

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		const uint8_t sample_count = argc - 1;
		SigFilter filter(sample_count);

		int16_t test_array[sample_count];
		filter.Reset();

		cout << "For Array :";
		for (int i = 1; i <  argc; i++)
		{
			test_array[i - 1] = atoi(argv[i]);
			cout << " " << test_array[i - 1];
			filter.NewReading(test_array[i - 1]);
		}
		const int16_t f_avg = filter.GetFilteredAverage();
		cout << " -> Filtered average is : " <<  f_avg << endl;

		return (0);
	}
	else
	{
		return (1);
	}
}
