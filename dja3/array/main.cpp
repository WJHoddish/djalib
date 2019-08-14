#include <cassert>

#include "array.h"

int main(int argc, char* argv[])
{
	{

	}

	{
		using namespace dja;

		// multi-dimension array:
		Marray<int, 3> numbers((array_sizes(), 2, 3, 4));

		assert(numbers.size() == 2);
		assert(numbers.size_total() == 24);
		for (int i = 0; i < numbers.size(); i++)
		{
			array_ref<int, 2> numbers_2 = numbers[i];
			assert(numbers_2.size() == 3);
			assert(numbers_2.size_total() == 12);
			for (int j = 0; j < numbers_2.size(); j++)
			{
				array_ref<int, 1> numbers_3 = numbers_2[j];
				assert(numbers_3.size() == 4);
				assert(numbers_3.size_total() == 4);
				for (int k = 0; k < numbers_3.size(); k++)
				{
					numbers[i][j][k] = (i + 1) * (j + 1) * (k + 1);
					assert(numbers[i][j][k] == numbers_3[k]);
				}
			}
		}

		assert(numbers[1][2][1] == 12);
		assert(numbers[0][1][3] == 8);
	}
	return 0;
}