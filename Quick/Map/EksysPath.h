#pragma once

#include "json.h"

class CEksysPath
{
public:
	CEksysPath(bool only_distance = true, CString coord_system = "WGS84", CString route_type = "Optimal");
		
public:
	bool is_parse_;
	bool is_only_distance_;
	CString coord_system_;
	CString route_type_;

	Json::Value json_root_;
	std::vector<CPoint> pos_vector_;
	int GetRouteDistance(int index = -1);
	int GetRouteDistance(std::vector<CPoint>& vec);
	bool GetBodyJson(Json::Value& value);
	bool ParseJson();
	void SetRouteType(CString route_type) { route_type_ = route_type; };
	void AddPos(int start_pos_x, int end_posy_y);
	CString GetPostData();
	CString RouteStart(CString post_data);
};

