/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a simple file I/O plugin
*/

#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>
#include <osgDB/Registry>

class ReaderWriterSimple : public osgDB::ReaderWriter
{
public:
    ReaderWriterSimple()
    { supportsExtension( "simple", "Simple box format" ); }

    virtual const char* className() const
    { return "Simple Reader"; }

    virtual ReadResult readNode( std::istream& stream, const osgDB::ReaderWriter::Options* ) const
    {
        ReadResult rr = buildBoxes(stream);
        return rr;
    }

    virtual ReadResult readNode( const std::string& file, const osgDB::ReaderWriter::Options* options ) const
    {
        std::string ext = osgDB::getLowerCaseFileExtension( file );
        if ( !acceptsExtension(ext) ) return ReadResult::FILE_NOT_HANDLED;

        std::string fileName = osgDB::findDataFile( file, options );
        if ( fileName.empty() ) return ReadResult::FILE_NOT_FOUND;

        std::ifstream stream( fileName.c_str(), std::ios::in|std::ios::binary );
        if( !stream ) return ReadResult::ERROR_IN_READING_FILE;
        return readNode( stream, options );
    }

protected:
    osg::Geode* buildBoxes( std::istream& stream ) const
    {
        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        
        osgDB::Input fr;
        fr.attach( &stream );
        while( !fr.eof() )
        {
            if ( fr.matchSequence("%f %f %f %f") )
            {
                osg::Vec3 center;
                float width = 0.0;
                fr.readSequence( center );
                fr.readSequence( width );
                
                geode->addDrawable(
                    new osg::ShapeDrawable(new osg::Box(center, width)) );
            }
            else
                ++fr;
        }
        return geode.release();
    }
};

REGISTER_OSGPLUGIN( simple, ReaderWriterSimple )
