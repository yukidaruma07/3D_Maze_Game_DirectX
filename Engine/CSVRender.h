#pragma once
#include <string>
#include <vector>

class CSVRender {
private:
	std::vector<std::vector<std::string>> data_;
	std::string path_;
public:

	CSVRender(const std::string& path);
	~CSVRender();

	void Init();
	std::string  GetPath() const { return path_; }
	std::string GetData(int row, int col) const { return data_[row][col]; }
	int GetWidth() const { return data_.empty() ? 0 : data_[0].size(); }
	int GetHeight() const { return data_.size(); }

	std::vector<std::vector<std::string>> GetData() const { return data_; }
};

