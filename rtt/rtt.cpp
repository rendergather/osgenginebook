/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * An example of implementing Render-to-Texture (RTT)
*/

#include <osg/Camera>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

osg::Texture* createRttTexture( int texWidth, int texHeight )
{
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setInternalFormat( GL_RGBA );
    texture->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR );
    texture->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );
    
    texture->setTextureSize( texWidth, texHeight );
    return texture.release();
}

osg::Camera* createRttCamera( int texWidth, int texHeight, const osg::BoundingSphere& bs )
{
    osg::ref_ptr<osg::Camera> rttCamera = new osg::Camera;
    rttCamera->setClearMask( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    rttCamera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
    
    rttCamera->setViewport( 0, 0, texWidth, texHeight );
    rttCamera->setRenderOrder( osg::Camera::PRE_RENDER );
    rttCamera->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER_OBJECT );
    
    double viewDistance = 2.0 * bs.radius();
    double znear = viewDistance - bs.radius();
    double zfar = viewDistance + bs.radius();
    float top = 0.6 * znear;
    float right = 0.8 * znear;
    rttCamera->setProjectionMatrixAsFrustum( -right, right, -top, top, znear, zfar );
    
    osg::Vec3d upDirection( 0.0,0.0,1.0 );
    osg::Vec3d viewDirection( 0.0,-1.0,0.0 );
    osg::Vec3d center = bs.center();
    osg::Vec3d eyePoint = center + viewDirection * viewDistance;
    rttCamera->setViewMatrixAsLookAt( eyePoint, center, upDirection );
    
    return rttCamera.release();
}

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "axes.osg" );
    model->getOrCreateStateSet()->setMode( GL_LIGHTING,osg::StateAttribute::OFF );
    
    osg::ref_ptr<osg::Geode> quad = new osg::Geode;
    quad->addDrawable( osg::createTexturedQuadGeometry(
        osg::Vec3(0.0,0.0,0.0), osg::Vec3(1.0,0.0,0.0), osg::Vec3(0.0,0.0,1.0)) );
    
    int texWidth = 512, texHeight = 512;
    osg::Camera* rttCamera = createRttCamera( texWidth, texHeight, model->getBound() );
    osg::Texture* rttTexture = createRttTexture( texWidth, texHeight );
    
    rttCamera->addChild( model );
    rttCamera->attach( osg::Camera::COLOR_BUFFER, rttTexture );
    quad->getOrCreateStateSet()->setTextureAttributeAndModes( 0, rttTexture );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( quad.get() );
    root->addChild( rttCamera );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
