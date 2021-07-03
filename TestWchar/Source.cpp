#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <stdio.h>
#include <string>
#include <locale>
#include <codecvt> //possible C++11?
#include <fstream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include <random>
#include <time.h>
#include <conio.h>
#include "console.h"
using namespace std;

// khi xóa màn hình nó sẽ lấy color của trước đó làm màu nền
// textcolor từ 0-256: phần nguyên là màu nền,phần dư là màu chữ-

#define numberRetype 1
#define numberRetypeFinish 4

#define colorNotChoose 15
#define colorChoose 143

#define windowWidth 89
#define windowHeight 44

#define numberOfFile 15

vector<wstring> chooseNameFiles = { (L"Voca_01"),(L"Voca_02"),(L"Voca_03"),(L"Voca_04"),(L"Voca_05"),(L"Voca_06"),(L"Voca_07"),(L"Voca_08"),(L"Voca_09"),(L"Voca_10"),(L"Voca_11"),(L"Voca_12"),(L"Voca_13"),(L"Voca_14"),(L"Voca_15"),(L"Voca_16"),(L"Voca_42"),(L"Voca_VNU1"),(L"Voca_VNU2"),(L"Voca_VNU3"),(L"Voca_VNU4"),(L"Voca_VNU5"),(L"Voca_VNU6"),(L"Voca_VNU7"),(L"Voca_VNU8"),(L"Voca_VNU9"),(L"Voca_VNU10"),(L"Voca_VNU11"),(L"Test_02"),(L"Quit") };
vector<wstring> chooseEngViet = { (L"English"),(L"Vietnamese") };
vector<wstring> chooseWhenFinish = { (L"Practice again this file"),(L"Back to menu"),(L"Quit Program") };
enum TrangThai { UPUP, DOWN, LEFT, RIGHT, ENTER };

TrangThai key(int z) {
	if (z == 224) {
		char c;
		c = _getch();
		if (c == 72)
			return UPUP;
		if (c == 80)
			return DOWN;
	}
	else if (z == 13)
		return ENTER;
}

class eachRow {
public:
	wstring english;
	vector<wstring> viet;
	wstring ipa;
	wstring loaiTu;
};

void printVecWstring(vector<wstring> vec) {
	for (int i = 0; i < vec.size() - 1; i++)
		wcout << vec[i] << ", ";
	wcout << vec[vec.size() - 1];
}

int tableChoose(vector<wstring> temp, int k) {	// k = stt bảng chọn
	int indexChoose = 0;
	system("cls");
	wstring title_0 = L"Choose file you want to practice:";
	wstring title_1 = L"Choose language you want to practice:";
	while (1)
	{
		TextColor(15);
		clrscr();
		if (k == 0)
			wcout << setw(windowWidth / 2 + title_0.length() / 2) << title_0;
		else if (k == 1)
			wcout << setw(windowWidth / 2 + title_1.length() / 2) << title_1;
		wcout << endl << endl;
		for (int i = 0; i < temp.size(); i++) {
			if (i == indexChoose) {
				TextColor(colorNotChoose);
				wcout << setw(windowWidth / 2 - temp[i].length() / 2 - 1) << " ";
				TextColor(colorChoose);
				wcout << temp[i] << endl;
			}
			else {
				TextColor(colorNotChoose);
				if (temp[i].length() % 2 == 1)
					wcout << setw(windowWidth / 2 + temp[i].length() / 2) << temp[i] << endl;
				else wcout << setw(windowWidth / 2 + temp[i].length() / 2 - 1) << temp[i] << endl;
			}
		}

		int k = _getch();
		TrangThai cur = key(k);
		if (cur == DOWN) {
			indexChoose++;
			if (indexChoose == temp.size())
				indexChoose = 0;
		}
		if (cur == UPUP) {
			indexChoose--;
			if (indexChoose == -1)
				indexChoose = temp.size() - 1;
		}
		if (cur == ENTER)
		{
			return indexChoose;
		}
	}
}

