#ifndef __CMATRIX_H
#define __CMATRIX_H
#include <string.h>
#include "CVector.h"


class CMatrix4x4
{
public:
	CMatrix4x4();                                // �����������.
	CMatrix4x4(const CMatrix4x4 &m);             // ������������� �����������.
	CMatrix4x4(float r11, float r12, float r13, float r14,
		float r21, float r22, float r23, float r24,
		float r31, float r32, float r33, float r34,
		float r41, float r42, float r43, float r44);
	~CMatrix4x4();                               // ����������.

	void Clear();                                // ����� �������.
	void Zero();                                 // ����� �������, ��� �������� = 0.

	void operator=(CMatrix4x4 m);                // ������������� �������� = 
	CMatrix4x4 operator-(CMatrix4x4 m);          // ������������� �������� - 
	CMatrix4x4 operator+(CMatrix4x4 m);          // ������������� �������� + 
	CMatrix4x4 operator*(CMatrix4x4 m);          // ������������� �������� * 
	CMatrix4x4 operator/(CMatrix4x4 m);          // ������������� �������� / 

	void operator +=(CMatrix4x4 m);              // ������������� �������� +=
	void operator -=(CMatrix4x4 m);              // ������������� �������� -=
	void operator *=(CMatrix4x4 m);              // ������������� �������� *=
	void operator /=(CMatrix4x4 m);              // ������������� �������� /=

	CMatrix4x4 operator-(float f);               // ������������� �������� - 
	CMatrix4x4 operator+(float f);               // ������������� �������� + 
	CMatrix4x4 operator*(float f);               // ������������� �������� * 
	CMatrix4x4 operator/(float f);               // ������������� �������� / 

	CVector4 operator*(CVector4 v);             // CVector4 * matrix (��������� ������� �� �������)

	void operator -=(float f);                   // ������������� �������� -=
	void operator +=(float f);                   // ������������� �������� +=
	void operator *=(float f);                   // ������������� �������� *=
	void operator /=(float f);                   // ������������� �������� /=

	bool operator ==(CMatrix4x4 v);              // ������������� �������� ==
	bool operator !=(CMatrix4x4 v);              // ������������� �������� !=

	void Translate(CVector4 Translate);          // ���������� ����� � 3D.
	void Translate(float x, float y, float z);   // ���������� ����� � 3D.
	void Rotate(double angle, int x, int y,
		int z);                          // �������� 3D �����.
	bool inverseMatrix(CMatrix4x4 m);            // �������� ������� ������ �������.
	bool invertMatrix(CMatrix4x4 m);             // �������������� �������.
	CVector4 VectorMatrixMultiply(CVector4 v);
	CVector4 VectorMatrixMultiply3x3(CVector4 v);
	CVector4 transformPoint(CVector4 v);         // ������������� ����� ������ �������.
	bool CreateShadowMatrix(CVector4 planeNormal,
		CVector4 lightPos);  // �������� ������� �����.

	float matrix[16];                            // 4x4 ������� � ���������� �������.
};

#endif