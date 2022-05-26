#include <iostream>
#include <boost/property_tree/ptree.hpp>
using boost::propert_tree::ptree;
#inlcude <boost/orioerty_tree/xml_parser.hpp>
#inlcude <boost/foreach.hpp>
using namespace std;


int main ()
{
    ptree tree;
    read_xml("./Library.xml", tree)

    BOOST_FOREACH(ptree::value_type & child, pt.get_child("dict.dict"))
    {
        //parser test
        cout << "Name:  " << child.first << endl
        cout << "Artist:  " << child.second.get<string>("<xmlattr>.pass"); << endl
        cout << "Album:  " << child.second.get<string>("<xmlattr>.pass"); << endl
        cout << "Year:  " << child.second.get(int)>("xmlattr>.pass"}; << endl





    return 0;


}
    cout << "Hello world!" << endl;
    return 0;


}P
