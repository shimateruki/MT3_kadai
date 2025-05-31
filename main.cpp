#include <Novice.h>
#include <cmath>
#include <cassert>
#include <corecrt_math.h>
#include<imgui.h>
#include "MatrixUtility.h"

const char kWindowTitle[] = "LC1C_09_シマ_テルキ_タイトル";




float Length(const Vector3& v) {
	
	return sqrtf(v.x * v.x + v.y * v.y+v.z*v.z);
}

bool isCollision(const Sphere& s1, const Sphere& s2)
{
	float distance = Length(s2.center - s1.center);
	if (distance <= s1.radius + s2.radius)
	{
		return true;
	}
	return false;
}



static const int kRowHeight = 30;
static const int kColuWidth = 80;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColuWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColuWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColuWidth * 3, y, "%s", label);
}





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


int kWindowsWidth = 1280;
int kWindowsHeight = 720;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowsWidth, kWindowsHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	MatrixUtility* matrixUtility = new MatrixUtility();
	//カメラ
	Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };
	Vector3 cameraPosition = { 0.0f, 1.0f, 5.0f };

	Sphere sphere[2];
	sphere[0].center = { 0, 0, 0 };
	sphere[0].radius = { 1 };
	sphere[0].color = WHITE;

	sphere[1].center = { 1.5f, 0, 1.5f };
	sphere[1].radius = { 1 };
	sphere[1].color = WHITE;





	

	

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

			//行列の計算

		Matrix4x4 cameraMatrix = matrixUtility-> MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { cameraRotate }, cameraTranslate);
		Matrix4x4 viewMatrix = matrixUtility->Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = matrixUtility-> MakePerspectiveFovMatrix(0.45f, float(kWindowsWidth) / float(kWindowsHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = matrixUtility-> Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = matrixUtility-> MakeViewportMatrix(0, 0, float(kWindowsWidth), float(kWindowsHeight), 0.0f, 1.0f);

		if (isCollision(sphere[0], sphere[1]))
		{
			for (int i = 0; i < 2; i++)
			{
				sphere[i].color = RED;
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				sphere[i].color = WHITE;
			}
		}

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///




		//imGit処理
		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		
		// 1つ目の球体
		ImGui::DragFloat3("Sphere[0] Center", &sphere[0].center.x, 0.01f); 
		ImGui::DragFloat("Sphere[0] Radius", &sphere[0].radius, 0.01f);   

		// 2つ目の球体
		ImGui::DragFloat3("Sphere[1] Center", &sphere[1].center.x, 0.01f); 
		ImGui::DragFloat("Sphere[1] Radius", &sphere[1].radius, 0.01f);   
		ImGui::End();

	

		// --- 描画処理 ---
		matrixUtility ->DrawGrid(viewProjectionMatrix, viewportMatrix);
		for (int i = 0; i < 2; i++)
		{
		
			matrixUtility->DrawSphere(sphere[i], viewProjectionMatrix, viewportMatrix, sphere[i].color); // 赤色

		}
	
	
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