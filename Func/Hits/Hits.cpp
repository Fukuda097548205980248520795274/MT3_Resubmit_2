#include "Hits.h"

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="s1">球1</param>
/// <param name="s2">球2</param>
/// <returns>true or false</returns>
bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	// 球同士の距離
	float distance = Length(Subtract(s2.center, s1.center));

	if (distance <= s1.radius + s2.radius)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="sphere">球</param>
/// <param name="plane">平面</param>
/// <returns>true or false</returns>
bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	float distance = Dot(plane.normal, sphere.center) - plane.distance;

	if (std::fabs(distance) <= sphere.radius)
	{
		return true;
	}

	return false;


}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="segment">線分</param>
/// <param name="plane">平面</param>
/// <returns>true or false</returns>
bool IsCollision(const Segment& segment, const Plane& plane)
{
	// 法線 dot 終点との差分
	float NdotD = Dot(plane.normal, segment.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	return true;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="line">直線</param>
/// <param name="plane">平面</param>
/// <returns>true or false</returns>
bool IsCollision(const Line& line, const Plane& plane)
{
	// 法線 dot 終点との差分
	float NdotD = Dot(plane.normal, line.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	// 法線 dot 始点
	float NdotO = Dot(plane.normal, line.origin);

	// 媒介変数
	float t = (plane.distance - NdotO) / NdotD;

	if (t >= 0 && t <= 1)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="ray">半直線</param>
/// <param name="plane">平面</param>
/// <returns>ture or false</returns>
bool IsCollision(const Ray& ray, const Plane& plane)
{
	// 法線 dot 終点との差分
	float NdotD = Dot(plane.normal, ray.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	// 法線 dot 始点
	float NdotO = Dot(plane.normal, ray.origin);

	// 媒介変数
	float t = (plane.distance - NdotO) / NdotD;

	if (t >= 0)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="aabb1">AABB1</param>
/// <param name="aabb2">AABB2</param>
/// <returns>true or false</returns>
bool IsCollision(const AABB& aabb1, const AABB aabb2)
{
	if (aabb1.max.x >= aabb2.min.x &&
		aabb1.min.x <= aabb2.max.x)
	{
		if (aabb1.max.y >= aabb2.min.y &&
			aabb1.min.y <= aabb2.max.y)
		{
			if (aabb1.max.z >= aabb2.min.z &&
				aabb1.min.z <= aabb2.max.z)
			{
				return true;
			}
		}
	}

	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="sphere">球</param>
/// <returns></returns>
bool IsCollision(const AABB& aabb, const Sphere& sphere)
{
	// 最近接点
	Vector3 closestPoint =
	{
		std::clamp(sphere.center.x , aabb.min.x , aabb.max.x),
		std::clamp(sphere.center.y , aabb.min.y , aabb.max.y),
		std::clamp(sphere.center.z , aabb.min.z , aabb.max.z)
	};

	// 最近接点と球の中心の距離を求める
	float distance = Length(Subtract(closestPoint, sphere.center));

	// 距離が半径よりも小さかったら衝突する
	if (distance <= sphere.radius)
	{
		return true;
	}

	return false;
}


/// <summary>
/// 当たり判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="segment">線分</param>
/// <returns>true or false</returns>
bool IsCollision(const AABB& aabb, const Segment& segment)
{
	Vector3 tMin =
	{
		(aabb.min.x - segment.origin.x) / segment.diff.x,
		(aabb.min.y - segment.origin.y) / segment.diff.y,
		(aabb.min.z - segment.origin.z) / segment.diff.z
	};

	Vector3 tMax =
	{
		(aabb.max.x - segment.origin.x) / segment.diff.x,
		(aabb.max.y - segment.origin.y) / segment.diff.y,
		(aabb.max.z - segment.origin.z) / segment.diff.z
	};


	Vector3 tNear =
	{
		min(tMin.x , tMax.x),
		min(tMin.y , tMax.y),
		min(tMin.z , tMax.z)
	};

	Vector3 tFar =
	{
		max(tMin.x , tMax.x),
		max(tMin.y , tMax.y),
		max(tMin.z , tMax.z)
	};

	float tmin = max(max(tNear.x, tNear.y), tNear.z);
	float tmax = min(min(tFar.x, tFar.y), tFar.z);

	if (tmin <= tmax)
	{
		return true;
	}

	return false;
}


/// <summary>
/// 当たり判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="line">直線</param>
/// <returns>true or false</returns>
bool IsCollision(const AABB& aabb, const Line& line)
{
	Vector3 tMin =
	{
		(aabb.min.x - line.origin.x) / line.diff.x,
		(aabb.min.y - line.origin.y) / line.diff.y,
		(aabb.min.z - line.origin.z) / line.diff.z
	};

	Vector3 tMax =
	{
		(aabb.max.x - line.origin.x) / line.diff.x,
		(aabb.max.y - line.origin.y) / line.diff.y,
		(aabb.max.z - line.origin.z) / line.diff.z
	};

	Vector3 tNear =
	{
		min(tMin.x , tMax.x),
		min(tMin.y , tMax.y),
		min(tMin.z , tMax.z)
	};

	Vector3 tFar =
	{
		max(tMin.x , tMax.x),
		max(tMin.y , tMax.y),
		max(tMin.z , tMax.z)
	};


	float tmin = max(max(tNear.x, tNear.y), tNear.z);
	float tmax = min(min(tFar.x, tFar.y), tFar.z);

	if (tmin <= 1.0f && tmax >= 0.0f)
	{
		if (tmin <= tmax)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="ray">半直線</param>
/// <returns>true or false</returns>
bool IsCollision(const AABB& aabb, const Ray& ray)
{
	Vector3 tMin =
	{
		(aabb.min.x - ray.origin.x) / ray.diff.x,
		(aabb.min.y - ray.origin.y) / ray.diff.y,
		(aabb.min.z - ray.origin.z) / ray.diff.z
	};

	Vector3 tMax =
	{
		(aabb.max.x - ray.origin.x) / ray.diff.x,
		(aabb.max.y - ray.origin.y) / ray.diff.y,
		(aabb.max.z - ray.origin.z) / ray.diff.z
	};

	Vector3 tNear =
	{
		min(tMin.x , tMax.x),
		min(tMin.y , tMax.y),
		min(tMin.z , tMax.z)
	};

	Vector3 tFar =
	{
		max(tMin.x , tMax.x),
		max(tMin.y , tMax.y),
		max(tMin.z , tMax.z)
	};


	float tmin = max(max(tNear.x, tNear.y), tNear.z);
	float tmax = min(min(tFar.x, tFar.y), tFar.z);

	if (tmax >= 0.0f)
	{
		if (tmin <= tmax)
		{
			return true;
		}
	}

	return false;
}