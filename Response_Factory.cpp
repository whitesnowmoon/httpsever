#include "Response_Factory.h"

Response* Response_Factory::CreatResponse(module_name name, SeverRequest* request) {
	if (module_name::GET == name) {
		Response*p= new Get_SeverResponse(request, request->sock);
		return  p;
	}

}
