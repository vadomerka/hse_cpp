/*
 *Разработать класс матрица, который удовлетворяет следующим требованиям:
 *1)Для представления элементов матрицы будем использовать наиболее компактное 
 *2)Используем правильное управление ресурсами, памятью:
 *  -Распределение
 *  -Освобождение
 *  -Глубокое копирование
 *3)Добавляем операционную семантику ожидаемую для математического объекта матрица
 (делаем перегрузку оператора) сложение, транспонирование, проверка на равенство, неравенство
 *4)Для представления составных элементов матрицы: столбцы строки создадим легковесные
 *обертки, которые можно будет передавать по значению(аналогия с итераторами и string_view).
 *Не забываем про константность
 *5)Добавляем в матрицу умение быть хорошо воспитанным контейнером:
 *Итераторы, бегины, энды и.т.д
 *6)Научим матрицу быть перемещаемым объектом (НЛО)
 *7)Сделаем матрицу шаблоном, чтобы это была матрица произвольных объектов
 *
 *А)Будем тестировать функционал матрицы обычными асертами
*/

#include <iostream>
#include <cassert>

#include "matrix.h"

void test01() {
    assert(true);
}

void test02() {
    Matrix m;
    assert(true);
}

void test03() {
    Matrix m(3, 4, 42);
    assert(m.GetRowsNum() == 3 && m.GetColsNum() == 4);
    assert(m.GetEl(1, 2) == 42);
}

void PrintMatrixRow(Matrix::ConstRow row) {
    for (size_t i = 0; i < row.size(); ++i) {
        std::cout << row[i] << ' ';
    }
    std::cout << '\n';
}

//передаем row по значению, потому что это похоже на итератор(всегда передаются по значению)
void DoubleRow(Matrix::Row row) {
    for (size_t i = 0; i < row.size(); ++i) {
        row[i] *= 2;
    }
}


void test04() {
    Matrix m(3, 4, 42);

    //Matrix::Row row(1, &m); // это возможно, но недопустимо
    PrintMatrixRow(m[1]); //Распечатывает вторую строку
    DoubleRow(m[1]);
    const Matrix::Row& row1 = m[1];
    //PrintMatrixRow(m[1]);
    PrintMatrixRow(row1);
    //PrintMatrixCol(m(2)); //Распечатывает 2 столбец
}

void PrintKthRow(const Matrix& m, size_t k) {
    PrintMatrixRow(m[k]);
}

void test05() {
    Matrix m(3, 4, 42);
    PrintKthRow(m, 1);
}

int main() {
    test01();
    test02();
    test03();
    test04();
    std::cout << "Allright";
    return 0;
}