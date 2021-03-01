#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Создание новой матрицы
int** newMatrix(int columnsCount, int rowsCount) {
	int** matrix = new int* [columnsCount];
	for (int i = 0; i < columnsCount; i++) {
		matrix[i] = new int[rowsCount];
	}
	return matrix;
}

// Ввод размера матрицы
// matrixNum - порядковый номер матрицы,
void getMatrixSize(int matrixNum, int* columnsCount, int* rowsCount) {

	int N = 0, M = 0;
	while (N <= 0 || M <= 0) {
		std::cout << "Введите размеры " << matrixNum << " первой матрицы" << endl;
		cin >> N >> M;
	}
	*columnsCount = N;
	*rowsCount = M;
}


//Выбор способа заполнения матрицы
// matrixNum - порядковый номер матрицы,
int getChoiceUser() {
	int choice = 0;

	while (choice < 1 || choice > 2) {
		cout << "Выберите способ заполнения матрицы\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> choice;
	}
	return choice;
}


// вывод матрицы
void printMatrix(int matrixNum, int** matrix, int columnsCount, int rowsCount) {
	std::cout << "\nМатрица " << matrixNum << endl;
	for (int i = 0; i < columnsCount; i++) {
		for (int j = 0; j < rowsCount; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << endl;
	}
}


// Заполнение матрицы с учетом выбора способа заполнения 
// matrixNum - порядковый номер матрицы,
// userChoice - выбор пользователя, полученное в результате выполнения функции getChoiceUser

int** fillMatrix(int matrixNum, int userChoice, int** matrix, int columnsCount, int rowsCount) {
	switch (userChoice)
	{
	case 1:
		for (int i = 0; i < columnsCount; i++)
			for (int j = 0; j < rowsCount; j++)
				cin >> matrix[i][j];
		break;
	case 2:
		for (int i = 0; i < columnsCount; i++)
			for (int j = 0; j < rowsCount; j++)
				matrix[i][j] = rand() % 10;
	}

	return matrix;
}

//Приведение матрицы к требуемому размеру
int** reductionMatrix(int length, int** matrix, int columnsCount, int rowsCount) {
	int** redMatrix = new int* [length];
	for (int i = 0; i < length; i++)
	{
		redMatrix[i] = new int[length];
		for (int j = 0; j < length; j++)
			redMatrix[i][j] = 0;
	}

	for (int i = 0; i < columnsCount; i++)
		for (int j = 0; j < rowsCount; j++)
			redMatrix[i][j] = matrix[i][j];
	return redMatrix;

}


//Разбиение матриц на подматрицы и их заполнение
int*** creatAndFillSubMatrix(int length, int** redMatrix) {
	//int** mat1 = new int* [length / 2];
	//for (int i = 0; i < length / 2; i++)
	//{
	//	mat1[i] = new int[length / 2];
	//	for (int j = 0; j < length / 2; j++)
	//		mat1[i][j] = redMatrix[i][j];
	//}
	//int** mat2 = new int* [length / 2];
	//for (int i = 0; i < length / 2; i++)
	//{
	//	mat2[i] = new int[length / 2];
	//	for (int j = 0; j < length / 2; j++)
	//		mat2[i][j] = redMatrix[i][j + length / 2];
	//}
	//int** mat3 = new int* [length / 2];
	//for (int i = 0; i < length / 2; i++)
	//{
	//	mat3[i] = new int[length / 2];
	//	for (int j = 0; j < length / 2; j++)
	//		mat3[i][j] = redMatrix[i + length / 2][j];
	//}
	//int** mat4 = new int* [length / 2];
	//for (int i = 0; i < length / 2; i++)
	//{
	//	mat4[i] = new int[length / 2];
	//	for (int j = 0; j < length / 2; j++)
	//		mat4[i][j] = redMatrix[i + length / 2][j + length / 2];
	//}

	int*** subMatrix = new int** [4];
	for (int i = 0; i < 4; i++)
	{
		subMatrix[i] = new int* [length / 2];
		for (int j = 0; j < length / 2; j++)
			subMatrix[i][j] = new int[length / 2];
	}

	for (int i = 0; i < length / 2; i++)
		for (int j = 0; j < length / 2; j++) {
			subMatrix[0][i][j] = redMatrix[i][j];
			subMatrix[1][i][j] = redMatrix[i][j + length / 2];
			subMatrix[2][i][j] = redMatrix[i + length / 2][j];
			subMatrix[3][i][j] = redMatrix[i + length / 2][j + length / 2];
		}
	return subMatrix;
}

//Создание массива промежуточных матриц
int*** createIntermediateMatrices(int length) {
	int*** p = new int** [7];
	for (int i = 0; i < 7; i++)
	{
		p[i] = new int* [length / 2];
		for (int j = 0; j < length / 2; j++)
			p[i][j] = new int[length / 2];
	}
	return p;
}

//Вычисление значений промежуточных матриц
int*** calculateIntermediateMatrix(int length, int*** p, int*** subMatrixFirst, int*** subMatrixSecond) {
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < length / 2; j++)
			for (int k = 0; k < length / 2; k++)
				p[i][j][k] = 0;

	for (int i = 0; i < length / 2; i++)
		for (int j = 0; j < length / 2; j++)
			for (int z = 0; z < length / 2; z++) {
				p[0][i][j] += (subMatrixFirst[0][i][z] + subMatrixFirst[3][i][z]) * (subMatrixSecond[0][z][j] + subMatrixSecond[3][z][j]);
				p[1][i][j] += (subMatrixFirst[2][i][z] + subMatrixFirst[3][i][z]) * subMatrixSecond[0][z][j];
				p[2][i][j] += subMatrixFirst[0][i][z] * (subMatrixSecond[1][z][j] - subMatrixSecond[3][z][j]);
				p[3][i][j] += subMatrixFirst[3][i][z] * (subMatrixSecond[2][z][j] - subMatrixSecond[0][z][j]);
				p[4][i][j] += (subMatrixFirst[0][i][z] + subMatrixFirst[1][i][z]) * subMatrixSecond[3][z][j];
				p[5][i][j] += (subMatrixFirst[2][i][z] - subMatrixFirst[0][i][z]) * (subMatrixSecond[0][z][j] + subMatrixSecond[1][z][j]);
				p[6][i][j] += (subMatrixFirst[1][i][z] - subMatrixFirst[3][i][z]) * (subMatrixSecond[2][z][j] + subMatrixSecond[3][z][j]);
			}
	return p;
}

