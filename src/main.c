#include <time.h>
#include <raylib.h>

#include "./fonts.h"

#define BASE_WIDTH		640
#define BASE_HEIGHT		360

#define WIDTH       	(BASE_WIDTH * 1.25)
#define HEIGHT      	(BASE_HEIGHT * 1.25)
#define FONT_RAW    	OpenSansRegularFont
#define FONT_LEN    	OpenSansRegularFont_len
#define FONT_SIZE   	(72 * 1.25)
#define FONT_SPACING  	(4 * 1.25)
#define FONT_COLOR  	(CLITERAL(Color){255, 255, 255, 255})
#define BG_COLOR    	(CLITERAL(Color){16, 16, 16, 255})

int main() {
	int  screenWidth = GetMonitorWidth(0), screenHeight = GetMonitorHeight(0);
	int windowPosX = (screenWidth - WIDTH) / 2, windowPosY = (screenHeight - HEIGHT) / 2;

	InitWindow(WIDTH, HEIGHT, "gClock");
	SetWindowPosition(windowPosX, windowPosY);
	SetTargetFPS(24);

	Font font = LoadFontFromMemory("ttf", FONT_RAW, FONT_LEN, FONT_SIZE, 0, 0);
	SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BG_COLOR);

		// Get Current Time and Date as text
		time_t now = time(NULL);
		struct tm* local = localtime(&now);
		char time_text[32], date_text[32];
	    strftime(time_text, sizeof(time_text), "%I:%M:%S %p", local);    // 12-hour with AM/PM
	    strftime(date_text, sizeof(date_text), "%a %Y/%m/%d", local);	 // Day of week, Year/Month/Day

		// Get Vector2 Size for Time and Date text
		Vector2 time_size = MeasureTextEx(font, time_text, FONT_SIZE, FONT_SPACING);
		Vector2 date_size = MeasureTextEx(font, date_text, FONT_SIZE, FONT_SPACING);

		// Draw Time and Date
		DrawTextEx(
			font, time_text,
			(Vector2){(int)(WIDTH / 2 - time_size.x / 2), (int)(HEIGHT / 3 - time_size.y / 3)},
			FONT_SIZE, FONT_SPACING, FONT_COLOR
		);
		DrawTextEx(
			font, date_text,
			(Vector2){(int)(WIDTH / 2 - date_size.x / 2), (int)((HEIGHT / 3 - date_size.y / 3) + date_size.y)},
			FONT_SIZE, FONT_SPACING, FONT_COLOR
		);

		EndDrawing();
	}

	UnloadFont(font);
	CloseWindow();
	return 0;
}
