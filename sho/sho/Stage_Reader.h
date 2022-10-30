#include "rapidjson/document.h";
#include <iostream>
#include <fstream>
#include <string>
#pragma once
using namespace std;
using namespace rapidjson;

//���� ���, Document �������� �Ű������� ������ �� ���� ��ο� �ִ� json ������ �о ���ڷ� ���� Document �ּҿ� �������ش�
//Manager���� �� �Լ��� ������ �ڱ� Document�� �����س���, �װ� �о enemy�� �����Ѵ�
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


