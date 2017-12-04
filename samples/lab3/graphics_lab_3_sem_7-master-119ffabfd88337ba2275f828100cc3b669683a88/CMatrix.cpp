#include"CMatrix.h"


CMatrix4x4::CMatrix4x4()
{
	// Инициализируем все переменные
	Clear();
}


CMatrix4x4::CMatrix4x4(const CMatrix4x4 &m)
{
	matrix[0] = m.matrix[0];
	matrix[4] = m.matrix[4];
	matrix[8] = m.matrix[8];
	matrix[12] = m.matrix[12];

	matrix[1] = m.matrix[1];
	matrix[5] = m.matrix[5];
	matrix[9] = m.matrix[9];
	matrix[13] = m.matrix[13];

	matrix[2] = m.matrix[2];
	matrix[6] = m.matrix[6];
	matrix[10] = m.matrix[10];
	matrix[14] = m.matrix[14];

	matrix[3] = m.matrix[3];
	matrix[7] = m.matrix[7];
	matrix[11] = m.matrix[11];
	matrix[15] = m.matrix[15];
}


CMatrix4x4::CMatrix4x4(float r11, float r12, float r13, float r14,
	float r21, float r22, float r23, float r24,
	float r31, float r32, float r33, float r34,
	float r41, float r42, float r43, float r44)
{
	// Чтобы тождественность матрицы, устанавливайте её значения примерно так...
	matrix[0] = r11; matrix[1] = r12; matrix[2] = r13; matrix[3] = r14;
	matrix[4] = r21; matrix[5] = r22; matrix[6] = r23; matrix[7] = r24;
	matrix[8] = r31; matrix[9] = r32; matrix[10] = r33; matrix[11] = r34;
	matrix[12] = r41; matrix[13] = r42; matrix[14] = r43; matrix[15] = r44;
}


CMatrix4x4::~CMatrix4x4()
{

}


void CMatrix4x4::operator =(CMatrix4x4 m)
{
	// Устанавливает все значения матрицы в значения "m"
	matrix[0] = m.matrix[0]; matrix[1] = m.matrix[1]; matrix[2] = m.matrix[2];
	matrix[3] = m.matrix[3];
	matrix[4] = m.matrix[4]; matrix[5] = m.matrix[5]; matrix[6] = m.matrix[6];
	matrix[7] = m.matrix[7];
	matrix[8] = m.matrix[8]; matrix[9] = m.matrix[9]; matrix[10] = m.matrix[10];
	matrix[11] = m.matrix[11];
	matrix[12] = m.matrix[12]; matrix[13] = m.matrix[13]; matrix[14] = m.matrix[14];
	matrix[15] = m.matrix[15];
}


CMatrix4x4 CMatrix4x4::operator -(CMatrix4x4 m)
{
	// Возвращает значение матрица - m
	return CMatrix4x4(matrix[0] - m.matrix[0], matrix[1] - m.matrix[1], matrix[2] - m.matrix[2],
		matrix[3] - m.matrix[3], matrix[4] - m.matrix[4], matrix[5] - m.matrix[5],
		matrix[6] - m.matrix[6], matrix[7] - m.matrix[7], matrix[8] - m.matrix[8],
		matrix[9] - m.matrix[9], matrix[10] - m.matrix[10], matrix[11] - m.matrix[11],
		matrix[12] - m.matrix[12], matrix[13] - m.matrix[13],
		matrix[14] - m.matrix[14], matrix[15] - m.matrix[15]);
}


CMatrix4x4 CMatrix4x4::operator +(CMatrix4x4 m)
{
	// Возвращает значение матрица + m.
	return CMatrix4x4(matrix[0] + m.matrix[0], matrix[1] + m.matrix[1], matrix[2] + m.matrix[2],
		matrix[3] + m.matrix[3], matrix[4] + m.matrix[4], matrix[5] + m.matrix[5],
		matrix[6] + m.matrix[6], matrix[7] + m.matrix[7], matrix[8] + m.matrix[8],
		matrix[9] + m.matrix[9], matrix[10] + m.matrix[10], matrix[11] + m.matrix[11],
		matrix[12] + m.matrix[12], matrix[13] + m.matrix[13],
		matrix[14] + m.matrix[14], matrix[15] + m.matrix[15]);
}


