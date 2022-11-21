cmake_minimum_required (VERSION 3.8.2)

project (YAWN)

add_subdirectory ("ThirdParty")

add_library (YAWN STATIC 
	"Source/SDL2/ClockSDL2.cpp"
	"Source/SDL2/CommonSDL2.cpp"
	"Source/SDL2/GraphicsDeviceSDL2.cpp"
	"Source/SDL2/MutexSDL2.cpp"
	"Source/SDL2/PlatformSDL2.cpp"
	"Source/SDL2/ThreadSDL2.cpp"
	
	"Source/Win32/DirectoryMonitorWin32.cpp"
	
	"Source/Animation.cpp"
	"Source/AnimationPlayer.cpp"
	"Source/Application.cpp"
	"Source/CanvasItem.cpp"
	"Source/Clock.cpp"
	"Source/Color.cpp"
	"Source/DirectoryMonitor.cpp"
	"Source/GraphicsDevice.cpp"
	"Source/GraphicsResource.cpp"
	"Source/Hash.cpp"
	"Source/IdPool.cpp"
	"Source/Image.cpp"
	"Source/Logger.cpp"
	"Source/Main.cpp"
	"Source/Math.cpp"
	"Source/Memory.cpp"
	"Source/Mutex.cpp"
	"Source/Node.cpp"
	"Source/Node2D.cpp"
	"Source/Platform.cpp"
	"Source/Reference.cpp"
	"Source/Reflection.cpp"
	"Source/ResourceManager.cpp"
	"Source/Scene.cpp"
	"Source/Settings.cpp"
	"Source/Sprite.cpp"
	"Source/String.cpp"
	"Source/Texture.cpp"
	"Source/Thread.cpp"
	"Source/TileMap.cpp"
	"Source/TileMapData.cpp"
	"Source/Variant.cpp"
	"Source/Vector2.cpp"
)
target_compile_features (YAWN PUBLIC cxx_std_17)
target_include_directories (YAWN PUBLIC "Include")
target_link_libraries (YAWN PRIVATE STB SDL2-static SDL2main)
target_compile_definitions (YAWN PUBLIC YAWN_SDL2)

if (WIN32)
	target_compile_definitions (YAWN PRIVATE NOMINMAX _CRT_SECURE_NO_WARNINGS)
endif ()

add_subdirectory ("Example")
