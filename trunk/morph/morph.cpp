/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create morph animations
*/

#include <osg/Group>
#include <osgAnimation/MorphGeometry>
#include <osgAnimation/BasicAnimationManager>
#include <osgDB/ReadFile>
#include <osgUtil/SmoothingVisitor>
#include <osgViewer/Viewer>

osg::Geometry* createSourceGeometry()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( osg::Vec3(0.0, 5.0,-2.5) );
    vertices->push_back( osg::Vec3(0.0, 0.0,-2.5) );
    vertices->push_back( osg::Vec3(2.5, 5.0, 0.0) );
    vertices->push_back( osg::Vec3(2.5, 0.0, 0.0) );
    vertices->push_back( osg::Vec3(5.0, 5.0,-2.5) );
    vertices->push_back( osg::Vec3(5.0, 0.0,-2.5) );
    
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray( vertices.get() );
    geom->addPrimitiveSet( new osg::DrawArrays(GL_QUAD_STRIP,0,6) );
    
    osgUtil::SmoothingVisitor smv;
    smv.smooth( *geom );
    return geom.release();
}

osg::Geometry* createTargetGeometry()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( osg::Vec3(0.0, 5.0, 1.0) );
    vertices->push_back( osg::Vec3(0.0, 0.0, 1.0) );
    vertices->push_back( osg::Vec3(2.5, 5.0,-1.0) );
    vertices->push_back( osg::Vec3(2.5, 0.0,-1.0) );
    vertices->push_back( osg::Vec3(5.0, 5.0, 1.0) );
    vertices->push_back( osg::Vec3(5.0, 0.0, 1.0) );
    
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray( vertices.get() );
    geom->addPrimitiveSet( new osg::DrawArrays(GL_QUAD_STRIP,0,6) );
    
    osgUtil::SmoothingVisitor smv;
    smv.smooth( *geom );
    return geom.release();
}

void createMorphKeyframes( osgAnimation::FloatKeyframeContainer* container )
{
    container->push_back( osgAnimation::FloatKeyframe(0.0, 0.0) );
    container->push_back( osgAnimation::FloatKeyframe(2.0, 1.0) );
}

int main( int argc, char** argv )
{
    osg::ref_ptr<osgAnimation::FloatLinearChannel> channel =
        new osgAnimation::FloatLinearChannel;
    channel->setName( "0" );
    channel->setTargetName( "MorphCallback" );
    createMorphKeyframes( channel->getOrCreateSampler()->getOrCreateKeyframeContainer() );
    osg::ref_ptr<osgAnimation::Animation> anim = new osgAnimation::Animation;
    anim->setPlaymode( osgAnimation::Animation::PPONG );
    anim->addChannel( channel.get() );
    
    osg::ref_ptr<osgAnimation::BasicAnimationManager> mng =
        new osgAnimation::BasicAnimationManager;
    mng->registerAnimation( anim.get() );
    
    osg::ref_ptr<osgAnimation::MorphGeometry> morph =
        new osgAnimation::MorphGeometry( *createSourceGeometry() );
    morph->addMorphTarget( createTargetGeometry() );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( morph.get() );
    geode->setUpdateCallback( new osgAnimation::UpdateMorph("MorphCallback") );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( geode.get() );
    root->setUpdateCallback( mng );
    
    mng->playAnimation( anim.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
