#include "DxLib.h"
#include "MATRIX.h"
#include "VECTOR.h"
static int m_Key[256];  // キーの入力状態格納用変数


// KeyCodeのキーの入力状態を取得する
int Keyboard_Get(int KeyCode);
// キーの入力状態更新
void Keyboard_Update();

namespace km{
	//	Matrix4X1型をVector3型に変換
	Vector3 MATRIX_TO_VECTOR3(Matrix4X1 &mat);

	//　Vector3型をMatrix4X1型に変換
	Matrix4X1 VECTOR3_TO_MATRIX(Vector3 &vec);
}