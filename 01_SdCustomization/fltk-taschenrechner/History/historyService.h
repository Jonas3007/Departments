#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct HistoryEntry
{
	string entry;
	string result;
};

class HistoryService
{
private:
	

public:
	// Attributes
	string currentFile;
	std::vector<HistoryEntry> tempHistory;
	string filePath;

	// Getter/Setter
	string getCurrentFile() const { return currentFile; }
	string getFilePath() const { return filePath; }
	void setCurrentFile(string file);

	// Methods
	void AddtoTempHistory(string entry, double result);
	void AddtoTempHistory(string entry, string result);
	void createFile();
	void SaveHistory();
	string GetHistory();
};
