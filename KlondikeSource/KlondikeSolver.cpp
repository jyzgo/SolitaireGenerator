#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

#include<fstream>
#include<ctime>
#include"Solitaire.h"
#include<string>
#include<vector>
using namespace std;


bool LoadGame(string const& f, Solitaire & s, unsigned int & index) {
	while (index < f.size() && f[index] == '\r' || f[index] == '\n' || f[index] == '\t' || f[index] == ' ') { index++; }
	if (index >= f.size()) { return false; }
	int gameType = 0;
	int startIndex = index;
	if (f[index] == '#') {
		while (index < f.size() && f[index++] != '\n') {}
		return false;
	} else if (f[index] == 'T' || f[index] == 't') {
		int lineCount = 0;
		while (index < f.size() && lineCount < 8) {
			if (f[index++] == '\n') { lineCount++; }
		}
		s.LoadPysol(f.substr(startIndex, index - startIndex));
	} else if (f[index] == 'G' || f[index] == 'g') {
		while (index < f.size() && f[index++] != ' ') {}
		startIndex = index;
		while (index < f.size() && f[index++] != '\n') {}
		s.Shuffle1(atoi(f.substr(startIndex, index - startIndex).c_str()));
	} else {
		while (index < f.size() && f[index++] != '\n') {}
		s.LoadSolitaire(f.substr(startIndex, index - startIndex));
	}
	return true;
}

void swapVec(vector<string>& vec)
{
	vector<string> newVec;
	for (int i = 0; i < vec.size(); i++)
	{
		newVec.push_back(vec[i]);
	}
	//return;

	vec[0] = newVec[0];
	vec[1] = newVec[1];
	vec[2] = newVec[3];
	vec[3] = newVec[6];
	vec[4] = newVec[10];
	vec[5] = newVec[15];
	vec[6] = newVec[21];
	vec[7] = newVec[2];
	vec[8] = newVec[4];
	vec[9] = newVec[7];
	vec[10] = newVec[11];
	vec[11] = newVec[16];
	vec[12] = newVec[22];
	vec[13] = newVec[5];
	vec[14] = newVec[8];
	vec[15] = newVec[12];
	vec[16] = newVec[17];
	vec[17] = newVec[23];
	vec[18] = newVec[9];
	vec[19] = newVec[13];
	vec[20] = newVec[18];
	vec[21] = newVec[24];
	vec[22] = newVec[14];
	vec[23] = newVec[19];
	vec[24] = newVec[25];
	vec[25] = newVec[20];
	vec[26] = newVec[26];
	vec[27] = newVec[27];
}

