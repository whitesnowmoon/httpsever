#include "SeverConfig.h"
#include "SeverXML.h"
#include "../SeverError/SeverError.h"

std::vector<SocketHandle> SeverConfig::listenHandles;
std::vector<std::pair<std::string, std::string>>  SeverConfig::staticheader;
std::string  SeverConfig::CApath;
std::string  SeverConfig::password;
std::string  SeverConfig::srcrootpath;
std::string SeverConfig::CAkey;
std::string SeverConfig::openfile;
bool SeverConfig::init(std::string configpath) {
    SeverXML XML;
    if (!XML.init(configpath)) {
        SeverError::PushError(SEVERERRORCODE::SEVERCONFIGFILEPATHNOTEXIST);
        return false;
    }
    if (XML.analysis() == -1) {
        SeverError::PushError(SEVERERRORCODE::SEVERCONFIGFILEFORMERROR);
        return false;
    }
    std::vector<SeverXML::imformation> imformations = XML.getImformation();


    for (auto field = imformations.begin(); field != imformations.end(); field++)
    {
        if (field->tagname == "connect") {
            APPICANTION_LAYER_TYPE temp;
            if (field->attributes[2].second == "_HTTPS_")
                temp = APPICANTION_LAYER_TYPE::_HTTPS_;
            else if (field->attributes[2].second == "_HTTP_")
                temp = APPICANTION_LAYER_TYPE::_HTTP_;
            else if (field->attributes[2].second == "_ORIGIN_")
                temp = APPICANTION_LAYER_TYPE::_ORIGIN_;
            else
            {
                SeverError::PushError(SEVERERRORCODE::SEVERCONFIGFILEATTRNOTEXIST);
                return false;
            }
            SeverConfig::listenHandles.emplace_back(field->attributes[0].second, \
                std::atoi(field->attributes[1].second.c_str()), \
                SEVER_SOCKET_ERROR, temp);
        }     
        if (field->tagname == "header") {
            if (field->attributes[0].second == "*") {
                SeverConfig::staticheader.emplace_back(field->attributes[1].first, field->attributes[1].second);
            }
        }
        if (field->tagname == "srcrootpath") {
            SeverConfig::srcrootpath = field->ID;
        }
        if (field->tagname == "openfile") {
            SeverConfig::openfile = field->ID;
        }

        if (field->tagname == "CA") {
            SeverConfig::CApath = field->attributes[0].second;
            SeverConfig::CAkey = field->attributes[1].second;
            SeverConfig::password =field->ID;
        }                    //只做了初步判断
    }
    return true;
}


