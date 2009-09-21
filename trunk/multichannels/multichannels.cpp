/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create multi animation channels and merge them
*/

#include <osg/MatrixTransform>
#include <osgAnimation/UpdateCallback>
#include <osgAnimation/BasicAnimationManager>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

void createKeyframes1( osgAnimation::Vec3KeyframeContainer* container )
{
    container->push_back( osgAnimation::Vec3Keyframe(0.0, osg::Vec3( 0.0,0.0,0.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(10.0,osg::Vec3(10.0,0.0,-10.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(20.0,osg::Vec3( 0.0,0.0,0.0)) );
}

void createKeyframes2( osgAnimation::Vec3KeyframeContainer* container )
{
    container->push_back( osgAnimation::Vec3Keyframe(0.0, osg::Vec3(0.0,0.0,0.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(10.0,osg::Vec3(0.0,0.0,10.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(15.0,osg::Vec3(0.0,0.0,8.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(20.0,osg::Vec3(0.0,0.0,0.0)) );
}

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "glider.osg" );
    
    osg::ref_ptr<osgAnimation::Vec3LinearChannel> ch1 = new osgAnimation::Vec3LinearChannel;
    ch1->setName( "position" );
    ch1->setTargetName( "PathCallback" );
    createKeyframes1( ch1->getOrCreateSampler()->getOrCreateKeyframeContainer() );
    osg::ref_ptr<osgAnimation::Animation> anim1 = new osgAnimation::Animation;
    anim1->setPlaymode( osgAnimation::Animation::LOOP );
    anim1->addChannel( ch1.get() );
    
    osg::ref_ptr<osgAnimation::Vec3LinearChannel> ch2 = new osgAnimation::Vec3LinearChannel;
    ch2->setName( "position" );
    ch2->setTargetName( "PathCallback" );
    createKeyframes2( ch2->getOrCreateSampler()->getOrCreateKeyframeContainer() );
    osg::ref_ptr<osgAnimation::Animation> anim2 = new osgAnimation::Animation;
    anim2->setPlaymode( osgAnimation::Animation::LOOP );
    anim2->addChannel( ch2.get() );
    
    osg::ref_ptr<osg::MatrixTransform> animRoot = new osg::MatrixTransform;
    animRoot->addChild( model );
    animRoot->setDataVariance( osg::Object::DYNAMIC );
    animRoot->setUpdateCallback( new osgAnimation::UpdateTransform("PathCallback") );
    
    osg::ref_ptr<osgAnimation::BasicAnimationManager> mng =
        new osgAnimation::BasicAnimationManager;
    mng->registerAnimation( anim1.get() );
    mng->registerAnimation( anim2.get() );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( animRoot.get() );
    root->setUpdateCallback( mng.get() );
    
    mng->playAnimation( anim1.get(), 0, 0.3 );
    mng->playAnimation( anim2.get(), 0, 0.7 );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
