#include "common_header.h";
#include <chrono>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;
int main() {
	string line;
	std::ifstream afile;
	ofstream bfile;
	ofstream cfile;
	std::chrono::time_point<std::chrono::system_clock> start, end;///시간 측정
	start = std::chrono::system_clock::now();

	vector<string> NYT_text;
	vector<string> APW_text;
	get_text_name(NYT_text, APW_text);
	int ny = 0, ap = 0;

	ifstream aaa("lists");

	while (getline(aaa, line)) {
		if (line.at(28) == 'A') {
			ap++;
			APW_text.push_back(line);
		}
		else {
			ny++;
			NYT_text.push_back(line);
		}
	}
	for (int i = 0; i < APW_text.size(); i++) {
		cout<<APW_text[i]<<endl;
	}
	cout << APW_text.size() << endl;

	end = std::chrono::system_clock::now();/// time calculated
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << "s\n";
	while (1) {

	}
	aaa.close();
	int i = 0;
	while (i < ny) {
		read_txt(afile, bfile, NYT_text[i]);
		i++;
	}
	i = 0;
	while (i <  ap) {
		read_txt(afile, bfile, APW_text[i]);
		i++;
	}



	/*
	if (line.compare("<DOCNO>") == 0) {
	afile >> line;
	bfile << "<DOCNO> : " << line << endl;
	line.clear();
	}
	else if (line.compare("<HEADLINE>") == 0) {

	}

	*/

	return 0;
}