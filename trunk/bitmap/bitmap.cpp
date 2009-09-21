/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a bitmap in the world
*/

#include <osg/DrawPixels>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main( int argc, char** argv )
{
    osg::ref_ptr<osg::DrawPixels> bitmap1 = new osg::DrawPixels;
    bitmap1->setPosition( osg::Vec3(0.0, 0.0, 0.0) );
    bitmap1->setImage( osgDB::readImageFile("osg64.png") );
    
    osg::ref_ptr<osg::DrawPixels> bitmap2 = new osg::DrawPixels;
    bitmap2->setPosition( osg::Vec3(80.0, 0.0, 0.0) );
    bitmap2->setImage( osgDB::readImageFile("osg128.png") );
    
    osg::ref_ptr<osg::DrawPixels> bitmap3 = new osg::DrawPixels;
    bitmap3->setPosition( osg::Vec3(200.0, 0.0, 0.0) );
    bitmap3->setImage( osgDB::readImageFile("osg256.png") );
    bitmap3->setSubImageDimensions( 64, 64, 128, 128 );
    bitmap3->setUseSubImage( true );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( bitmap1.get() );
    geode->addDrawable( bitmap2.get() );
    geode->addDrawable( bitmap3.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( geode.get() );
    return viewer.run();
}