CMatrix4x4 CMatrix4x4::operator *(CMatrix4x4 m)
{
	// Возвращает значение матрица * m.
	return CMatrix4x4(matrix[0] * m.matrix[0] + matrix[4] * m.matrix[1] + matrix[8] *
		m.matrix[2] + matrix[12] * m.matrix[3],
		matrix[1] * m.matrix[0] + matrix[5] * m.matrix[1] + matrix[9] *
		m.matrix[2] + matrix[13] * m.matrix[3],
		matrix[2] * m.matrix[0] + matrix[6] * m.matrix[1] + matrix[10] *
		m.matrix[2] + matrix[14] * m.matrix[3],
		matrix[3] * m.matrix[0] + matrix[7] * m.matrix[1] + matrix[11] *
		m.matrix[2] + matrix[15] * m.matrix[3],
		matrix[0] * m.matrix[4] + matrix[4] * m.matrix[5] + matrix[8] *
		m.matrix[6] + matrix[12] * m.matrix[7],
		matrix[1] * m.matrix[4] + matrix[5] * m.matrix[5] + matrix[9] *
		m.matrix[6] + matrix[13] * m.matrix[7],
		matrix[2] * m.matrix[4] + matrix[6] * m.matrix[5] + matrix[10] *
		m.matrix[6] + matrix[14] * m.matrix[7],
		matrix[3] * m.matrix[4] + matrix[7] * m.matrix[5] + matrix[11] *
		m.matrix[6] + matrix[15] * m.matrix[7],
		matrix[0] * m.matrix[8] + matrix[4] * m.matrix[9] + matrix[8] *
		m.matrix[10] + matrix[12] * m.matrix[11],
		matrix[1] * m.matrix[8] + matrix[5] * m.matrix[9] + matrix[9] *
		m.matrix[10] + matrix[13] * m.matrix[11],
		matrix[2] * m.matrix[8] + matrix[6] * m.matrix[9] + matrix[10] *
		m.matrix[10] + matrix[14] * m.matrix[11],
		matrix[3] * m.matrix[8] + matrix[7] * m.matrix[9] + matrix[11] *
		m.matrix[10] + matrix[15] * m.matrix[11],
		matrix[0] * m.matrix[12] + matrix[4] * m.matrix[13] + matrix[8] *
		m.matrix[14] + matrix[12] * m.matrix[15],
		matrix[1] * m.matrix[12] + matrix[5] * m.matrix[13] + matrix[9] *
		m.matrix[14] + matrix[13] * m.matrix[15],
		matrix[2] * m.matrix[12] + matrix[6] * m.matrix[13] + matrix[10] *
		m.matrix[14] + matrix[14] * m.matrix[15],
		matrix[3] * m.matrix[12] + matrix[7] * m.matrix[13] + matrix[11] *
		m.matrix[14] + matrix[15] * m.matrix[15]);
}


