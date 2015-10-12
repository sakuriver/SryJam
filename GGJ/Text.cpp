#include "DxLib.h"
#include "Text.h"
#include <string.h>
#define BLACK GetColor(0,0,0)

Text::Text(){
	chara_pic[0][0] = LoadGraph("Resources/Chara/YOU_NORMAL.png");
	chara_pic[0][1] = LoadGraph("Resources/Chara/YOU_EGAO.png");
	chara_pic[0][2] = LoadGraph("Resources/Chara/YOU_ODOROKI.png");
	chara_pic[0][3] = LoadGraph("Resources/Chara/YOU_NAKI.png");
	chara_pic[0][4] = LoadGraph("Resources/Chara/YOU_KONWAKU.png");
	chara_pic[0][5] = LoadGraph("Resources/Chara/YOU_KIZETU.png");

	chara_pic[1][0] = LoadGraph("Resources/Chara/W_PIERO_NORMAL.png");
	chara_pic[1][1] = LoadGraph("Resources/Chara/W_PIERO_WARAI.png");
	chara_pic[1][2] = LoadGraph("Resources/Chara/W_PIERO_ODOROKI.png");
	chara_pic[1][3] = LoadGraph("Resources/Chara/W_PIERO_MUKANZYO.png");
	chara_pic[1][4] = LoadGraph("Resources/Chara/W_PIERO_FUMAN.png");
	chara_pic[1][5] = LoadGraph("Resources/Chara/W_PIERO_ASERI.png");
	chara_pic[1][6] = LoadGraph("Resources/Chara/W_PIERO_IKARI.png");

	chara_pic[2][0] = LoadGraph("Resources/Chara/M_PIERO_NORMAL.png");
	chara_pic[2][1] = LoadGraph("Resources/Chara/M_PIERO_WARAI.png");
	chara_pic[2][2] = LoadGraph("Resources/Chara/M_PIERO_TAKAWARAI.png");
	chara_pic[2][3] = LoadGraph("Resources/Chara/M_PIERO_NAYAMI.png");
	chara_pic[2][4] = LoadGraph("Resources/Chara/M_PIERO_IKARI.png");

	m_window = LoadGraph("Resources/text/Message_window.png");
	
	Eventpic[1] = LoadGraph("Resources/text/merry_1.png");
	Eventpic[2] = LoadGraph("Resources/text/merry_2.png");
	Eventpic[3] = LoadGraph("Resources/text/merry_3.png");
	Eventpic[4] = LoadGraph("Resources/text/merry_4.png");
	Eventpic[5] = LoadGraph("Resources/data/Ferriswheel_1.png");
	Eventpic[6] = LoadGraph("Resources/data/Ferriswheel_2.png");
	mode=0;
	txtcount=0;
	n=0;
	picframe =1;
	for(int i=0;i<66;i++){
		string_a[i]='\0';
		string_b[i]='\0';
	}
	for(int i=0;i<11;i++){chara[i]='\0';}
	c[0]='\0';
	c[1]='\0';
	c[2]='\0';

}
int Text::txtMain(int scene)
{
	my_scene=scene;
	switch(mode){
	case 0:	txtLoad();	break;
	case 1:	
		if(txtcount%3==0)txtCheck();
			txtKey();
		if(CheckHitKey(KEY_INPUT_ESCAPE )==ON){
				txtreset();
				mode = 2;
				break;
		}
		txtDrawpic();
		txtDraw();
		txtcount++;
		break;
	case 2:
		mode = 0;
		txtcount=0;
		return -1;
		break;
	}
	return 0;
}
void Text::txtLoad()
{
	switch(my_scene){
	case prologue:		fp = FileRead_open("Resources/text/prologue.txt");		break;//ファイル読み込み
	case mirror_text:	fp = FileRead_open("Resources/text/mirror_text.txt");	break;
	case mirror_door:	fp = FileRead_open("Resources/text/mirror_door.txt");	break;
	case hospital_text:	fp = FileRead_open("Resources/text/hospital_text.txt"); break;
	case gocart_text:	fp = FileRead_open("Resources/text/gocart_text.txt");	break;
	case merry_text:	fp = FileRead_open("Resources/text/merry_text.txt");	break;
	case merry_mobA:	fp = FileRead_open("Resources/text/merry_mobA.txt");	break;
	case merry_mobB:	fp = FileRead_open("Resources/text/merry_mobB.txt");	break;
	case merry_mobC:	fp = FileRead_open("Resources/text/merry_mobC.txt");	break;
	case merry_mobD:	fp = FileRead_open("Resources/text/merry_mobD.txt");	break;
	case merry_mobE:	fp = FileRead_open("Resources/text/merry_mobE.txt");	break;
	case merry_mobF:	fp = FileRead_open("Resources/text/merry_mobF.txt");	break;
	case merry_pierrot:	fp = FileRead_open("Resources/text/merry_pierrot.txt"); break;
	case merry_bad:		fp = FileRead_open("Resources/text/merry_bad.txt");		break;
	case merry_good:	fp = FileRead_open("Resources/text/merry_good.txt");	break;
	case ferriswheel_a:	fp = FileRead_open("Resources/text/ferriswheel_a.txt");	break;
	case ferriswheel_b:	fp = FileRead_open("Resources/text/ferriswheel_b.txt");	break;
	case epilogue:		fp = FileRead_open("Resources/text/epilogue.txt");		break;
	}
	mode=1;
}
void Text::txtCheck(){
	switch(n){
	case 0:												//キャラ情報取得
		while(!n){
			c[0] = FileRead_getc( fp ) ;				//半角取得
			c[1] = FileRead_getc( fp ) ;				//半角取得　合わせて全角1文字
			switch(c[0]){								//picflag[0]はキャラの種類、[1]は表情
			case 'M':picflag[0]=0;picflag[1]=c[1]-'0';	break;//主人公
			case 'G':picflag[0]=1;picflag[1]=c[1]-'0';	break;//女ピエロ
			case 'B':picflag[0]=2;picflag[1]=c[1]-'0';	break;//男ピエロ
			case 'L':window_LR=left;					break;//Lなら左側に描写
			case 'R':window_LR=right;					break;//Rなら右側に描写
			case 'N':window_LR=2;						break;//立ち絵無しキャラ
			}
			if(c[0]=='\x0A'||c[1]=='\x0A')n=1;			//改行があったらテキスト1行目へ
		}
		break;
	case 1:												//テキスト1行目
		c[0] = FileRead_getc( fp ) ;					//半角取得
		c[1] = FileRead_getc( fp ) ;					//半角取得　合わせて全角1文字
		if(c[0]=='\x0A'||c[1]=='\x0A')n=2;				//改行があったらテキスト2行目へ
		else strcat( string_a, c-'\0' );				//なければ文字を結合
		break;
	case 2:												//テキスト2行目
		c[0] = FileRead_getc( fp ) ;					//半角取得
		c[1] = FileRead_getc( fp ) ;					//半角取得　合わせて全角1文字
		if(c[0]=='\x0A'||c[1]=='\x0A')n=3;				//改行があったら次のセリフへ
		else if(c[0]=='e'&&c[1]=='d')n=4;				//edとついていたらテキスト終了
		else strcat( string_b, c );						//なければ文字を結合
		break;
	}
}
void Text::txtDraw()
{	
	if(window_LR==left){												//
		SetDrawBright( 255, 255, 255) ;
		DrawTurnGraph(0,0,chara_pic[picflag[0]][picflag[1]],true);
	}else if(window_LR==right){
		SetDrawBright( 255, 255, 255) ;
		DrawGraph(300,0,chara_pic[picflag[0]][picflag[1]],true);
	}
	DrawGraph(0,270,m_window,true);
	textset[0] = strlen(string_a)/2;
	textset[1] = strlen(string_b)/2;
	DrawString(85+9*(28-textset[0]),370,string_a,GetColor(255,255,255),TRUE);//
	DrawString(85+9*(28-textset[1]),395,string_b,GetColor(255,255,255),TRUE);//
}
void Text::txtDrawpic(){		//専用背景が存在する場合
	switch(my_scene){
	case 1:	
		break;
	case 2:	
		break;
	case 3:
		break;
	case merry_text:
		DrawGraph(0,0,Eventpic[picframe],true);
		picframe = pic.animationIs(4,0.5,false)+1;
		break;
	case ferriswheel_a:
		DrawGraph(0,0,Eventpic[5],true);
		break;
	case ferriswheel_b:
		DrawGraph(0,0,Eventpic[6],true);
		break;
	case merry_pierrot:
		break;
	}
}
void Text::txtKey(){
	if(CheckHitKey(KEY_INPUT_X )==ON||CheckHitKey(KEY_INPUT_Z)==ON||CheckHitKey(KEY_INPUT_RETURN )==ON){
		if(key_flag[0]==OFF){
			key_flag[0]=ON;
			if(n==4){				//テキストの
				txtreset();
				mode=2;
				FileRead_close( fp ) ;
			}else if(n==3){			//
				txtreset();
			}else{
				while(n<3)
					txtCheck();
			}
		}
	}else key_flag[0]=OFF;	
}
void Text::txtreset(){
	string_a[0]='\0';
	string_b[0]='\0';
	chara[0]='\0';
	n=0;
	txtcount=0;
}