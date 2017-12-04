#ifndef __CVECTOR_H
#define __CVECTOR_H

#include<math.h>

// Введём новый класс для удобства хранения текстурных координат обьекта:
class CTexCoord
{
public:
	CTexCoord()
	{
		tu = 0.0f; tv = 0.0f;
	}

	CTexCoord(float u, float v)
	{
		tu = u; tv = v;
	}

	float tu, tv;                      // Массив текстурных координат
};


class CVector4
{
public:
	CVector4();                                        // Конструктор
	CVector4(float X, float Y, float Z);               // Перегруженный конструктор
	CVector4(float X, float Y, float Z, float W);      // Опять перегруженный конструктор
	CVector4(const CVector4 &v);                       // И ещё один.

	void operator=(CVector4 v);                        // Перегруженный оператор =
	CVector4 operator-(CVector4 v);                    // Перегруженный оператор - 
	CVector4 operator+(CVector4 v);                    // Перегруженный оператор + 
	CVector4 operator*(CVector4 v);                    // Перегруженный оператор * 
	CVector4 operator/(CVector4 v);                    // Перегруженный оператор / 
	CVector4 operator+(float f);                       // Перегруженный оператор + 
	CVector4 operator-(float f);                       // Перегруженный оператор - 
	CVector4 operator*(float f);                       // Перегруженный оператор * 
	CVector4 operator/(float f);                       // Перегруженный оператор / 

	void operator +=(CVector4 v);                      // Перегруженный оператор +=
	void operator -=(CVector4 v);                      // Перегруженный оператор -=
	void operator *=(CVector4 v);                      // Перегруженный оператор *=
	void operator /=(CVector4 v);                      // Перегруженный оператор /=
	void operator +=(float f);                         // Перегруженный оператор +=
	void operator -=(float f);                         // Перегруженный оператор -=
	void operator *=(float f);                         // Перегруженный оператор *=
	void operator /=(float f);                         // Перегруженный оператор /=

	bool operator ==(CVector4 v);                      // Перегруженный оператор ==
	bool operator !=(CVector4 v);                      // Перегруженный оператор !=

	void CrossProduct(CVector4 v1, CVector4 v2);       // Возвращает Cross Product векторов v1 и v2.
	void CrossProduct3(CVector4 v1, CVector4 v2,
		CVector4 v3);                   // Возвращает Cross Product векторов v1, v2, v3.
	float DotProduct3(CVector4 v1);                    // Скалярное произведение 3 от v1
	float DotProduct4(CVector4 v1);                    // Скалярное произведение 4 от v1
	float GetLength();                                 // Возвращает длинно данного обьекта
	void Normal();                                     // Нормализует вектор
	void Normalize(CVector4 Triangle[]);               // Находит нормаль треугольника
	void CalculateTangentVector(CVector4 Point1,
		CVector4 Point2,
		CVector4 Point3,
		CVector4 NormalOfA,
		CTexCoord P1Tex,
		CTexCoord P2Tex,
		CTexCoord P3Tex);      // Вычисляет tagent вектор и сохраняет его
	void ExtendVertexPos(CVector4 lightPos,            // Находит точку, основываясь на позиции источника
		float Extend);                // света и текущей точки, сохраняет здесь.
	void ExtendVertexPos(CVector4 currentVertex,       // 
		CVector4 lightPos,            // 
		float Extend);
	CVector4 GetRotatedX(double angle);                // Вращение вокруг x.
	CVector4 GetRotatedY(double angle);                // Вращение вокруг y.
	CVector4 GetRotatedZ(double angle);                // Вращение вокруг z.
	CVector4 GetRotatedAxis(double angle, CVector4 axis);  // Вращение вокруг произвольной оси.
	void CalculateBinormalVector(CVector4 tangent,
		CVector4 normal);     // Вычисляет бинормаль.
	void ClampTo01();                                  // "закрепляет" этот вектор между 0 и 1.


	float x, y, z, w;                                  // Вершинные x, y, и z координаты.
};

#endif