CMatrix4x4 CMatrix4x4::operator /(CMatrix4x4 m)
{
	return CMatrix4x4(matrix[0] / m.matrix[0] + matrix[4] / m.matrix[1] + matrix[8] /
		m.matrix[2] + matrix[12] / m.matrix[3],
		matrix[1] / m.matrix[0] + matrix[5] / m.matrix[1] + matrix[9] /
		m.matrix[2] + matrix[13] / m.matrix[3],
		matrix[2] / m.matrix[0] + matrix[6] / m.matrix[1] + matrix[10] /
		m.matrix[2] + matrix[14] / m.matrix[3],
		matrix[3] / m.matrix[0] + matrix[7] / m.matrix[1] + matrix[11] /
		m.matrix[2] + matrix[15] / m.matrix[3],
		matrix[0] / m.matrix[4] + matrix[4] / m.matrix[5] + matrix[8] /
		m.matrix[6] + matrix[12] / m.matrix[7],
		matrix[1] / m.matrix[4] + matrix[5] / m.matrix[5] + matrix[9] /
		m.matrix[6] + matrix[13] / m.matrix[7],
		matrix[2] / m.matrix[4] + matrix[6] / m.matrix[5] + matrix[10] /
		m.matrix[6] + matrix[14] / m.matrix[7],
		matrix[3] / m.matrix[4] + matrix[7] / m.matrix[5] + matrix[11] /
		m.matrix[6] + matrix[15] / m.matrix[7],
		matrix[0] / m.matrix[8] + matrix[4] / m.matrix[9] + matrix[8] /
		m.matrix[10] + matrix[12] / m.matrix[11],
		matrix[1] / m.matrix[8] + matrix[5] / m.matrix[9] + matrix[9] /
		m.matrix[10] + matrix[13] / m.matrix[11],
		matrix[2] / m.matrix[8] + matrix[6] / m.matrix[9] + matrix[10] /
		m.matrix[10] + matrix[14] / m.matrix[11],
		matrix[3] / m.matrix[8] + matrix[7] / m.matrix[9] + matrix[11] /
		m.matrix[10] + matrix[15] / m.matrix[11],
		matrix[0] / m.matrix[12] + matrix[4] / m.matrix[13] + matrix[8] /
		m.matrix[14] + matrix[12] / m.matrix[15],
		matrix[1] / m.matrix[12] + matrix[5] / m.matrix[13] + matrix[9] /
		m.matrix[14] + matrix[13] / m.matrix[15],
		matrix[2] / m.matrix[12] + matrix[6] / m.matrix[13] + matrix[10] /
		m.matrix[14] + matrix[14] / m.matrix[15],
		matrix[3] / m.matrix[12] + matrix[7] / m.matrix[13] + matrix[11] /
		m.matrix[14] + matrix[15] / m.matrix[15]);
}


CMatrix4x4 CMatrix4x4::operator -(float f)
{
	return CMatrix4x4(matrix[0] - f, matrix[1] - f, matrix[2] - f, matrix[3] - f,
		matrix[4] - f, matrix[5] - f, matrix[6] - f, matrix[7] - f,
		matrix[8] - f, matrix[9] - f, matrix[10] - f, matrix[11] - f,
		matrix[12] - f, matrix[13] - f, matrix[14] - f, matrix[15] - f);
}


CMatrix4x4 CMatrix4x4::operator +(float f)
{
	return CMatrix4x4(matrix[0] + f, matrix[1] + f, matrix[2] + f, matrix[3] + f,
		matrix[4] + f, matrix[5] + f, matrix[6] + f, matrix[7] + f,
		matrix[8] + f, matrix[9] + f, matrix[10] + f, matrix[11] + f,
		matrix[12] + f, matrix[13] + f, matrix[14] + f, matrix[15] + f);
}


CMatrix4x4 CMatrix4x4::operator *(float f)
{
	return CMatrix4x4(matrix[0] * f, matrix[1] * f, matrix[2] * f, matrix[3] * f,
		matrix[4] * f, matrix[5] * f, matrix[6] * f, matrix[7] * f,
		matrix[8] * f, matrix[9] * f, matrix[10] * f, matrix[11] * f,
		matrix[12] * f, matrix[13] * f, matrix[14] * f, matrix[15] * f);
}


CMatrix4x4 CMatrix4x4::operator /(float f)
{
	// Возвращает значение этого вектора / f. Делаем это умножением на (1/f)
	if (f == 0) f = 1;
	f = 1 / f;

	return CMatrix4x4(matrix[0] * f, matrix[1] * f, matrix[2] * f, matrix[3] * f,
		matrix[4] * f, matrix[5] * f, matrix[6] * f, matrix[7] * f,
		matrix[8] * f, matrix[9] * f, matrix[10] * f, matrix[11] * f,
		matrix[12] * f, matrix[13] * f, matrix[14] * f, matrix[15] * f);
}


bool CMatrix4x4::operator ==(CMatrix4x4 m)
{
	// Возвращает true если все значения эквивалентны
	for (int i = 0; i < 16; i++)
	{
		if (matrix[i] != m.matrix[i])
			return false;
	}

	return true;
}


void CMatrix4x4::operator +=(CMatrix4x4 m)
{
	(*this) = (*this) + m;
}


void CMatrix4x4::operator -=(CMatrix4x4 m)
{
	(*this) = (*this) - m;
}


void CMatrix4x4::operator *=(CMatrix4x4 m)
{
	(*this) = (*this) * m;
}


