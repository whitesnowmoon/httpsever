#include "SeverXML.h"

SeverXML::SeverXML(std::string path): path(path){
}

SeverXML::SeverXML() {
}

bool SeverXML::init(std::string path) {
	this->path = path;
	file.open(path.c_str(), std::ios_base::in | std::ios_base::binary);
	if (!file.is_open()) {
		std::cout << path << "configfile can not open\n";
		return false;
	}
	return true;
}

bool SeverXML::init() {
	file.open(path.c_str(), std::ios_base::in | std::ios_base::binary);
	if (!file.is_open()) {
		std::cout << path << "configfile can not open\n";
		return false; 
	}
	return true;
}

SeverXML::~SeverXML() {
	if (file.is_open()) {
		file.close();
	}
}

int SeverXML::analysis() {
	return document();
}

std::vector<SeverXML::imformation> SeverXML::getImformation() {
	return this->imformations;
}

void SeverXML::printimformation() {
	for (auto i : this->imformations)
	{
		std::cout << "[name]:" << i.tagname << "=" << i.ID << "\n";
		std::cout << "[field]:\n";
		for (auto var : i.attributes)
		{
			std::cout << "         " << var.first << ":" << var.second << "\n";;
		}
	}
}

int SeverXML::document() {
	curtoken = gettoken(0);
	if (curtoken.first == SeverXML::TokenForm::LeftSquareBrackets) {
		while (true)
		{
			curtoken = gettoken(0);
			if (curtoken.first == SeverXML::TokenForm::RightSquareBrackets) {
				std::cout << "configfile load document success\n";
				return 1;
			}
			if (element() == -1) {
				std::cout << "configfile element error\n";
				return -1;
			}

		}
		
	}
	else
	{
		return -1;
	}
}

int SeverXML::element() {
	if (starttag()==-1) {
		std::cout << "configfile starttag error\n";
		return -1;
	}
	curtoken = gettoken(1);
	getid();
	cur.ID = curtoken.second;
	curtoken = gettoken(0);
	if (endtag() == -1) {
		std::cout << "configfile endtag error\n";
		return -1;
	}
	imformations.push_back(this->cur);
	this->cur.attributes.clear();
	this->cur.ID.clear();
	this->cur.tagname.clear();
	return 1;
}

int SeverXML::starttag() {
	if (curtoken.first == SeverXML::TokenForm::LeftAngleBracket) {
			curtoken = gettoken(0);
		if (curtoken.first == SeverXML::TokenForm::ID){
			if (getid() == 1) {
				cur.tagname = curtoken.second;
			}
			curtoken = gettoken(0);
			while (curtoken.first!= SeverXML::TokenForm::RightAngleBracket)
			{
				if (attr() == -1) {
					std::cout << "configfile attr error\n";
					return -1;
				}
				curtoken = gettoken(0);
			}
			if (curtoken.first == SeverXML::TokenForm::RightAngleBracket) {
				return 1;
			}else{
				std::cout << "configfile RightAngleBracket\n";
				return -1;
			}
		}else{
			return -1;
		}
	}else{
		std::cout << "configfile lack LeftAngleBracket\n";
		return -1;
	}
	return 0;
}

int SeverXML::endtag() {
	if (curtoken.first == SeverXML::TokenForm::LeftAngleBracket) {
		curtoken = gettoken(0);
		if (curtoken.first == SeverXML::TokenForm::Slash) {
			curtoken = gettoken(0);
			if (getid() == 1) {
				if (cur.tagname != curtoken.second) {
					std::cout << "configfile tagname consistent error\n";
					return -1;
				}
			}
			curtoken = gettoken(0);
			if (curtoken.first == SeverXML::TokenForm::RightAngleBracket) {
				return 1;
			}else{
				return -1;
				std::cout << "configfile RightAngleBracket\n";
			}
		}else{
			std::cout << "configfile lack Slash\n";
			return -1;
		}
	}else{
		std::cout << "configfile lack LeftAngleBracket\n";
		return -1;
	}
}


