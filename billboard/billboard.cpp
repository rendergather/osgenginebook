/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a billboard forest
*/

#include <osg/Billboard>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#define RAND(min, max) ((min) + (double)rand()/(RAND_MAX+1)*((max)-(min)))

void createTrees( osg::Billboard& root )
{
    root.getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    root.getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D( osgDB::readImageFile("tree.rgba") );
    for ( unsigned int i=0; i<200; ++i )
    {
        osg::ref_ptr<osg::Drawable> tree =
            osg::createTexturedQuadGeometry( osg::Vec3(0,0,0), osg::Vec3(RAND(0.5,1.5),0,0), osg::Vec3(0,0,RAND(1.0,2.0)) );
        tree->getOrCreateStateSet()->setTextureAttributeAndModes( 0, texture.get() );
        
        root.addDrawable( tree.get(), osg::Vec3(RAND(-10,10), RAND(-10,10), 0.0) );
    }
}

int main( int argc, char** argv )
{
    osg::ref_ptr<osg::Billboard> treeGeode = new osg::Billboard;
    treeGeode->setMode( osg::Billboard::POINT_ROT_EYE );
    createTrees( *treeGeode );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( treeGeode.get() );
    return viewer.run();
}
