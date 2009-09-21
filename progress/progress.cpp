/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to control the progress while reading/writing files
*/

#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>
#include <osgDB/ReadFile>
#include <osgDB/Registry>
#include <osgViewer/Viewer>
#include <iostream>

template<typename Elem, typename Tr=std::char_traits<Elem> >
class ProgressingStreamBuf: public std::basic_filebuf<Elem, Tr>
{
public:
    typedef std::basic_filebuf<Elem, Tr> BaseType;
    ProgressingStreamBuf( const std::string &filename )
    : BaseType(), _count(0), _readSize(0)
    {
        if ( open(filename.c_str(), std::ios_base::in|std::ios_base::binary) )
            pubseekoff( 0, std::ios_base::beg, std::ios_base::in );
    }
    
protected:
    virtual int_type uflow()
    {
        int_type value = BaseType::uflow();
        _count++;
        _readSize += egptr() - gptr();
        if ( (_count%10)==0 ) std::cout << _readSize;
        else std::cout << ".";
        return value;
    }
    
    int _count;
    int _readSize;
};

class ProgressingReadCallback : public osgDB::Registry::ReadFileCallback
{
public:
    typedef ProgressingStreamBuf<char> ProgressingStringBuf;
    typedef osgDB::ReaderWriter::ReadResult ReadResult;
    ProgressingReadCallback() {}
    
    virtual osgDB::ReaderWriter::ReadResult readNode( const std::string& file,
                                                      const osgDB::Options* options )
    {
        std::string ext = osgDB::getLowerCaseFileExtension(file);
        osgDB::ReaderWriter::ReadResult rr;
        osgDB::ReaderWriter *rw = osgDB::Registry::instance()->getReaderWriterForExtension(ext);
        if ( rw )
        {
            std::string fileName = osgDB::findDataFile(file, options);
            if ( fileName.empty() ) return ReadResult::FILE_NOT_FOUND;
            
            ProgressingStringBuf* ps = new ProgressingStringBuf(fileName);
            if( !ps->is_open() ) return ReadResult::ERROR_IN_READING_FILE;
            
            rr = rw->readNode( std::istream(ps), options );
            delete ps;
        }
        else
            rr = osgDB::Registry::instance()->readNodeImplementation(file, options);
        return rr;
    }
};

int main( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osgDB::Registry::instance()->setReadFileCallback( new ProgressingReadCallback );
    osg::Node* model = osgDB::readNodeFiles( arguments );
    if ( !model ) model = osgDB::readNodeFile( "cow.osg" );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( model );
    return viewer.run();
}
