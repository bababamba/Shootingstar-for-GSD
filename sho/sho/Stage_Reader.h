#include "rapidjson/document.h";
#include <iostream>
#include <fstream>
#include <string>
#pragma once
using namespace std;
using namespace rapidjson;

//파일 경로, Document 참조형을 매개변수로 받으면 그 파일 경로에 있는 json 파일을 읽어서 인자로 받은 Document 주소에 저장해준다
//Manager에서 이 함수를 실행해 자기 Document에 저장해놓고, 그걸 읽어서 enemy를 생성한다
void file_parse(string path, Document* tar_doc) { 
	ifstream file_in(path);
	string temp1; string temp2;
	if( !file_in ) { 
		cout << "json document generate error\n";
		return;
	} else { 
		while( !file_in.eof() ) {
			getline(file_in,temp2);
			temp1 += temp2;
		}
		//cout << const_cast<char*>(temp1.c_str()) << endl;
		tar_doc->Parse(const_cast<char*>(temp1.c_str()));
		//cout << "json error code : "<<tar_doc->GetParseError()<<endl;
		//cout << "parse sucs\n";
		return;
	}
}