void CMatrix4x4::operator /=(CMatrix4x4 m)
{
	(*this) = (*this) / m;
}


bool CMatrix4x4::operator !=(CMatrix4x4 m)
{
	return !((*this) == m);
}


void CMatrix4x4::operator -=(float f)
{
	(*this) = (*this) - f;
}


void CMatrix4x4::operator +=(float f)
{
	(*this) = (*this) + f;
}


void CMatrix4x4::operator *=(float f)
{
	(*this) = (*this) * f;
}


void CMatrix4x4::operator /=(float f)
{
	// Делит этот обьект на f и сохраняет результат
	(*this) = (*this) / f;
}


void CMatrix4x4::Clear()
{
	matrix[0] = 1.0f; matrix[1] = 0.0f; matrix[2] = 0.0f; matrix[3] = 0.0f;
	matrix[4] = 0.0f; matrix[5] = 1.0f; matrix[6] = 0.0f; matrix[7] = 0.0f;
	matrix[8] = 0.0f; matrix[9] = 0.0f; matrix[10] = 1.0f; matrix[11] = 0.0f;
	matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = 1.0f;

	// Если вы помните матрицы из школьного/институтского курса, вы заметите, что
	// здесь диагональ: matrix[0], [5], [10], и [15]. Таким образом и сбрасывается матрица.
}


void CMatrix4x4::Zero()
{
	// Чтобы установить значения матрицы в нули, делайте примерно так...
	matrix[0] = 0.0f; matrix[1] = 0.0f; matrix[2] = 0.0f; matrix[3] = 0.0f;
	matrix[4] = 0.0f; matrix[5] = 0.0f; matrix[6] = 0.0f; matrix[7] = 0.0f;
	matrix[8] = 0.0f; matrix[9] = 0.0f; matrix[10] = 0.0f; matrix[11] = 0.0f;
	matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = 0.0f;
}


void CMatrix4x4::Translate(CVector4 Translate)
{
	Clear();

	// Чтобы транслировать матрицу 4x4, нужно переместить значения нижних рядов. 
	matrix[12] = Translate.x;
	matrix[13] = Translate.y;
	matrix[14] = Translate.z;
	matrix[15] = 1.0f;
}


void CMatrix4x4::Translate(float x, float y, float z)
{
	Clear();

	matrix[12] = x;
	matrix[13] = y;
	matrix[14] = z;
	matrix[15] = 1.0f;
}


void CMatrix4x4::Rotate(double angle, int x, int y, int z)
{
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	if (x)
	{
		matrix[5] = cosine;
		matrix[6] = sine;
		matrix[9] = -sine;
		matrix[10] = cosine;
	}

	if (y)
	{
		matrix[0] = cosine;
		matrix[2] = -sine;
		matrix[8] = sine;
		matrix[10] = cosine;
	}

	if (z)
	{
		matrix[0] = cosine;
		matrix[1] = sine;
		matrix[4] = -sine;
		matrix[5] = cosine;
	}
}


