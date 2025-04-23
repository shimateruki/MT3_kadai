#include <Novice.h>
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
//1 平行移動
Matrix4x4 MakeTranslateMatirx(const Vector3& translate)
{
	Matrix4x4 result = {};
	// 単位行列に平行移動成分を加える
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;



	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;
	return result;
};

//2 拡大縮小行列
Matrix4x4 makeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result = {};
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};
//3 座標変換
Vector3 TransForm(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result = {};


	/*result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0]+vector.z*matrix.m;
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1]+vector.z*;
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2]+vector.z*;
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;*/

}

static const int kRowHeight = 30;
static const int kColuWidth = 80;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x , y+20, "%s", label);
	for (int row = 0; row < 4; ++row)
	{
		for (int colum = 0; colum < 4; ++colum)
		{
			Novice::ScreenPrintf(x+ colum* kColuWidth, y+40 + row* kRowHeight, "%6.02f", matrix.m[row][colum]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) 
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x+ kColuWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColuWidth*2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColuWidth * 3, y, "%s", label);
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	Vector3 translate = { 4.1f, 2.6f, 0.8f };
	Vector3 scale = { 1.5f, 5.2f, 7.3f };
	Vector3 point = { 2.3f, 3.8f, 1.4f };
	Matrix4x4 translateMatrix = MakeTranslateMatirx(translate);
	Matrix4x4 scaleMatrix = makeScaleMatrix(scale);
	Matrix4x4 transFormMatrix = {
		1.0f, 2.0f, 3.0f,4.0f,
		3.0f, 1.0f, 1.0f, 2.0f,
		1.0f, 4.0f, 2.0f, 3.0f,
		2.0f, 2.0f, 1.0f, 3.0f

	};
	
	


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
		Vector3 transFormed = TransForm(point, transFormMatrix);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0,0,transFormed, "transformed");
		MatrixScreenPrintf(0,0,translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, scaleMatrix, "scaleMatrix");

	
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
