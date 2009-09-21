/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create texture animations
*/

#include <osg/ImageSequence>
#include <osg/Texture2D>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

void createTexture2D( osg::StateSet& ss, osg::Image* image )
{
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage( image );
    
    texture->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR );
    texture->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );
    texture->setWrap( osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_BORDER );
    texture->setWrap( osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_BORDER );
    ss.setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON );
}

int main( int argc, char** argv )
{
    osg::ref_ptr<osg::ImageSequence> imageSequence = new osg::ImageSequence;
    char buffer[2] = "";
    for ( int i=0; i<10; ++i )
    {
        _itoa_s( i, buffer, 2, 10 );
        std::string file = buffer;
        imageSequence->addImage( osgDB::readImageFile(file+".jpg") );
    }
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( osg::createTexturedQuadGeometry(
        osg::Vec3(0.0,0.0,0.0), osg::Vec3(1.0,0.0,0.0), osg::Vec3(0.0,0.0,1.0), 1.0, 1.0) );
    createTexture2D( *(geode->getOrCreateStateSet()), imageSequence.get() );
    
    imageSequence->setLength( 10.0 );
    imageSequence->play();
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( geode.get() );
    return viewer.run();
}
