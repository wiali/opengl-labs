#ifndef __CMATRIX_H
#define __CMATRIX_H
#include <string.h>
#include "CVector.h"


class CMatrix4x4
{
public:
	CMatrix4x4();                                // Конструктор.
	CMatrix4x4(const CMatrix4x4 &m);             // Перегруженный конструктор.
	CMatrix4x4(float r11, float r12, float r13, float r14,
		float r21, float r22, float r23, float r24,
		float r31, float r32, float r33, float r34,
		float r41, float r42, float r43, float r44);
	~CMatrix4x4();                               // Деструктор.

	void Clear();                                // Сброс матрицы.
	void Zero();                                 // Сброс матрицы, все значения = 0.

	void operator=(CMatrix4x4 m);                // Перегруженный оператор = 
	CMatrix4x4 operator-(CMatrix4x4 m);          // Перегруженный оператор - 
	CMatrix4x4 operator+(CMatrix4x4 m);          // Перегруженный оператор + 
	CMatrix4x4 operator*(CMatrix4x4 m);          // Перегруженный оператор * 
	CMatrix4x4 operator/(CMatrix4x4 m);          // Перегруженный оператор / 

	void operator +=(CMatrix4x4 m);              // Перегруженный оператор +=
	void operator -=(CMatrix4x4 m);              // Перегруженный оператор -=
	void operator *=(CMatrix4x4 m);              // Перегруженный оператор *=
	void operator /=(CMatrix4x4 m);              // Перегруженный оператор /=

	CMatrix4x4 operator-(float f);               // Перегруженный оператор - 
	CMatrix4x4 operator+(float f);               // Перегруженный оператор + 
	CMatrix4x4 operator*(float f);               // Перегруженный оператор * 
	CMatrix4x4 operator/(float f);               // Перегруженный оператор / 

	CVector4 operator*(CVector4 v);             // CVector4 * matrix (умножение вектора на матрицу)

	void operator -=(float f);                   // Перегруженный оператор -=
	void operator +=(float f);                   // Перегруженный оператор +=
	void operator *=(float f);                   // Перегруженный оператор *=
	void operator /=(float f);                   // Перегруженный оператор /=

	bool operator ==(CMatrix4x4 v);              // Перегруженный оператор ==
	bool operator !=(CMatrix4x4 v);              // Перегруженный оператор !=

	void Translate(CVector4 Translate);          // Трансляция точки в 3D.
	void Translate(float x, float y, float z);   // Трансляция точки в 3D.
	void Rotate(double angle, int x, int y,
		int z);                          // Вращение 3D точки.
	bool inverseMatrix(CMatrix4x4 m);            // Инверсия текущих данных матрицы.
	bool invertMatrix(CMatrix4x4 m);             // инвертирование матрицы.
	CVector4 VectorMatrixMultiply(CVector4 v);
	CVector4 VectorMatrixMultiply3x3(CVector4 v);
	CVector4 transformPoint(CVector4 v);         // трансформация точки против матрицы.
	bool CreateShadowMatrix(CVector4 planeNormal,
		CVector4 lightPos);  // Создание матрицы теней.

	float matrix[16];                            // 4x4 матрица в одномерном массиве.
};

#endif