bool CMatrix4x4::inverseMatrix(CMatrix4x4 m)
{
	float tempMatrix[16] = { 0 };
	float d12, d13, d23, d24, d34, d41;

	d12 = m.matrix[2] * m.matrix[7] - m.matrix[3] * m.matrix[6];
	d13 = m.matrix[2] * m.matrix[11] - m.matrix[3] * m.matrix[10];
	d23 = m.matrix[6] * m.matrix[11] - m.matrix[7] * m.matrix[10];
	d24 = m.matrix[6] * m.matrix[15] - m.matrix[7] * m.matrix[14];
	d34 = m.matrix[10] * m.matrix[15] - m.matrix[11] * m.matrix[14];
	d41 = m.matrix[14] * m.matrix[3] - m.matrix[15] * m.matrix[2];

	tempMatrix[0] = m.matrix[5] * d34 - m.matrix[9] * d24 + m.matrix[13] * d23;
	tempMatrix[1] = -(m.matrix[1] * d34 + m.matrix[9] * d41 + m.matrix[13] * d13);
	tempMatrix[2] = m.matrix[1] * d24 + m.matrix[5] * d41 + m.matrix[13] * d12;
	tempMatrix[3] = -(m.matrix[1] * d23 - m.matrix[5] * d13 + m.matrix[9] * d12);

	// Вычисляем детерминант
	float determinant = m.matrix[0] * tempMatrix[0] + m.matrix[4] * tempMatrix[1] +
		m.matrix[8] * tempMatrix[2] + m.matrix[12] * tempMatrix[3];

	// Очищаем, если детерминант равен нулю.
	if (determinant == 0.0)
	{
		Clear();
		return false;
	}

	float invDeterminant = 1.0f / determinant;

	// Вычисляем инверсию
	tempMatrix[0] *= invDeterminant;
	tempMatrix[1] *= invDeterminant;
	tempMatrix[2] *= invDeterminant;
	tempMatrix[3] *= invDeterminant;

	tempMatrix[4] = -(m.matrix[4] * d34 - m.matrix[8] * d24 + m.matrix[12] * d23) * invDeterminant;
	tempMatrix[5] = m.matrix[0] * d34 + m.matrix[8] * d41 + m.matrix[12] * d13  * invDeterminant;
	tempMatrix[6] = -(m.matrix[0] * d24 + m.matrix[4] * d41 + m.matrix[12] * d12) * invDeterminant;
	tempMatrix[7] = m.matrix[0] * d23 - m.matrix[4] * d13 + m.matrix[8] * d12  * invDeterminant;

	// Пред-вычисляем 2х2 детерминанты для первых двух рядов
	d12 = m.matrix[0] * m.matrix[5] - m.matrix[1] * m.matrix[12];
	d13 = m.matrix[0] * m.matrix[9] - m.matrix[1] * m.matrix[8];
	d23 = m.matrix[4] * m.matrix[9] - m.matrix[5] * m.matrix[8];
	d24 = m.matrix[4] * m.matrix[13] - m.matrix[5] * m.matrix[12];
	d34 = m.matrix[8] * m.matrix[13] - m.matrix[9] * m.matrix[12];
	d41 = m.matrix[12] * m.matrix[1] - m.matrix[13] * m.matrix[0];

	tempMatrix[8] = m.matrix[7] * d34 - m.matrix[11] * d24 + m.matrix[15] * d23 * invDeterminant;
	tempMatrix[9] = -(m.matrix[3] * d34 + m.matrix[11] * d41 + m.matrix[15] * d13) * invDeterminant;
	tempMatrix[10] = m.matrix[3] * d24 + m.matrix[7] * d41 + m.matrix[15] * d12 * invDeterminant;
	tempMatrix[11] = -(m.matrix[3] * d23 - m.matrix[7] * d13 + m.matrix[11] * d12) * invDeterminant;
	tempMatrix[12] = -(m.matrix[6] * d34 - m.matrix[10] * d24 + m.matrix[14] * d23) * invDeterminant;
	tempMatrix[13] = m.matrix[2] * d34 + m.matrix[10] * d41 + m.matrix[14] * d13 * invDeterminant;
	tempMatrix[14] = -(m.matrix[2] * d24 + m.matrix[6] * d41 + m.matrix[14] * d12) * invDeterminant;
	tempMatrix[15] = m.matrix[2] * d23 - m.matrix[6] * d13 + m.matrix[10] * d12 * invDeterminant;

	// Сохраняем временную матрицу в нашу матрицу
	matrix[0] = tempMatrix[0];  matrix[1] = tempMatrix[1];
	matrix[2] = tempMatrix[2];  matrix[3] = tempMatrix[3];
	matrix[4] = tempMatrix[4];  matrix[5] = tempMatrix[5];
	matrix[6] = tempMatrix[6];  matrix[7] = tempMatrix[7];
	matrix[8] = tempMatrix[8];  matrix[9] = tempMatrix[9];
	matrix[10] = tempMatrix[10]; matrix[11] = tempMatrix[11];
	matrix[12] = tempMatrix[12]; matrix[13] = tempMatrix[13];
	matrix[14] = tempMatrix[14]; matrix[15] = tempMatrix[15];

	return true;
}


