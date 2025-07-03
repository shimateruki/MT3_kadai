#define NOMINMAX
#include "MatrixUtility.h"
#include <cfloat> // FLT_EPSILON のために必要 (または独自のEPSILONを定義)
#include <cmath>


Vector3 operator+(const Vector3& objA, const Vector3& objB)
{
	Vector3 sc = Vector3(0, 0, 0);
	sc.x = objA.x + objB.x;
	sc.y = objA.y + objB.y;
	sc.z = objA.z + objB.z;
	return sc;
}

Vector3 operator-(const Vector3& objA, const Vector3& objB)
{
	Vector3 sc = Vector3(0, 0, 0);
	sc.x = objA.x - objB.x;
	sc.y = objA.y - objB.y;
	sc.z = objA.z - objB.z;
	return sc;
}

Vector3 operator+(Vector3& v, float s) {
	Vector3 result;
	result.x = v.x + s;
	result.y = v.y + s;
	result.z = v.z + s;
	return result;
}

Vector3 operator*(const Vector3& objA, const float objB) {
	Vector3 sc = Vector3(0, 0, 0);
	sc.x = objA.x + objB;
	sc.y = objA.y + objB;
	sc.z = objA.z + objB;
	return sc;
}


Vector3& operator*=(Vector3& v, float s) {
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}

Vector3& operator/=(Vector3& v, float s) {
	v.x /= s;
	v.y /= s;
	v.z /= s;
	return v;
}




Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;
	return lhv;
}

Vector3& operator-=(Vector3& lhv, const Vector3& rhv) {
	lhv.x -= rhv.x;
	lhv.y -= rhv.y;
	lhv.z -= rhv.z;
	return lhv;
}








//透視投影行列
Matrix4x4  MatrixUtility::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result = {};
	float f = 1.0f / tanf(fovY / 2.0f);
	result.m[0][0] = f / aspectRatio;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0.0f;
	return result;
}
//正射影行列
Matrix4x4  MatrixUtility::MakeOrthographicMatrix(float left, float top, float right,
	float bottom, float nearClip, float farClip)
{
	Matrix4x4 result{};
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[2][3] = 0.0f;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;
	return result;
}
//3　ビューボート返還行列

Matrix4x4  MatrixUtility::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result{};
	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4  MatrixUtility::MakeScaleMatrix(const Vector3& scale) {

	Matrix4x4 result{ scale.x, 0.0f, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 0.0f, scale.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	return result;
}

Matrix4x4  MatrixUtility::MakeRotateXMatrix(float theta) {
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	Matrix4x4 result{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos, sin, 0.0f, 0.0f, -sin, cos, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	return result;
}

Matrix4x4  MatrixUtility::MakeRotateYMatrix(float theta) {
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	Matrix4x4 result{ cos, 0.0f, -sin, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sin, 0.0f, cos, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	return result;
}

Matrix4x4  MatrixUtility::MakeRotateZMatrix(float theta) {
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	Matrix4x4 result{ cos, sin, 0.0f, 0.0f, -sin, cos, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	return result;
}

Matrix4x4  MatrixUtility::MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translate.x, translate.y, translate.z, 1.0f };

	return result;
}

Matrix4x4  MatrixUtility::Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.m[row][col] = m1.m[row][0] * m2.m[0][col] + m1.m[row][1] * m2.m[1][col] + m1.m[row][2] * m2.m[2][col] + m1.m[row][3] * m2.m[3][col];
		}
	}
	return result;
}


Matrix4x4  MatrixUtility::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = Multiply(Multiply(rotateXMatrix, rotateYMatrix), rotateZMatrix);
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	Matrix4x4 worldMatrix = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);

	return worldMatrix;
}

Vector3 MatrixUtility::Multiply(const Vector3& v, float scalar) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

