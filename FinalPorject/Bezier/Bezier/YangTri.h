#pragma once
#include<vector>

class YangTri
{
public:
	int GetElem(int times, int j);//获取第times行的第j个元素

private:
	std::vector<std::vector<unsigned int>> Tri{//主数据体
	{1},
	{1,1},
	{1,2,1},
	{1,3,3,1},
	{1,4,6,4,1}
	};
};