bool CheckAndMove(int index)
{
	string line;
	std::string::size_type sz;
	//char* fileName = "";// initialized properly
	//sprintf(fileName, "Sol\\original\\solitaire%d.txt", index);
	string fileName = "Sol\\original\\solitaire" + to_string(index) + ".txt";
	ifstream myfile(fileName);
	string curDec = "";
	if (myfile.is_open())
	{
		vector<string> m;

		while (getline(myfile, line))
		{
			//cout << line << '\n';
			int i_dec = std::stoi(line, &sz);

			int num = (i_dec) % 13 + 1;
			int suit = i_dec / 13 + 1;
			if (suit == 1)
			{
				suit = 2;
			}
			else if (suit == 2)
			{
				suit = 1;
			}


			int pre = -1;
			string fi;
			if (num == 0)
			{
				cout << "num " << i_dec << "\n";

			}

			if (num < 10)
			{
				fi = std::to_string(0) + to_string(num) + to_string(suit);
			}
			else
			{
				fi = to_string(num) + to_string(suit);
			}

			m.push_back(fi);

			

			cout << " <" << fi << "> ";

		}
		
		//for (int i = 0; i < 28; i++)
		//{
		//	cout << " m " << m[i] << "\n";
		//}

		swapVec(m);

		for (int i = 0; i < m.size(); i++)
		{
			//cout << "af m " << m[i] << "\n";
			curDec += m[i];
		}



		cout << " final " << curDec << "\n";
		myfile.close();
	}

	else cout << "Unable to open file";

	//return 0;

	Solitaire s;
	s.Initialize();

	bool commandLoaded = false;
	int outputMethod = 0;
	int multiThreaded = 1;
	int maxClosedCount = 0;
	bool fastMode = false;
	string fileContents;
	bool replay = false;
	bool showMoves = false;
	bool success = false;

	//-----
	;
	if (!s.LoadSolitaire(curDec)) { cout << "Specified deck is invalid."; return 0; }
	commandLoaded = true;
	//---

	outputMethod = 1;
	showMoves = true;
	//for (int i = 1; i < argc; i++) 
	//{

	//	if (_stricmp(argv[i], "-draw") == 0 || _stricmp(argv[i], "/draw") == 0 || _stricmp(argv[i], "-dc") == 0 || _stricmp(argv[i], "/dc") == 0) {
	//		if (i + 1 >= argc) { cout << "You must specify draw count."; return 0; }
	//		int drawCount = atoi(argv[i + 1]);
	//		if (drawCount < 1 || drawCount > 12) { cout << "Please specify a valid draw count from 1 to 12."; return 0; }
	//		s.SetDrawCount(drawCount);
	//		i++;
	//	} else if (_stricmp(argv[i], "-deck") == 0 || _stricmp(argv[i], "/deck") == 0 || _stricmp(argv[i], "-d") == 0 || _stricmp(argv[i], "/d") == 0) {
	//		if (i + 1 >= argc) { cout << "You must specify deck to load."; return 0; }
	//		if (commandLoaded) { cout << "Only one method can be specified (deck/game/file)."; return 0; }
	//		if (!s.LoadSolitaire(argv[i + 1])) { cout << "Specified deck is invalid."; return 0; }
	//		commandLoaded = true;
	//		i++;
	//	} else if (_stricmp(argv[i], "-game") == 0 || _stricmp(argv[i], "/game") == 0 || _stricmp(argv[i], "-g") == 0 || _stricmp(argv[i], "/g") == 0) {
	//		if (i + 1 >= argc) { cout << "You must specify a game number to load. Any integeral number."; return 0; }
	//		if (commandLoaded) { cout << "Only one method can be specified (deck/game/file)."; return 0; }
	//		commandLoaded = true;
	//		s.Shuffle1(atoi(argv[i + 1]));
	//		i++;
	//	} else if (_stricmp(argv[i], "-out") == 0 || _stricmp(argv[i], "/out") == 0 || _stricmp(argv[i], "-o") == 0 || _stricmp(argv[i], "/o") == 0) {
	//		if (i + 1 >= argc) { cout << "You must specify a valid output method. 0 or 1."; return 0; }
	//		outputMethod = atoi(argv[i + 1]);
	//		if (outputMethod < 0 || outputMethod > 2) { cout << "You must specify a valid output method. 0, 1, or 2."; return 0; }
	//		i++;
	//	} else if (_stricmp(argv[i], "-states") == 0 || _stricmp(argv[i], "/states") == 0 || _stricmp(argv[i], "-s") == 0 || _stricmp(argv[i], "/s") == 0) {
	//		if (i + 1 >= argc) { cout << "You must specify max states."; return 0; }
	//		maxClosedCount = atoi(argv[i + 1]);
	//		if (maxClosedCount < 0) { cout << "You must specify a valid max number of states."; return 0; }
	//		i++;
	//	} else if (_stricmp(argv[i], "-fast") == 0 || _stricmp(argv[i], "/fast") == 0 || _stricmp(argv[i], "-f") == 0 || _stricmp(argv[i], "/f") == 0) {
	//		fastMode = true;
	//		if (maxClosedCount == 0) { maxClosedCount = 200000; }
	//	} else if (_stricmp(argv[i], "-m") == 0 || _stricmp(argv[i], "/m") == 0 || _stricmp(argv[i], "-multi") == 0 || _stricmp(argv[i], "/multi") == 0) {
	//		if (i + 1 >= argc) { cout << "You must specify number of threads."; return 0; }
	//		multiThreaded = atoi(argv[i + 1]);
	//		if (multiThreaded < 2 || multiThreaded > 99) { cout << "You must specify a valid number of threads."; return 0; }
	//		i++;
	//	} else if (_stricmp(argv[i], "-mvs") == 0 || _stricmp(argv[i], "/mvs") == 0 || _stricmp(argv[i], "-moves") == 0 || _stricmp(argv[i], "/moves") == 0) {
	//		showMoves = true;
	//	} else if (_stricmp(argv[i], "-r") == 0 || _stricmp(argv[i], "/r") == 0) {
	//		replay = true;
	//	} else if (_stricmp(argv[i], "-?") == 0 || _stricmp(argv[i], "/?") == 0 || _stricmp(argv[i], "?") == 0 || _stricmp(argv[i], "/help") == 0 || _stricmp(argv[i], "-help") == 0) {
	//		cout << "Klondike Solver V2.0\nSolves games of Klondike (Patience) solitaire minimally or a faster best try.\n\n";
	//		cout << "KlondikeSolver [/DC] [/D] [/G] [/O] [/M] [/S] [/F] [/R] [/MVS] [Path]\n\n";
	//		cout << "  /DRAW # [/DC #]       Sets the draw count to use when solving. Defaults to 1.\n\n";
	//		cout << "  /DECK str [/D str]    Loads the deck specified by the string.\n\n";
	//		cout << "  /GAME # [/G #]        Loads a random game with seed #.\n\n";
	//		cout << "  Path                  Solves deals specified in the file.\n\n";
	//		cout << "  /R                    Replays solution to output if one is found.\n\n";
	//		cout << "  /MULTI # [/M #]       Uses # threads to solve deals.\n";
	//		cout << "                        Only works when solving minimally.\n\n";
	//		cout << "  /OUT # [/O #]         Sets the output method of the solver.\n";
	//		cout << "                        Defaults to 0, 1 for Pysol, and 2 for minimal output.\n";
	//		cout << "  /MOVES [/MVS]         Will also output a compact list of moves made when a\n";
	//		cout << "                        solution is found.";
	//		cout << "  /STATES # [/S #]      Sets the maximum number of game states to evaluate\n";
	//		cout << "                        before terminating. Defaults to 5,000,000.\n\n";
	//		cout << "  /FAST [/F]            Run the solver in a best attempt mode, which is\n";
	//		cout << "                        faster, but not guaranteed to give minimal solution.\n";
	//		return 0;
	//	} else {

	//		if (commandLoaded) { cout << "Only one method can be specified (deck/game/file)."; return 0; }
	//		commandLoaded = true;
	//		ifstream file(argv[i], ios::in | ios::binary);
	//		if (!file) { cout << "You must specify a valid and accessible file."; return 0; }
	//		file.seekg(0, ios::end);
	//		fileContents.resize((unsigned int)file.tellg());
	//		file.seekg(0, ios::beg);
	//		file.read(&fileContents[0], fileContents.size());
	//		file.close();
	//	}
	//}



	if (maxClosedCount == 0) { maxClosedCount = 5000000; }
	unsigned int fileIndex = 0;
	do {
		if (fileContents.size() > fileIndex) {
			if (!LoadGame(fileContents, s, fileIndex)) {
				continue;
			}
		}
		s.ResetGame();

		if (outputMethod == 0) {
			cout << s.GameDiagram() << "\n\n";
		}
		else if (outputMethod == 1) {
			cout << s.GameDiagramPysol() << "\n\n";
		}

		clock_t total = clock();
		SolveResult result = CouldNotComplete;
		if (fastMode) {
			int bestCount = 512;
			int bestFoundation = 0;
			result = s.SolveFast(maxClosedCount, 0, 0);
			if (result == SolvedMinimal || result == SolvedMayNotBeMinimal) {
				bestCount = s.MovesMadeNormalizedCount();
			}
			bestFoundation = s.FoundationCount();
			Solitaire best = s;
			s.ResetGame();
			result = s.SolveFast(maxClosedCount, 0, 4);
			if ((result == SolvedMinimal || result == SolvedMayNotBeMinimal) && s.MovesMadeNormalizedCount() < bestCount) {
				best = s; bestCount = s.MovesMadeNormalizedCount(); bestFoundation = s.FoundationCount();
			}
			if (s.FoundationCount() > bestFoundation) {
				best = s; bestFoundation = s.FoundationCount();
			}
			s.ResetGame();
			result = s.SolveFast(maxClosedCount, 1, 4);
			if ((result == SolvedMinimal || result == SolvedMayNotBeMinimal) && s.MovesMadeNormalizedCount() < bestCount) {
				best = s; bestCount = s.MovesMadeNormalizedCount(); bestFoundation = s.FoundationCount();
			}
			if (s.FoundationCount() > bestFoundation) {
				best = s; bestFoundation = s.FoundationCount();
			}
			s = best;
			if (bestFoundation == 52) { result = SolvedMayNotBeMinimal; }
		}
		else if (multiThreaded > 1) {
			result = s.SolveMinimalMultithreaded(multiThreaded, maxClosedCount);
		}
		else {
			result = s.SolveMinimal(maxClosedCount);
		}
		bool canReplay = false;
		if (result == SolvedMinimal) {
			cout << "Minimal solution in " << s.MovesMadeNormalizedCount() << " moves.";
			canReplay = true;
		}
		else if (result == SolvedMayNotBeMinimal) {
			cout << "Solved in " << s.MovesMadeNormalizedCount() << " moves.";
			canReplay = true;
		}
		else if (result == Impossible) {
			cout << "Impossible. Max cards in foundation " << s.FoundationCount() << " at " << s.MovesMadeNormalizedCount() << " moves.";
		}
		else if (result == CouldNotComplete) {
			cout << "Unknown. Max cards in foundation " << s.FoundationCount() << " at " << s.MovesMadeNormalizedCount() << " moves.";
		}
		cout << " Took " << (clock() - total) << " ms.\n";

		if (outputMethod < 2 && replay && canReplay) {
			int movesToMake = s.MovesMadeCount();
			s.ResetGame();
			for (int i = 0; i < movesToMake; i++) {
				cout << "----------------------------------------\n";
				cout << s.GetMoveInfo(s[i]) << "\n\n";
				s.MakeMove(s[i]);

				if (outputMethod == 0) {
					cout << s.GameDiagram() << "\n\n";
				}
				else {
					cout << s.GameDiagramPysol() << "\n\n";
				}
			}
			cout << "----------------------------------------\n";
		}
		if (showMoves && canReplay) {
			cout << s.MovesMade() << "\n\n";
		}
		else if (showMoves) {
			cout << "\n";
		}
		success = canReplay;
	} while (fileContents.size() > fileIndex);
	return success;

}
void MoveSuccess(int index)
{
	string oldfileName = "Sol\\original\\solitaire" + to_string(index) + ".txt";
	string newfileName = "Sol\\Winable\\solitaire" + to_string(index) + ".txt";
	rename(oldfileName.c_str(), newfileName.c_str());
}

