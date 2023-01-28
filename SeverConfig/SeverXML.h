/*

https://www.w3.org/TR/REC-xml/
.........................................................
这里是自定义简化版
词法分析:
对于值提供转义 \ 后一个特殊标识 < > = \" 空格 会被转成值
<值> id:1  content:char* 
<    id:2  content:null
>	 id:3  content:null
=	 id:4  content:null
"	 id:5  content:null
/	 id:6  content:null
{	 id:7  content:null
}    id:8  content:null
一般分隔'\r' '\n' '\t' '0x20'
状态图
 终态<  > = "  '\r' '\n' '\t' '0x20'
语法分析:
<文档>:={<元素s>}    <元素s>:= <元素s><元素>|><元素>|E   <元素s>:=<元素><T> <T>:= <元素><T>|E
<元素>:=<开始标签><值><结束标签>

<开始标签>:='<'<值> <属性s> '>'
<结束标签>:='<'/<值>'>'
<属性s>:=<属性s><属性>|E

<属性>:=<值>="<值>"
<值>:=char*



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
	bool init(std::string path);						//返回turn正确，false不存在
	bool init();
	int analysis();                                   //返回1正确，返回-1错误
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