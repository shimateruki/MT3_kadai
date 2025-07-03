#pragma once
#include <Novice.h>
#include <cmath>
#include <cassert>
#include <corecrt_math.h>
#include <algorithm>

struct Vector2
{
	float x;
	float y;
};

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
};

struct Sphere {
	Vector3 center;
	float radius;
	unsigned int color;
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
	unsigned int color;
};

struct  Plane
{
	Vector3 normal;//法線
	float distance;//距離
};

struct Triangle
{
	Vector3 vertices[3];//頂点
};

struct AABB
{
	Vector3 min;
	Vector3 max;
};


Vector3 operator+(const Vector3& objA, const Vector3& objB);
Vector3 operator-(const Vector3& objA, const Vector3& objB);
Vector3 operator+(Vector3& v, float s);
Vector3 operator*(const Vector3& objA, const float objB);
// 代入演算子オーバーロード
Vector3& operator+=(Vector3& lhs, const Vector3& rhv);
Vector3& operator-=(Vector3& lhs, const Vector3& rhv);
Vector3& operator*=(Vector3& v, float s);
Vector3& operator/=(Vector3& v, float s);

class MatrixUtility {
public:
	//透視投影行列
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
	//正射影行列
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	//ビューボート返還行列
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	Matrix4x4 MakeRotateXMatrix(float theta);

	Matrix4x4 MakeRotateYMatrix(float theta);

	Matrix4x4 MakeRotateZMatrix(float theta);

	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	Vector3 Multiply(const Vector3& v, float scalar);

	


	Matrix4x4 Inverse(const Matrix4x4& m);

	//3 座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	//クロス積
	Vector3 Cross(const Vector3& v1, const Vector3& v2);

	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	// グリッド描画関数
	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);


	Vector3 Add(const Vector3& v1, const Vector3& v2);
	Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	Vector3 Project(const Vector3& v1, const Vector3& v2);

	Vector3 ClossetPoint(const Vector3& point, const Segment& segment);

	float Dot(const Vector3& v1, const Vector3& v2);

	bool IsCollision(const Sphere& sphere, const Plane& s2);

	bool IsCollision(const Segment& segment, const Plane& plane);

	bool IsCollision(const Segment& segment, const Triangle& triangle);
	bool isCollision(const AABB& aabb1, const AABB& aabb2);
	bool IsCollision(const AABB& aabb, const Sphere& sphere);
	bool IsCollision(const AABB& aabb, const Segment&segment);

	Vector3 Perpendicular(const Vector3& vector);

	Vector3 Normalize(const Vector3& v);

	void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
};

