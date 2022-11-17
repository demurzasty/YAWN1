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
	
	"Source/Application.cpp"
	"Source/CanvasItem.cpp"
	"Source/Clock.cpp"
	"Source/GraphicsDevice.cpp"
	"Source/GraphicsResource.cpp"
	"Source/Hash.cpp"
	"Source/IdPool.cpp"
	"Source/Image.cpp"
	"Source/Logger.cpp"
	"Source/Main.cpp"
	"Source/Memory.cpp"
	"Source/Mutex.cpp"
	"Source/Node.cpp"
	"Source/Node2D.cpp"
	"Source/Reference.cpp"
	"Source/Scene.cpp"
	"Source/Sprite.cpp"
	"Source/String.cpp"
	"Source/Texture.cpp"
	"Source/Thread.cpp"
	"Source/Vector2.cpp"
	"Source/Platform.cpp"
)
target_compile_features (YAWN PUBLIC cxx_std_17)
target_include_directories (YAWN PUBLIC "Include")
target_link_libraries (YAWN PRIVATE STB SDL2-static SDL2main)

add_subdirectory ("Example")
