#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int N = 0, NZ = 0;

/*
добавление элементов в массив
принимает позиции, указатели на массивы
возвращает значение
*/
int addElements(int i, int j, int* mass, int* LI, int* LJ)
{
	int AA = 0;
	int N1 = LI[i] - 1;
	int N2 = LI[i + 1] - 1;
	for(int k = N1; k < N2; k++)
	{
		if(LJ[k] == j + 1)
		{
			AA = mass[k];
			break;
		}
	}
	return AA;
}

//проверка на то, что значение является числом
//принимает строку, возвращает лог.значение
bool isNumber(string str)
{
	for(size_t i = 0; i < str.length(); i++)
	{
		if(!(str[i] >= '0' && str[i] <= '9'))
		{
			return false;
		}
	}
	return true;
}

//преобразование строки в число
//принимает строку, возвращает число
int strToInt(string str)
{
	int answer = 0;
	for(size_t i = 0; i < str.length(); i++)
	{
		answer *= 10;
		answer += str[i] - '0';
	}
	return answer;
}

/*
создание переменной пары значений (логическое и вектор)
Вектор содержит элементы строки
функция из строки получает значения, при этом проверяя значения на момент ощибок или несоответсвия типов
устанавливается размер матрицы N
возвращает лог.значение со значением правильный ли формат данных
*/
pair <bool, vector <int> > fLine(string str)
{
	vector <string> strElem;
	vector <int> answer;
	string temp;
	for(size_t i = 0; i < str.length(); i++)
	{
		if(str[i] != ' ')
		{
			//конкатенация строк
			temp += str[i];
		}
		else
		{
			if(temp.length())
			{
				//добавление элемента в конец
				strElem.push_back(temp);
				temp = "";

				//увеличение пер-ой размера матрицы
				N++;
			}
		}
	}
	if(temp != "")
	{
		//добавление элемента в конец
		strElem.push_back(temp);

		//увеличение пер-ой размера матрицы
		N++;
	}

	for(int i = 0; i < N; i++)
	{
		//если не число
		if(!isNumber(strElem[i]))
			return {false, answer};
	}

	for(int i = 0; i < N; i++)
	{
		//добавление преобразованных string в int
		answer.push_back(strToInt(strElem[i]));
	}
	return {true, answer};
}

/*
создание переменной пары значений (логическое и вектор)
Вектор содержит элементы строки
то есть функция из строки получает значения, при этом проверяя значения на момент ощибок или несоответсвия типов, и
устанавливается значение ненулевых элементов
возвращает лог.значение со значением правильный ли формат данных
*/
pair <bool, vector <int> > splitString(string str)
{
	vector <string> strElem;
	vector <int> answer;
	string temp;
	int j = 0;
	for(size_t i = 0; i < str.length(); i++)
	{
		if(str[i] != ' ')
		{
			//конкатенация строк
			temp += str[i];
		}
		else
		{
			if(temp.length())
			{
				if(j == N)
				{
					return {false, answer};
				}
				//добавление элемента в конец
				strElem.push_back(temp);
				j++;
				temp = "";
				//увеличение пер-ой числа ненулевых эл-ов
				NZ++;
			}
		}
	}
	if(temp != "")
	{
		if(j == N)
		{
			return {false, answer};
		}
		//добавление элемента в конец
		strElem.push_back(temp);
		j++;
		//увеличение пер-ой числа ненулевых эл-ов
		NZ++;
	}

	for(size_t i = 0; i < strElem.size(); i++)
	{
		//если не число
		if(!isNumber(strElem[i]))
			return {false, answer};
	}

	for(size_t i = 0; i < strElem.size(); i++)
	{
		//добавление преобразованных string в int
		answer.push_back(strToInt(strElem[i]));
	}
	return {true, answer};
}

//указатель на массив эл-ов симметричных относительно диагонали
int* AL = nullptr;

//указатели на массивы элементов диагонали
int* AD = nullptr;

//указатели на массивы элементов выше главной диагонали
int* AU = nullptr;
int* TAU = nullptr;

//указатель на массив эле-ов(хранит вторые индексы)
int* LJ = nullptr;
int* TLJ = nullptr;

//местоположение 1-го ненулевого элемента строки
int* LI = nullptr;

