#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

//�}�b�v�̃T�C�Y(��{��1)
const int map_size = 1;
//�c���̍ő吔(�}�b�v�ɂ���ĕύX)
<<<<<<< HEAD
const int map_max_x = 104, map_max_y = 18;
=======
const int map_max_x = 25, map_max_y = 14;
>>>>>>> kuri

class Mapchip
{
public:
	static void CsvToVector(std::vector<std::vector<int>>& mapData, std::string fName);

	static int GetChipNum(int x, int y, std::vector<int> map);

	static void ChangeChipNum(int x, int y, std::vector<int>& map);
};

