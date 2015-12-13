#include "DxLib.h"

static int m_Key[256];  // キーの入力状態格納用変数


// KeyCodeのキーの入力状態を取得する
int Keyboard_Get(int KeyCode);
// キーの入力状態更新
void Keyboard_Update();