//Создание вспомогательных матриц
//Подсчет значений вспомогательных матриц из промежуточных
int*** auxiliaryMatrices(int length, int*** p) {
	int*** auxiliaryMatrix = new int** [4];
	for (int i = 0; i < 4; i++)
	{
		auxiliaryMatrix[i] = new int* [length / 2];
		for (int j = 0; j < length / 2; j++)
			auxiliaryMatrix[i][j] = new int[length / 2];
	}


	for (int i = 0; i < length / 2; i++)
		for (int j = 0; j < length / 2; j++)
		{
			auxiliaryMatrix[0][i][j] = p[0][i][j] + p[3][i][j] - p[4][i][j] + p[6][i][j];
			auxiliaryMatrix[1][i][j] = p[2][i][j] + p[4][i][j];
			auxiliaryMatrix[2][i][j] = p[1][i][j] + p[3][i][j];
			auxiliaryMatrix[3][i][j] = p[0][i][j] - p[1][i][j] + p[2][i][j] + p[5][i][j];
		}
	return auxiliaryMatrix;
}

int** workWithResultingMatrix(int length, int*** auxiliaryMatrix) {
	//Создание результирующей матрицы
	int** resultingMatrix = new int* [length];
	for (int i = 0; i < length; i++)
		resultingMatrix[i] = new int[length];


	//Занесение информации из вспомогательных матриц в результирующую
	for (int i = 0; i < length / 2; i++)
		for (int j = 0; j < length / 2; j++)
		{
			resultingMatrix[i][j] = auxiliaryMatrix[0][i][j];
			resultingMatrix[i][j + length / 2] = auxiliaryMatrix[1][i][j];
			resultingMatrix[i + length / 2][j] = auxiliaryMatrix[2][i][j];
			resultingMatrix[i + length / 2][j + length / 2] = auxiliaryMatrix[3][i][j];
		}


	//Выравнивание границ результирующей матрицы
	int x = 0, f = 100, s = 100;
	for (int i = 0; i < length; i++)
	{
		x = 0;
		for (int j = 0; j < length; j++)
			if (resultingMatrix[i][j] != 0)
			{
				x++;
				f = 100;
			}

		if (x == 0 && i < f)
			f = i;
	}

	for (int i = 0; i < length; i++)
	{
		x = 0;
		for (int j = 0; j < length; j++)
			if (resultingMatrix[j][i] != 0)
			{
				x++;
				s = 100;
			}

		if (x == 0 && i < s)
			s = i;
	}

	int** resultMatrix = new int* [f];
	for (int i = 0; i < f; i++)
	{
		resultMatrix[i] = new int[s];
		for (int j = 0; j < s; j++)
			resultMatrix[i][j] = resultingMatrix[i][j];
	}
	cout << "\nРезультирующая матрица\n\n";
	printMatrix(0, resultMatrix, f, s);

	for (int i = 0; i < length; i++)
	{
		delete[] resultingMatrix[i];
	}
	return resultMatrix;

	for (int i = 0; i < f; i++)
		delete[] resultMatrix[i];
}





