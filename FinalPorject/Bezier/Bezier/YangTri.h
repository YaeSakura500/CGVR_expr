#pragma once
#include<vector>

class YangTri
{
public:
	int GetElem(int times, int j);//��ȡ��times�еĵ�j��Ԫ��

private:
	std::vector<std::vector<unsigned int>> Tri{//��������
	{1},
	{1,1},
	{1,2,1},
	{1,3,3,1},
	{1,4,6,4,1}
	};
};