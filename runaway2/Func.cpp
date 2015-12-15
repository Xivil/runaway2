#include "Func.h"

// KeyCodeのキーの入力状態を取得する
int Keyboard_Get(int KeyCode){
	return m_Key[KeyCode]; // KeyCodeの入力状態を返す
}

// キーの入力状態更新
void Keyboard_Update(){
	char tmpKey[256];             // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey);  // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++){
		if (tmpKey[i] != 0){ // i番のキーコードに対応するキーが押されていたら
			m_Key[i]++;   // 加算
		}
		else {              // 押されていなければ
			m_Key[i] = 0; // 0にする
		}
	}
}

namespace km{
	Vector3 MATRIX_TO_VECTOR3(Matrix4X1 &mat){
		return GetVector3(mat.index[0], mat.index[1], mat.index[2]);
	}
	Matrix4X1 VECTOR3_TO_MATRIX(Vector3 &vec){
		Matrix4X1 ret;
		ret.index[0] = vec.get_x();
		ret.index[1] = vec.get_y();
		ret.index[2] = vec.get_z();
		ret.index[3] = 1;

		return ret;
	}
}