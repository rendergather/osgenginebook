/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a bird's eye view
*/

#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

osg::Camera* createBirdsEye( const osg::BoundingSphere& bs )
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setClearMask( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
    
    double viewDistance = 2.0 * bs.radius();
    double znear = viewDistance - bs.radius();
    double zfar = viewDistance + bs.radius();
    float top = bs.radius();
    float right = bs.radius();
    camera->setProjectionMatrixAsOrtho( -right, right, -top, top, znear, zfar );
    
    osg::Vec3d upDirection( 0.0,1.0,0.0 );
    osg::Vec3d viewDirection( 0.0,0.0,1.0 );
    osg::Vec3d center = bs.center();
    osg::Vec3d eyePoint = center + viewDirection * viewDistance;
    camera->setViewMatrixAsLookAt( eyePoint, center, upDirection );
    
    return camera.release();
}

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "lz.osg" );
    
    osg::Camera* camera = createBirdsEye( model->getBound() );
    camera->addChild( model );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( camera );
    return viewer.run();
}