bool CMatrix4x4::invertMatrix(CMatrix4x4 m)
{
	matrix[0] = m.matrix[0];  matrix[1] = m.matrix[4];  matrix[2] = m.matrix[8];
	matrix[4] = m.matrix[1];  matrix[5] = m.matrix[5];  matrix[6] = m.matrix[9];
	matrix[8] = m.matrix[2];  matrix[9] = m.matrix[6];  matrix[10] = m.matrix[10];

	// Очищаем
	matrix[3] = 0.0f; matrix[7] = 0.0f; matrix[11] = 0.0f; matrix[15] = 1.0f;

	// Трансляция - это разница между скалярным произведением вращения и вращением
	matrix[12] = -(m.matrix[12] * m.matrix[0]) - (m.matrix[13] * m.matrix[1]) - (m.matrix[14] * m.matrix[2]);
	matrix[13] = -(m.matrix[12] * m.matrix[4]) - (m.matrix[13] * m.matrix[5]) - (m.matrix[14] * m.matrix[6]);
	matrix[14] = -(m.matrix[12] * m.matrix[8]) - (m.matrix[13] * m.matrix[9]) - (m.matrix[14] * m.matrix[10]);
	return true;
}


CVector4 CMatrix4x4::VectorMatrixMultiply(CVector4 v)
{
	CVector4 out;

	out.x = (v.x * matrix[0]) + (v.y * matrix[4]) + (v.z * matrix[8]) + matrix[12];
	out.y = (v.x * matrix[1]) + (v.y * matrix[5]) + (v.z * matrix[9]) + matrix[13];
	out.z = (v.x * matrix[2]) + (v.y * matrix[6]) + (v.z * matrix[10]) + matrix[14];

	return out;
}


CVector4 CMatrix4x4::VectorMatrixMultiply3x3(CVector4 v)
{
	CVector4 out;

	out.x = (v.x * matrix[0]) + (v.y * matrix[4]) + (v.z * matrix[8]);
	out.y = (v.x * matrix[1]) + (v.y * matrix[5]) + (v.z * matrix[9]);
	out.z = (v.x * matrix[2]) + (v.y * matrix[6]) + (v.z * matrix[10]);

	return out;
}


CVector4 CMatrix4x4::transformPoint(CVector4 v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;

	v.x = x * matrix[0] +
		y * matrix[4] +
		z * matrix[8] + matrix[12];

	v.y = x * matrix[1] +
		y * matrix[5] +
		z * matrix[9] + matrix[13];

	v.z = x * matrix[2] +
		y * matrix[6] +
		z * matrix[10] + matrix[14];

	v.w = x * matrix[2] +
		y * matrix[7] +
		z * matrix[11] + matrix[15];

	return v;
}


bool CMatrix4x4::CreateShadowMatrix(CVector4 planeNormal, CVector4 lightPos)
{
	Clear();

	// Чтобы создать матрицу теней, сначала нужно получить скалярное произведение нормали
	// поверхности и позиции света. Мы сохраним результат в float-переменной dotProduct.
	// Используем функцию DotProduct из нашего класса CVector4.
	float dotProduct = planeNormal.DotProduct4(lightPos);

	// Создаем матрицу теней путем добавления наших значений...
	matrix[0] = dotProduct - lightPos.x * planeNormal.x;
	matrix[4] = 0.0f - lightPos.x * planeNormal.y;
	matrix[8] = 0.0f - lightPos.x * planeNormal.z;
	matrix[12] = 0.0f - lightPos.x * planeNormal.w;

	matrix[1] = 0.0f - lightPos.y * planeNormal.x;
	matrix[5] = dotProduct - lightPos.y * planeNormal.y;
	matrix[9] = 0.0f - lightPos.y * planeNormal.z;
	matrix[13] = 0.0f - lightPos.y * planeNormal.w;

	matrix[2] = 0.0f - lightPos.z * planeNormal.x;
	matrix[6] = 0.0f - lightPos.z * planeNormal.y;
	matrix[10] = dotProduct - lightPos.z * planeNormal.z;
	matrix[14] = 0.0f - lightPos.z * planeNormal.w;

	matrix[3] = 0.0f - lightPos.w * planeNormal.x;
	matrix[7] = 0.0f - lightPos.w * planeNormal.y;
	matrix[11] = 0.0f - lightPos.w * planeNormal.z;
	matrix[15] = dotProduct - lightPos.w * planeNormal.w;


	return true;
}