void nhapLaiTu(wstring t) {

}

void answerWrongWordByVietScreen3(vector<eachRow> listWrongWord, bool kOL) { // kOL: kind of language (trả lời bằng tiếng viet: 1, english: 0)

}



int answer(wfstream& fin, int kOL)		// kOL: kind of language (trả lời bằng tiếng viet: 1, english: 0)
{
	_setmode(_fileno(stdout), _O_WTEXT);								// Needed for output
	_setmode(_fileno(stdin), _O_WTEXT);									// Needed for input
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);		// UTF-8
	fin.imbue(loc);

	TextColor(15);
	system("cls");
	vector<eachRow> listWrongWord;
	vector<eachRow> listWord;				// Danh sách toàn bộ từ trong file
	vector<wstring> listWordLap;
	wstring numberAnswerByEng, numberAnswerByVie, a;

	rewind(stdin);
	getline(fin, numberAnswerByEng);	// lấy 2 hàng đầu tiên về số lần đọc
	rewind(stdin);
	getline(fin, numberAnswerByVie);

	wcout << L"Number of practice times by Enlish: " << numberAnswerByEng << endl;
	wcout << L"Number of practice times by Vietnamese: " << numberAnswerByVie << endl;
	// listWord = danh sách từ
	while (fin)					// WHY WHILE(FIN) FAIL ???????????
	{
		eachRow temp;
		rewind(stdin);
		getline(fin, temp.english, L'(');
		if (temp.english == L"end")
			break;
		rewind(stdin);
		getline(fin, temp.loaiTu, L' ');
		rewind(stdin);
		getline(fin, temp.ipa, L')');
		temp.ipa.erase(temp.ipa.begin(), temp.ipa.begin() + 2);

		// đọc dữ liệu các từ tiếng việt
		wstring tempAllViet;
		rewind(stdin);
		getline(fin, tempAllViet);

		wstring delimiter = L", ";
		size_t pos = 0;
		wstring token;
		while ((pos = tempAllViet.find(delimiter)) != string::npos) {
			token = tempAllViet.substr(0, pos);
			temp.viet.push_back(token);
			tempAllViet.erase(0, pos + delimiter.length());
		}
		temp.viet.push_back(tempAllViet);

		if (fin)
			listWord.push_back(temp);
	}

	// Kiểm tra các từ lặp, nếu có từ trùng thì cho vào list từ lặp
	for (int i = 0; i < listWord.size() - 1; i++) {
		for (int j = i + 1; j < listWord.size(); j++) {
			if (listWord[i].viet[0] == listWord[j].viet[0])
				listWordLap.push_back(listWord[i].viet[0]);
		}
	}

	wcout << L"Number of word: " << listWord.size() << endl << endl;
	int length = listWord.size();
	int lengthTemp = length;

	// Trả lời bằng tiếng anh
	if (!kOL) {
		for (int i = 0; i < length; i++) {
			int rn = rand() % lengthTemp;
			wstring a;
			int viTriXDauDong = whereX();
			int viTriYDauDong = whereY();

			wcout << L"[" << i + 1 << L"] ";
			printVecWstring(listWord[rn].viet);
			

			// Nếu là từ lặp thì hiển thị thêm phần loại từ
			for (int i = 0; i < listWordLap.size(); i++) {
				if (listWord[rn].viet[0] == listWordLap[i])
					wcout << " (" << listWord[rn].loaiTu << ")";
			}

			wcout << ": ";
			rewind(stdin);
			getline(wcin, a);
			int flag_99 = 0;
			if (a != listWord[rn].english)
			{
				eachRow temp;
				temp = listWord[rn];
				listWrongWord.push_back(temp);
				wcout << "(" << listWord[rn].ipa << "): " << listWord[rn].english << endl;
				wcout << L"nhap lai tu nay " << numberRetype << L" lan: " << endl;
				for (int i = 0; i < numberRetype; i++) {
					wstring fail;
					do {
						rewind(stdin);
						getline(wcin, fail);
						if (fail == L"b")
							break;
					} while (fail != listWord[rn].english);
				}
			}

			// hiển thị ipa khi trả lời đúng bằng tiếng anh
			if (a == listWord[rn].english)
			{
				int offsetBlank;
				if (i < 9)
					offsetBlank = 7;
				else offsetBlank = 8;
				int lengthAllViet = 0;
				for (int i = 0; i < listWord[rn].viet.size(); i++)
					lengthAllViet += listWord[rn].viet[i].length();
				lengthAllViet += (listWord[rn].viet.size() - 1) * 2;
				gotoXY(viTriXDauDong + offsetBlank + listWord[rn].english.length() + lengthAllViet, viTriYDauDong);
				wcout << "(" <<listWord[rn].loaiTu<<" - "<< listWord[rn].ipa << ")" << endl;
			}
			listWord.erase(listWord.begin() + rn);
			lengthTemp--;
		}
	}

	// Trả lời bằng tiếng việt
	else {
		for (int i = 0; i < length; i++)
		{
			int rn = rand() % lengthTemp;
			wstring a;
			wcout << L"[" << i + 1 << L"] " << listWord[rn].english << "("<<listWord[rn].loaiTu<<" - " << listWord[rn].ipa << "): ";
			rewind(stdin);
			int xTruoc = whereX(), yTruoc = whereY();
			getline(wcin, a);
			int xDau = whereX(), yDau=whereY();
			int flag_99 = 0;
			
			// Kiểm tra xem trùng 1 trong các từ tiếng việt
			for (int i = 0; i < listWord[rn].viet.size(); i++)
				if (1||a == listWord[rn].viet[i] || a == L"c") {
					gotoXY(xTruoc, yTruoc);
					wcout << listWord[rn].viet[i]<<endl;
					flag_99 = 1;
					break;
				}

			// Nếu trả lời sai tức là không trùng với từ nào trong list từ tiếng viết
			if (!flag_99) {
				eachRow temp;
				temp = listWord[rn];
				listWrongWord.push_back(temp);
			
				printVecWstring(listWord[rn].viet);
				wcout << endl;
				wcout << L"nhap lai tu nay " << numberRetype << L" lan: " << endl;
				for (int i = 0; i < numberRetype; i++) {
					wstring fail;
					bool tempBreak = 0;
					do {
						rewind(stdin);
						getline(wcin, fail);
						
						// Nếu nhập phím 'd' thì pop list từ sai.
						if (fail == L"d")
						{
							listWrongWord.pop_back();
							gotoXY(xDau, yDau);
							wcout << L"                                                         " << endl;
							wcout << L"                                                         " << endl;
							wcout << L"                                                         " << endl;
							gotoXY(xDau, yDau);
							tempBreak = 1;
							break;
						}
					} while (fail != listWord[rn].viet[0]);
					if (tempBreak)
						break;
				}
			}
			listWord.erase(listWord.begin() + rn);
			lengthTemp--;
		}
	}
	TextColor(15);
	system("cls");

	// Viết lại list từ sai
	if (listWrongWord.size() <= 0)
		wcout << "No words wrong!";
	else {

		wcout << L"You have " << listWrongWord.size() << L" word wrong accounting " << (int)(((double)listWrongWord.size() / length) * 100) << L"(%) all word!" << endl;
		wcout << L"Practic again words wrong: " << endl;
		for (int i = 0; i < listWrongWord.size(); i++) {
			wcout << listWrongWord[i].english << " (";
			for (int k = 0; k < listWordLap.size(); k++)
				if (listWrongWord[i].viet[0] == listWordLap[k])
					wcout << listWrongWord[i].loaiTu << " - ";
			wcout << listWrongWord[i].ipa << L"): ";


			int j = 0;
			for (j; j < listWrongWord[i].viet.size() - 1; j++) {
				wcout << listWrongWord[i].viet[j] << ", ";
			}
			wcout << listWrongWord[i].viet[j] << endl;
		}
		wcout << "========================" << endl;
		int _xx = whereX(); int _yy = whereY();

		// Trả lời bằng từ sai bằng tiếng anh
		if (!kOL) {
			for (int i = 0; i < numberRetypeFinish; i++) {
				// Xóa hết phần đã trả lời để quay lại trả lời các từ sai lần tiếp theo
				gotoXY(_xx, _yy);
				for (int j = 0; j < listWrongWord.size() * 2; j++) {
					wcout << L"                                                                 " << endl;
				}

				// Trả lời sai phần tiếp theo
				gotoXY(_xx, _yy);
				for (int p = 0; p < listWrongWord.size(); p++) {
					int j = 0;
					for (j; j < listWrongWord[p].viet.size() - 1; j++) {
						wcout << listWrongWord[p].viet[j] << ", ";
					}
					wcout << listWrongWord[p].viet[j] << ": ";
					wstring _temp;
					do {
						rewind(stdin);
						getline(wcin, _temp);
					} while (_temp != listWrongWord[p].english);
				}
			}
		}

		// Trả lời từ sai bằng tiếng việt
		else {
			for (int i = 0; i < numberRetypeFinish; i++) {
				gotoXY(_xx, _yy);
				for (int j = 0; j < listWrongWord.size() * 2; j++) {
					wcout << "                                                                 " << endl;
				}
				gotoXY(_xx, _yy);
				for (int p = 0; p < listWrongWord.size(); p++) {

					wcout << listWrongWord[p].english << L": ";
					wstring _temp;
					do {
						rewind(stdin);
						getline(wcin, _temp);
					} while (_temp != listWrongWord[p].viet[0]);
				}
			}
		}

	}

	//// Sửa số lần đã đọc file
	fin.seekg(0);
	wstring temptemp;
	size_t pos_0 = 0, pos_1 = 0;
	int number_0 = std::stoi(numberAnswerByEng, &pos_0);
	int number_1 = std::stoi(numberAnswerByVie, &pos_1);
	if (!kOL) {				// trả lời bằng tiếng anh
		number_0++;
		fin << number_0;
		fin.close();
	}
	else {
		number_1++;
		fin << number_0 << L"\n";
		fin << number_1;
		fin.close();
	}
	wcout << endl << "Press 'c' to continue: ";
	wchar_t finish;
	do {
		wcin >> finish;
	} while (finish != 'c');
	return 1;
}

