/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create character animations
*/

#include <osg/ShapeDrawable>
#include <osgAnimation/Bone>
#include <osgAnimation/Skeleton>
#include <osgAnimation/BasicAnimationManager>
#include <osgViewer/Viewer>

osgAnimation::Bone* createBone( const char* name, const osg::Vec3& trans )
{
    osg::ref_ptr<osgAnimation::Bone> bone = new osgAnimation::Bone;
    bone->setBindMatrixInBoneSpace( osg::Matrix::translate(trans) );
    bone->setName( name );
    bone->setDefaultUpdateCallback();
    
    osg::ref_ptr<osg::Box> box = new osg::Box( trans*0.5, trans.length(), 0.2, 0.2 );
    osg::Quat quat;
    quat.makeRotate( osg::Vec3(1.0,0.0,0.0), trans );
    box->setRotation( quat );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( new osg::ShapeDrawable(box.get()) );
    bone->addChild( geode.get() );
    return bone.release();
}

osgAnimation::Channel* createChannel( const char* name, float rad )
{
    osg::ref_ptr<osgAnimation::QuatSphericalLinearChannel> channel
        = new osgAnimation::QuatSphericalLinearChannel;
    channel->setName( "quaternion" );
    channel->setTargetName( name );
    
    osgAnimation::QuatKeyframeContainer* keyframes =
        channel->getOrCreateSampler()->getOrCreateKeyframeContainer();
    keyframes->push_back( osgAnimation::QuatKeyframe(0.0, osg::Quat(0.0, osg::Y_AXIS)) );
    keyframes->push_back( osgAnimation::QuatKeyframe(8.0, osg::Quat(rad, osg::Y_AXIS)) );
    return channel.release();
}

int main( int argc, char** argv )
{
    osgAnimation::Bone* bone0 = createBone( "bone0", osg::Vec3(0.0,0.0,0.0) );
    osgAnimation::Bone* bone1 = createBone( "bone1", osg::Vec3(1.0,0.0,0.0) );
    osgAnimation::Bone* bone2 = createBone( "bone2", osg::Vec3(1.0,0.0,0.0) );
    
    osg::ref_ptr<osgAnimation::Skeleton> skelroot = new osgAnimation::Skeleton;
    skelroot->setDefaultUpdateCallback();
    skelroot->addChild( bone0 );
    bone0->addChild( bone1 );
    bone1->addChild( bone2 );
    
    osg::ref_ptr<osgAnimation::Animation> anim = new osgAnimation::Animation;
    anim->setPlaymode( osgAnimation::Animation::PPONG );
    anim->addChannel( createChannel("bone1", osg::PI_2) );
    anim->addChannel( createChannel("bone2", osg::PI_2) );
    
    osg::ref_ptr<osgAnimation::BasicAnimationManager> manager = new osgAnimation::BasicAnimationManager;
    manager->registerAnimation( anim.get() );
    manager->playAnimation( anim.get() );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( skelroot.get() );
    root->setUpdateCallback( manager.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