int SeverXML::attr() {
	std::pair<std::string, std::string> attribute;
	getid();
	attribute.first = curtoken.second;
	curtoken = gettoken(0);
	if (curtoken.first == SeverXML::TokenForm::Equal) {
		curtoken = gettoken(0);
		if (curtoken.first == SeverXML::TokenForm::Quotation) {
			curtoken = gettoken(2);
			getid();
			attribute.second = curtoken.second;
			this->cur.attributes.push_back(attribute);
			curtoken = gettoken(0);
			if (curtoken.first == SeverXML::TokenForm::Quotation) {
				return 1;
			}else{
				return -1;
				std::cout << "configfile right lack Quotation\n";
			}
		}else{
			std::cout << "configfile Left lack Quotation\n";
		}
	}else{
		std::cout << "configfile lack Equal\n";
	}
	return 0;
}

int SeverXML::getid() {
	if (curtoken.first == SeverXML::TokenForm::ID) {
		return 1;
	}
	else
	{
		std::cout << "configfile lack id\n";
		return -1;
	}
}

std::pair<SeverXML::TokenForm, std::string> SeverXML::gettoken(int stauts) {		//此处写法有问题，集中一起写了分0，1，2，要分开
	char character=0;
	std::pair<SeverXML::TokenForm, std::string> token;
	file.read(&character, sizeof(character));
	if(stauts==0)
	while (character == '\r' || character == '\n' || character == ' ' || character == '\t')
	{
		file.read(&character, sizeof(character));
	}
	if (character=='=') {
		token.second.push_back('=');
		token.first = SeverXML::TokenForm::Equal;
		return token;
	}
	else if (character == '<') {
		token.second.push_back('<');
		token.first = SeverXML::TokenForm::LeftAngleBracket;
		return token;
	}
	else if (character == '>') {
		token.second.push_back('>');
		token.first = SeverXML::TokenForm::RightAngleBracket;
		return token;
	}
	else if (character == '/') {
		token.first = SeverXML::TokenForm::Slash;
		token.second.push_back('/');
		return token;
	}
	else if (character == '"') {
		token.first = SeverXML::TokenForm::Quotation;
		token.second.push_back('"');
		return token;
	}
	else if (character == '{') {
		token.first = SeverXML::TokenForm::LeftSquareBrackets;
		token.second.push_back('{');
		return token;
	}
	else if (character == '}') {
		token.first = SeverXML::TokenForm::RightSquareBrackets;
		token.second.push_back('}');
		return token;
	}
	else{		
		if (stauts == 0) {
			while (character != '=' && character != '<' && character != '>'\
				&& character != '/' && character != '"' && character != ' '\
				&& character != '\r' && character != '\n' && character != '\t')\
			{
				if (character == '\\') {
					file.read(&character, sizeof(character));
				}
				token.second.push_back(character);
				if (!file.read(&character, sizeof(character)).gcount()) {
					token.first = SeverXML::TokenForm::ID;
					return token;
				}
			}
			token.first = SeverXML::TokenForm::ID;
			file.seekp(-1, std::ios_base::cur);
			return token;
		}
		else if (stauts == 2) {
			while (stauts == 2 && character != '"')\
			{
				if (character == '\\') {
					file.read(&character, sizeof(character));
					token.second.push_back(character);
				}
				else
				{
					token.second.push_back(character);
				}
				if (!file.read(&character, sizeof(character)).gcount()) {
					token.first = SeverXML::TokenForm::ID;
					return token;
				}
			}
			token.first = SeverXML::TokenForm::ID;
			file.seekp(-1, std::ios_base::cur);
			return token;
		}
		else
		{
			while (stauts == 1 && character != '<')\
			{
				if (character == '\\') {
					file.read(&character, sizeof(character));
					token.second.push_back(character);
				}
				else
				{
					token.second.push_back(character);
				}
				if (!file.read(&character, sizeof(character)).gcount()) {
					token.first = SeverXML::TokenForm::ID;
					return token;
				}
			}
			token.first = SeverXML::TokenForm::ID;
			file.seekp(-1, std::ios_base::cur);
			return token;
		}
	}

}
