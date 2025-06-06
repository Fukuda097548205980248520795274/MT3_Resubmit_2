#pragma once
#include <stdint.h>

// 2次元ベクトル
typedef struct Vector2
{
	float x;
	float y;
}Vector2;

// 3次元ベクトル
typedef struct Vector3
{
	float x;
	float y;
	float z;

	Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
	Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }
}Vector3;

// 4x4行列
typedef struct Matrix4x4
{
	float m[4][4];
}Matrix4x4;

// 球
typedef struct Sphere
{
	// 中心点
	Vector3 center;

	// 半径
	float radius;
}Sphere;

// 線分
typedef struct Segment
{
	// 始点
	Vector3 origin;

	// 終点への差分ベクトル
	Vector3 diff;
}Segment;

// 直線
typedef struct Line
{
	// 始点
	Vector3 origin;

	// 終点への差分ベクトル
	Vector3 diff;
}Line;

// 半直線
typedef struct Ray
{
	// 始点
	Vector3 origin;

	// 終点への差分ベクトル
	Vector3 diff;
}Ray;

// 平面
typedef struct Plane
{
	// 法線
	Vector3 normal;

	// 距離
	float distance;
}Plane;

// 三角形
typedef struct Triangle
{
	// 頂点
	Vector3 vertices[3];
}Triangle;

// AABB
typedef struct AABB
{
	// 最小点
	Vector3 min;

	// 最大点
	Vector3 max;
}AABB;


// ばね
typedef struct Spring
{
	// 固定された位置
	Vector3 anchor;

	// 自然長
	float naturalLength;

	// 剛性
	float siffiness;

	// 減衰係数
	float dampingCoefficent;
}Spring;

// ボール
typedef struct Ball
{
	// 位置
	Vector3 position;

	// 速度
	Vector3 velocity;

	// 加速度
	Vector3 acceleration;

	// 質量
	float mass;

	// 半径
	float radius;

	// 色
	uint32_t color;
}Ball;

// 円運動
typedef struct CircularMotion
{
	// 中心点
	Vector3 center;

	// 角度
	float angle;

	// 角速度
	float anglerVelocity;

	// 軌道の半径
	float orbitRadius;


	// 点
	Vector3 point;

	// 点の半径
	float pointRadius;
}CircularMotion;

// 振り子
typedef struct Pendulum
{
	// アンカーポイント　固定された位置
	Vector3 anchor;

	// 紐の長さ
	float length;

	// 現在の角度
	float angle;

	// 角速度ω
	float anglerVelocity;

	// 角加速度
	float anglerAcceleration;

	// 点（先端）
	Vector3 point;

}Pendulum;

// 円錐振り子
typedef struct ConicalPendulum
{
	// アンカーポイント　固定された位置
	Vector3 anchor;

	// 紐の長さ
	float length;

	// 円錐の頂角の半分
	float halfApexAngle;

	// 現在の角度
	float angle;

	// 角速度
	float anglerVelocity;

	// 点（先端）
	Vector3 point;
}ConicalPendulum;

// カプセル化
typedef struct Capsule
{
	// 線分
	Segment segment;

	// 半径
	float radius;
}Capsule;