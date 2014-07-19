// ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <tinyxml\tinyxml.h>
#include <tinyxml\tinystr.h>
#include <string>
#include <Include/UtilDir.h>
#include <Include/UtilConvert.h>
#include ".\LeakDiag\LeakDiagParser.h"

using namespace std;

string GetXMLPath()
{
	return (LPCSTR)Util::Convert::UnicodeToGBK(Util::Dir::GetDataDir()) +string( "\\QQ_Leak.xml");
}
bool CreateXmlFile(string& szFileName)
{//����xml�ļ�,szFilePathΪ�ļ������·��,�������ɹ�����true,����false
    try
    {
        //����һ��XML���ĵ�����
        TiXmlDocument *myDocument = new TiXmlDocument();
        //����һ����Ԫ�ز����ӡ�
        TiXmlElement *RootElement = new TiXmlElement("Persons");
        myDocument->LinkEndChild(RootElement);
        //����һ��PersonԪ�ز����ӡ�
        TiXmlElement *PersonElement = new TiXmlElement("Person");
        RootElement->LinkEndChild(PersonElement);
        //����PersonԪ�ص����ԡ�
        PersonElement->SetAttribute("ID", "1");
        //����nameԪ�ء�ageԪ�ز����ӡ�
        TiXmlElement *NameElement = new TiXmlElement("name");
        TiXmlElement *AgeElement = new TiXmlElement("age");
        PersonElement->LinkEndChild(NameElement);
        PersonElement->LinkEndChild(AgeElement);
        //����nameԪ�غ�ageԪ�ص����ݲ����ӡ�
        TiXmlText *NameContent = new TiXmlText("������");
        TiXmlText *AgeContent = new TiXmlText("22");
        NameElement->LinkEndChild(NameContent);
        AgeElement->LinkEndChild(AgeContent);
		CStringA appPath = Util::Convert::UnicodeToGBK(Util::Dir::GetAppDir());
        string seperator = "\\";
        string fullPath = string(appPath.GetBuffer(0)) + seperator + szFileName;
        myDocument->SaveFile(fullPath.c_str());//���浽�ļ�
    }
    catch (string&)
    {
        return false;
    }
    return true;
}

bool ReadXmlFile(string& szFileName)
{//��ȡXml�ļ���������
    try
    {
		CStringA appPath = Util::Convert::UnicodeToGBK(Util::Dir::GetAppDir());
        string seperator = "\\";
        string fullPath = appPath.GetBuffer(0) +seperator+szFileName;
        //����һ��XML���ĵ�����
        TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
        myDocument->LoadFile();
        //��ø�Ԫ�أ���Persons��
        TiXmlElement *RootElement = myDocument->RootElement();
       // �����Ԫ�����ƣ������Persons��
        cout << RootElement->Value() << endl;
        //��õ�һ��Person�ڵ㡣
        TiXmlElement *FirstPerson = RootElement->FirstChildElement();
        //��õ�һ��Person��name�ڵ��age�ڵ��ID���ԡ�
        TiXmlElement *NameElement = FirstPerson->FirstChildElement();
        TiXmlElement *AgeElement = NameElement->NextSiblingElement();
        TiXmlAttribute *IDAttribute = FirstPerson->FirstAttribute();
        //�����һ��Person��name���ݣ��������ǣ�age���ݣ�����ID���ԣ�����
        cout << NameElement->FirstChild()->Value() << endl;
        cout << AgeElement->FirstChild()->Value() << endl;
        cout << IDAttribute->Value()<< endl;
    }
    catch (string& e)
    {
        return false;
    }
    return true;
}
int main()
{
	string fileName = GetXMLPath();
	LeakDiagParser parser;
	parser.Load(fileName);
	cout<<parser.TotalLeak()/1024<<"k"<<endl;
}