#include <string.h>

// geos 
#include <geos/geom/PrecisionModel.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Geometry.h>
#include <geos/geom/Point.h>
#include <geos/io/WKTReader.h>

// boost 
#include <boost/algorithm/string.hpp>

//constants 
#define OSM_ID 0
#define OSM_TILEID 1
#define OSM_OID 2
#define OSM_ZORDER 3
#define OSM_POLYGON 4

using namespace std;
using namespace geos;
using namespace geos::io;
using namespace geos::geom;

/*reads in the OSM data and generates MBB for spatial objects.*/

int main(int argc, char** argv)
{
    char * tag = NULL;
    if (argc>1)
    {
        tag= argv[1];
    }

    GeometryFactory *gf = new GeometryFactory(new PrecisionModel(),4326);
    WKTReader *wkt_reader= new WKTReader(gf);
    Geometry *poly ; 
    string DEL = " ";
    vector<string> fields;
    double low[2], high[2];
    string input_line ;
    while(cin && getline(cin, input_line) && !cin.eof())
    {
        boost::split(fields, input_line, boost::is_any_of("|"));
        poly = wkt_reader->read(fields[OSM_POLYGON]);
        const Envelope * env = poly->getEnvelopeInternal();
        low [0] = env->getMinX();
        low [1] = env->getMinY();
        high [0] = env->getMaxX();
        high [1] = env->getMaxY();
        cout << fields[OSM_ID] << DEL ;
        if (NULL != tag )  cout << tag << DEL ;
        cout << low[0] << DEL << low[1] << DEL << high[0] << DEL << high[1] << endl;
        fields.clear();
    }
    cout.flush();
    return 0;
}