//逆行列
Matrix4x4  MatrixUtility::Inverse(const Matrix4x4& m)
{
	Matrix4x4 result = {};


	float a11 = m.m[0][0], a12 = m.m[0][1], a13 = m.m[0][2], a14 = m.m[0][3];
	float a21 = m.m[1][0], a22 = m.m[1][1], a23 = m.m[1][2], a24 = m.m[1][3];
	float a31 = m.m[2][0], a32 = m.m[2][1], a33 = m.m[2][2], a34 = m.m[2][3];
	float a41 = m.m[3][0], a42 = m.m[3][1], a43 = m.m[3][2], a44 = m.m[3][3];


	float det = a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42 + a11 * a24 * a32 * a43
		- a11 * a24 * a33 * a42 - a11 * a23 * a32 * a44 - a11 * a22 * a34 * a43
		- a12 * a21 * a33 * a44 - a13 * a21 * a34 * a42 - a14 * a21 * a32 * a43
		+ a14 * a21 * a33 * a42 + a13 * a21 * a32 * a44 + a12 * a21 * a34 * a43
		+ a12 * a23 * a31 * a44 + a13 * a24 * a31 * a42 + a14 * a22 * a31 * a43
		- a14 * a23 * a31 * a42 - a13 * a22 * a31 * a44 - a12 * a24 * a31 * a43
		- a12 * a23 * a34 * a41 - a13 * a24 * a32 * a41 - a14 * a22 * a33 * a41
		+ a14 * a23 * a32 * a41 + a13 * a22 * a34 * a41 + a12 * a24 * a33 * a41;
	if (det == 0.0f) {
		// 逆行列が存在しない（行列式が0）
		return result;
	}

	float invDet = 1.0f / det;

	// 以下、各要素に対応する余因子を手動計算して代入（転置あり）

	// 1行目
	result.m[0][0] = (a22 * (a33 * a44 - a34 * a43) - a23 * (a32 * a44 - a34 * a42) + a24 * (a32 * a43 - a33 * a42)) * invDet;
	result.m[0][1] = -(a12 * (a33 * a44 - a34 * a43) - a13 * (a32 * a44 - a34 * a42) + a14 * (a32 * a43 - a33 * a42)) * invDet;
	result.m[0][2] = (a12 * (a23 * a44 - a24 * a43) - a13 * (a22 * a44 - a24 * a42) + a14 * (a22 * a43 - a23 * a42)) * invDet;
	result.m[0][3] = -(a12 * (a23 * a34 - a24 * a33) - a13 * (a22 * a34 - a24 * a32) + a14 * (a22 * a33 - a23 * a32)) * invDet;

	// 2行目
	result.m[1][0] = -(a21 * (a33 * a44 - a34 * a43) - a23 * (a31 * a44 - a34 * a41) + a24 * (a31 * a43 - a33 * a41)) * invDet;
	result.m[1][1] = (a11 * (a33 * a44 - a34 * a43) - a13 * (a31 * a44 - a34 * a41) + a14 * (a31 * a43 - a33 * a41)) * invDet;
	result.m[1][2] = -(a11 * (a23 * a44 - a24 * a43) - a13 * (a21 * a44 - a24 * a41) + a14 * (a21 * a43 - a23 * a41)) * invDet;
	result.m[1][3] = (a11 * (a23 * a34 - a24 * a33) - a13 * (a21 * a34 - a24 * a31) + a14 * (a21 * a33 - a23 * a31)) * invDet;

	// 3行目
	result.m[2][0] = (a21 * (a32 * a44 - a34 * a42) - a22 * (a31 * a44 - a34 * a41) + a24 * (a31 * a42 - a32 * a41)) * invDet;
	result.m[2][1] = -(a11 * (a32 * a44 - a34 * a42) - a12 * (a31 * a44 - a34 * a41) + a14 * (a31 * a42 - a32 * a41)) * invDet;
	result.m[2][2] = (a11 * (a22 * a44 - a24 * a42) - a12 * (a21 * a44 - a24 * a41) + a14 * (a21 * a42 - a22 * a41)) * invDet;
	result.m[2][3] = -(a11 * (a22 * a34 - a24 * a32) - a12 * (a21 * a34 - a24 * a31) + a14 * (a21 * a32 - a22 * a31)) * invDet;

	// 4行目
	result.m[3][0] = -(a21 * (a32 * a43 - a33 * a42) - a22 * (a31 * a43 - a33 * a41) + a23 * (a31 * a42 - a32 * a41)) * invDet;
	result.m[3][1] = (a11 * (a32 * a43 - a33 * a42) - a12 * (a31 * a43 - a33 * a41) + a13 * (a31 * a42 - a32 * a41)) * invDet;
	result.m[3][2] = -(a11 * (a22 * a43 - a23 * a42) - a12 * (a21 * a43 - a23 * a41) + a13 * (a21 * a42 - a22 * a41)) * invDet;
	result.m[3][3] = (a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 * a31)) * invDet;

	return result;
}

