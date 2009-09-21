/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create keyframe animations
*/

#include <osg/MatrixTransform>
#include <osgAnimation/UpdateCallback>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class PlayCallback : public osg::NodeCallback
{
public:
    PlayCallback( osgAnimation::Animation* anim ) : _animation(anim) {}
    
    void operator()( osg::Node* node, osg::NodeVisitor* nv )
    {
        if ( nv && nv->getVisitorType()==osg::NodeVisitor::UPDATE_VISITOR )
        {
            osgAnimation::ChannelList& channels = _animation->getChannels();
            for ( osgAnimation::ChannelList::iterator itr=channels.begin();
                  itr!=channels.end(); ++itr )
            {
                osgAnimation::Target* target = (*itr)->getTarget();
                target->reset();
            }
            
            const osg::FrameStamp* fs = nv->getFrameStamp();
            _animation->update( fs->getSimulationTime() );
            
            for ( osgAnimation::ChannelList::iterator itr=channels.begin();
                  itr!=channels.end(); ++itr )
            {
                osgAnimation::Target* target = (*itr)->getTarget();
                target->normalize();
            }
        }
        traverse( node, nv );
    }

protected:
    osgAnimation::Animation* _animation;
};

void createPositionKeyframes( osgAnimation::Vec3KeyframeContainer* container )
{
    container->push_back( osgAnimation::Vec3Keyframe(0.0, osg::Vec3(0.0,0.0,0.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(2.0, osg::Vec3(5.0,0.0,0.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(4.0, osg::Vec3(5.0,0.0,5.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(6.0, osg::Vec3(0.0,0.0,5.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(8.0, osg::Vec3(0.0,0.0,0.0)) );
}

void createEulerKeyframes( osgAnimation::Vec3KeyframeContainer* container )
{
    container->push_back( osgAnimation::Vec3Keyframe(0.0, osg::Vec3(    0.0,0.0,    0.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(2.0, osg::Vec3(osg::PI,0.0,    0.0)) );
    container->push_back( osgAnimation::Vec3Keyframe(4.0, osg::Vec3(osg::PI,0.0,osg::PI)) );
    container->push_back( osgAnimation::Vec3Keyframe(6.0, osg::Vec3(    0.0,0.0,osg::PI)) );
    container->push_back( osgAnimation::Vec3Keyframe(8.0, osg::Vec3(    0.0,0.0,    0.0)) );
}

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "glider.osg" );
    
    osg::ref_ptr<osgAnimation::Vec3LinearChannel> ch1 = new osgAnimation::Vec3LinearChannel;
    ch1->setName( "position" );
    ch1->setTargetName( "PathCallback" );
    createPositionKeyframes( ch1->getOrCreateSampler()->getOrCreateKeyframeContainer() );
    
    osg::ref_ptr<osgAnimation::Vec3LinearChannel> ch2 = new osgAnimation::Vec3LinearChannel;
    ch2->setName( "euler" );
    ch2->setTargetName( "PathCallback" );
    createEulerKeyframes( ch2->getOrCreateSampler()->getOrCreateKeyframeContainer() );
    
    osg::ref_ptr<osgAnimation::Animation> anim = new osgAnimation::Animation;
    anim->setPlaymode( osgAnimation::Animation::LOOP );
    anim->setStartTime( 0.0 );
    anim->setWeight( 1.0 );
    anim->addChannel( ch1.get() );
    anim->addChannel( ch2.get() );
    
    osg::ref_ptr<osgAnimation::UpdateTransform> callback =
        new osgAnimation::UpdateTransform( "PathCallback" );
    callback->osgAnimation::AnimationUpdateCallback::link( anim.get() );
    
    osg::ref_ptr<osg::MatrixTransform> animRoot = new osg::MatrixTransform;
    animRoot->addChild( model );
    animRoot->setDataVariance( osg::Object::DYNAMIC );
    animRoot->setUpdateCallback( callback.get() );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( animRoot.get() );
    root->setUpdateCallback( new PlayCallback(anim.get()) );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