int ADi = 0, AUi = 0, ALi = 0, LJi = 0, LIi = 1, Sum = 0;
bool squareMatrix; //лог.значение истины NxN матрицы
int iTemp = 0;
vector <int> F_elems; //вектор значений
pair <bool, vector<int> > couples; //пары значений лог.значения и вектор
map <pair<int, int>, int> MAP; //контейнер со значением пары и числовым значением
string FLine;

//проверка ввода пункта меню
//возвращает номер пункта меню
int GetModeFromConsole()
{
	string mode = "";
	cout << "\nВыберите пункт меню:" << endl;
	cout << "1. Чтение из файла" << endl;
	cout << "2. Ввод с клавиатуры" << endl;
	cout << "3. Выход" << endl;
	int exit = 0;
	while(exit != 1)
	{
		cin >> mode;
		if((mode == "1") || (mode == "2") || (mode == "3"))
		{
			return atoi(mode.c_str());
		}
		else
		{
			cout << "Введите правильный режим" << endl;
		}
	}
}

void description()
{
	cout << "Введите числовые значения квадратной" << endl;
	cout << "разреженной структурно-симметричной матрицы" << endl;
	cout << "!Размер матрицы будет равен количеству элементов в первой строке" << endl;
	cout << "Пример ввода:\n1 0\n0 0" << endl;
	cout << "Ввод матрицы:" << endl;
}

void MethodER();
void MethodCmdError();
void MethodFileError();
void MethodThisBegin();
void MethodThisBeginFirst();

void MethodER()
{
	if(sizeof(AD) / sizeof(int) > 1) delete[] AD;
	if(sizeof(AU) / sizeof(int) > 1) delete[] AU;
	if(sizeof(AL) / sizeof(int) > 1) delete[] AL;
	if(sizeof(LJ) / sizeof(int) > 1) delete[] LJ;
	if(sizeof(LI) / sizeof(int) > 1) delete[] LI;
	if(sizeof(TLJ) / sizeof(int) > 1) delete[] TLJ;
	if(sizeof(TAU) / sizeof(int) > 1) delete[] TAU;
	AD = nullptr;
	AU = nullptr;
	AL = nullptr;
	LJ = nullptr;
	LI = nullptr;
	TLJ = nullptr;
	TAU = nullptr;
	F_elems.clear();
}

void MethodFileError()
{
	cout << "Неверный формат матрицы (не квадратная /";
	cout << " присутствуют символы / не структурно-симметричная)" << endl;
	MethodER();
}

