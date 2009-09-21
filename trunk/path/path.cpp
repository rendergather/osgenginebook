/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to quickly create animation paths
*/

#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

osg::AnimationPath* createPath()
{
    typedef osg::AnimationPath::ControlPoint ControlPoint;
    osg::Vec3 yoz(1.0, 0.0, 0.0), xoz(0.0, 1.0, 0.0), xoy(0.0, 0.0, 1.0);
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    
    path->insert( 0.0,
        ControlPoint(osg::Vec3(0.0,0.0,0.0), osg::Quat(    0.0,yoz,0.0,xoz,    0.0,xoy)) );
    path->insert( 2.0,
        ControlPoint(osg::Vec3(5.0,0.0,0.0), osg::Quat(osg::PI,yoz,0.0,xoz,    0.0,xoy)) );
    path->insert( 4.0,
        ControlPoint(osg::Vec3(5.0,0.0,5.0), osg::Quat(osg::PI,yoz,0.0,xoz,osg::PI,xoy)) );
    path->insert( 6.0,
        ControlPoint(osg::Vec3(0.0,0.0,5.0), osg::Quat(    0.0,yoz,0.0,xoz,osg::PI,xoy)) );
    path->insert( 8.0,
        ControlPoint(osg::Vec3(0.0,0.0,0.0), osg::Quat(    0.0,yoz,0.0,xoz,    0.0,xoy)) );
    return path.release();
}

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "glider.osg" );
    
    osg::AnimationPath* path = createPath();
    path->setLoopMode( osg::AnimationPath::LOOP );
    
    osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
    root->addChild( model );
    root->setUpdateCallback( new osg::AnimationPathCallback(path) );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
