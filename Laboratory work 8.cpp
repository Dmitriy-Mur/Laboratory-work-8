#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct student {
	string surname;			// Фамилия
	string name;			// Имя
	string patronymic;      // Отчество
	string date_of_birth;   // Дата рождения
	string adress;          // Адрес
	float rating;			// Рейтинг
	void enter_info(string s, string n, string p, string d, string a, float r) {
		surname = s;        // Функция заполняет поля 
		name = n;			// для одного объекта (студента)
		patronymic = p;
		date_of_birth = d;
		adress = a;
		rating = r;
	}
};

int main() {
	setlocale(LC_ALL, "RU");
	system("chcp 1275");
	system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int kol_st;                   	// Переменная для количества студентов
	student mass[50];             	// Массив для 50 студентов
	cout << "Введите количество студентов: ";
	cin >> kol_st;
	for (int i = 0; i < kol_st; i++) {
		string s, n, p, d, a;
		float r;					// В цикле вводим данные о студентах
		cout << "Введите ФИО, дату рождения, адрес, рейтинг студента № " << i + 1 << endl;
		cin >> s >> n >> p >> d >> a >> r;
		mass[i].enter_info(s, n, p, d, a, r);
	}
	int zmass[50]; 					// Массив, хранящий индексы элементов, которые нужно удалить 
	int k = 0;						//Количество людей с одной датой рождения - длина запр. массива
	for (int i = 0; i < kol_st - 1; i++) {
		for (int j = i + 1; j < kol_st; j++) {
			if (mass[i].date_of_birth == mass[j].date_of_birth) {
				zmass[k] = i;       // Цикл сравнивает даты рождения студентов и добавляет
				zmass[k + 1] = j;   // В массив zmass, который хранит индексы студентов с одной
				k += 2;	            // Датой рождения (все студенты в массиве mass)
			}
		}
	}
	bool f = false;
	int zfam;						// Хранит индекс элемента с указанной фамилией, 
	string fam;     				// перед которым нужно вставить ещё один элемент
	cout << "Введите фамилию человека, перед которым надо поставить другого: ";
	cin >> fam;
	for (int i = 0; i < kol_st; i++) {
		if (mass[i].surname == fam) {
			zfam = i;  // В цикле перебираются все элементы для поиска указанной
			f = true;  // фамилии, если такая есть, флаг переворачивается
		}
	}
	if (f == true) {			                       // Если f == true, нужно добавить дополнительный элемент
		for (int i = kol_st; i > zfam; i--) {
			mass[i] = mass[i - 1];                     // В массиве элементы сдвигаются вправо, остаётся место
		}			                                   // перед элементом с нужной фамилией, его занимает 
		string s1, n1, p1, d1, a1; 	                   // новый элемент, вводимый с клавиатуры
		float r1;
		cout << "Введите ФИО, дату рождения, адрес, рейтинг нового студента " << endl;
		cin >> s1 >> n1 >> p1 >> d1 >> a1 >> r1;
		mass[zfam].enter_info(s1, n1, p1, d1, a1, r1);
		kol_st += 1;	                                // Добавился новый студент
		for (int i = 0; i < k; i++) { 			        // k - количество людей с одной датой рождения.
			if (zmass[i] >= zfam) {    		            // К индексам элементов для удаления, которые сдвинулись
				zmass[i] += 1;							// на 1 вправо после добавки нового элемента,
			}											// прибавляется 1 для сохранения текущих индексов
		}
	}
	// Для каждого элемента проверяется, можно ли его вводить в файл	
	ofstream f1("f1.txt");        			// Включение файла для записи		   
	for (int i = 0; i < kol_st; i++) {
		bool fl = true;						// Флаг, нужно ли удалять элемент
		for (int j = 0; j < k; j++) {
			if (i == zmass[j]) {  		    // Если индекс элемента находится в zmass, флаг 
				fl = false;					// переворачивается, чтобы не пропустить элемент в файл 
			}
		}
		if (fl) {
			f1 << mass[i].surname << " " << mass[i].name << " " << mass[i].patronymic <<
				" " << mass[i].adress << " " << mass[i].date_of_birth << " " << mass[i].rating << endl;
		}
	}  					   // Если флаг не перевернулся, элемент записывается в файл
	f1.close();
	return 0;
}

/*
Карпов Родион Лукьевич 05.12.2000 Пушкина4 48
Петухов Арсений Тихонович 22.01.2003 Колотушкина12 8
Киселёв Владлен Демьянович 05.12.2000 Гардеева8 51
Шаров Панкрат Фролович 15.10.2002 Орловска6 21

Шашкова Елена Рудольфовна 13.03.2003 Центральная7 89
*/