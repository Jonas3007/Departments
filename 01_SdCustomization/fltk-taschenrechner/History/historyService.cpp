#include <historyService.h>
#include <fstream>
#include <sstream>

std::ostream &operator<<(std::ostream &os, const HistoryEntry &h)
{
	os << h.entry << " = " << h.result;
	return os;
}
void HistoryService ::setCurrentFile(string file)
{
	if(file.find(".txt") == string::npos)
	{
		file += ".txt";
	}
	currentFile = file;
	filePath = std::string(PROJECT_SOURCE_DIR) + "/History/Data/" + currentFile;
	
}


void HistoryService ::AddtoTempHistory(std::string entry, double result)
{
	HistoryEntry entryStruct;
	entryStruct.entry = entry;
	entryStruct.result = std::to_string(result);
	tempHistory.push_back(entryStruct);
}


void HistoryService ::AddtoTempHistory(std::string entry, std::string result)
{
	HistoryEntry entryStruct;
	entryStruct.entry = entry;
	entryStruct.result = result;
	tempHistory.push_back(entryStruct);
}

void HistoryService :: createFile()
{
	ofstream myFile;
	myFile.open(filePath);
	myFile.close();
}

void HistoryService ::SaveHistory() 
{
	ofstream historyFile;
	historyFile.open(filePath, std::ios::app); 
	if (!historyFile.is_open())
	{
		createFile();
		historyFile.open(filePath, std::ios::app);
	}
	cout << "Saving history to: " << filePath << endl;
	for (const auto &entry : tempHistory)
	{
		historyFile << entry << endl; 
	}
	historyFile.close();
	tempHistory.clear();
}


string HistoryService ::GetHistory()
{
	ifstream historyFile(filePath);

	if (!historyFile.is_open())
	{
		std::cerr << "[ERROR] File could not be opened!\n";
		return "";
	}
	std::ostringstream content;
	content << historyFile.rdbuf();
	return content.str();
}
vector<string> HistoryService ::GetIncomingFile(string filename)
{
	ifstream incomingFile(std::string(PROJECT_SOURCE_DIR) + "/History/Data/Incoming/" + filename );

	if (!incomingFile.is_open())
	{
		std::cerr << "[ERROR] File could not be opened!\n";
	}
	vector<string> listOfCalculations;
	string line;
	while (std::getline(incomingFile, line))
	{
		listOfCalculations.push_back(line);
	}
	incomingFile.close();
	return listOfCalculations;
	
}

	