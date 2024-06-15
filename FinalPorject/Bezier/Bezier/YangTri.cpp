#include "YangTri.h"

int YangTri::GetElem(int times, int j)
{
	int d = times - Tri.size();
	if (d < 0)
	{
		return Tri[times][j];
	}
	else
	{
		for (size_t i = 0; i <= d; i++)
		{
			std::vector<unsigned int> temp{ 1 };
			for (size_t j = 0; j < Tri.back().size() - 1; j++)
			{
				temp.push_back(Tri.back()[j] + Tri.back()[j + 1]);
			}
			temp.push_back(1);
			Tri.push_back(temp);
		}
		return Tri[times][j];
	}
}
