/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create cameras on multi-windows
*/

#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

osg::Camera* createCamera( int x, int y, int w, int h )
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;
    
    osg::DisplaySettings* ds = osg::DisplaySettings::instance();
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();
    
    osg::ref_ptr<osg::GraphicsContext> gc =
        osg::GraphicsContext::createGraphicsContext( traits.get() );
    
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext( gc.get() );
    camera->setViewport( new osg::Viewport(0,0, traits->width, traits->height) );
    return camera.release();
}

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "cow.osg" );
    
    osgViewer::Viewer viewer;
    viewer.addSlave( createCamera(100,100,400,300), osg::Matrixd::translate( 1.0,-1.0,0.0), osg::Matrixd() );
    viewer.addSlave( createCamera(505,100,400,300), osg::Matrixd::translate(-1.0,-1.0,0.0), osg::Matrixd() );
    viewer.addSlave( createCamera(100,405,400,300), osg::Matrixd::translate( 1.0, 1.0,0.0), osg::Matrixd() );
    viewer.addSlave( createCamera(505,405,400,300), osg::Matrixd::translate(-1.0, 1.0,0.0), osg::Matrixd() );
    viewer.setSceneData( model );
    return viewer.run();
}