void MoveFail(int index)
{
	string oldfileName = "Sol\\original\\solitaire" + to_string(index) + ".txt";
	string newfileName = "Sol\\Unable\\solitaire" + to_string(index) + ".txt";
	rename(oldfileName.c_str(), newfileName.c_str());

}

bool FileExist(int index)
{
	string oldfileName = "Sol\\original\\solitaire" + to_string(index) + ".txt";
	if (std::ifstream(oldfileName))
	{
		return true;
			 
	}
	return false;
}

int main(int argc, char * argv[]) {

	//for (int i = 0; i < 10; i++)
	//{
	//	char* s = "";// initialized properly
	//	sprintf(s, "You: %d CPU: %d", i, i);
	//	ifstream m(s);
	//}
	//std::ofstream outfile("test.txt");

	//outfile << "my text here!" << std::endl;

	//outfile.close();

	//return 0;
	int success = 0;
	int fail = 0;
	const int max = 323;
	for (int i = 1; i < max; i++)
	{
		if (!FileExist(i))
		{
			cout << "File not exist " << i << "\n";
			continue;
		}

		bool s = CheckAndMove(i);
		if(s)
		{
			success++;
			MoveSuccess(i);
		}
		else
		{
			fail++;
			MoveFail(i);
		}

	}
	
	cout << "All file done success file num->" << success << " fail file num->" << fail << "\n";
	return 0;
}



