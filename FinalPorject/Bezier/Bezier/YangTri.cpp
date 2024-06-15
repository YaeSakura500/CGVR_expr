#include "YangTri.h"

int YangTri::GetElem(int times, int j)
{
	int d = times - Tri.size();
	if (d < 0)//若已存在，直接查表
	{
		return Tri[times][j];
	}
	else//不存在则迭代计算并更新数组
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