int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int columnsCount_firstMatrix, rowsCount_firstMatrix;
	int columnsCount_secondMatrix, rowsCount_secondMatrix;
	int k, length = 2;

	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	getMatrixSize(1, &columnsCount_firstMatrix, &rowsCount_firstMatrix);
	getMatrixSize(2, &columnsCount_secondMatrix, &rowsCount_secondMatrix);
	int** matrixFirst = newMatrix(columnsCount_firstMatrix, rowsCount_firstMatrix);
	int** matrixSecond = newMatrix(columnsCount_secondMatrix, rowsCount_secondMatrix);

	int userChoice = getChoiceUser();
	matrixFirst = fillMatrix(1, userChoice, matrixFirst, columnsCount_firstMatrix, rowsCount_firstMatrix);
	matrixSecond = fillMatrix(2, userChoice, matrixSecond, columnsCount_secondMatrix, rowsCount_secondMatrix);

	printMatrix(1, matrixFirst, columnsCount_firstMatrix, rowsCount_firstMatrix);
	printMatrix(2, matrixSecond, columnsCount_secondMatrix, rowsCount_secondMatrix);

	while (length < columnsCount_firstMatrix || length < columnsCount_secondMatrix
		|| length < rowsCount_firstMatrix || length < rowsCount_secondMatrix)
		length *= 2;
	int** redactionMatrixFirst = reductionMatrix(length, matrixFirst, columnsCount_firstMatrix, rowsCount_firstMatrix);
	int** redactionMatrixSecond = reductionMatrix(length, matrixSecond, columnsCount_secondMatrix, rowsCount_secondMatrix);

	cout << "Приведенные матрицы\n";
	cout << "\nМатрица 1\n\n";
	printMatrix(1, redactionMatrixFirst, length, length);
	cout << "\nМатрица 2\n\n";
	printMatrix(2, redactionMatrixSecond, length, length);

	int*** subMatrixFirst = creatAndFillSubMatrix(length, redactionMatrixFirst);
	int*** subMatrixSecond = creatAndFillSubMatrix(length, redactionMatrixSecond);

	//Создание промежуточных матриц
	int*** p = createIntermediateMatrices(length);
	//Вычисление значений промежуточных матриц 
	int*** intermediateMatrixNew = calculateIntermediateMatrix(length, p, subMatrixFirst, subMatrixSecond);
	//Работа со вспомогательными матрицами
	int*** auxiliaryMatrix = auxiliaryMatrices(length, p);

	int** resultMatrix = workWithResultingMatrix(length, auxiliaryMatrix);

	system("pause");


	//Освобождение памяти
	//for (int i = 0; i < columnsCount_firstMatrix; i++)
	//	delete[] matrixFirst[i];
	//for (int i = 0; i < columnsCount_secondMatrix; i++)
	//	delete[] matrixSecond[i];

	//for (int i = 0; i < length; i++)
	//{
	//	delete[] redactionMatrixFirst[i];
	//	delete[] redactionMatrixSecond[i];
	//	delete[] resultMatrix[i];
	//}

	delete[] matrixFirst, matrixSecond, redactionMatrixFirst, redactionMatrixSecond, resultMatrix;
	delete[] p, subMatrixFirst, subMatrixSecond;
	return 0;
}

