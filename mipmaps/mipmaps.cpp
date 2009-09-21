/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to generate texture mipmaps
*/

#include <osg/Texture2D>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>

osg::Image* createCustomMipmap( unsigned int resolution )
{
    unsigned int totalSize = 0;
    unsigned int res = resolution;
    osg::Image::MipmapDataType mipmapData;
    for ( unsigned int i=0; res>0; res>>=1, ++i )
    {
        if ( i>0 ) mipmapData.push_back( totalSize );
        totalSize += res*res*4;
    }
    
    osg::ref_ptr<osg::Image> image = new osg::Image;
    image->setImage( resolution, resolution, 1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE,
                     new unsigned char[totalSize], osg::Image::USE_NEW_DELETE );
    image->setMipmapLevels( mipmapData );
    
    unsigned char* ptr = image->data();
    res = resolution;
    for ( unsigned int i=0; res>0; res>>=1, ++i )
    {
        for ( unsigned int s=0; s<res; ++s )
        {
            for ( unsigned int t=0; t<res; ++t )
            {
                unsigned char color = (((s&0x4)==0)^((t&0x4)==0)) * 255;
                *ptr++ = color; *ptr++ = color; *ptr++ = color;
                *ptr++ = 255;
            }
        }
    }
    return image.release();
}

osg::Image* createInternalMipmap( unsigned int resolution )
{
    unsigned int totalSize = resolution*resolution*4;
    
    osg::ref_ptr<osg::Image> image = new osg::Image;
    image->setImage( resolution, resolution, 1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE,
                     new unsigned char[totalSize], osg::Image::USE_NEW_DELETE );
    
    unsigned char* ptr = image->data();
    for ( unsigned int s=0; s<resolution; ++s )
    {
        for ( unsigned int t=0; t<resolution; ++t )
        {
            unsigned char color = (((s&0x4)==0)^((t&0x4)==0)) * 255;
            *ptr++ = color; *ptr++ = color; *ptr++ = color;
            *ptr++ = 255;
        }
    }
    return image.release();
}

void createTexture2D( osg::StateSet& ss, bool useCustomizedData )
{
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    if ( useCustomizedData ) texture->setImage( createCustomMipmap(32) );
    else texture->setImage( createInternalMipmap(32) );
    
    texture->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR );
    texture->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );
    texture->setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
    texture->setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );
    ss.setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON );
}

int main( int argc, char** argv )
{
    osg::ref_ptr<osg::Geode> quad1 = new osg::Geode;
    quad1->addDrawable( osg::createTexturedQuadGeometry(
        osg::Vec3(0.0,0.0,0.0), osg::Vec3(1.0,0.0,0.0), osg::Vec3(0.0,0.0,1.0)) );
    createTexture2D( *(quad1->getOrCreateStateSet()), true );
    
    osg::ref_ptr<osg::Geode> quad2 = new osg::Geode;
    quad2->addDrawable( osg::createTexturedQuadGeometry(
        osg::Vec3(2.0,0.0,0.0), osg::Vec3(1.0,0.0,0.0), osg::Vec3(0.0,0.0,1.0)) );
    createTexture2D( *(quad2->getOrCreateStateSet()), false );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( quad1.get() );
    root->addChild( quad2.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
