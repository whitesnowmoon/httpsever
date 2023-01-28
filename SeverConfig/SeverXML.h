/*

https://www.w3.org/TR/REC-xml/
.........................................................
�������Զ���򻯰�
�ʷ�����:
����ֵ�ṩת�� \ ��һ�������ʶ < > = \" �ո� �ᱻת��ֵ
<ֵ> id:1  content:char* 
<    id:2  content:null
>	 id:3  content:null
=	 id:4  content:null
"	 id:5  content:null
/	 id:6  content:null
{	 id:7  content:null
}    id:8  content:null
һ��ָ�'\r' '\n' '\t' '0x20'
״̬ͼ
 ��̬<  > = "  '\r' '\n' '\t' '0x20'
�﷨����:
<�ĵ�>:={<Ԫ��s>}    <Ԫ��s>:= <Ԫ��s><Ԫ��>|><Ԫ��>|E   <Ԫ��s>:=<Ԫ��><T> <T>:= <Ԫ��><T>|E
<Ԫ��>:=<��ʼ��ǩ><ֵ><������ǩ>

<��ʼ��ǩ>:='<'<ֵ> <����s> '>'
<������ǩ>:='<'/<ֵ>'>'
<����s>:=<����s><����>|E

<����>:=<ֵ>="<ֵ>"
<ֵ>:=char*



*/

#ifndef SEVERXML_H
#define SEVERXML_H

#include<fstream>
#include<iostream>
#include<map>
#include<vector>


class SeverXML
{
public:
	typedef struct imformation_
	{
		std::string tagname;
		std::vector<std::pair<std::string, std::string>> attributes;
		std::string ID;
	}imformation;
	SeverXML(std::string path);
	SeverXML();
	bool init(std::string path);						//����turn��ȷ��false������
	bool init();
	int analysis();                                   //����1��ȷ������-1����
	std::vector<imformation> getImformation();
	void printimformation();
	~SeverXML();

private:
	std::string path;
	class Element
	{
	public:
		std::string tagName;
		std::map<std::string, std::string> attrbute;
		std::string id;
	};
	enum class TokenForm
	{
		ID = 1,
		LeftAngleBracket,
		RightAngleBracket,
		Equal,
		Quotation,
		Slash,
		LeftSquareBrackets,
		RightSquareBrackets
	};
	std::vector<imformation>  imformations;
	std::pair<SeverXML::TokenForm, std::string> curtoken;
	imformation cur;
	int document();
	int element();
	int starttag();
	int endtag();
	int attr();
	int getid();
	std::pair<TokenForm, std::string> gettoken(int stauts);
	std::fstream file;
};

#endif // !SEVERXML_H