void MethodThisBeginFirst()
{
	string fileName;
	cout << endl << "Введите имя файла с расширением txt: ";
	cin >> fileName;
	size_t end;

	//последнее вхождения '.'
	end = fileName.rfind('.');

	//если нет расширения файла
	if(end == string::npos)
	{
		cout << "Не указан формат файла." << endl;
		MethodThisBeginFirst();
	}
	else
	{
		if(end != fileName.size())
		{
			string format = "";
			//запись расширения после точки
			for(size_t i = end + 1; i < fileName.size(); i++)
			{
				format += fileName[i];
			}
			//проверка соответствия расширения
			if(format != "txt")
			{
				cout << "Неверный формат файла." << endl;
				MethodThisBeginFirst();
			}
		}
		else
		{
			cout << "Не указан формат файла." << endl;
			MethodThisBeginFirst();
		}
	}

	ifstream in;
	in.open(fileName, ios::in);

	//проверка существования файла
	if(!(in.is_open()))
	{
		cout << "Файл не найден." << endl;
		MethodThisBeginFirst();
	}

	MAP.clear();
	N = 0; NZ = 0; //пер-ые отвечающие за размер матрицы и кол-во её ненулевых элементов
	string F_Line;
	//Начало обработки первой строки
	getline(in, F_Line);
	couples = fLine(F_Line);

	if(!couples.first)
	{
		MethodFileError();
	}
	F_elems = couples.second;

	for(int i = 0; i < N; i++)
	{
		cout << F_elems[i] << " ";
	}
	cout << '\n';
	//создание массивов значений
	TAU = new int[(N - 1) * N / 2]; TLJ = new int[(N - 1) * N / 2];
	AD = new int[N]; LI = new int[N];
	ADi = 0; AUi = 0; ALi = 0; LJi = 0; LIi = 1;
	LI[0] = 1;
	iTemp = 0;
	AD[ADi] = F_elems[ADi];
	for(int i = ADi + 1; i < N; i++)
	{
		if(F_elems[i] != 0)
		{
			TAU[AUi++] = F_elems[i];
			TLJ[LJi++] = i + 1;
			MAP[{i, ADi}] = 1;

		}
	}
	LI[LIi] = AUi - iTemp + LI[LIi - 1];
	LIi++;
	ADi++;
	//конец обработки первой строки

	//обработка остальных строк
	squareMatrix = true;
	for(; ADi < N || !in.eof(); ADi++)
	{
		if(in.eof())
		{
			squareMatrix = false;
			break;
		}
		getline(in, F_Line);
		couples = splitString(F_Line);
		F_elems = couples.second;

		cout << F_Line << '\n';
		bool ch = false;

		//проверка, квадратная ли матрица
		if(F_elems.size() != N || ADi >= N)
		{
			ch = true;
			squareMatrix = false;
		}

		if(!ch)
		{
			iTemp = AUi;
			AD[ADi] = F_elems[ADi];
			for(size_t i = ADi + 1; i < F_elems.size(); i++)
			{
				if(F_elems[i] != 0)
				{
					TAU[AUi++] = F_elems[i];
					TLJ[LJi++] = i + 1;
					MAP[{i, ADi}] = 1;
					MAP[{ADi, i}] = 1;
				}
			}
			for(int i = 0; i < ADi; i++)
			{
				if(F_elems[i] == 0 && MAP[{ADi, i}] != 0)
				{
					MethodFileError();
				}
				if(F_elems[i] != 0 && MAP[{ADi, i}] == 0)
				{
					MethodFileError();
				}
				MAP[{ADi, i}] = F_elems[i];
			}
		}

		LI[LIi] = AUi - iTemp + LI[LIi - 1];
		LIi++;
	}
	if(squareMatrix == false)
	{
		cout << "Неверный формат матрицы (не квадратная /";
		cout << " присутствуют символы / не структурно-симметричная)" << endl;
		return;
	}

	AL = new int[AUi];
	iTemp = 0;
	for(int i = 0; i < N; i++)
	{
		for(int j = i + 1; j < N; j++)
		{
			if(MAP[{j, i}] != 0)
			{
				AL[iTemp++] = MAP[{j, i}];
			}
		}
	}
	AU = new int[AUi];
	LJ = new int[LJi];
	for(int i = 0; i < LJi; i++) LJ[i] = TLJ[i];
	for(int i = 0; i < AUi; i++) AU[i] = TAU[i];
	F_elems.clear();
	//конец обработки остальных строк

	//сумма элементов, лежащих на i+j - четное
	Sum = 0;

	//добавление эл-ов диагонали
	for(int i = 0; i < N; i++)
	{
		Sum += AD[i];
	}
	//добавление эл-ов выше диагонали и i+j - чётное число
	for(int i = 0; i < N; i++)
	{
		for(int j = 2 + i; j < N; j += 2)
		{
			Sum += addElements(i, j, AU, LI, LJ);
		}
	}
	//добавление эл-ов ниже диагонали и i+j - чётное число
	for(int i = 2; i < N; i++)
	{
		for(int j = i - 2; j >= 0; j -= 2)
		{
			Sum += addElements(j, i, AL, LI, LJ);
		}
	}

	//вывод суммы эл-ов, если i+j - четное
	cout << "Cумма элементов равна " << Sum << endl;
	//main();
}

