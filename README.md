# rescue-princess
## Name Game : Rescue Princess
## Description : 
	*Đánh bại hết quái vật và boss trên đường đi để giải cứu công chúa*
## How to play :
 	1. Ấn chuột trái để tấn công , ấn nút lên để nhảy , nút sang phải để đi sang phải , nút sang trái để đi sang trái
 	2. Tránh va chạm với quái vật hoặc đạn của quái vật nếu không sẽ bị mất mạng
 	3. Cố gắng không để rơi xuống vực thẳm nếu không sẽ mất mạng
 	4. Ăn item hp để được thêm mạng
	5. Ăn item weapon để đổi weapon mạnh hơn
	
## How to install :
1. Tải SDL_2 , SDL_Image , SDL_mixer , SDL_font
	+ [SDL2](https://github.com/libsdl-org/SDL/releases/download/release-2.26.5/SDL2-devel-2.26.5-mingw.tar.gz)
	+ [SDL2_image](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.6.3-mingw.tar.gz)
	+ [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.6.3-mingw.tar.gz)
	+ [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.20.2.tar.gz)
2. Setting in codeblocks
	+ Project -> Build options -> Linker settings : trong mục Other linker options gắn -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
	+ Project -> Build options -> Search directories : trong mục compiler ta add những cái sau ![image](https://user-images.githubusercontent.com/112330953/230707956-d9a0dfb1-85b5-46e2-90a5-14101773f18c.png)
	+ Project -> Build options -> Search directories : trong mục linker ta add những cái sau ![image](https://user-images.githubusercontent.com/112330953/230707821-56055c9b-3f6f-4a2a-8794-e703be87741d.png)

