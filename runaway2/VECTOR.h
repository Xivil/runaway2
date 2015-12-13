#pragma once
#pragma warning(disable:4244)
#include <math.h>
#include <iostream>
#include "DxLib.h"
#include "Macro.h"
using namespace std;

/*
	ベクトル
	ベクトルとは向きを持った力や速さのこと
	例えば時速100キロメートルといえば単なる大きさだが、
	東に時速100キロメートルといえばそれは向きと大きさを持ったベクトルとなる
	ゲームにおいては原点を基準とした座標で表す事が多い

	ベクトルは足したり引いたり掛けたり割ったり出来る。
	内積と外積というベクトル独特の要素もある。
	足し算と引き算はベクトルの座標の演算をすれば良い
	(1,2,3)と(4,5,6)という2つのベクトルの足し算
	(5,7,9)となる。引き算も同じように計算する
	掛け算と割り算の場合はベクトル同士ではなくベクトルと大きさで計算する
	(1,2,3,)×2＝(2,4,6)というように計算

	内積と外積について解説
	内積は2つのベクトルの要素をそれぞれ掛け、それぞれを足し合わせた物。値は整数となる
	内積の記号は・となる
	例　A(1,2,3)・B(4,5,6)＝1*4+2*5+3*6＝32となる
	内積の値が正か負かで2つのベクトルの角度が90以上がどうかがわかる
	A・B < 0　ならば角度は90度以上
	A・B > 0　ならば角度は90度以下
	A・B = 0　ならば垂直
	となる。

	外積は3次元ベクトルのみに存在する概念で、
*/

/*
	名前空間　namespace nameとすることで名前空間を指定することが出来る
	例えば、
	namespace A{
		void draw();
	}
	とすればdraw()関数は名前空間Aに属する
	このdraw()を使用するには
	A::draw()と記述する。
	名前空間は別のクラスや関数などの混同や衝突を避けるためにある。
*/
namespace km{
	//	3次元ベクトルのクラス
	typedef class Vector3{
	public:
		float x, y, z;		//	座標

		/*
			コンストラクタ
			クラスのオブジェクトを生成した時に必ず実行される関数のこと
		*/
		Vector3(float ex = 0, float why = 0, float zee = 0);

		/*
			コピーコンストラクタ
			コンストラクタを初期化するときにのみ他のオブジェクトの値をコピーするコンストラクタ
			例
			Vector3 a(1, 2, 3);
			Vector3 b = a;

			また、クラスの値渡しをするとき（クラスのポインタ変数や参照変数(*,&)を使用しない引数)に
			その関数を終了するときにデストラクタが呼ばれてしまう。
			この時動的確保した変数があり、それをデストラクタで開放するときはそれらも同時に開放するので
			コピーコンストラクタで複製しておく必要がある。
			コピーコンストラクタは仮引数とした場合にも作用がある
		*/
		/*
			動的確保するポインタ型変数を持つクラスのコピーコンストラクタの例
			単に配列の要素数を確保しているだけのクラスNum
			ポインタ型変数aと個数を表すnum変数を持つ

			class Num{
			public:
				int *a;
				int num;
				Num(int num){
					a = new int[num];
					this->num = num;
				}
				Num(const Num &dst){
					a = new int[num]
				}
				~Num(){
					delete[] a;
				}
			};
		*/
		Vector3(const Vector3 &obj);

		virtual ~Vector3(){};

		//	ゲッターとセッター
		//	クラスの変数は非公開にするのが基本　他のクラスや関数から好き勝手いじられては困るので
		//	メンバ変数を公開するか非公開にするかは保留中　現状ではテストを兼ねているのでとりあえず公開にしている
		inline float get_x() const;
		inline float get_y() const;
		inline float get_z() const;
		inline Vector3 get_all() const;
		void set_x(const float x);
		void set_y(const float y);
		void set_z(const float z);
		void set_all(const Vector3 &a);
		//	代入演算子のオーバーロード
		Vector3& operator = (const Vector3 &v);

		//	ベクトルの大きさの計算
		float getMagnitude() const;

		/*　演算子のオーバーロードとは演算子の処理を自分で定義して実装すること
			記述方法は、
			戻り値 名前 operator 演算子（ 引数 ）{ 処理 }
			となる。
			普通の関数と違うところは関数名を使用しないところにある。
			下記の場合では
			Vector3型変数a = Vector3型変数b * 3.2;
			と記述することでaにbを3,2倍した値が代入される
			いちいち関数の名前を使用せずに演算子で代用するものと考えてもらうとわかりやすい
			
		*/
		//	ベクトルのスカラー倍　スカラー倍とは通常の掛け算のこと
		//	乗算演算子のオーバーロード
		Vector3 operator * (float num) const;
		friend Vector3 operator * (float num, const Vector3 &v);

		//　乗算代入演算子のオーバーロード
		Vector3& operator *= (float num);

		//	ベクトルの加算
		//	加算演算子のオーバーロード
		Vector3 operator+(const Vector3 &P2)const;


		//	加算代入演算子のオーバーロード
		Vector3& operator+=(const Vector3 &P2);

		//	ベクトルの引き算
		//　除算演算子のオーバーロード
		Vector3 operator - (const Vector3 &v) const;

		//	除算代入演算子のオーバーロード
		Vector3& operator -= (const Vector3 &v);

		//ベクトルの正規化
		void Normalize();

		//	2つのベクトルの内積
		float Dot(const Vector3 &v);

		//	2つのベクトルの外積
		Vector3 Cross(const Vector3 &v);

		//　コンソール用の各メンバ変数の表示
		void print();
	}Point3;

	//	内積から角度を計算
	float Scalar(const Vector3 &v1, const Vector3 &v2);

	Vector3 GetVector3(float x, float y, float z);

	VECTOR Vector3ToDxVector(Vector3& a);

}

