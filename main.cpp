#include <Novice.h>
#include <cmath>
#include <cassert>
#include <corecrt_math.h>

const char kWindowTitle[] = "LC1C_09_シマ_テルキ_タイトル";
struct Vector3
{
	float x;
	float y;
	float z;
};

struct Matrix4x4
{
	float m[4][4];
};

//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result{};
	float f = 1.0f / tanf(fovY / 2.0f);
	result.m[0][0] = f / aspectRatio;
	result.m[1][1] = f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	return result;
}
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top,  float right,
	float bottom, float nearClip, float farClip)
{
	Matrix4x4 result{};
	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;
	return result;
}
//3　ビューボート返還行列

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result{};
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height / 2.0f; // Y軸反転
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;
	return result;
}

static const int kRowHeight = 30;
static const int kColuWidth = 80;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y + 20, "%s", label);
	for (int row = 0; row < 4; ++row)
	{
		for (int colum = 0; colum < 4; ++colum)
		{
			Novice::ScreenPrintf(x + colum * kColuWidth, y + 40 + row * kRowHeight, "%6.02f", matrix.m[row][colum]);
		}
	}
}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };








	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 orthographicMatrix = MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
		Matrix4x4 perspectiveFovMatrix = MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f,1000.0f );
		Matrix4x4 viewportMatrix = MakeViewportMatrix(100.0f, 200.0f,600.0f, 300.0f, 0.0f, 1.0f );


			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///

		MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		MatrixScreenPrintf(0, kRowHeight*5, perspectiveFovMatrix, "perspectiveFovMatrix");
		MatrixScreenPrintf(0, kRowHeight*10, viewportMatrix, "viewportMatrix");

	
	

		///
		/// ↑描画処理ここまで
		///



			///
			/// ↑描画処理ここまで
			///

			// フレームの終了
			Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}