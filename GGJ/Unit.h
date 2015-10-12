#pragma once
#include <memory>
#include <string>

//継承先で色々設定する
class Unit{

protected:

	Unit():sizeX_(0),sizeY_(0){};
	virtual ~Unit(){};

	//描写
	virtual void render() = 0;
	//更新処理
	virtual void updata(bool through){};
	
	virtual void updata(int through){};

	//画像読み込み用メソッド
	//ファイル名/配列/縦数/横数
	void loadGh(const std::string& ghName,int* gh,const int ghx,const int ghy,const int index);



protected:

	//画像サイズ格納
	int sizeX_,sizeY_;

};