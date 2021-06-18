#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "upload-api/responses/response_200.h"
#include "upload-api/routes/status.h"

namespace pt = boost::property_tree;

boost::beast::http::response<boost::beast::http::string_body> Status(const boost::beast::http::request<boost::beast::http::dynamic_body>& req)
{
	pt::ptree root;
	pt::ptree fruits_node;

	pt::ptree apple_node;
	apple_node.put("", "apple");
	fruits_node.push_back(std::make_pair("", apple_node));
	pt::ptree orange_node;
	orange_node.put("", "orange");
	fruits_node.push_back(std::make_pair("", orange_node));

	root.add_child("fruits", fruits_node);

	std::ostringstream oss;
	boost::property_tree::json_parser::write_json(oss, root);

	return make_200<boost::beast::http::string_body>(req, oss.str(), "text/html");;
}
