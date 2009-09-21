/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create state set callbacks
*/

#include <osg/Fog>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class FogCallback : public osg::StateSet::Callback
{
public:
    virtual void operator()( osg::StateSet* ss, osg::NodeVisitor* nv )
    {
        if ( !ss ) return;
        
        osg::Fog* fog = dynamic_cast<osg::Fog*>( ss->getAttribute(osg::StateAttribute::FOG) );
        if ( fog )
        {
            float start = fog->getStart();
            if ( start<fog->getEnd()-5.0 ) fog->setStart( start+5.0 );
        }
    }
};

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "lz.osg" );
    
    osg::ref_ptr<osg::Fog> fog = new osg::Fog;
    fog->setMode( osg::Fog::LINEAR );
    fog->setColor( osg::Vec4(1.0, 1.0, 1.0, 1.0) );
    fog->setStart( 1.0 );
    fog->setEnd( 2000.0 );
    
    osg::StateSet* ss = model->getOrCreateStateSet();
    ss->setAttributeAndModes( fog.get() );
    ss->setUpdateCallback( new FogCallback );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( model );
    return viewer.run();
}
