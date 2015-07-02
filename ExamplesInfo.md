# 示例程序说明 #

本书附带的所有示例程序源代码均可以通过版本控制工具SVN获取。安装了SVN的用户可以输入下面的指令，以签出最新的代码：
> `svn checkout http://osgenginebook.googlecode.com/svn/trunk`
Windows用户也可以在[这里](http://osgenginebook.googlecode.com/files/Examples.rar)下载完整版本的WinRAR压缩包。

示例程序的运行要求使用市面上常见的PC计算机和3D显示卡，并尽量更新您的显示驱动程序到最新的版本；系统和软件方面的要求和注意事项如下所示：

  * 示例程序在这些系统平台和编译环境中测试通过：Windows XP SP3，Visual Studio 2008（VS9） SP1；以及Arch Linux 0.72，gcc 4.0.3。作者不能保证它们在其它地方中也能够完全正常地编译和运行，但是认为这些测试程序可以运行于大部分已知的系统平台和编译环境。

  * **所有的示例程序均可依赖OpenSceneGraph 2.9.5进行编译，绝大部分例子也可以在OpenSceneGraph 2.8.2下编译执行。**

  * morph例子不能工作于OpenSceneGraph 2.9.4以下的环境，使用较低OSG版本的用户可以通过额外的CMake选项BUILD\_EXAMPLE\_2\_9\_4阻止它的生成，即：
> > `# cmake -DBUILD_EXAMPLE_2_9_4=OFF`
  * gui例子和progress例子不能在Linux操作系统平台下运行。

  * OpenSceneGraph 2.9.5的下载地址为：http://www.openscenegraph.org/downloads/developer_releases/OpenSceneGraph-2.9.5.zip

  * OpenSceneGraph 2.8.2的下载地址为：http://www.openscenegraph.org/downloads/stable_releases/OpenSceneGraph-2.8.2/source/OpenSceneGraph-2.8.2.zip

  * **请使用CMake 2.6或者更高的版本编译生成所有的示例程序。**

  * CMake 2.6.4 for Windows的下载地址为：http://www.cmake.org/files/v2.6/cmake-2.6.4-win32-x86.exe

  * CMake 2.6.4 for Linux的下载地址为：http://www.cmake.org/files/v2.6/cmake-2.6.4-Linux-i386.sh

如果您在编译和运行例子程序的过程中发现问题，或者您在更多的系统平台和编译器环境中成功地运行了这些程序，欢迎您向作者提出，帮助我们改进和更新代码。



## Readme ##

You may use SVN to check out the latest examples source code:

> `svn checkout http://osgenginebook.googlecode.com/svn/trunk`
You may also download the WinRAR archive [here](http://osgenginebook.googlecode.com/files/Examples.rar).

You will need a personal computer and a 3D graphics card to run examples. The latest version of the graphics driver is also required to get best performance.

Notes and known issues:

  * The examples have already been tested on: Windows SP3 and Visual Studio 2008 (VS9) SP1, as well as Arch Linux 0.72 and gcc 4.0.3. They are also believed to work with most modern operation systems and development environments.

  * **You will need at least OpenSceneGraph 2.9.5 to build all the examples, or OpenSceneGraph 2.8.2 with limitation.**

  * The morph example is unable to work under versions lower than OpenSceneGraph 2.9.4. You will need add a definiation BUILD\_EXAMPLE\_2\_9\_4 to the cmake command line:
> > `# cmake -DBUILD_EXAMPLE_2_9_4=OFF`
  * The gui and progress examples are unable to work under Linux at present.

  * Download OpenSceneGraph 2.9.5 at: http://www.openscenegraph.org/downloads/developer_releases/OpenSceneGraph-2.9.5.zip

  * Download OpenSceneGraph 2.8.2 at: http://www.openscenegraph.org/downloads/stable_releases/OpenSceneGraph-2.8.2/source/OpenSceneGraph-2.8.2.zip

  * **You will need at least CMake 2.6 to build all the examples.**

  * Download CMake 2.6.4 for Windows at: http://www.cmake.org/files/v2.6/cmake-2.6.4-win32-x86.exe

  * Download CMake 2.6.4 for Linux at: http://www.cmake.org/files/v2.6/cmake-2.6.4-Linux-i386.sh

Any tests, suggestions and thoughts are welcomed.