//3 座標変換
Vector3  MatrixUtility::Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result = {};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

//クロス積
Vector3  MatrixUtility::Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 result = {};
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}



// 球体描画関数
void  MatrixUtility::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 16; // 分割数
	const float pi = 3.14159265359f;
	const float kLonStep = 2 * pi / float(kSubdivision);  // 経度ステップ
	const float kLatStep = pi / float(kSubdivision);      // 緯度ステップ

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatStep * latIndex;
		float latNext = lat + kLatStep;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonStep;
			float lonNext = lon + kLonStep;

			// 球面座標をワールド座標に変換
			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(latNext) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(latNext),
				sphere.center.z + sphere.radius * cosf(latNext) * sinf(lon)
			};
			Vector3 c = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lonNext),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lonNext)
			};

			// ビュー行列 → ビューポート行列を通してスクリーン座標に変換
			Vector3 screenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
		}
	}
}

// グリッド描画関数
void  MatrixUtility::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridStep = (kGridHalfWidth * 2.0f) / float(kSubdivision);
	const uint32_t color1 = 0xAAAAAAFF; // 通常線の色（灰色）
	const uint32_t color2 = BLACK;      // 中心線の色（黒）

	for (uint32_t i = 0; i <= kSubdivision; ++i) {
		float pos = -kGridHalfWidth + i * kGridStep;

		// 中心線かどうか判定
		bool isCenter = (abs(pos) < 0.001f);

		// X軸に平行な線（Z方向に位置する）
		Vector3 startX = { -kGridHalfWidth, 0.0f, pos };
		Vector3 endX = { kGridHalfWidth, 0.0f, pos };
		Vector3 screenStartX = Transform(Transform(startX, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEndX = Transform(Transform(endX, viewProjectionMatrix), viewportMatrix);
		uint32_t colorX = isCenter ? color2 : color1;
		Novice::DrawLine(int(screenStartX.x), int(screenStartX.y), int(screenEndX.x), int(screenEndX.y), colorX);

		// Z軸に平行な線（X方向に位置する）
		Vector3 startZ = { pos, 0.0f, -kGridHalfWidth };
		Vector3 endZ = { pos, 0.0f, kGridHalfWidth };
		Vector3 screenStartZ = Transform(Transform(startZ, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEndZ = Transform(Transform(endZ, viewProjectionMatrix), viewportMatrix);
		uint32_t colorZ = isCenter ? color2 : color1;
		Novice::DrawLine(int(screenStartZ.x), int(screenStartZ.y), int(screenEndZ.x), int(screenEndZ.y), colorZ);
	}
}



Vector3 MatrixUtility::Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 MatrixUtility::Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}


Vector3 MatrixUtility::Project(const Vector3& v1, const Vector3& v2) {
	float v2LengthSq = v2.x * v2.x + v2.y * v2.y + v2.z * v2.z;
	assert(v2LengthSq != 0.0f); // 0除算防止

	float dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	float scalar = dot / v2LengthSq;

	Vector3 result{
		v2.x * scalar,
		v2.y * scalar,
		v2.z * scalar
	};

	return result;
}

Vector3 MatrixUtility::ClossetPoint(const Vector3& point, const Segment& segment) {
	Vector3 originToPoint{
		point.x - segment.origin.x,
		point.y - segment.origin.y,
		point.z - segment.origin.z
	};

	Vector3 projected = Project(originToPoint, segment.diff);

	Vector3 closest{
		segment.origin.x + projected.x,
		segment.origin.y + projected.y,
		segment.origin.z + projected.z
	};

	return closest;
}

float Length(const Vector3& v) {

	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float MatrixUtility::Dot(const Vector3& v1, const Vector3& v2) {
	// 各成分を掛け合わせて合計する
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//bool MatrixUtility::IsCollision(const Sphere& sphere, const Plane& plane)
//{
//	
//	float signedDistance = Dot(sphere.center, plane.normal) - plane.distance;
//
//
//	if (fabsf(signedDistance) <= sphere.radius) 
//	{
//		return true; // 衝突している
//	}
//	return false; // 衝突していない
//}

bool MatrixUtility::IsCollision(const Segment& segment, const Plane& plane)
{
	float dot = Dot(plane.normal, segment.diff);

	float distanceOriginToPlane = Dot(segment.origin, plane.normal) - plane.distance;


	if (std::fabs(dot) < 1.0f)
	{
		// 線分の開始点が平面上にあるか確認

		if (std::fabs(distanceOriginToPlane) < 1.0f)
		{

			return true;
		} else
		{

			return false;
		}
	}


	float t = -distanceOriginToPlane / dot;


	if (t >= 0.0f && t <= 1.0f)
	{
		return true;
	} else
	{
		return false;
	}
}

bool MatrixUtility::IsCollision(const Segment& segment, const Triangle& triangle) {
	// 各頂点を取得  
	Vector3 v0 = triangle.vertices[0];
	Vector3 v1 = triangle.vertices[1];
	Vector3 v2 = triangle.vertices[2];

	// 線分の始点と終点を取得  
	Vector3 p0 = segment.origin;
	Vector3 p1 = Add(segment.origin, segment.diff);

	// 線分と平面の衝突判定  
	Plane plane;
	plane.normal = Normalize(Cross(Subtract(v1, v0), Subtract(v2, v0)));
	plane.distance = Dot(plane.normal, v0);

	if (!IsCollision(segment, plane)) {
		return false;
	}

	// 衝突点を計算  
	float dot = Dot(plane.normal, segment.diff);
	float distanceOriginToPlane = Dot(segment.origin, plane.normal) - plane.distance;
	float t = -distanceOriginToPlane / dot;
	Vector3 collisionPoint = Add(segment.origin, Multiply(segment.diff, t));

	// 各辺を結んだベクトルと頂点と衝突点を結んだベクトルのクロス積を計算  
	Vector3 v0p = Subtract(collisionPoint, v0);
	Vector3 v1p = Subtract(collisionPoint, v1);
	Vector3 v2p = Subtract(collisionPoint, v2);

	Vector3 v01 = Subtract(v1, v0);
	Vector3 v12 = Subtract(v2, v1);
	Vector3 v20 = Subtract(v0, v2);

	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);

	// 全てのクロス積の内積が正なら衝突している  
	if (Dot(cross01, cross12) > 0.0f && Dot(cross12, cross20) > 0.0f) {
		return true;
	}

	return false;
}

bool MatrixUtility::isCollision(const AABB& aabb1, const AABB& aabb2)
{
	return (aabb1.max.x >= aabb2.min.x && aabb1.min.x <= aabb2.max.x) &&
		(aabb1.max.y >= aabb2.min.y && aabb1.min.y <= aabb2.max.y) &&
		(aabb1.max.z >= aabb2.min.z && aabb1.min.z <= aabb2.max.z);
}

bool MatrixUtility::IsCollision(const AABB& aabb, const Sphere& sphere)
{
	//最近接点を求める
	Vector3 clossetPoint{ std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
		std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
		std::clamp(sphere.center.z, aabb.min.z, aabb.max.z) };
	//最近接点と球の中心の距離を求める
    float distance = Length(Subtract(clossetPoint, sphere.center));
	//距離が球の半径以下なら衝突している
	return distance <= sphere.radius;
}

bool MatrixUtility::IsCollision(const AABB& aabb, const Segment& segment)
{
	
       // 線分の方向ベクトルを正規化  
       Vector3 direction = Normalize(segment.diff);  

       // 線分の始点と終点を取得  
       Vector3 p0 = segment.origin;  
       Vector3 p1 = Add(segment.origin, segment.diff);  

       // AABBの各軸に対するtNearとtFarを計算  
       float tNearX = (direction.x > 0.0f) ? (aabb.min.x - p0.x) / direction.x : (aabb.max.x - p0.x) / direction.x;  
       float tFarX = (direction.x > 0.0f) ? (aabb.max.x - p0.x) / direction.x : (aabb.min.x - p0.x) / direction.x;  

       float tNearY = (direction.y > 0.0f) ? (aabb.min.y - p0.y) / direction.y : (aabb.max.y - p0.y) / direction.y;  
       float tFarY = (direction.y > 0.0f) ? (aabb.max.y - p0.y) / direction.y : (aabb.min.y - p0.y) / direction.y;  

       float tNearZ = (direction.z > 0.0f) ? (aabb.min.z - p0.z) / direction.z : (aabb.max.z - p0.z) / direction.z;  
       float tFarZ = (direction.z > 0.0f) ? (aabb.max.z - p0.z) / direction.z : (aabb.min.z - p0.z) / direction.z;  

       // tMinとtMaxを計算  
       float tMin = std::max(std::max(tNearX, tNearY), tNearZ);  
       float tMax = std::min(std::min(tFarX, tFarY), tFarZ);  

       // tMin <= tMaxなら衝突している  
       return tMin <= tMax;  
    }






Vector3 MatrixUtility::Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f)
	{
		return{ -vector.y, vector.x, 0.0f };
	}
	return { 0.0f, -vector.z, vector.y };
}

// Vector3 を正規化する関数
Vector3 MatrixUtility::Normalize(const Vector3& v) {
	Vector3 result = v;

	float len = Length(v);


	if (len != 0.0f) {
		result.x /= len;
		result.y /= len;
		result.z /= len;
	}
	return result;
}

void MatrixUtility::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// 平面の中心点 (原点に最も近い点) を計算
	Vector3 center = Multiply(plane.normal, plane.distance);

	Vector3 perpendDiculor[4]; // 変数名はそのまま
	// perpendDiculor[0] を U軸方向として利用
	perpendDiculor[0] = Normalize(Perpendicular(plane.normal));

	// perpendDiculor[1] は元の定義のまま。今回は直接四隅の計算には使わない
	perpendDiculor[1] = { -perpendDiculor[0].x, -perpendDiculor[0].y, perpendDiculor[0].z };

	// perpendDiculor[2] を V軸方向として利用 (perpendDiculor[0]と法線の外積)
	perpendDiculor[2] = Normalize(Cross(plane.normal, perpendDiculor[0]));

	// perpendDiculor[3] は元の定義のまま。今回は直接四隅の計算には使わない
	perpendDiculor[3] = { -perpendDiculor[2].x, -perpendDiculor[2].y, -perpendDiculor[2].z };

	// 描画する平面のサイズを決定する定数 (半分の幅/高さ)
	const float kPlaneExtent = 2.0f; // この値を調整して、描画される平面のサイズを変更

	Vector3 points[4]; // 最終的なスクリーン座標を格納する配列 (変数名そのまま)

	// ここで points[0]からpoints[3]に四隅の点を計算し直す
	// 従来のループは削除し、四隅の点を明示的に割り当てる

	// point[0]: 中心から (+U軸方向 +V軸方向) に進んだ点 (右上)
	Vector3 p0_world = Add(center, Add(Multiply(perpendDiculor[0], kPlaneExtent), Multiply(perpendDiculor[2], kPlaneExtent)));
	points[0] = Transform(Transform(p0_world, viewProjectionMatrix), viewportMatrix);

	// point[1]: 中心から (-U軸方向 +V軸方向) に進んだ点 (左上)
	Vector3 p1_world = Add(center, Add(Multiply(perpendDiculor[0], -kPlaneExtent), Multiply(perpendDiculor[2], kPlaneExtent)));
	points[1] = Transform(Transform(p1_world, viewProjectionMatrix), viewportMatrix);

	// point[2]: 中心から (-U軸方向 -V軸方向) に進んだ点 (左下)
	Vector3 p2_world = Add(center, Add(Multiply(perpendDiculor[0], -kPlaneExtent), Multiply(perpendDiculor[2], -kPlaneExtent)));
	points[2] = Transform(Transform(p2_world, viewProjectionMatrix), viewportMatrix);

	// point[3]: 中心から (+U軸方向 -V軸方向) に進んだ点 (右下)
	Vector3 p3_world = Add(center, Add(Multiply(perpendDiculor[0], kPlaneExtent), Multiply(perpendDiculor[2], -kPlaneExtent)));
	points[3] = Transform(Transform(p3_world, viewProjectionMatrix), viewportMatrix);

	// 計算した点を順番に結んで四角形を描画する
	// point[0] (右上) -> point[1] (左上) -> point[2] (左下) -> point[3] (右下) -> point[0] (右上)
	Novice::DrawLine(static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		static_cast<int>(points[1].x), static_cast<int>(points[1].y), color);
	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<int>(points[2].x), static_cast<int>(points[2].y), color);
	Novice::DrawLine(static_cast<int>(points[2].x), static_cast<int>(points[2].y),
		static_cast<int>(points[3].x), static_cast<int>(points[3].y), color);
	Novice::DrawLine(static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		static_cast<int>(points[0].x), static_cast<int>(points[0].y), color);
}

