/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create paged LOD nodes
*/

#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/PagedLOD>
#include <osgViewer/Viewer>

osg::Geode* createBox( const osg::Vec3& center, float width )
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(
        new osg::ShapeDrawable(new osg::Box(center, width)) );
    return geode.release();
}

osg::Group* createPagedLOD( int row, int col )
{
    osg::ref_ptr<osg::Group> root = new osg::Group;
    char buffer[5] = "";
    for ( int i=0; i<row; i++ )
    {
        for ( int j=0; j<col; j++ )
        {
            std::string filename = "house.ive.";
#ifdef _WIN32
			_itoa_s( i*10, buffer, 5, 10 );
            filename += buffer; filename += ",";
            _itoa_s( j*10, buffer, 5, 10 );
            filename += buffer; filename += ",0.trans";
#else
			gcvt( i*10, 5, buffer );
            filename += buffer; filename += ",";
			gcvt( j*10, 5, buffer );
            filename += buffer; filename += ",0.trans";
#endif
            osg::ref_ptr<osg::PagedLOD> lod = new osg::PagedLOD;
            lod->setCenter( osg::Vec3(i*10,j*10,0.0) );
            lod->addChild( createBox(osg::Vec3(i*10,j*10,0.0),1), 200.0, FLT_MAX );
            lod->setFileName( 1, filename );
            lod->setRange( 1, 0.0, 200.0 );
            root->addChild( lod.get() );
        }
    }
    return root.release();
}

int main( int argc, char** argv )
{
    osgViewer::Viewer viewer;
    viewer.setSceneData( createPagedLOD(30,30) );
    return viewer.run();
}
