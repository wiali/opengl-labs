#include"CVector.hpp"

#define PI_VALUE 3.141592654


CVector4::CVector4()
{
	x = y = z = 0.0;
}


CVector4::CVector4(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}


CVector4::CVector4(float X, float Y, float Z, float W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}


CVector4::CVector4(const CVector4 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}


void CVector4::operator =(CVector4 v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}


CVector4 CVector4::operator -(CVector4 v)
{
	return CVector4(x - v.x, y - v.y, z - v.z);
}


CVector4 CVector4::operator +(CVector4 v)
{
	return CVector4(x + v.x, y + v.y, z + v.z);
}


CVector4 CVector4::operator *(CVector4 v)
{
	return CVector4(x * v.x, y * v.y, z * v.z);
}


CVector4 CVector4::operator /(CVector4 v)
{
	return CVector4(x / v.x, y / v.y, z / v.z);
}


CVector4 CVector4::operator +(float f)
{
	return CVector4(x + f, y + f, z + f);
}


CVector4 CVector4::operator -(float f)
{
	return CVector4(x - f, y - f, z - f);
}


CVector4 CVector4::operator *(float f)
{
	return CVector4(x * f, y * f, z * f);
}


CVector4 CVector4::operator /(float f)
{
	f = 1 / f;

	return CVector4(x * f, y * f, z * f);
}


void CVector4::operator +=(CVector4 v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}


void CVector4::operator -=(CVector4 v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}


void CVector4::operator *=(CVector4 v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}


void CVector4::operator /=(CVector4 v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
}


void CVector4::operator +=(float f)
{
	x += f;
	y += f;
	z += f;
}


void CVector4::operator -=(float f)
{
	x -= f;
	y -= f;
	z -= f;
}


void CVector4::operator *=(float f)
{
	x *= f;
	y *= f;
	z *= f;
}


void CVector4::operator /=(float f)
{
	f = 1 / f;

	x *= f;
	y *= f;
	z *= f;
}


bool CVector4::operator ==(CVector4 v)
{
	return ((x == v.x) && (y == v.y) && (z == v.z));
}


bool CVector4::operator !=(CVector4 v)
{
	return !((x == v.x) && (y == v.y) && (z == v.z));
}


void CVector4::CrossProduct(CVector4 v1, CVector4 v2)
{
	x = ((v1.y * v2.z) - (v1.z * v2.y));
	y = ((v1.z * v2.x) - (v1.x * v2.z));
	z = ((v1.x * v2.y) - (v1.y * v2.x));
}


void CVector4::CrossProduct3(CVector4 v1, CVector4 v2, CVector4 v3)
{
	x = v1.y * v2.z * v3.w +
		v1.z * v2.w * v3.y +
		v1.w * v2.y * v3.z -
		v1.y * v2.w * v3.z -
		v1.z * v2.y * v3.w -
		v1.w * v2.z * v3.y;

	y = v1.x * v2.w * v3.z +
		v1.z * v2.x * v3.w +
		v1.w * v2.z * v3.x -
		v1.x * v2.z * v3.w -
		v1.z * v2.w * v3.x -
		v1.w * v2.x * v3.z;

	z = v1.x * v2.y * v3.w +
		v1.y * v2.w * v3.x +
		v1.w * v2.x * v3.y -
		v1.x * v2.w * v3.y -
		v1.y * v2.x * v3.w -
		v1.w * v2.y * v3.x;

	w = v1.x * v2.z * v3.y +
		v1.y * v2.x * v3.z +
		v1.z * v2.y * v3.x -
		v1.x * v2.y * v3.z -
		v1.y * v2.z * v3.x -
		v1.z * v2.x * v3.y;
}


float CVector4::DotProduct3(CVector4 v1)
{
	return x * v1.x + y * v1.y + z * v1.z;
}


float CVector4::DotProduct4(CVector4 v1)
{
	return x * v1.x + y * v1.y + z * v1.z + w * v1.w;
}


float CVector4::GetLength()
{
	return (float)sqrt((x * x + y * y + z * z));
}


void CVector4::Normal()
{
	float lenght = GetLength();

	if (lenght == 0.0f)
		lenght = 1.0f;

	x = x / lenght;
	y = y / lenght;
	z = z / lenght;
	w = w / lenght;
}


void CVector4::Normalize(CVector4 Triangle[])
{
	CVector4 v1, v2;

	v1.x = Triangle[0].x - Triangle[1].x;
	v1.y = Triangle[0].y - Triangle[1].y;
	v1.z = Triangle[0].z - Triangle[1].z;
	v1.w = Triangle[0].w - Triangle[1].w;

	v2.x = Triangle[1].x - Triangle[2].x;
	v2.y = Triangle[1].y - Triangle[2].y;
	v2.z = Triangle[1].z - Triangle[2].z;
	v2.w = Triangle[1].w - Triangle[2].w;

	CrossProduct(v1, v2);
	Normal();
}