void MatrixUtility::DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 screenVertices[3];
	for (int i = 0; i < 3; ++i) {
		screenVertices[i] = Transform(Transform(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}
	// 三角形の各辺を描画
	Novice::DrawLine(static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
		static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y), color);
	Novice::DrawLine(static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y), color);
	Novice::DrawLine(static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
		static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y), color);
}

void MatrixUtility::DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// AABBの8つのコーナーを計算
	Vector3 corners[8] = {
		{ aabb.min.x, aabb.min.y, aabb.min.z },
		{ aabb.max.x, aabb.min.y, aabb.min.z },
		{ aabb.max.x, aabb.max.y, aabb.min.z },
		{ aabb.min.x, aabb.max.y, aabb.min.z },
		{ aabb.min.x, aabb.min.y, aabb.max.z },
		{ aabb.max.x, aabb.min.y, aabb.max.z },
		{ aabb.max.x, aabb.max.y, aabb.max.z },
		{ aabb.min.x, aabb.max.y, aabb.max.z }
	};
	// ビュー行列 → ビューポート行列を通してスクリーン座標に変換
	Vector3 screenCorners[8];
	for (int i = 0; i < 8; ++i) {
		screenCorners[i] = Transform(Transform(corners[i], viewProjectionMatrix), viewportMatrix);
	}
	// AABBの各辺を描画
	for (int i = 0; i < 4; ++i) {
		int next = (i + 1) % 4;
		int nextTop = next + 4;
		// 底面の線
		Novice::DrawLine(static_cast<int>(screenCorners[i].x), static_cast<int>(screenCorners[i].y),
			static_cast<int>(screenCorners[next].x), static_cast<int>(screenCorners[next].y), color);
		// 上面の線
		Novice::DrawLine(static_cast<int>(screenCorners[i + 4].x), static_cast<int>(screenCorners[i + 4].y),
			static_cast<int>(screenCorners[nextTop].x), static_cast<int>(screenCorners[nextTop].y), color);
		// 側面の線
		Novice::DrawLine(static_cast<int>(screenCorners[i].x), static_cast<int>(screenCorners[i].y),
			static_cast<int>(screenCorners[i + 4].x), static_cast<int>(screenCorners[i + 4].y), color);
	}
}
