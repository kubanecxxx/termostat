/**
 * @file gui_port.h
 *
 * @date 26.5.2012
 *      @author Kubanec
 */

#ifndef GUI_PORT_H_
#define GUI_PORT_H_

namespace GuiFramework
{
/**
 * @defgroup GUI_PORT
 * @{
 */

#include "st7735.hpp"

/**
 * @defgroup STM32F407_PORT
 * @{
 */

/**
 * @brief number of functional buttons
 */
#define BUTTON_COUNT 3

/**
 * @brief portovací třída
 *
 * uživatel musí dopsat metody pro práci s low level věcma
 */
class port
{
public:
	static uint32_t input_buttons(void);
	static void init(void);
	static void Erase(uint32_t start, uint32_t stop);
	static void * Write(const void * datas, uint32_t size);

	static inline void FillRGB(uint16_t color)
	{
		St7735::FillRGB(color);
	}
	static inline void PutsStringBackground(const char * data, uint16_t x,
			uint16_t y, uint16_t color, uint16_t background_color, uint8_t size)
	{
		St7735::PutsStringBackground(data, x, y, color, background_color, size);
	}
	static inline void drawLine(uint16_t x1, uint16_t y1, uint16_t x2,
			uint16_t y2, uint16_t color)
	{
		St7735::DrawLine(x1, x2, y1, y2, color);
	}
	static inline void putPixel(uint16_t x, uint16_t y, uint16_t color)
	{
		St7735::DrawPixel(x, y, color);
	}
	static inline void drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2,
			uint16_t y2, uint16_t color)
	{
		St7735::DrawRectangle(x1, y1, x2, y2, color);
	}

private:
	static uint32_t address;
};
}
/**
 * @}
 */

/**
 * @}
 */

#endif /* GUI_PORT_H_ */
