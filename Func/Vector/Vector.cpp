#include "Vector.h"

/// <summary>
/// 加算する
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns>加算したベクトル</returns>
Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	// 加算したベクトル
	Vector3 add;
	add = { v1.x + v2.x , v1.y + v2.y, v1.z + v2.z };

	return add;
}

/// <summary>
/// 減算する
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns>減産したベクトル</returns>
Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	// 減産したベクトル
	Vector3 subtract;
	subtract = { v1.x - v2.x , v1.y - v2.y , v1.z - v2.z };

	return subtract;
}

/// <summary>
/// スカラー倍する
/// </summary>
/// <param name="scalar">スカラー</param>
/// <param name="v">ベクトル</param>
/// <returns>スカラー倍したベクトル</returns>
Vector3 Multiply(float scalar, const Vector3& v)
{
	// スカラー倍したベクトル
	Vector3 multiply;
	multiply = { v.x * scalar , v.y * scalar , v.z * scalar };

	return multiply;
}

/// <summary>
/// 内積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns>内積</returns>
float Dot(const Vector3& v1, const Vector3& v2)
{
	// 内積
	float dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return dot;
}

/// <summary>
/// 長さ（ノルム）を求める
/// </summary>
/// <param name="v">ベクトル</param>
/// <returns>長さ（ノルム）</returns>
float Length(const Vector3& v)
{
	// 長さ
	float length = sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));

	return length;
}

/// <summary>
/// 正規化する
/// </summary>
/// <param name="v">ベクトル</param>
/// <returns>正規化したベクトル</returns>
Vector3 Normalize(const Vector3& v)
{
	// 正規化したベクトル
	struct Vector3 normalize = { 0.0f ,0.0f ,0.0f };

	// 長さ
	float length = Length(v);

	
	if (length != 0.0f)
	{
		normalize = { v.x / length , v.y / length , v.z / length };
	}

	return normalize;
}

/// <summary>
/// ベクトルを出力する
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="vector">ベクトル</param>
/// <param name="label">文字</param>
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	const int kColumnWidth = 64;

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

/// <summary>
/// クロス積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns>クロス積</returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	// クロス積
	Vector3 cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;

	return cross;
}

/// <summary>
/// 正射影ベクトルを求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns>正射影ベクトル</returns>
Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	// 正規化したベクトル
	Vector3 normalizeV2 = Normalize(v2);

	// 正射影ベクトル
	Vector3 project = Multiply(Dot(v1, normalizeV2), normalizeV2);

	return project;
}

/// <summary>
/// 最近接点を求める
/// </summary>
/// <param name="point">点</param>
/// <param name="segment">線分</param>
/// <returns>最近接点</returns>
Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	// 最近接点
	Vector3 closestPoint = Add(segment.origin, point);

	return closestPoint;
}

/// <summary>
/// 垂直ベクトルを求める
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns>垂直ベクトル</returns>
Vector3 Perpendiculer(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f)
	{
		return { -vector.y , vector.x , 0.0f };
	}

	return { 0.0f , -vector.z , vector.y };
}

/// <summary>
/// 反射ベクトルを求める
/// </summary>
/// <param name="input">入力</param>
/// <param name="normal">法線</param>
/// <returns></returns>
Vector3 Reflect(const Vector3& input, const Vector3& normal)
{
	Vector3 reflect;

	reflect = input - 2.0f * Dot(input, normal) * normal;

	return reflect;
}