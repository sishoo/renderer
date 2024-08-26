CC = x86_64-w64-mingw32-g++

INCLUDE = -IC:\Users\PCema\VulkanSDK\1.3.250.1\Include\ -Iinclude/

LINK = -LC:\Users\PCema\VulkanSDK\1.3.250.1\Lib\ -Llib/ -lvulkan-1 -lglfw3dll

SOURCES = source/main.cpp source/renderer/renderer.cpp

debug: source/main.cpp
	$(CC) $(SOURCES) -o main.exe -Wall $(INCLUDE) $(LINK)



release: source/main.cpp
	$(CC) $(SOURCES) -o main.exe -Wall -Ofast -march=native $(INCLUDE) $(LINK)	