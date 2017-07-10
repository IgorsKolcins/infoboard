TARGET = CPicturesStorage.cpp CFontStorage.cpp Engine.cpp main.cpp board.cpp ./lib/TFont/TFont.cpp ./lib/TFont/ftf.cpp ./lib/Picture.cpp ./lib/json.cpp ./widgets/WgBackground.cpp ./widgets/WgClock.cpp ./widgets/WgCalendar.cpp ./widgets/WgForecast.cpp ./widgets/WgAds.cpp

TARGETFAST = Engine.cpp main.cpp board.cpp ./widgets/ScrBackground.cpp ./widgets/WgBackground.cpp ./widgets/WgCalendar.cpp ./widgets/WgClock.cpp ./widgets/WgWeather.cpp ./widgets/WgKpnference.cpp

NAME = infoboard
NAMEFAST = infofast
PREFIX = /usr/local/bin


LIBFLAGS=-L/opt/vc/lib -lEGL -lGLESv2 -ljpeg
GENERAL_FOR_VG=-I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads
PNGFLAGS=shell pkg-config libpng --cflags
PNGLIB=shell pkg-config libpng --libs

NEEDS=-lshapes -lm  -std=c++11 -lpng -fpermissive `curl-config --libs` -lstdc++ -I/usr/include/freetype2 -lfreetype

.PHONY: program clean

$(NAME): $(TARGET)
	g++ $(GENERAL_FOR_VG) $(LIBFLAGS) $(TARGET) -o $(NAME) $(NEEDS)

$(NAMEFAST): $(TARGETFAST)
	g++ $(GENERAL_FOR_VG) $(LIBFLAGS) $(TARGETFAST) -o $(NAME) $(NEEDS)

clean:
	rm -rf $(NAME) *.o && rm -rf ./widgets/*.o