void run() {
	int screen_1 = 1, screen_2 = 0, screen_3 = 0;
	int index_1, index_2, index_3;
	while (1) {
		if (screen_1) {
			system("cls");
			index_1 = tableChoose(chooseNameFiles, 0);
			if (index_1 == chooseNameFiles.size() - 1)
				return;
			screen_1 = screen_3 = 0;
			screen_2 = 1;
		}

		if (screen_2) {
			system("cls");
			wstring link = L"D:/Document/English/06_Vocabulary/VocaText/" + chooseNameFiles[index_1] + L".txt";
			index_2 = tableChoose(chooseEngViet, 1);
			wfstream fin(link);
			if (!fin) {
				wcout << "cann't open file! ";
				return;
			}
			answer(fin, index_2);
			fin.close();
			screen_1 = screen_2 = 0;
			screen_3 = 1;
		}

		if (screen_3) {
			system("cls");
			index_3 = tableChoose(chooseWhenFinish, 2);
			if (index_3 == 2)
				return;
			else if (index_3 == 0) {
				screen_1 = screen_3 = 0;
				screen_2 = 1;
			}
			else if (index_3 == 1) {
				screen_1 = 1;
				screen_2 = screen_3 = 1;
			}
		}
	}

}

int wmain(int argc, wchar_t* argv[]) {
	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
	_setmode(_fileno(stdin), _O_WTEXT); //needed for input
	srand((int)time(0));
	run();
	TextColor(15);
}