void MethodThisBegin()
{
	bool first = true;
	MAP.clear();
	N = 0; NZ = 0; //пер-ые отвечающие за размер матрицы и кол-во её ненулевых элементов

	//начало обработки первой строки
	if(first)
		getline(cin, FLine);
	getline(cin, FLine);
	first = false;
	couples = fLine(FLine);
	if(!couples.first)
	{
		MethodCmdError();
	}
	F_elems = couples.second;
	//создание массивов значений
	TAU = new int[(N - 1) * N / 2];
	TLJ = new int[(N - 1) * N / 2];
	AD = new int[N]; LI = new int[N];
	ADi = 0; AUi = 0; ALi = 0; LJi = 0; LIi = 1;
	LI[0] = 1;
	iTemp = 0;
	AD[ADi] = F_elems[ADi];
	for(int i = ADi + 1; i < N; i++)
	{
		if(F_elems[i] != 0)
		{
			TAU[AUi++] = F_elems[i];
			TLJ[LJi++] = i + 1;
			MAP[{i, ADi}] = 1;

		}
	}
	LI[LIi] = AUi - iTemp + LI[LIi - 1];
	LIi++;
	ADi++;
	//конец обработки первой строки

	//обработка остальных строк
	squareMatrix = true;
	for(; ADi < N; ADi++)
	{
		getline(cin, FLine);
		couples = splitString(FLine);
		F_elems = couples.second;

		bool ch = false;
		//установка лог. значения размера матрицы
		if(F_elems.size() != N)
		{
			ch = true;
			squareMatrix = false;
		}

		if(!ch)
		{
			iTemp = AUi;
			AD[ADi] = F_elems[ADi];
			for(int i = ADi + 1; i < N; i++)
			{
				if(F_elems[i] != 0)
				{
					TAU[AUi++] = F_elems[i];
					TLJ[LJi++] = i + 1;
					MAP[{i, ADi}] = 1;
				}
			}

			//Проверка Если aij ≠ 0, то и aji ≠ 0;
			//Если aij = 0, то и aji = 0;
			for(int i = 0; i < ADi; i++)
			{
				if(F_elems[i] == 0 && MAP[{ADi, i}] != 0)
				{
					MethodCmdError();
				}
				if(F_elems[i] != 0 && MAP[{ADi, i}] == 0)
				{
					MethodCmdError();
				}
				MAP[{ADi, i}] = F_elems[i];
			}
		}

		LI[LIi] = AUi - iTemp + LI[LIi - 1];
		LIi++;
	}
	//проверка соответсвия матрицы условию
	if(squareMatrix == false)
	{
		cout << "Неверный формат матрицы (не квадратная /";
		cout << " присутствуют символы / не структурно-симметричная)" << endl;
		MethodThisBegin();
	}

	AL = new int[AUi];
	iTemp = 0;
	for(int i = 0; i < N; i++)
	{
		for(int j = i + 1; j < N; j++)
		{
			if(MAP[{j, i}] != 0)
			{
				AL[iTemp++] = MAP[{j, i}];
			}
		}
	}
	AU = new int[AUi];
	LJ = new int[LJi];

	for(int i = 0; i < LJi; i++)
	{
		LJ[i] = TLJ[i];
	}
	for(int i = 0; i < AUi; i++)
	{
		AU[i] = TAU[i];
	}
	//конец обработки остальных строк

	//сумма элементов, лежащих на i+j - четное
	Sum = 0;

	//добавление эл-ов диагонали
	for(int i = 0; i < N; i++)
	{
		Sum += AD[i];
	}

	//добавление эл-ов, лежащих выше диагонали и i+j - четное
	for(int i = 0; i < N; i++)
	{
		for(int j = 2 + i; j < N; j += 2)
		{
			Sum += addElements(i, j, AU, LI, LJ);
		}
	}

	//добавление элементов, лежащих ниже диагонали и i+j - четное
	for(int i = 2; i < N; i++)
	{
		for(int j = i - 2; j >= 0; j -= 2)
		{
			Sum += addElements(j, i, AL, LI, LJ);
		}
	}

	//вывод суммы эл-ов, где i+j - четное
	cout << "Cумма элементов равна " << Sum << endl;
	//main();
}

void MethodCmdError()
{
	if(sizeof(AD) / sizeof(int) > 1) delete[] AD;
	if(sizeof(AU) / sizeof(int) > 1) delete[] AU;
	if(sizeof(AL) / sizeof(int) > 1) delete[] AL;
	if(sizeof(LJ) / sizeof(int) > 1) delete[] LJ;
	if(sizeof(LI) / sizeof(int) > 1) delete[] LI;
	if(sizeof(TLJ) / sizeof(int) > 1) delete[] TLJ;
	if(sizeof(TAU) / sizeof(int) > 1) delete[] TAU;
	AD = nullptr;
	AU = nullptr;
	AL = nullptr;
	LJ = nullptr;
	LI = nullptr;
	TLJ = nullptr;
	TAU = nullptr;
	F_elems.clear();
	cout << "Неверный формат матрицы (не квадратная /";
	cout << " присутствуют символы / не структурно-симметричная)" << endl;
	MethodThisBegin();
}

void Menu()
{
	int mode = GetModeFromConsole();
	//cin >> command;
	if(mode == 2)
	{
		description();
		//отметка при неверном вводе данных
		MethodThisBegin();
		MethodER();
	}
	else if(mode == 1)
	{
		MethodThisBeginFirst();
		MethodER();
	}
	else if(mode == 3)
	{
		cout << "До свидания!" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Menu();
	return 0;
}