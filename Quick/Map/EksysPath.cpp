#include "stdafx.h"
#include "EksysPath.h"
#include <math.h>
#include <algorithm>
#include <wininet.h>
#include "afxinet.h"
#include <string.h>

/*
RouteType : 
"Optimal", 	    "최적"
"Shortest",     "최단"
"Custom", 	    "특정"
"CommonRoad", 	"일반도로"
"HighWayRoad", 	"고속도로"
"TollFree", 	"고속도로"


. 옵션 
- WantShape: Shape Pos 정보(0: 사용안함 / 1: 사용)
- WantName: 교차로명(0: 사용안함 / 1: 사용) >> 현재 지원하지 않는 옵션입니다. 

2. 결과값
2.1. ResultCode 
- 0000  // 정상
- 1000  // 초기화 필요함 (결과를 넘길 수 없음)
- 2000  // 알수 없는 요청 타입
- 3000 // 경로를 생성할 수 없습니다.
- 4000  // 부정확한 요청 Parameters

2.2. PostList 받지않는 옵션
- WantShape 옵션을 0으로 설정하면 됩니다. 

3. 경유지 포함 경로탐색 
- TR_8002 옵션으로 경로탐색을 진행합니다. 
- 서버소스 및 Java 샘플을 첨부합니다. 서버소스는 이전 설치되어 있는 서버에 덮어쓰기하세요. 
*/


CEksysPath::CEksysPath(bool only_distance, CString coord_system, CString route_type)
{
	is_parse_ = false;
	is_only_distance_ = only_distance;	
	coord_system_ = coord_system;
	route_type_ = route_type;
}

void CEksysPath::AddPos(int start_pos_x, int end_posy_y)
{
	pos_vector_.push_back(CPoint(start_pos_x, end_posy_y));
}

int CEksysPath::GetRouteDistance(int index)
{
	int distance = 0;
	Json::Value jsonBody;
	CString temp; temp.Format("%d", index);

	if (GetBodyJson(jsonBody)) {

		Json::ValueIterator it = jsonBody.begin();

		while (it != jsonBody.end()) {

			if (temp == (*it)["ID"].asCString())
				return (*it)["Distance"].asInt();

			distance += (*it)["Distance"].asInt();
			it++;
		}
	}

	return distance;
}


int CEksysPath::GetRouteDistance(std::vector<CPoint>& vec)
{
	if (is_only_distance_)
		return 0;

	int distance = 0;
	Json::Value jsonBody;

	if (GetBodyJson(jsonBody)) {
		for (int i = 0; i < (int)pos_vector_.size() - 1; i++) {
			for (int j = 0; j < (int)jsonBody.size(); j++) {
				Json::Value data = jsonBody[j];

				if (atoi(data["ID"].asCString()) == i) {
					distance += data["Distance"].asInt();
					Json::Value pos_list = data["PosList"];
					Json::ValueIterator it = pos_list.begin();

					while (it != pos_list.end()) {
						vec.push_back(CPoint((int)((*it)["X"].asFloat() * 1000000), (int)((*it)["Y"].asFloat() * 1000000)));
						it++;
					}

					break;
				}				
			}
		}
	}

	return distance;
}

bool CEksysPath::GetBodyJson(Json::Value& value)
{
	if (!ParseJson())
		return false;

	if (!json_root_)						   return false;
	if (!json_root_["ResultCode"])			   return false;
	if (json_root_["ResultCode"].asInt() != 0) return false;
	if (!json_root_["ResultList"])		 	   return false;
	if (json_root_["ResultList"].size() == 0)  return false;
	if (!json_root_["ResultList"][0])	 	   return false;
	if (json_root_["ResultList"][0]["ResultCode"].asInt() != 0)  return false;

	value = json_root_["ResultList"];
	return true;
}

bool CEksysPath::ParseJson()
{
	if (is_parse_)
		return true;

	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	JSONCPP_STRING errs;

	CString post_data = GetPostData();
	CString result = RouteStart(post_data);
	char* text = (char*)((LPCSTR)result);
	bool ok = reader->parse(text, text + std::strlen(text), &json_root_, &errs);

	is_parse_ = (ok && errs.size() == 0);

	delete reader;
	return is_parse_;
}

CString CEksysPath::GetPostData()
{
	Json::Value root;
	root["TRType"] = "TR_8001";
	root["IsDebug"] = 0;

	Json::Value option;
	option["CoordSystem"] = std::string(coord_system_);
	option["RouteType"] = std::string(route_type_);
	option["WantShape"] = is_only_distance_ ? 0 : 2;
	option["WantName"] = 0;
	root["Option"] = option;

	Json::Value list_array;

	int index = 0;	

	for (index = 0; index < (int)pos_vector_.size() - 1; index++) {
		Json::Value list;
		CString id; 
		id.Format("%d", index);
		list["ID"] = std::string(id);

		CPoint start_point = pos_vector_.at(index);
		CPoint end_point = pos_vector_.at(index + 1);

		Json::Value org;
		//path_start["SeqID"] = 0;
		org["Lon"] = start_point.x * 0.000001;
		org["Lat"] = start_point.y * 0.000001;
		org["Angle"] = -1;
		org["Both"] = -1;
		org["WidePos"] = -1;
		list["Org"] = org;

		Json::Value dst;
		//path_dest["SeqID"] = 1;
		dst["Lon"] = end_point.x * 0.000001;
		dst["Lat"] = end_point.y * 0.000001;
		dst["Angle"] = -1;
		dst["Both"] = -1;
		dst["WidePos"] = -1;

		list["Dst"] = dst;

		list_array.append(list);
	}

	root["List"] = list_array;
	
	/*
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "";
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	std::ostringstream os;
	writer->write(root, &os);
	std::string str = os.str();
	*/

	Json::StyledWriter writer;
	std::string str = writer.write(root);

	return "TRID=TR_8001&REQ=" + CString(str.c_str());
}

CString CEksysPath::RouteStart(CString post_data)
{
	CString strJson;
		
	HINTERNET hSession = InternetOpen("CEksysPath", PRE_CONFIG_INTERNET_ACCESS, NULL, NULL, 0);
	//HINTERNET hConnect = InternetConnect(hSession, "211.172.242.189", 8088, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	HINTERNET hConnect = InternetConnect(hSession, "121.254.252.25", 8089, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	HINTERNET hHttpFile = HttpOpenRequest(hConnect, "POST", "WiseRP/RPService", HTTP_VERSION, NULL, NULL, INTERNET_FLAG_DONT_CACHE, 0);

	char szPostData[2048] = { 0 };
	lstrcpy(szPostData, post_data);


	if (::HttpSendRequest(hHttpFile, "Content-type: application/x-www-form-urlencoded;charset=utf8\r\n", -1, szPostData, lstrlen(szPostData))) {
		char buffer[1025];
		DWORD dwReadByte = 0, dwErrorCount = 0;

		while (::InternetReadFile(hHttpFile, buffer, 1024, &dwReadByte)) {
			buffer[dwReadByte] = 0;
			strJson += buffer;

			if (dwReadByte < 1024) {
				dwErrorCount++;
				if (dwErrorCount > 10) break;
			}
			else dwErrorCount = 0;
		}

		::InternetCloseHandle(hHttpFile);
	}
	::InternetCloseHandle(hConnect);
	::InternetCloseHandle(hSession);

	return strJson;
}