void CVector4::CalculateTangentVector(CVector4 Point1, CVector4 Point2, CVector4 Point3,
	CVector4 NormalOfA, CTexCoord P1Tex, CTexCoord P2Tex,
	CTexCoord P3Tex)
{
	CVector4 VectorAB = Point2 - Point1;

	CVector4 VectorAC = Point3 - Point1;

	CVector4 ProjAB = VectorAB - (NormalOfA * NormalOfA.DotProduct4(VectorAB));
	CVector4 ProjAC = VectorAC - (NormalOfA * NormalOfA.DotProduct4(VectorAC));

	float TexCoorUAB = P2Tex.tu - P1Tex.tu;
	float TexCoorUAC = P3Tex.tu - P1Tex.tu;

	float TexCoorVAB = P2Tex.tv - P1Tex.tv;
	float TexCoorVAC = P3Tex.tv - P1Tex.tv;

	if ((TexCoorUAC * TexCoorVAB) > (TexCoorUAB * TexCoorVAC))
	{
		TexCoorUAC = -TexCoorUAC;
		TexCoorUAB = -TexCoorUAB;
	}

	CVector4 Tangent = (ProjAB * TexCoorUAC) - (ProjAC * TexCoorUAB);
	Tangent.Normal();

	*this += Tangent;
}


void CVector4::ExtendVertexPos(CVector4 currentVertex, CVector4 lightPos, float Extend)
{
	CVector4 lightDir;
	CVector4 newPos;

	lightDir = currentVertex - lightPos;

	newPos = lightPos + lightDir * Extend;

	x = newPos.x;
	y = newPos.y;
	z = newPos.z;
	w = newPos.w;
}


void CVector4::ExtendVertexPos(CVector4 lightPos, float Extend)
{
	CVector4 lightDir;
	CVector4 newPos;

	lightDir = CVector4(x, y, z, w) - lightPos;

	newPos = lightPos + lightDir * Extend;

	x = newPos.x;
	y = newPos.y;
	z = newPos.z;
	w = newPos.w;
}


CVector4 CVector4::GetRotatedX(double angle)
{
	float sinAngle = (float)sin(PI_VALUE * angle / 180);
	float cosAngle = (float)cos(PI_VALUE * angle / 180);

	return CVector4(x, y * cosAngle - z * sinAngle, y * sinAngle + z * cosAngle, w);
}


CVector4 CVector4::GetRotatedY(double angle)
{
	float sinAngle = (float)sin(PI_VALUE * angle / 180);
	float cosAngle = (float)cos(PI_VALUE * angle / 180);

	return CVector4(x * cosAngle + z * sinAngle, y, -x * sinAngle + z * cosAngle, w);
}


CVector4 CVector4::GetRotatedZ(double angle)
{
	float sinAngle = (float)sin(PI_VALUE * angle / 180);
	float cosAngle = (float)cos(PI_VALUE * angle / 180);

	return CVector4(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle, z, w);
}


CVector4 CVector4::GetRotatedAxis(double angle, CVector4 axis)
{
	if (angle == 0.0) return (*this);

	axis.Normal();

	CVector4 RotationRow1, RotationRow2, RotationRow3;

	double newAngle = PI_VALUE * angle / 180;
	float sinAngle = (float)sin(newAngle);
	float cosAngle = (float)cos(newAngle);
	float oneSubCos = 1.0f - cosAngle;

	RotationRow1.x = (axis.x) * (axis.x) + cosAngle * (1 - (axis.x) * (axis.x));
	RotationRow1.y = (axis.x) * (axis.y) * (oneSubCos)-sinAngle * axis.z;
	RotationRow1.z = (axis.x) * (axis.z) * (oneSubCos)+sinAngle * axis.y;

	RotationRow2.x = (axis.x) * (axis.y) * (oneSubCos)+sinAngle * axis.z;
	RotationRow2.y = (axis.y) * (axis.y) + cosAngle * (1 - (axis.y) * (axis.y));
	RotationRow2.z = (axis.y) * (axis.z) * (oneSubCos)-sinAngle * axis.x;

	RotationRow3.x = (axis.x) * (axis.z) * (oneSubCos)-sinAngle * axis.y;
	RotationRow3.y = (axis.y) * (axis.z) * (oneSubCos)+sinAngle * axis.x;
	RotationRow3.z = (axis.z) * (axis.z) + cosAngle * (1 - (axis.z) * (axis.z));

	return CVector4(this->DotProduct3(RotationRow1),
		this->DotProduct3(RotationRow2),
		this->DotProduct3(RotationRow3));
}


void CVector4::CalculateBinormalVector(CVector4 tangent, CVector4 normal)
{
	this->CrossProduct(tangent, normal);
}


void CVector4::ClampTo01()
{
	CVector4 temp(x, y, z, w);
	temp.Normal();
	temp = temp * 0.5f + CVector4(0.5f, 0.5f, 0.5f);

	x = temp.x;
	y = temp.y;
	z = temp.z;
}
