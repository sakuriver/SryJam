//#include "ReadFileData.h"
//#include <fstream>
//
//using namespace std;
//
////�����ł̓t�@�C���ǂݍ��݂����Ă���
////�Q�lURL�Fhttp://d.hatena.ne.jp/osyo-manga/20090907/1252329868
//void ReadFileData::read(vector<char> &buffer, const char* filename){
//
//	ifstream in( filename );
//	if(!in){
//
//	}else{
//		buffer.resize(in.seekg(0,ifstream::end).tellg());
//		in.seekg(0,ifstream::beg).read(&buffer[0],
//			static_cast<streamsize>(buffer.size()) );
//	}
//}