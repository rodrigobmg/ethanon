/*--------------------------------------------------------------------------------------
 Ethanon Engine (C) Copyright 2008-2012 Andre Santee
 http://www.asantee.net/ethanon/

    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the
    Software without restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so, subject to the
    following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
--------------------------------------------------------------------------------------*/

#include "ETHResourceProvider.h"
#include <Platform/Platform.h>

Platform::FileLoggerPtr ETHResourceProvider::m_logger(
	new Platform::FileLogger(Platform::GetProgramDirectory() + Platform::FileLogger::GetLogPath() + GS_L("eth.log.txt")));

ETHResourceProvider::ETHResourceProvider(
		ETHGraphicResourceManagerPtr graphicResources, ETHAudioResourceManagerPtr audioResources,
		boost::shared_ptr<ETHShaderManager> shaderManager, const str_type::string& resourcePath,
		VideoPtr video, AudioPtr audio, InputPtr input)
{
	m_graphicResources = graphicResources;
	m_audioResources = audioResources;
	m_shaderManager = shaderManager;
	m_resourcePath = resourcePath;
	m_video = video;
	m_audio = audio;
	m_input = input;
}

void ETHResourceProvider::Log(const str_type::string& str, const Platform::Logger::TYPE& type)
{
	m_logger->Log(str, type);
}

ETHGlobalScaleManagerPtr& ETHResourceProvider::GetGlobalScaleManager()
{
	return m_globalScaleManager;
}

const Platform::FileLogger* ETHResourceProvider::GetLogger() const
{
	return m_logger.get();
}

ETHGraphicResourceManagerPtr ETHResourceProvider::GetGraphicResourceManager()
{
	return m_graphicResources;
}

ETHAudioResourceManagerPtr ETHResourceProvider::GetAudioResourceManager()
{
	return m_audioResources;
}

boost::shared_ptr<ETHShaderManager> ETHResourceProvider::GetShaderManager()
{
	return m_shaderManager;
}

str_type::string ETHResourceProvider::GetProgramPath()
{
	return m_programPath;
}

str_type::string ETHResourceProvider::GetResourcePath()
{
	return m_resourcePath;
}

void ETHResourceProvider::SetResourcePath(const str_type::string& path)
{
	m_resourcePath = Platform::AddLastSlash(path);
	m_video->SetBitmapFontDefaultPath(m_resourcePath + ETHDirectories::GetBitmapFontPath());
}

const VideoPtr& ETHResourceProvider::GetVideo()
{
	return m_video;
}

const AudioPtr& ETHResourceProvider::GetAudio()
{
	return m_audio;
}

const InputPtr& ETHResourceProvider::GetInput()
{
	return m_input;
}

str_type::string ETHResourceProvider::GetByteCodeSavePath()
{
	#if !defined(ANDROID) && !defined(APPLE_IOS)
		return GetResourcePath();
	#else
		return m_video->GetExternalStoragePath();
	#endif
}

str_type::string ETHResourceProvider::m_programPath = Platform::GetProgramDirectory();

ETHGraphicResourceManagerPtr ETHResourceProvider::m_graphicResources;
ETHAudioResourceManagerPtr ETHResourceProvider::m_audioResources;
boost::shared_ptr<ETHShaderManager> ETHResourceProvider::m_shaderManager;
str_type::string ETHResourceProvider::m_resourcePath;
VideoPtr ETHResourceProvider::m_video;
AudioPtr ETHResourceProvider::m_audio;
InputPtr ETHResourceProvider::m_input;
ETHGlobalScaleManagerPtr ETHResourceProvider::m_globalScaleManager(new ETHGlobalScaleManager);